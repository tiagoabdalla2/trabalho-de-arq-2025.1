// LEDs de 3 a 8
const int led1 = 3;
const int led2 = 4;
const int led3 = 5;
const int led4 = 6;
const int led5 = 7;
const int led6 = 8;

// Buzzer
const int buzzerPin = 10;

// Sensor Ultrassônico
const int triggerPin = 12;
const int echoPin = 11;

// Frequências para o buzzer
int freqBaixa = 300;
int freqMedia = 600;
int freqAlta = 1000;

long duracao;
float distancia;

void setup() {
  Serial.begin(9600);

  // Configura pinos de LED
  for (int i = 3; i <= 8; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }

  pinMode(buzzerPin, OUTPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.println("Sistema iniciado!");
}

void loop() {
  distancia = medirDistancia();
  Serial.print("Distância: ");
  Serial.print(distancia);
  Serial.println(" cm");

  if (distancia <= 100) {
    modoCritico();
  } else if (distancia <= 200) {
    modoAlertaVisualRapido();
  } else if (distancia <= 400) {
    modoAlertaVisualModerado();
  } else {
    desligarTudo();
  }

  delay(200);
}

float medirDistancia() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  duracao = pulseIn(echoPin, HIGH);
  float d = duracao * 0.034 / 2;
  return d;
}

void desligarTudo() {
  for (int i = 3; i <= 8; i++) {
    digitalWrite(i, LOW);
  }
  noTone(buzzerPin);
}

void modoAlertaVisualModerado() {
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);

  tone(buzzerPin, freqBaixa);
  delay(300);

  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, LOW);
  digitalWrite(led4, HIGH);
  delay(300);

  noTone(buzzerPin);
}

void modoAlertaVisualRapido() {
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);

  tone(buzzerPin, freqMedia);
  delay(150);

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  delay(150);

  noTone(buzzerPin);
}

void modoCritico() {
  for (int i = 3; i <= 8; i++) {
    digitalWrite(i, HIGH);
  }

  tone(buzzerPin, freqAlta);
}
