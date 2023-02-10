#define IN1 11
#define IN2 10
#define IN3 6
#define IN4 5

long leftDistance = 0; //from left sensor
long fwdDistance = 0; //from middle sensor
long rightDistance = 0; //from right sensor
bool status = true;

// leftSensor = readUltrasonicDistance(7,4);
// middleSensor = readUltrasonicDistance(3,2);
// rightSensor = readUltrasonicDistance(9,8);

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return (pulseIn(echoPin, HIGH) * 0.01723);
}

void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  status = true;
}

void loop() {
  while (true) {
    forward();
    fwdDistance = readUltrasonicDistance(3, 2);
    leftDistance = readUltrasonicDistance(7, 4);
    rightDistance = readUltrasonicDistance(9, 8);
    if (fwdDistance < 20 || leftDistance < 5 || rightDistance < 5) {
      status = false;
      break;
    }
  }
  stop();
  delay(500);
  reverse();
  delay(250);
  stop();
  delay(500);
  fwRight();
  delay(550);
  fwdDistance = readUltrasonicDistance(3, 2);
  rightDistance = readUltrasonicDistance(9, 8);
  if (fwdDistance < 15 || rightDistance < 8) {
    stop();
    delay(500);
    rvRight();
    delay(550);
    stop();
    delay(500);
    fwLeft();
    delay(550);
    fwdDistance = readUltrasonicDistance(3, 2);
    leftDistance = readUltrasonicDistance(7, 4);
    if (fwdDistance < 15 || leftDistance < 8) {
      stop();
      delay(500);
      rvLeft();
      delay(550);
      stop();
      delay(500);
      turn360();
      delay(500);
      stop();
    }
    delay(300);
  }
  delay(300);
  status = true;
}

void forward() {
  analogWrite (IN1, 175); //HIGH
  analogWrite (IN4, 175); //HIGH
  analogWrite (IN2, 0);
  analogWrite (IN3, 0);
}

void reverse() {
  analogWrite (IN2, 200); //HIGH
  analogWrite (IN3, 200); //HIGH
  analogWrite (IN1, 0);
  analogWrite (IN4, 0);
}

void stop() {
  analogWrite (IN4, 0);
  analogWrite (IN3, 0);
  analogWrite (IN1, 0);
  analogWrite (IN2, 0);
}

void fwRight() {
  analogWrite (IN1, 175); //HIGH
  analogWrite (IN3, 0);
  analogWrite (IN2, 0);
  analogWrite (IN4, 0);
}

void fwLeft() {
  analogWrite (IN4, 175); //HIGH
  analogWrite (IN3, 0);
  analogWrite (IN1, 0);
  analogWrite (IN2, 0);
}

void rvRight() {
  analogWrite (IN2, 175); //HIGH
  analogWrite (IN1, 0);
  analogWrite (IN3, 0);
  analogWrite (IN4, 0);
}

void rvLeft() {
  analogWrite (IN3, 175); //HIGH
  analogWrite (IN1, 0);
  analogWrite (IN2, 0);
  analogWrite (IN4, 0);
}

void turn360() {
  analogWrite (IN1, 175); //HIGH
  analogWrite (IN3, 175); //HIGH
  analogWrite (IN2, 0);
  analogWrite (IN4, 0);
}
