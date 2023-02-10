#define IN1 11
#define IN2 10
#define IN3 6
#define IN4 5

long distance = 0;
long turnDistance = 0;
bool status = true;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT); 
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return (pulseIn(echoPin, HIGH)*0.01723);
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
  while(true){
    forward();
    distance = readUltrasonicDistance(3,2);
    if (distance < 20){
      status = false;
      break;
    }
  }
  stop();
  delay(500);
  reverse();
  delay(100);
  stop();
  delay(500);
  fwRight();
  delay(550);
  turnDistance = readUltrasonicDistance(3,2);
  if (turnDistance < 10) { 
    stop();
    delay(300);
    rvRight();
    delay(550);
    stop();
    delay(500);
    fwLeft();
    delay(550);
    turnDistance = readUltrasonicDistance(3,2);
    if (turnDistance < 10) { 
      stop();
      delay(300);
      rvLeft();
      delay(550);
      stop();
      delay(500);
      turn();
      delay(500);
      stop();
      status = true;
    }
    delay(500);
    status = true;
  }
  delay(500);
  status = true;
}

void forward(){
  analogWrite (IN1, 200); //HIGH
  analogWrite (IN4, 200); //HIGH
  analogWrite (IN2, 0); 
  analogWrite (IN3, 0);
}

void reverse(){
  analogWrite (IN2, 250); //HIGH
  analogWrite (IN3, 250); //HIGH
  analogWrite (IN1, 0); 
  analogWrite (IN4, 0);
}

void fwRight(){
  analogWrite (IN1, 150); //HIGH
  analogWrite (IN3, 0); 
  analogWrite (IN2, 0);
  analogWrite (IN4, 0);
}

void fwLeft(){
  analogWrite (IN4, 150); //HIGH 
  analogWrite (IN3, 0);
  analogWrite (IN1, 0); 
  analogWrite (IN2, 0);
}

void rvRight(){
  analogWrite (IN2, 150); //HIGH
  analogWrite (IN1, 0); 
  analogWrite (IN3, 0); 
  analogWrite (IN4, 0);
}

void rvLeft(){
  analogWrite (IN3, 150); //HIGH
  analogWrite (IN1, 0); 
  analogWrite (IN2, 0);
  analogWrite (IN4, 0); 
}

void stop(){
  analogWrite (IN4, 0); 
  analogWrite (IN3, 0); 
  analogWrite (IN1, 0); 
  analogWrite (IN2, 0);
}

void turn(){
  analogWrite (IN1, 150); //HIGH
  analogWrite (IN3, 150); //HIGH
  analogWrite (IN2, 0);
  analogWrite (IN4, 0);
}
