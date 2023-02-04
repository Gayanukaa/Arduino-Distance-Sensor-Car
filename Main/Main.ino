#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

long distance = 0;
long turnDistance = 0;

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
}

void forward(){
  digitalWrite (IN1, HIGH); 
  digitalWrite (IN4, HIGH); 
  digitalWrite (IN2, LOW); 
  digitalWrite (IN3, LOW);
}

void backward(){
  digitalWrite (IN2, HIGH); 
  digitalWrite (IN3, HIGH); 
  digitalWrite (IN1, LOW); 
  digitalWrite (IN4, LOW);
}

void right(){
  digitalWrite (IN1, HIGH); 
  digitalWrite (IN3, LOW); 
  digitalWrite (IN2, LOW); 
  digitalWrite (IN4, LOW);
}

void left(){
  digitalWrite (IN4, HIGH); 
  digitalWrite (IN3, LOW); 
  digitalWrite (IN1, LOW); 
  digitalWrite (IN2, LOW);
}

void stop(){
  digitalWrite (IN4, LOW); 
  digitalWrite (IN3, LOW); 
  digitalWrite (IN1, LOW); 
  digitalWrite (IN2, LOW);
}

void loop() {
  forward();
  distance = readUltrasonicDistance(3,2);
  if (distance < 150) {      // determining distance
    stop();
    delay(500);
    backward();
    delay(500);
    stop();
    delay(500);
    right();
    delay(500);
    turnDistance = readUltrasonicDistance(3,2);
    if (turnDistance < 100) { 
      stop();
      delay(500);
      left();
      delay(500);
      stop();
      delay(500);
      left();
      delay(500);
      turnDistance = readUltrasonicDistance(3,2);
      if (turnDistance < 100) { 
        stop();
        delay(500);
        left();
        delay(500);
        stop();
      }
    } 
  }
}
