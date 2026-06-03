const uint8_t LED_PIN = 13;
const uint8_t BTN_PIN = 2;
const unsigned long DEBOUNCE_MS = 50;

bool ledOn = false;
int lastReading = HIGH;
int stableState = HIGH;
unsigned long lastDebounce = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  int reading = digitalRead(BTN_PIN);
  if (reading != lastReading) lastDebounce = millis();
  if ((millis() - lastDebounce) > DEBOUNCE_MS) {
    if (reading != stableState) {
      stableState = reading;
      if (stableState == LOW) {
        ledOn = !ledOn;
        digitalWrite(LED_PIN, ledOn ? HIGH : LOW);
        Serial.println(F("Toggle"));
      }
    }
  }
  lastReading = reading;
}
