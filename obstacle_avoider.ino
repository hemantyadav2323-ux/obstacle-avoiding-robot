// Obstacle Avoiding Robot - Tinkercad simulation
// 3-pin ultrasonic sensor (SIG on pin 2) + L293D driving two DC motors

const int SIG_PIN = 2;

// Left Motor Control Pins
const int MOTOR_L_F = 4;
const int MOTOR_L_B = 5;

// Right Motor Control Pins
const int MOTOR_R_F = 6;
const int MOTOR_R_B = 7;

const int STOP_DISTANCE = 25;  // cm, react when an obstacle is closer than this

void setup() {
  pinMode(MOTOR_L_F, OUTPUT);
  pinMode(MOTOR_L_B, OUTPUT);
  pinMode(MOTOR_R_F, OUTPUT);
  pinMode(MOTOR_R_B, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  long distance = readDistanceCm();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > STOP_DISTANCE) {
    // Path is clear -> drive forward
    Serial.println("State: FORWARD");
    moveMotors(HIGH, LOW, HIGH, LOW);
    delay(100);
  }
  else {
    // Obstacle ahead -> stop, back up, turn, then continue
    Serial.println("State: STOP");
    moveMotors(LOW, LOW, LOW, LOW);
    delay(1000);

    Serial.println("State: REVERSE");
    moveMotors(LOW, HIGH, LOW, HIGH);
    delay(1500);

    Serial.println("State: TURN");
    moveMotors(HIGH, LOW, LOW, HIGH);   // spin in place
    delay(1500);

    moveMotors(LOW, LOW, LOW, LOW);
    delay(500);
  }
}

// Reads the 3-pin ultrasonic sensor and returns the distance in cm
long readDistanceCm() {
  pinMode(SIG_PIN, OUTPUT);
  digitalWrite(SIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(SIG_PIN, HIGH);
  delayMicroseconds(5);
  digitalWrite(SIG_PIN, LOW);

  pinMode(SIG_PIN, INPUT);
  long duration = pulseIn(SIG_PIN, HIGH, 30000);

  if (duration == 0) {
    return 999;  // no echo -> nothing in range
  }
  return duration / 58;  // microseconds to cm
}

void moveMotors(int l1, int l2, int r1, int r2) {
  digitalWrite(MOTOR_L_F, l1);
  digitalWrite(MOTOR_L_B, l2);
  digitalWrite(MOTOR_R_F, r1);
  digitalWrite(MOTOR_R_B, r2);
}
