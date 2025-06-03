#include <DHT.h>
#include <ArduinoJson.h>
#include <Servo.h>

#define dhtpin 2
#define dhttype DHT22
#define servoPin 9

DHT dht(dhtpin, dhttype);
Servo myservo;

int ledR = 11;
int ledY = 12;
int ledG = 13;

bool modoReparo = false;

void setup() {
  Serial.begin(9600);
  dht.begin();
  myservo.attach(servoPin);

  pinMode(ledR, OUTPUT);
  pinMode(ledY, OUTPUT);
  pinMode(ledG, OUTPUT);
}

void loop() {

  if (Serial.available() > 0) {
    char comando = Serial.read();
    if (comando == '1') {
      modoReparo = true;
      Serial.println("Modo de Reparo ATIVADO.");
    } else if (comando == '0') {
      modoReparo = false;
      Serial.println("Modo de Reparo DESATIVADO.");
    }
  }

  int temp = dht.readTemperature();
  int umi = dht.readHumidity();

  StaticJsonDocument<100> json;
  json["Temperatura"] = temp;
  json["Umidade"] = umi;

  serializeJson(json, Serial);
  Serial.println();

  if (modoReparo) {
    digitalWrite(ledR, HIGH);
    digitalWrite(ledY, HIGH);
    digitalWrite(ledG, HIGH);
    myservo.write(90);
    delay(1000);
    digitalWrite(ledR, LOW);
    digitalWrite(ledY, LOW);
    digitalWrite(ledG, LOW);
    myservo.write(0);
    delay(1000);
    return;
  }

  if ((temp >= 70 && temp <= 80) || (umi >= 0 && umi <= 10)) {
    digitalWrite(ledR, HIGH);
    digitalWrite(ledY, LOW);
    digitalWrite(ledG, LOW);
    myservo.write(90);
    Serial.println("Falha Critica: Válvula aberta!");
  } else if ((temp >= 60 && temp <= 69) || (umi >= 11 && umi <= 30)) {
    digitalWrite(ledR, LOW);
    digitalWrite(ledY, HIGH);
    digitalWrite(ledG, LOW);
    myservo.write(0);
    Serial.println("Alerta: Temperatura ou Umidade fora do ideal!");
  } else {
    digitalWrite(ledR, LOW);
    digitalWrite(ledY, LOW);
    digitalWrite(ledG, HIGH);
    myservo.write(0);
  }
  delay(2000);
}