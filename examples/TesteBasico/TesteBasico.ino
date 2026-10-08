/*
  TesteBasico - TR0548_K10

  Move o robo em todas as direcoes, uma de cada vez.
  Usa M1 (lado esquerdo) e M2 (lado direito).

  Se o robo andar para tras quando deveria ir para frente,
  descomente as linhas inverterMotor() no setup().
*/

#include <TR0548_K10.h>

TR0548_K10 robo;

void setup() {
  Serial.begin(115200);

  if (!robo.begin()) {
    Serial.println("Placa DFR0548 nao encontrada. Confira os cabos e o endereco I2C.");
    while (true) delay(1000);
  }

  // robo.inverterMotor(1);  // descomente se o motor 1 girar ao contrario
  // robo.inverterMotor(2);  // descomente se o motor 2 girar ao contrario

  Serial.println("Placa encontrada. Iniciando teste...");
}

void loop() {
  Serial.println("Frente");
  robo.frente(200);
  delay(2000);

  Serial.println("Tras");
  robo.tras(200);
  delay(2000);

  Serial.println("Esquerda");
  robo.esquerda(200);
  delay(1000);

  Serial.println("Direita");
  robo.direita(200);
  delay(1000);

  Serial.println("Parado");
  robo.stopAll();
  delay(3000);
}
