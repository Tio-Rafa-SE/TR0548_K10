# TR0548_K10

Biblioteca Arduino para controlar a placa **micro:Driver (DFR0548)**, da DFRobot, usando a **UNIHIKER K10** (ou qualquer ESP32). Com poucos comandos em português você liga motores DC e servos, ideal para robótica educacional.

Feita por Rafael Oliveira (Tio Rafa), professor e desenvolvedor de robótica educacional no Centro Paula Souza.

## O que a placa faz

A DFR0548 tem um chip PCA9685 conversando por I2C (endereço `0x40`) e entrega:

- 4 motores DC (M1 a M4), até 1,5 A por canal
- 8 servos (S1 a S8)

Tudo isso ocupando apenas os dois fios do I2C (SDA e SCL).

## Instalação

### Pelo ZIP (funciona agora)

1. Nesta página, clique em **Code > Download ZIP**
2. Na Arduino IDE: **Sketch > Incluir Biblioteca > Adicionar biblioteca .ZIP**
3. Instale também a dependência: **Sketch > Incluir Biblioteca > Gerenciar Bibliotecas**, procure por **Adafruit PWM Servo Driver Library** e clique em Instalar
4. Selecione a placa **UNIHIKER K10** em *Ferramentas > Placa* e reinicie a IDE

### Pelo Gerenciador de Bibliotecas

Quando a biblioteca for aceita no registro oficial do Arduino, bastará procurar por **TR0548_K10**.

## Ligação

Ligue o SDA e o SCL da DFR0548 ao I2C da K10 (pinos P20/SDA e P19/SCL do conector de borda), alimente a placa de forma adequada e conecte motores e servos. Se tiver dúvida se a placa está sendo vista, rode o exemplo **ScannerI2C**: ela deve aparecer em `0x40`.

## Primeiro código

```cpp
#include <TR0548_K10.h>

TR0548_K10 robo;

void setup() {
  Serial.begin(115200);

  if (!robo.begin()) {
    Serial.println("Placa nao encontrada!");
    while (true) delay(1000);
  }

  robo.frente(200);   // velocidade de 0 a 255
  delay(2000);
  robo.stopAll();
}

void loop() {}
```

## Comandos

### Motores individuais (número de 1 a 4)

| Comando | O que faz |
|---|---|
| `motor(n, v)` | Velocidade `v` de -255 a 255 (positivo = frente, negativo = trás) |
| `motorFrente(n, v)` | Gira para frente |
| `motorTras(n, v)` | Gira para trás |
| `motorParar(n)` | Para o motor |
| `inverterMotor(n)` | Inverte o sentido do motor `n` (para motores montados espelhados) |
| `stopAll()` | Para os 4 motores |

### Robô diferencial (M1 = lado esquerdo, M2 = lado direito)

| Comando | O que faz |
|---|---|
| `frente(v)` / `tras(v)` | Anda reto |
| `esquerda(v)` / `direita(v)` | Gira no próprio eixo |
| `tanque(esq, dir)` | Velocidade de cada lado, de -255 a 255 (permite curvas) |

### Servos (número de 1 a 8)

| Comando | O que faz |
|---|---|
| `servo(n, angulo)` | Posiciona o servo de 0 a 180 graus |

### Outros

| Comando | O que faz |
|---|---|
| `begin()` | Inicia a placa. Retorna `true` se ela respondeu no I2C |
| `TR0548_K10 robo(Wire1, 0x40)` | Usa outro barramento I2C ou outro endereço |

## Mapa de canais

| Recurso | Canais do PCA9685 |
|---|---|
| Motor M1, M2, M3, M4 | (6,7), (4,5), (2,3), (0,1) |
| Servo S1 a S8 | 15 a 8 |

## Cuidados importantes

- **Uma frequência para tudo.** O PCA9685 usa a mesma frequência em todos os canais. A biblioteca fixa 50 Hz, exigência dos servos. Os motores funcionam normalmente assim, mas podem emitir um leve chiado.
- **Alimentação.** Motores e servos pedem mais corrente do que a USB entrega. Use fonte ou bateria adequada na placa.
- **Motor girando ao contrário?** Use `inverterMotor(n)` ou troque os fios do motor.

## Exemplos

Em **Arquivo > Exemplos > TR0548_K10**:

- `TesteBasico`: frente, trás, esquerda e direita
- `ControleIndividual`: testa cada motor separadamente
- `RoboDiferencial`: retas, curvas e giro no lugar
- `TesteServos`: varredura de um servo
- `ScannerI2C`: diagnóstico de conexão

## Referências

- Página oficial da placa: https://wiki.dfrobot.com/DFR0548
- Código oficial da DFRobot (MakeCode), usado como referência de canais e pulsos: https://github.com/DFRobot/pxt-motor

## Contato

- Site: https://tiorafa.tec.br
- E-mail: contato@tiorafa.tec.br
- Redes: @prof.tiorafa (YouTube, Instagram e TikTok)

## Licença

MIT. Veja o arquivo [LICENSE](LICENSE). Use, modifique e compartilhe, mantendo os créditos.
