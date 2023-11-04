// Este código é um teste que envolve dois jogadores competindo para tocar sensores táteis em um ESP32.

int LED_PIN1 = 21;       // Pino do LED para jogador 1
int LED_PIN2 = 3;       // Pino do LED para jogador 2
int LED_PIN6 = 22;       // Pino do LED para início do jogo
#define TOUCH_PIN1 15     // Pino tátil para o Jogador 1
#define TOUCH_PIN2 12     // Pino tátil para o Jogador 2
#define TOUCH_START_PIN 13 // Pino tátil para iniciar o jogo
#define BLINK_INTERVAL 250

int ledState1 = LOW;     // Estado do LED do jogador 1
int ledState2 = LOW;     // Estado do LED do jogador 2
int startGame = LOW;     // Estado do jogo (início/desligado)
unsigned long previousMillis = 0; // Armazena o tempo anterior, usado para controlar o intervalo de piscagem
unsigned long startTime = 0;       // Tempo de início do jogo
unsigned long player1Time = 0;     // Tempo do jogador 1
unsigned long player2Time = 0;     // Tempo do jogador 2
int player1Score = 0;              // Pontuação do jogador 1
int player2Score = 0;              // Pontuação do jogador 2

void setup() {
  // Inicializa a comunicação serial com uma taxa de transmissão de 115200 baud.
  Serial.begin(115200);
  
  // Configura os pinos como saídas ou entradas conforme necessário.
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  pinMode(LED_PIN6, OUTPUT);
  pinMode(TOUCH_PIN1, INPUT);
  pinMode(TOUCH_PIN2, INPUT);
  pinMode(TOUCH_START_PIN, INPUT);
}

void loop() {
  if (startGame == LOW) {
    touchRead(TOUCH_START_PIN);
    delay(100);
    // Espera pelo toque no sensor de início do jogo
    if (touchRead(TOUCH_START_PIN) < 25) {
      Serial.println("Jogo iniciado");
      startGame = HIGH;
      for (int i=0; i<3; i++){
        digitalWrite(LED_PIN6, HIGH); // Acende o LED de início do jogo
        delay(100);
        digitalWrite(LED_PIN6, LOW); // Desliga o LED de início do jogo
        delay(100);
      }
      digitalWrite(LED_PIN6, HIGH);
      startTime = millis();
    }
  } 
  if (startGame == HIGH) {
    // Verifica o toque nos sensores dos jogadores
    touchRead(TOUCH_PIN1);
    delay(100);
    touchRead(TOUCH_PIN2);
    delay(100);
    
    if (touchRead(TOUCH_PIN1) > 0  && touchRead(TOUCH_PIN1) < 25) {
      digitalWrite(LED_PIN1, HIGH);
      player1Time = millis() - startTime;
      player1Score++;
      displayResults("Jogador 1", player1Time, player1Score);
      startGame = LOW;
      digitalWrite(LED_PIN6, LOW); // Desliga o LED de início do jogo
    } 
	if (touchRead(TOUCH_PIN2) > 0  && touchRead(TOUCH_PIN2) < 25) {
      digitalWrite(LED_PIN2, HIGH);
      player2Time = millis() - startTime;
      player2Score++;
      displayResults("Jogador 2", player2Time, player2Score);
      startGame = LOW;
      digitalWrite(LED_PIN6, LOW); // Desliga o LED de início do jogo
    }
  }
}

void displayResults(const char* playerName, unsigned long time, int score) {
  // Exibe os resultados dos jogadores no monitor serial.
  Serial.print(playerName);
  Serial.print(" tocou em ");
  Serial.print(time);
  Serial.print(" ms. Pontuação: ");
  Serial.println(score);
  delay(2000);  // Aguarda 2 segundos antes de redefinir os LEDs.
  digitalWrite(LED_PIN1, LOW); // Desliga o LED do jogador 1
  digitalWrite(LED_PIN2, LOW); // Desliga o LED do jogador 2
}