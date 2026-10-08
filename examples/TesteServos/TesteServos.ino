/*
  TesteServos - TR0548_K10

  Varre o servo ligado ao conector S1 de 0 a 180 graus e volta.
  Troque o numero para testar S2 ... S8.

  Atencao: servos puxam bastante corrente. Alimente a placa com fonte
  adequada e nao dependa apenas da porta USB.
*/

#include <TR0548_K10.h>

TR0548_K10 robo;

const uint8_t SERVO = 1;  // 1 a 8

void setup() {
  Serial.begin(115200);

  if (!robo.begin()) {
    Serial.println("Placa DFR0548 nao encontrada.");
    while (true) delay(1000);
  }
}

void loop() {
  for (int angulo = 0; angulo <= 180; angulo += 5) {
    robo.servo(SERVO, angulo);
    delay(30);
  }
  for (int angulo = 180; angulo >= 0; angulo -= 5) {
    robo.servo(SERVO, angulo);
    delay(30);
  }
}
