#include <Servo.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(13,12,5,4,3,2); // LCD 설정
const int buzzer = 10;            // 10번핀에 피에조 버저 연결
Servo servo;                      // 서보모터 이름 'servo'

void setup() {
    Serial.begin(9600);
    lcd.begin(16,2);          // 16X2 LCD 설정
    pinMode(buzzer,OUTPUT);   // 버저 핀을 출력으로 설정
    servo.attach(6);          // 6번 핀에 서보모터 연결
}

void loop() {
    pinMode(9,OUTPUT);   // 초음파 신호 송신
    digitalWrite(9,LOW);
    delayMicroseconds(2);
    digitalWrite(9,HIGH);
    delayMicroseconds(2);
    digitalWrite(9,LOW);
    delayMicroseconds(2);

    pinMode(9,INPUT);                // 9번핀(초음파센서)을 입력으로 설정
    double time = pulseIn(9,HIGH);   // 경과시간
    double distance = time/58;       // 거리측정, cm단위로 출력

    if(distance<=100) { // 범위 1m 이내 
        int tempValue = analogRead(A0);          // 온도센서 값을 temp에 저장
        float volt = tempValue * 5.0 / 1024.0;   // 전압 값 변환
        float temperature = volt * 100 - 50;     // 온도 값 변환
        String tempstring = String(temperature);
        lcd.setCursor(0,0);
        lcd.print("TEMPARATURE:" + tempstring);
        lcd.setCursor(0,1);
            if(temperature>=37.5) { // 37.5도 이상일 때
                lcd.print("STOP");  // LCD에 'STOP'출력|alert()호출|servo각도=90
                alert();
                door(90);
            }
            else {                  // 37.5도 이상이 아닐 때
                door(0);           // LCD에'PASS'출력|servo각도=0
                lcd.print("PASS");
            }
            delay(100);
    }
}

void door(int x) {
    servo.write(x);      // servo각도=x
    delay(1);
}

void alert() {
    tone(buzzer, 2000);  // 2000주파수와 구형파를 핀에 출력
    delay(1000);
    noTone(buzzer);      // tone()에 의해 발생한 버저 중지
}