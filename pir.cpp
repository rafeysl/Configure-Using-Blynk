#define BLYNK_TEMPLATE_ID "ISI_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Sensor PIR"
#define BLYNK_AUTH_TOKEN "ISI_AUTH_TOKEN"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "NAMA_WIFI";
char pass[] = "PASSWORD_WIFI";

#define PIR_PIN D5
#define LED_PIN D6
#define BUZZER_PIN D7

BlynkTimer timer;

void bacaPIR() {
  int gerakan = digitalRead(PIR_PIN);

  Blynk.virtualWrite(V0, gerakan);

  if (gerakan == HIGH) {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    Blynk.virtualWrite(V1, "Gerakan Terdeteksi");
  } else {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    Blynk.virtualWrite(V1, "Tidak Ada Gerakan");
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, bacaPIR);
}

void loop() {
  Blynk.run();
  timer.run();
}