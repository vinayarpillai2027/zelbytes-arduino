#include <DHT.h>

// Pin definitions
#define DHTPIN 7
#define DHTTYPE DHT22
#define LDR_PIN A1
#define SOIL_PIN A0
#define TRIG_PIN 9
#define ECHO_PIN 10

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // CSV header
  Serial.println("Temperature(C),Humidity(%),LDR,Soil,Distance(cm)");
}

void loop() {
  // Read DHT22
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Read LDR and Soil Moisture
  int ldrValue = analogRead(LDR_PIN);
  int soilValue = analogRead(SOIL_PIN);

  // Read Ultrasonic Sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.0343 / 2.0;

  // Print sensor values
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read DHT22!");
  } else {
    Serial.print(temperature);
    Serial.print(",");

    Serial.print(humidity);
    Serial.print(",");

    Serial.print(ldrValue);
    Serial.print(",");

    Serial.print(soilValue);
    Serial.print(",");

    Serial.println(distance);
  }

  delay(2000); // Wait 2 seconds before next reading
}