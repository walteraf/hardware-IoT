#include <FS.h>
#include "SPIFFS.h"
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

int pinoLED = 22;      // Pino do LED
int pinoBotao = 21;    // Pino do botão
bool estadoLED = false; // Estado inicial do LED (inicialmente desligado)
String caminhoArquivo = "/estado_led.txt"; // Caminho do arquivo para salvar o estado do LED

// Inicialize as configurações do NTP
const char* servidorNTP = "pool.ntp.org";
const long fusoHorario_sec = 0;
const int horarioVerao_sec = 3600;
WiFiUDP udpNTP;
NTPClient clienteNTP(udpNTP, servidorNTP, fusoHorario_sec);

// Configuração para armazenar os logs
String caminhoArquivoLog = "/logs.txt";
int maximoRegistrosLog = 100;

void setup() {
  Serial.begin(115200);
  pinMode(pinoLED, OUTPUT);
  pinMode(pinoBotao, INPUT_PULLUP);
  SPIFFS.begin();
  
  // Conecte-se à rede Wi-Fi
  WiFi.begin("IMD Visitantes", "");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao Wi-Fi...");
  }
  Serial.println("Conectado ao Wi-Fi");

  // Inicialize o cliente NTP
  clienteNTP.begin();
  clienteNTP.update();
  
  // Obtenha a hora atual e escreva um log
  String horaAtual = clienteNTP.getFormattedTime();
  escreverLog("Sistema iniciado. Hora atual: " + horaAtual);
  
  // Leitura inicial do estado do LED a partir do arquivo
  lerEstadoLED();
}

void loop() {
  int estadoBotao = digitalRead(pinoBotao);

  if (estadoBotao == LOW) {
    estadoLED = !estadoLED;
    digitalWrite(pinoLED, estadoLED ? HIGH : LOW);
    salvarEstadoLED();
    //Serial.println(estadoLED);

    // Obtenha a hora atual e escreva um log quando o LED muda de estado
    String horaAtual = clienteNTP.getFormattedTime();
    String textoLog = "LED " + String(estadoLED ? "ligado" : "desligado") + " em " + horaAtual;
    escreverLog(textoLog);
    Serial.println(textoLog);

    delay(200);
  }
}

// Função para ler o estado do LED do arquivo
void lerEstadoLED() {
  File arquivo = SPIFFS.open(caminhoArquivo, "r");
  if (arquivo) {
    String estado = arquivo.readStringUntil('\n');
    arquivo.close();
    if (estado == "1") {
      estadoLED = true;
    } else {
      estadoLED = false;
    }
    digitalWrite(pinoLED, estadoLED ? HIGH : LOW);
		Serial.println(estadoLED);
  }
}

// Função para salvar o estado do LED no arquivo
void salvarEstadoLED() {
  File arquivo = SPIFFS.open(caminhoArquivo, "w");
  if (arquivo) {
    if (estadoLED) {
      arquivo.println("1");
    } else {
      arquivo.println("0");
    }
    arquivo.close();
  }
}

// Função para escrever um log no arquivo
void escreverLog(String textoLog) {
  File arquivoLog = SPIFFS.open(caminhoArquivoLog, "a");
  if (arquivoLog) {
    arquivoLog.println(textoLog);
    arquivoLog.close();
  }
}