#include "TR0548_K10.h"

// Frequencia do PCA9685 (Hz). Deve ser 50 para os servos funcionarem.
static const uint16_t FREQ_PWM = 50;

// Pulso dos servos (microssegundos) - mesmo intervalo da biblioteca oficial da DFRobot.
static const uint16_t SERVO_US_MIN = 600;   // 0 grau
static const uint16_t SERVO_US_MAX = 2400;  // 180 graus

TR0548_K10::TR0548_K10(TwoWire &wire, uint8_t endereco)
    : _wire(&wire), _endereco(endereco), _pwm(endereco, wire) {
    for (uint8_t i = 0; i < 4; i++) _invertido[i] = false;
}

bool TR0548_K10::begin() {
    _pwm.begin();                 // inicia o I2C e reseta o PCA9685
    _pwm.setPWMFreq(FREQ_PWM);

    // Confere se a placa responde no endereco esperado
    _wire->beginTransmission(_endereco);
    bool encontrada = (_wire->endTransmission() == 0);

    if (encontrada) stopAll();
    return encontrada;
}

void TR0548_K10::_setMotor(uint8_t canalNegativo, uint8_t canalPositivo, int velocidade) {
    velocidade = constrain(velocidade, -255, 255);
    uint16_t duty = map(abs(velocidade), 0, 255, 0, 4095);

    if (velocidade > 0) {
        _pwm.setPWM(canalNegativo, 0, 0);
        _pwm.setPWM(canalPositivo, 0, duty);
    } else if (velocidade < 0) {
        _pwm.setPWM(canalPositivo, 0, 0);
        _pwm.setPWM(canalNegativo, 0, duty);
    } else {
        _pwm.setPWM(canalNegativo, 0, 0);
        _pwm.setPWM(canalPositivo, 0, 0);
    }
}

void TR0548_K10::motor(uint8_t numero, int velocidade) {
    if (numero < 1 || numero > 4) return;
    if (_invertido[numero - 1]) velocidade = -velocidade;

    // M1 -> canais 6,7 | M2 -> 4,5 | M3 -> 2,3 | M4 -> 0,1
    uint8_t canalNegativo = (4 - numero) * 2;
    _setMotor(canalNegativo, canalNegativo + 1, velocidade);
}

void TR0548_K10::motorFrente(uint8_t numero, int velocidade) { motor(numero, abs(velocidade)); }
void TR0548_K10::motorTras(uint8_t numero, int velocidade)   { motor(numero, -abs(velocidade)); }
void TR0548_K10::motorParar(uint8_t numero)                  { motor(numero, 0); }

void TR0548_K10::inverterMotor(uint8_t numero, bool inverter) {
    if (numero < 1 || numero > 4) return;
    _invertido[numero - 1] = inverter;
}

void TR0548_K10::frente(int velocidade)   { tanque(velocidade, velocidade); }
void TR0548_K10::tras(int velocidade)     { tanque(-velocidade, -velocidade); }
void TR0548_K10::esquerda(int velocidade) { tanque(-velocidade, velocidade); }
void TR0548_K10::direita(int velocidade)  { tanque(velocidade, -velocidade); }

void TR0548_K10::tanque(int esquerdo, int direito) {
    motor(1, esquerdo);
    motor(2, direito);
}

void TR0548_K10::stopAll() {
    for (uint8_t i = 1; i <= 4; i++) motor(i, 0);
}

void TR0548_K10::servo(uint8_t numero, uint8_t angulo) {
    if (numero < 1 || numero > 8) return;
    angulo = constrain(angulo, 0, 180);

    // S1 -> canal 15 ... S8 -> canal 8
    uint8_t canal = 16 - numero;

    // Periodo de 20 ms dividido em 4096 passos
    uint32_t us = SERVO_US_MIN + ((uint32_t)(SERVO_US_MAX - SERVO_US_MIN) * angulo) / 180;
    uint16_t passos = (us * 4096UL) / 20000UL;
    _pwm.setPWM(canal, 0, passos);
}
