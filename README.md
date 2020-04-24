## 손으로 말하는 키보드
```시각장애인을 위한 키보드 By Team Cluster```<br />
2019.08.19
***
### **I. 개요**
<img src=image/0.png width="70%" height="70%"/><br />
**손으로 말하는 키보드**는 <u>시각장애인과 사회적 약자들이 쉽게 키보드를 사용</u>하여 컴퓨터 및 여러 전자 기기에 접근할 수 있게 하기 위하여 만들어졌습니다.  

이 작품은 Team Cluster에 의해 제작되었고, 제9회 4차 산업혁명 SW경진대회에 출품되어 입상하였습니다.

해당 작품의 가장 큰 특징들은 다음과 같습니다.

- Free TTS를 사용하여 <u>한국어, 영어</u>를 지원하도록 고안되었습니다.
- Fusion 360으로 Frame을 3D 모델링하여 완성도를 높였습니다.
- Arduino로 프로그래밍되었으며, 여러 장치에 연결하여 사용할 수 있어 높은 휴대성과 호환성을 가지고 있습니다.

***
### **II. 작품의 제작 목적/필요성**
<img src=image/1.png width="100%" height="100%"/><br />
보건복지부 2016년 12월 장애인 현황 통계표에 따르면, 전체 장애인 등록현황 중 ```10.3%```가 시각장애인으로 나타나며, 그 중 약 20%는 1~3급 시각장애인임.<br />
시각장애인 및 사회에서 소외되고 있는 약자들을 위한 음성지원 키보드를 개발하여, 별도의 소프트웨어 설치 없이 누구나 편하게 사용할 수 있도록 하고자 하여 제작하게 됨.<br /> <br />
| 기존의 제품들   | 손으로 말하는 키보드 (제작품) |
| ----- | ---- |
| 한/영 키 입력의 점자가 미변환  | 점자 의존 X, 음성지원 제공  |
| 음성 한/영 변환 불가  | 음성 한/영 변환 지원  |
- ‘점자자판기’, ‘Windows 내레이터’, ‘안드로이드 버전 9 Voice Assistant’를 활용해서 시각장애인들이 실생활에서 활용하고 있지만, 이렇게 현재 <u>상용화 되어있는 제품들의 한계점을 보완하여</u> 키보드를 만들어 활용성을 높임.
- 시각장애인 등의 사회적 약자가 실생활에서 쓸 수 있어 접근성이 높음.

***
### **III. 제작 과정**
1. ATmega32U4 칩 기반의 ```Arduino Leonardo``` 사용. (USB 통신 기능 내장)
2. Fusion 360을 활용한 모델링.<br /> <img src=image/2.png width="70%" height="70%"/> <br />
3. 각 아날로그 핀 (A0~A10)마다 키보드 축 여러 개 납땜. 

***
### **IV. 프로그래밍**
키보드 작동 코드: mp3_device_arc.ino
```c
//COPYRIGHT TEAM CLUSTER ALL RIGHT RESERVED.
#include <Keyboard.h>
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
#define DELAY 100

int caps_lock = 0; //0: off, 1: off
int han_eng = 0; //0: eng, 1: han
int i, j, k, pressed;
SoftwareSerial mySerial(10, 11); //RX, TX

void setup() {
  //keyboard analogread code

  ...

  //mp3 code
  Serial.begin(9600); // 9600: Normal, 115200: INPUT TEST
  mySerial.begin(9600);
  mp3_set_serial(mySerial);    //set softwareSerial for DFPlayer-mini mp3 module 
  delay(1);                     // delay 1ms to set volume
  mp3_set_volume(30);          // value 0~30
  
}


void loop() {
   int readValue[12] = {30, 260, 400, 490, 570, 610, 655, 690, 715, 740, 760, 780};
   uint8_t exe[9][12] = {
      {KEY_F8, KEY_F7, KEY_F6, KEY_F5, KEY_F4, KEY_F3, KEY_F2, KEY_F1, KEY_ESC, 96, 'w', 0}, //A0
      ...
   }; 
   uint8_t pinPick[9] = {A0, A1, A2, A3, A4, A5, A6, A7, A9};
   uint8_t msc[88] = {
      0, 0, '1', '2', '3', '4', '5', '6', '7', '8',
      '9', '0', 45, 61, KEY_BACKSPACE,
      ...
   };
   for (i = 0; i < 9; i++) { //A0~A7, A9
      for (j = 0; j < 12; j++) { //각 저항
         if (analogRead(pinPick[i]) < readValue[j]) {
            Keyboard.press(exe[i][j]);
            pressed = 1;
            ...
         }
      }
      if (pressed) break;
   }
   if (pressed) {
      Keyboard.releaseAll();
      pressed = 0;
   }
   delay(DELAY);
}
```


***
### **V. 우수성 및 기대 효과**
- 저비용으로 효율성이 좋으며, 전용 SW가 필요 없어 휴대성과 편리성이 높음.
- (프레임도) 3D 프린터를 사용하여 소비자에 따라 커스터마이징이 가능하고, 업그레이드에 용이함.
- 인체에 무해한 ```PLA``` (친환경 소재)를 사용하였음.
- 사회적 약자들의 컴퓨터 접근성이 높아질 것으로 기대됨.
- 향후 소형보드 베이스로 회로를 구성한 ```'소형 키보드'```를 기획 중.


***
### **VI. 덧붙여서**
업로드된 파일들은 키보드 제작 및 아두이노 코딩, 프로그래밍에 사용된 SW 파일들입니다.

본 파일들의 저작권은 ```Team Cluster```에 귀속되며 <u>어떠한 산업적 목적으로도 2차적으로 재가공/사용될 수 없음</u>을 밝힙니다.

***
Copyright 2019. <u>Team Cluster</u> All Rights Reserved.