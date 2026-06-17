const uint8_t MOIST_PIN = A1;
const uint8_t MOIST_PWR = 7;  // tie to probe V+ if resistive
const int DRY_ADC = 820;      // calibrate on your bench
const int WET_ADC = 380;

int readMoistRaw() {
  digitalWrite(MOIST_PWR, HIGH);
  delay(10);
  int v = analogRead(MOIST_PIN);
  digitalWrite(MOIST_PWR, LOW);
  return v;
}

int toPercent(int raw) {
  return constrain(map(raw, DRY_ADC, WET_ADC, 0, 100), 0, 100);
}

void setup() {
  pinMode(MOIST_PWR, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int raw = readMoistRaw();
  Serial.print(F("raw=")); Serial.print(raw);
  Serial.print(F(" pct=")); Serial.println(toPercent(raw));
  delay(1000);
}