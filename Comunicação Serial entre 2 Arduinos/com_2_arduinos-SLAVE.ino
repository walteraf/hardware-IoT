// ESCRAVO

#include <SoftwareSerial.h>

SoftwareSerial ArduinoMaster(10, 11); // Comunicação com o Arduino Transmissor (Mestre)

#define ledPin 9
int brilhoLED = 0;

void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial com o monitor
  ArduinoMaster.begin(9600); // Inicializa a comunicação serial com o Arduino Transmissor
  pinMode(ledPin, OUTPUT); // Configura o pino do LED como saída
}

void loop() {
  if (ArduinoMaster.available()) {
    String data = ArduinoMaster.readStringUntil('\n');
    int sensorValor = data.substring(0, data.indexOf(",")).toInt();
    int estadoBotao = data.substring(data.indexOf(",") + 1).toInt();
    //Serial.println(sensorValor);

    if (sensorValor > 300) {
      Serial.println("Baixa luminosidade!");
      Serial.println(sensorValor);
    }

    if (estadoBotao == HIGH) {
      analogWrite(ledPin, 255); // Liga o LED na alta intensidade
      Serial.println("Botão pressionado");
      Serial.println(sensorValor);
    } else {
      brilhoLED = map(sensorValor, 0, 1023, 0, 255);
      analogWrite(ledPin, brilhoLED); // Define a luminosidade do LED com base no sensor
      Serial.println(sensorValor);
    }
  }
}