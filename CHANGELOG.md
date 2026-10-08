# Histórico de versões

## 2.0.0
- Biblioteca renomeada de `DFR0548_K10` para `TR0548_K10` (arquivos, classe e include).
- Corrigido: frequência do PWM agora é 50 Hz (antes 1000 Hz, o que impedia os servos de funcionar).
- Corrigido: canais dos servos seguem a placa (S1 = canal 15 ... S8 = canal 8).
- Corrigido: `servo()` ignora números fora de 1 a 8 e limita o ângulo a 0-180.
- Corrigido: pulso dos servos de 0,6 ms a 2,4 ms (antes chegava a 2,9 ms).
- Corrigido: "frente" dos motores segue o padrão da biblioteca oficial da DFRobot.
- Novo: `begin()` retorna `true`/`false` conforme a placa responda no I2C.
- Novo: `inverterMotor()` para motores montados espelhados.
- Novo: construtor aceita outro barramento I2C e outro endereço.
- Novo: exemplo `ScannerI2C`, README completo, licença MIT completa.

## 1.1.0
- Versão inicial (`DFR0548_K10`).
