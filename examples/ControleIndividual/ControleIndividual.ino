/*
  ControleIndividual - TR0548_K10

  Liga cada um dos 4 motores separadamente, para voce descobrir
  qual conector e qual motor e em que sentido ele gira.
*/

#include <TR0548_K10.h>

TR0548_K10 robo;

void setup() {
  Serial.begin(115200);

  if (!robo.begin()) {
    Serial.println("Placa DFR0548 nao encontrada.");
    while (true) delay(1000);
  }
}

void loop() {
  for (uint8_t m = 1; m <= 4; m++) {
    Serial.print("Motor ");
    Serial.print(m);
    Serial.println(": frente");
    robo.motorFrente(m, 255);
    delay(1500);

    Serial.print("Motor ");
    Serial.print(m);
    Serial.println(": tras");
    robo.motorTras(m, 255);
    delay(1500);

    robo.motorParar(m);
    delay(500);
  }
}
