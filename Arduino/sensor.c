const char buzzerPin = 9;
const char trigPin = 13;
const char echoPin = 12;

int pulseWidth;
int distance;
int distanceOld;

int buzzerDuration;

void setup() {
  Serial.begin(9600);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  
  digitalWrite(trigPin, LOW);
}

void loop() {
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pulseWidth = pulseIn(echoPin, HIGH);
  distance = pulseWidth/58;

  if(distance <= 100 || distance >= 2) {
    if((distance <= 100) && (distance >= 50)) {
      buzzerDuration = 100;
      buzzerOn();
    }
    else if((distance < 50) && (distance >= 20)) {
      buzzerDuration = 500;
      buzzerOn();
    }
    else if(distance < 20) {
      buzzerDuration = 100;
      buzzerOn();
    }
    else {
      noTone(buzzerPin);
    }
    delay(buzzerDuration);
  };
}

void buzzerOn() {
  tone(buzzerPin, 523);
  delay(100);
  notOne(buzzerPin);
}