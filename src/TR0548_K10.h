/*!
 * @file TR0548_K10.h
 * @brief Biblioteca para a placa micro:Driver (DFR0548, DFRobot) com UNIHIKER K10 / ESP32.
 *
 * A DFR0548 usa um chip PCA9685 (I2C, endereco 0x40) para acionar 4 motores DC
 * (drivers HR8833) e 8 servos. Esta biblioteca esconde os detalhes de canais e PWM
 * e oferece comandos simples em portugues.
 *
 * Mapa de canais do PCA9685 (conforme biblioteca oficial da DFRobot):
 *   Motor M1..M4 : canais (6,7), (4,5), (2,3), (0,1)  -> (negativo, positivo)
 *   Servo S1..S8 : canais 15..8
 *
 * IMPORTANTE: o PCA9685 tem UMA frequencia para todos os canais. Aqui ela fica
 * em 50 Hz, que e o que os servos exigem. Os motores funcionam normalmente
 * a 50 Hz (o controle de velocidade e feito pelo ciclo de trabalho).
 *
 * @author Rafael Oliveira (Tio Rafa)
 * @copyright 2026 Rafael Oliveira
 * @license MIT
 */

#ifndef TR0548_K10_H
#define TR0548_K10_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define TR0548_K10_VERSAO "2.0.0"

class TR0548_K10 {
public:
    /*!
     * @param wire  Barramento I2C (padrao: Wire).
     * @param endereco Endereco I2C do PCA9685 (padrao: 0x40).
     */
    TR0548_K10(TwoWire &wire = Wire, uint8_t endereco = 0x40);

    /*!
     * Inicializa o I2C e a placa. Chame no setup().
     * @return true se a placa respondeu no barramento, false se nao foi encontrada.
     */
    bool begin();

    // ---------- Motores individuais (numero 1 a 4) ----------
    /*! Velocidade de -255 a 255. Positivo = frente, negativo = tras, 0 = parar. */
    void motor(uint8_t numero, int velocidade);
    void motorFrente(uint8_t numero, int velocidade);
    void motorTras(uint8_t numero, int velocidade);
    void motorParar(uint8_t numero);

    /*! Inverte o sentido de um motor (util quando ele foi montado "espelhado"). */
    void inverterMotor(uint8_t numero, bool inverter = true);

    // ---------- Robo diferencial (M1 = lado esquerdo, M2 = lado direito) ----------
    void frente(int velocidade);
    void tras(int velocidade);
    /*! Gira no proprio eixo para a esquerda. */
    void esquerda(int velocidade);
    /*! Gira no proprio eixo para a direita. */
    void direita(int velocidade);
    /*! Controla cada lado separadamente (-255 a 255). Permite curvas. */
    void tanque(int esquerdo, int direito);

    /*! Para todos os motores (M1 a M4). */
    void stopAll();

    // ---------- Servos (numero 1 a 8) ----------
    /*! Angulo de 0 a 180 graus. */
    void servo(uint8_t numero, uint8_t angulo);

private:
    TwoWire *_wire;
    uint8_t _endereco;
    Adafruit_PWMServoDriver _pwm;
    bool _invertido[4];

    void _setMotor(uint8_t canalNegativo, uint8_t canalPositivo, int velocidade);
};

#endif
