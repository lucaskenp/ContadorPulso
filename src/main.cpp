#include <Arduino.h>

#define pin2 34
#define pin3 35
// Variável Volatile devido ao uso em mais de uma fonte de interrupção.
// O compilado armazena na memória RAM e não em um registrador.
volatile int long counterAB = 0;
uint8_t dir = 0;

void setup()
{
  Serial.begin(115200);

  // AttachInterrupt0, digital Pin 2, Sinal A
  // Ativa interrupção em qualquer mudança do sinal
  attachInterrupt(digitalPinToInterrupt(pin2), ai0, CHANGE);

  // AttachInterrupt1, digital pin 3, Sinal B
  // Ativa interrupção em qualquer mudança do sinal
  attachInterrupt(digitalPinToInterrupt(pin3), ai1, CHANGE);
}

void loop()
{
  Serial.print("Pulsos: ");
  Serial.println(counterAB);
}

// AttachInterrupt0, digital Pin 2, Sinal A - Qualquer mudança de borda (CHANGE)
void ai0()
{

  if (digitalRead(pin3) == LOW)
  {
    dir = 1;
  }
  else
  {
    dir = 0;
  }

  // Incrementa ou decrementa o contador de acordo com a condição do sinal no canal B
  if (digitalRead(pin3) == HIGH && digitalRead(pin2) == LOW)
  {
    counterAB++;
  }
  else
  {
    counterAB--;
  }

  if (digitalRead(pin3) == LOW && digitalRead(pin2) == HIGH)
  {
    counterAB++;
  }
  else
  {
    counterAB--;
  }
}

// AttachInterrupt1, digital Pin 3, Sinal B - Qualquer mudança de borda (CHANGE)
void ai1()
{

  // Determina qual o sentido de giro do encoder para o contador de voltas
  if (digitalRead(pin2) == HIGH)
  {
    dir = 1;
  }
  else
  {
    dir = 0;
  }
  // Incrementa ou decrementa o contador de acordo com a condição do sinal no canal A
  if (digitalRead(pin2) == LOW && digitalRead(pin3) == HIGH)
  {
    counterAB--;
  }
  else
  {
    counterAB++;
  }

  if (digitalRead(pin2) == HIGH && digitalRead(pin3) == LOW)
  {
    counterAB--;
  }
  else
  {
    counterAB++;
  }
}