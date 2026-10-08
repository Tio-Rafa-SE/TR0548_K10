/*
  ScannerI2C - TR0548_K10

  Lista os dispositivos encontrados no barramento I2C.
  A placa DFR0548 deve aparecer no endereco 0x40.
  Use este exemplo para diagnosticar problemas de conexao.
*/

#include <Wire.h>

void setup() {
  Serial.begin(115200);
  Wire.begin();
  delay(1000);
}

void loop() {
  Serial.println("Procurando dispositivos I2C...");
  uint8_t total = 0;

  for (uint8_t endereco = 1; endereco < 127; endereco++) {
    Wire.beginTransmission(endereco);
    if (Wire.endTransmission() == 0) {
      Serial.print("Encontrado: 0x");
      if (endereco < 16) Serial.print("0");
      Serial.println(endereco, HEX);
      total++;
    }
  }

  if (total == 0) Serial.println("Nenhum dispositivo encontrado.");
  Serial.println();
  delay(5000);
}
