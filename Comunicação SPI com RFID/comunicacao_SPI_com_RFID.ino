//Inclui as bibliotecas do SPI e do RC522
#include <SPI.h>
#include <MFRC522.h>

//Definição dos pinos de conexão do projeto 
#define PINO_SS 9
#define PINO_RST 8

//Cria o item para configurar o módulo RC522
MFRC522 mfrc522(PINO_SS, PINO_RST);

//Definição dos pinos de saída dos LEDs e do Buzzer
int LEDred = 12;
int LEDgreen = 13;
int buzzer = 10;

// Variável para controlar tentativas inválidas de acesso do cartão
int controle = 0;

void setup() {
  Serial.begin(9600); // Inicializa a serial
  SPI.begin();// Inicializa a comunicação SPI
  mfrc522.PCD_Init(); // Inicializa o módulo MFRC522
  Serial.println("Sistema Inicializado: Aproxime o token");
  
  // Pinos de saída
  pinMode(LEDred, OUTPUT);
  pinMode(LEDgreen, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop(){
  digitalWrite(LEDred, HIGH);
  digitalWrite(LEDgreen, LOW);
  digitalWrite(buzzer, LOW);
  if (!mfrc522.PICC_IsNewCardPresent()) return;// Aguarda a aproximação do token
  if (!mfrc522.PICC_ReadCardSerial()) return; // Seleciona qual token vai ser utilizado 
  Serial.print("UID da tag:"); // Mostra UID do token na serial
  String conteudo= ""; //Cria uma variável vazia, do tipo string
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if(mfrc522.uid.uidByte[i] < 0x10){
      Serial.print(" 0");
    }
    else{
      Serial.print(" ");
    }
    Serial.print(mfrc522.uid.uidByte[i], HEX);// Printa a mensagem convertida em hexadecimal
    if(mfrc522.uid.uidByte[i] < 0x10){
      conteudo.concat(String(" 0"));
    }
    else{
      conteudo.concat(String(" "));
    }
    conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  conteudo.toUpperCase(); //Coloca todas as letras da string em maiúscula
  if (conteudo.substring(1) == "53 A2 3C 91") { //Se for o cartão certo
    digitalWrite(LEDred, LOW);
    Serial.println("Acesso Liberado!");
    digitalWrite(LEDgreen, HIGH);
    delay(5000);
  }
  else { //Se for o cartão errado
    Serial.println("Cartão inválido!");
    for (int i=0; i<3; i++){
      digitalWrite(LEDred, LOW);
      delay(500);
      digitalWrite(LEDred, HIGH);
      delay(500);
    }
    controle++; //incrementa as tentativas inválidas
  }
  if (controle == 5){
    Serial.println("SISTEMA BLOQUEADO!");
    digitalWrite(buzzer, HIGH);
    for (int i=0; i<5; i++){
      digitalWrite(LEDred, LOW);
      delay(500);
      digitalWrite(LEDred, HIGH);
      delay(500);
    }
    controle = 0;
    digitalWrite(buzzer, LOW);
  }
  delay(1000);
}