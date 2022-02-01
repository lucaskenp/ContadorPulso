#include <Arduino.h>

volatile int long counterAB = 0;
volatile int long counterABatual = 0;

uint8_t dir = 0;
#define botao1 2
#define botao2 3

void a0()
{
  if (digitalRead(botao2) == LOW)
  {
    dir = 1;
    delay(100);
  }
  else
  {
    dir = 0;
    delay(100);
  }
  if (digitalRead(botao2) == HIGH && digitalRead(botao1) == LOW)
  {
    counterAB++;
    delay(100);
  }
  else
  {
    counterAB--;
    delay(100);
  }

  if (digitalRead(botao2) == LOW && digitalRead(botao1) == HIGH)
  {
    counterAB++;
    delay(100);
  }
  else
  {
    counterAB--;
    delay(100);
  }
}
void a1()
{

  // Determina qual o sentido de giro do encoder para o contador de voltas
  if (digitalRead(botao1) == HIGH)
  {
    dir = 1;
    delay(100);
  }
  else
  {
    dir = 0;
    delay(100);
  }
  // Incrementa ou decrementa o contador de acordo com a condição do sinal no canal A
  if (digitalRead(botao1) == LOW && digitalRead(botao2) == HIGH)
  {
    counterAB--;
    delay(100);
  }
  else
  {
    counterAB++;
    delay(100);
  }

  if (digitalRead(botao1) == HIGH && digitalRead(botao2) == LOW)
  {
    counterAB--;
    delay(100);
  }
  else
  {
    counterAB++;
    delay(100);
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(botao1, INPUT_PULLUP);
  pinMode(botao2, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(botao1), a0, CHANGE);
  attachInterrupt(digitalPinToInterrupt(botao2), a1, CHANGE);
}

void loop()
{
  Serial.print("Pulso: ");
  Serial.print(counterAB);
  Serial.print(" ----- Dir: ");
  Serial.println(dir);
  delay(500);
}