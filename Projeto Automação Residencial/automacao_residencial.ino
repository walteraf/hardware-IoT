//Bibliotecas utilizadas
#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
 
//Definição dos pinos
#define LED_conexao  23
#define LED_azul     27
#define LED_verde    26
#define LED_vermelho 33
#define LED_branco   32
 
#define WLAN_SSID       "AM"      // Nome da Rede Wifi
#define WLAN_PASS       "chocolate"     // Senha da Rede Wifi
 
/************************* Adafruit.io Configuração *********************************/
 
#define AIO_SERVER      "io.adafruit.com" //Adafruit Servidor
#define AIO_SERVERPORT  1883                  
#define AIO_USERNAME    "walteraf"      //Insira o usuario criado na adafruit io
#define AIO_KEY         "aio_qZUN354xnG7Kr9JgAbyZls0ztq7M" //Insira a chave de comunicação obtida na adafruit io
 
//Váriáveis utilizadas
 
int conectado = 1;
int conexao = 0;
 
unsigned long anterior = 0;
unsigned long intervalo = 15000;
unsigned long atual;
 
//Definição do Wifi Client
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
 
//Váriáveis criadas para comunicação com o MQTT
Adafruit_MQTT_Subscribe Light1 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/LED Azul");
Adafruit_MQTT_Subscribe Light2 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/LED Verde");    
Adafruit_MQTT_Subscribe Light3 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/LED Vermelho");
Adafruit_MQTT_Subscribe Light4 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/LED Branco");
 
//Funções
void MQTT_connect(); //Determina a conexão MQTT
void Conectar();     //Verifica a conexão o Wifi
 
void setup() {
  Serial.begin(115200);
 
  //Definição de saida e entrada de cada pino
  pinMode(LED_conexao,OUTPUT);
  pinMode(LED_azul,OUTPUT);
  pinMode(LED_verde,OUTPUT);
  pinMode(LED_vermelho,OUTPUT);
  pinMode(LED_branco, OUTPUT);
 
  //Desliga o LED de status de conexão do Wifi
  digitalWrite(LED_conexao,LOW);
   
  //Declaração de Tópicos de Leitura
  mqtt.subscribe(&Light1);
  mqtt.subscribe(&Light3);
  mqtt.subscribe(&Light2);
  mqtt.subscribe(&Light4); 
}
 
void loop() {
 
  Conectar(); // Verifica a conexão WiFi
  MQTT_connect(); // Conecta-se ao servidor MQTT
 
  // Leitura e controle dos LEDs com base nas mensagens recebidas
  Adafruit_MQTT_Subscribe *subscription;
  if((subscription = mqtt.readSubscription(100))) {
    if (subscription == &Light1) {
			// Lê a mensagem recebida para o Light1 (LED Azul)
      Serial.print(F("Got: "));
      Serial.println((char *)Light1.lastread);
      int Light1_State = atoi((char *)Light1.lastread);
      digitalWrite(LED_azul, Light1_State);
    }
    if (subscription == &Light2) {
      Serial.print(F("Got: "));
      Serial.println((char *)Light2.lastread);
      int Light2_State = atoi((char *)Light2.lastread);
      digitalWrite(LED_verde, Light2_State);
    }
    if (subscription == &Light3) {
      Serial.print(F("Got: "));
      Serial.println((char *)Light3.lastread);
      int Light3_State = atoi((char *)Light3.lastread);
      digitalWrite(LED_vermelho, Light3_State);
    }
    if (subscription == &Light4) {
      Serial.print(F("Got: "));
      Serial.println((char *)Light4.lastread);
      int Light4_State = atoi((char *)Light4.lastread);
      digitalWrite(LED_branco, Light4_State);
    }
  }
}
 
void MQTT_connect() {
  int8_t ret;
  //Conectando MQTT
  if (mqtt.connected()) {
    if(conectado){
      conectado = 0;
      Serial.println("MQTT Conectado!");
    }
    return;
  }
  Serial.print("Conectando MQTT...");
  uint8_t retries = 3;
  if((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Reconexao ao MQTT em 5 segundos...");
    mqtt.disconnect();
    delay(5000);
    conectado = 1;
    //retries--;
    if (retries == 0) {
      //retries = 3;
    }
  }
}
 
void Conectar(){
  //Verifica a conexão wifi
  if(WiFi.status() != WL_CONNECTED){
      conexao = 0; 
      //Conectando ao Wifi
      Serial.println();
      Serial.println();
      Serial.print("Conectando a rede: ");
      Serial.println(WLAN_SSID);
      //Inicializa Conexão Wifi
      WiFi.begin(WLAN_SSID, WLAN_PASS);
      while(WiFi.status() != WL_CONNECTED) {
            digitalWrite(LED_conexao,LOW);
            delay(100);
            digitalWrite(LED_conexao,HIGH);
            delay(100);
            Serial.print(".");
            conexao++;
            if(conexao == 30){
              ESP.restart();
            }
      }
      Serial.println("WiFi conectado!");
      Serial.println("Endereco de IP: ");
      Serial.println(WiFi.localIP());
      digitalWrite(LED_conexao,HIGH);
      conectado = 1;
      Serial.println();
  }
}