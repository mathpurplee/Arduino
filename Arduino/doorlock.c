#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>

const int buzzer = 0;                   // 0번핀에 피에조 버저 연결
Servo servo;                            // 서보모터 이름 servo
int angle;                              // 서보모터 회전각도
LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);   // LCD 설정

char enter[5];
char master[5] = "1111";                // 비밀번호는 1111
byte count = 0;
                                        // 키패드 설정
const byte numRows = 4;                 // 행의 수 설정
const byte numCols = 4;                 // 열의 수 설정
char keys[numRows][numCols] = {         // 행과 열에 대해 문자를 할당
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};
byte rowPins[numRows] = {8,7,6,5};      // 연결된 핀번호
byte colPins[numCols] = {4,3,2,1};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, numRows, numCols); //행과 열에 대한 정보

void setup() {
    servo.attach(9);                    //서보모터를 9번핀에 연결
    pinMode(buzzer,OUTPUT);             // 버저핀을 출력으로 설정
    lcd.begin(16,2);                    //16X2 LCD 설정
}

void loop() {
    servo.write(0);                     // 서보모터 각도=0
    lcd.setCursor(0,0);                 // 1행 0열
    lcd.print("ENTER PASSWORD");        // 첫째 줄에 "ENTER ENTERPASSWORD" 표시

    char Key = keypad.getKey();         // getKey()함수로 누른 키패드 숫자 파악
    if(Key!=0) {                        // Key에 값이 입력된 상태라면
        enter[count] = Key;
        lcd.setCursor(count, 1);        // 1행에 계속해서 출력
        lcd.print(enter[count]);
        count++;
    }
    if(count==4) {
        lcd.clear();                    // LCD 모듈 화면의 모든 표시를 지우기
        lcd.setCursor(0,0);             // 커서를 왼쪽 위로 옮김
        if(strcmp(enter, master) == 0) {// 비밀번호가 일치할 경우, strcmp함수로 두 문자열 enter, master 비교
            lcd.print("CORRECT");
            angle = map(angle, 0, 1023, 0, 180); // 범위 0~1023에서 angle 최댓값 180
            delay(3000);
            angle = map(angle, 0, 1023, 180, 0); // 범위 0~1023에서 angle 최솟값 180, 원위치로 돌아온다.
            servo.write(angle);          // 서보모터 각도=angle
        }
        else {                          // 비밀번호가 불일치할 경우
            lcd.print("INCORRECT");
            tone(buzzer, 1000);
            delay(1000);
            noTone(buzzer);             // tone() 에 의해 시작된 구형파의 발생을 멈춤
        }
        delay(1000);
        lcd.clear();                    // LCD 모듈의 화면의 모든표시를 지우고 함수 reset() 호출
        reset();
    }
}

void reset() {                          // count=0이 될때까지 count-- (초기화 기능)
    while(count!=0) {
        enter[count--] = 0;
    }
    return;
}