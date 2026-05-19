#define BLYNK_TEMPLATE_ID "ISI_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Sensor LDR"
#define BLYNK_AUTH_TOKEN "ISI_AUTH_TOKEN"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "NAMA_WIFI";
char pass[] = "PASSWORD_WIFI";

#define LDR_PIN A0
#define LED_PIN D5

BlynkTimer timer;

void bacaLDR() {
  int nilaiLDR = analogRead(LDR_PIN);

  Blynk.virtualWrite(V0, nilaiLDR);

  if (nilaiLDR < 500) {
    digitalWrite(LED_PIN, HIGH);
    Blynk.virtualWrite(V1, "Gelap - LED Menyala");
  } else {
    digitalWrite(LED_PIN, LOW);
    Blynk.virtualWrite(V1, "Terang - LED Mati");
  }

  Serial.print("Nilai LDR: ");
  Serial.println(nilaiLDR);
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, bacaLDR);
}

void loop() {
  Blynk.run();
  timer.run();
}