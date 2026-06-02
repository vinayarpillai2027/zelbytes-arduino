// Prints reserved pins — run once, read Serial Monitor
void setup() {
  Serial.begin(9600);
  Serial.println(F("Analog pins A0-A5 map to digital 14-19"));
  Serial.println(F("Avoid pins 0/1 when using USB Serial"));
}
void loop() {}