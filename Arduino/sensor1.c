const char buzzer = 9;   // 버저 핀, 트리거 핀,에코 핀번호를 설정
const char trig = 13;
const char echo = 12;

int pulseWidth;          // 거리측정에 필요한 펄스 폭과 거리변수 설정
int distance;
int distanceOld;
int buzzerDuration;      // 버저 출력 주기 변수

void setup() {
  Serial.begin(9600);        // 시리얼 통신 설정
  pinMode(trig, OUTPUT);     // 트리거 핀은 출력, 에코 핀은 입력으로 설정
  pinMode(echo, INPUT);
  pinMode(buzzer, OUTPUT);   // 버저 핀을 출력으로 설정
  digitalWrite(trig, LOW);
}

void loop() {
  digitalWrite(trig, HIGH);  
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  pulseWidth = pulseIn(echo, HIGH);  // Echo 펄스 폭을 측정해 puleWidth 변수에 저장
  distance = pulseWidth/58;          // 거리 계산

  if(distance <= 100 || distance >= 2) {            // 감지 거리의 전체 범위 0.2 ~ 1m
    if((distance <= 100) && (distance >= 50)) {     // 0.5 ~ 1m 
      buzzerDuration = 1000;
      alert();
    }
    else if((distance < 50) && (distance >= 20)) {  // 0.2 ~ 0.5m
      buzzerDuration = 500;
      alert();
    }
    else if(distance < 20) {                        // 0.2m 이내
      buzzerDuration = 100;
      alert();
    }
    else {
      noTone(buzzer);                               // tone() 에 의해 시작된 구형파의 발생을 멈춤                     
    }
    delay(buzzerDuration);
  };
}

void alert() {
  tone(buzzer, 2000);  // 2000주파수와 구형파를 핀에 출력
  delay(100);
  noTone(buzzer);
}