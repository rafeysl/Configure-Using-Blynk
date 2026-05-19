#define BLYNK_TEMPLATE_ID "ISI_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Kombinasi Sensor"
#define BLYNK_AUTH_TOKEN "ISI_AUTH_TOKEN"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <Servo.h>

char ssid[] = "NAMA_WIFI";
char pass[] = "PASSWORD_WIFI";

#define DHTPIN D4
#define DHTTYPE DHT11
#define PIR_PIN D5
#define LED_PIN D6
#define BUZZER_PIN D7
#define SERVO_PIN D8
#define LDR_PIN A0

DHT dht(DHTPIN, DHTTYPE);
Servo servo;
BlynkTimer timer;

void bacaSemuaSensor() {
  float suhu = dht.readTemperature();
  float kelembaban = dht.readHumidity();
  int gerakan = digitalRead(PIR_PIN);
  int nilaiLDR = analogRead(LDR_PIN);

  Blynk.virtualWrite(V0, suhu);
  Blynk.virtualWrite(V1, kelembaban);
  Blynk.virtualWrite(V2, gerakan);
  Blynk.virtualWrite(V3, nilaiLDR);

  if (suhu > 30 || gerakan == HIGH || nilaiLDR < 500) {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    servo.write(90);
    Blynk.virtualWrite(V4, "Bahaya / Kondisi Aktif");
  } else {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    servo.write(0);
    Blynk.virtualWrite(V4, "Kondisi Aman");
  }

  Serial.print("Suhu: ");
  Serial.print(suhu);
  Serial.print(" | Kelembaban: ");
  Serial.print(kelembaban);
  Serial.print(" | PIR: ");
  Serial.print(gerakan);
  Serial.print(" | LDR: ");
  Serial.println(nilaiLDR);
}

void setup() {
  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  dht.begin();
  servo.attach(SERVO_PIN);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(2000L, bacaSemuaSensor);
}

void loop() {
  Blynk.run();
  timer.run();
}