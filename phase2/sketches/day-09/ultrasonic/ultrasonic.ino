// HC-SR04 Ultrasonic Sensor with Arduino Uno

const int trigPin = 9;
const int echoPin = 10;

long duration;
float distance;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Clear TRIG pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send 10 µs pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read ECHO pulse duration
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance in cm
  distance = duration * 0.0343 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(500);
}