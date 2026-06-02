// Day 1 — Board bring-up (onboard LED on pin 13 for Uno/Nano)
const int LED_PIN = 13;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  while (!Serial) { ; }  // wait for USB on some boards
  Serial.println(F("Zelbytes Arduino Foundations — Day 1"));
  Serial.println(F("Board: check Tools > Board matches hardware"));
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
  delay(500);
}