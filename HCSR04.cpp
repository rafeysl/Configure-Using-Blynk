#define BLYNK_TEMPLATE_ID "ISI_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Ultrasonic"
#define BLYNK_AUTH_TOKEN "ISI_AUTH_TOKEN"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "NAMA_WIFI";
char pass[] = "PASSWORD_WIFI";

#define TRIG_PIN D5
#define ECHO_PIN D6
#define LED_PIN D7
#define BUZZER_PIN D8

BlynkTimer timer;

void bacaJarak() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long durasi = pulseIn(ECHO_PIN, HIGH);
  float jarak = durasi * 0.034 / 2;

  Blynk.virtualWrite(V0, jarak);

  if (jarak < 10) {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }

  Serial.print("Jarak: ");
  Serial.print(jarak);
  Serial.println(" cm");
}

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, bacaJarak);
}

void loop() {
  Blynk.run();
  timer.run();
}