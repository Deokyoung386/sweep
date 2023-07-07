#include <Servo.h>

Servo servo;

#define trig 6
#define echo 5
int angle = 0;
bool objectDetected = false;  // 물체 감지 여부를 저장하는 변수

void setup() {
  servo.attach(9);
  servo.write(180);  // 서보 모터 초기 각도 설정
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  long duration, distance;

  digitalWrite(trig, LOW);
  digitalWrite(echo, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = ((float)(340 * duration) / 10000) / 2;

  Serial.print("거리:");
  Serial.print(distance);
  Serial.println("cm");

  // 물체 감지 여부에 따른 서보 모터 제어
  if (!objectDetected && distance < 15) {
    // 물체를 처음으로 감지한 경우
    servo.write(130);
    delay(2000);
    servo.write(80);
    objectDetected = true;  // 물체 감지 상태 업데이트
  } else if (objectDetected && distance >= 15) {
    // 물체 감지 상태에서 물체가 사라진 경우
    servo.write(180);  // 제자리로 돌아가는 동작
    delay(2000);
    objectDetected = false;  // 물체 감지 상태 업데이트
  } //else if (objectDetected && distance < 15) {
    // 물체 감지 상태에서 물체를 다시 감지한 경우
    //servo.write(130);  // 추가 동작 수행
   // delay(2000);
    //servo.write(80);
   // delay(2000);
   else if (!objectDetected && distance < 15) {
    // 물체를 감지하지 않은 상태에서 물체가 나타난 경우
    servo.write(130);  // 두 번째 동작 수행
    delay(2000);
    servo.write(80);
    delay(2000);
    objectDetected = true;  // 물체 감지 상태 업데이트
  }
}

