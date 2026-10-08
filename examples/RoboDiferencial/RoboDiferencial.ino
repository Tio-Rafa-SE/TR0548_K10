/*
  RoboDiferencial - TR0548_K10

  Faz curvas controlando a velocidade de cada lado com tanque(esquerdo, direito).
    - lados iguais       -> reta
    - um lado mais lento -> curva
    - lados opostos      -> gira no lugar
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
  Serial.println("Reta");
  robo.tanque(200, 200);
  delay(2000);

  Serial.println("Curva suave para a direita");
  robo.tanque(220, 120);
  delay(2000);

  Serial.println("Curva suave para a esquerda");
  robo.tanque(120, 220);
  delay(2000);

  Serial.println("Gira no lugar");
  robo.tanque(180, -180);
  delay(1500);

  robo.stopAll();
  delay(3000);
}
