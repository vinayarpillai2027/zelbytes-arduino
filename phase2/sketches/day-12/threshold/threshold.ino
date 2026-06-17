#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22

#define SOIL_PIN A0
#define RELAY_PIN 8
#define LED_PIN 13

DHT dht(DHTPIN, DHTTYPE);

// Calibrate these values according to your sensor
const int SOIL_DRY = 600;  // Start irrigation
const int SOIL_WET = 400;  // Stop irrigation

enum State {
  IDLE,
  IRRIGATING,
  COOLDOWN,
  FAULT
};

State currentState = IDLE;

int dhtFailCount = 0;
unsigned long cooldownStart = 0;
const unsigned long COOLDOWN_TIME = 5000; // 5 seconds

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, LOW);  // Change if relay is active LOW
  digitalWrite(LED_PIN, LOW);

  Serial.println("Threshold Logic & State Machine Started");
}

void loop() {

  // Read sensors
  int soilValue = analogRead(SOIL_PIN);
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check DHT22 failures
  if (isnan(humidity) || isnan(temperature)) {
    dhtFailCount++;

    if (dhtFailCount >= 3) {
      currentState = FAULT;
    }
  } else {
    dhtFailCount = 0;
  }

  switch (currentState) {

    case IDLE:

      digitalWrite(RELAY_PIN, LOW);
      digitalWrite(LED_PIN, LOW);

      Serial.println("State: IDLE");

      if (soilValue > SOIL_DRY) {
        Serial.println("Soil Status: DRY");
        currentState = IRRIGATING;
      } else {
        Serial.println("Soil Status: WET");
      }

      break;


    case IRRIGATING:

      digitalWrite(RELAY_PIN, HIGH); // Use LOW if relay is active LOW
      digitalWrite(LED_PIN, HIGH);

      Serial.println("State: IRRIGATING");
      Serial.println("Valve ON");
      Serial.println("LED ON");

      if (soilValue < SOIL_WET) {
        currentState = COOLDOWN;
        cooldownStart = millis();
      }

      break;


    case COOLDOWN:

      digitalWrite(RELAY_PIN, LOW);
      digitalWrite(LED_PIN, LOW);

      Serial.println("State: COOLDOWN");

      if (millis() - cooldownStart >= COOLDOWN_TIME) {
        currentState = IDLE;
      }

      break;


    case FAULT:

      digitalWrite(RELAY_PIN, LOW);
      digitalWrite(LED_PIN, LOW);

      Serial.println("State: FAULT");
      Serial.println("DHT22 failed 3 consecutive times!");
      break;
  }

  // Print sensor values
  Serial.print("Soil Value: ");
  Serial.print(soilValue);

  if (soilValue > SOIL_DRY)
    Serial.print(" (DRY)");
  else if (soilValue < SOIL_WET)
    Serial.print(" (WET)");

  Serial.print(" | Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C");

  Serial.print(" | Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  delay(1000);
}