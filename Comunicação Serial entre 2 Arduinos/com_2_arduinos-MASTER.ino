// MESTRE

#include <SoftwareSerial.h>

SoftwareSerial ArduinoSlave(10, 11); // Comunicação com o Arduino Receptor (Escravo)

int sensorPin = A0;  // Pino do sensor de luminosidade (LDR)
int botaoPin = 2;   // Pino do botão
int sensorValor = 0; // Valor do sensor de luminosidade

void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial com o monitor
  ArduinoSlave.begin(9600); // Inicializa a comunicação serial com o Arduino Receptor (Escravo)
  pinMode(botaoPin, INPUT_PULLUP); // Configura o pino do botão como entrada com pull-up
}

void loop() {
  sensorValor = analogRead(sensorPin); // Lê o valor do sensor de luminosidade
  int estadoBotao = digitalRead(botaoPin); // Lê o estado do botão

  // Envia dados para o Arduino Receptor
  ArduinoSlave.print(sensorValor);
  ArduinoSlave.print(","); //EXPLICAR MELHOR ISSO
  ArduinoSlave.println(estadoBotao);

  delay(1000); // Aguarda 1 segundo antes de enviar novamente
}