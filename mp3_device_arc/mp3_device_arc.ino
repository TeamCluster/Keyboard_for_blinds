
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
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
  pinMode(A6, INPUT_PULLUP);
  pinMode(A7, INPUT_PULLUP);
  pinMode(A8, INPUT_PULLUP);
  pressed = 0;
  //mp3 code
  Serial.begin(9600); //9600: Normal, 115200: INPUT TEST
  mySerial.begin(9600);
  mp3_set_serial(mySerial);    //set softwareSerial for DFPlayer-mini mp3 module 
  delay(1);                     // delay 1ms to set volume
  mp3_set_volume(30);          // value 0~30
}


void loop() {
   int readValue[12] = {30, 260, 400, 490, 570, 610, 655, 690, 715, 740, 760, 780};
   uint8_t exe[9][12] = {
      {KEY_F8, KEY_F7, KEY_F6, KEY_F5, KEY_F4, KEY_F3, KEY_F2, KEY_F1, KEY_ESC, 96, 'w', 0}, //A0
      {208, 207, 206, KEY_F12, KEY_F11, KEY_F10, KEY_F9, 61, KEY_BACKSPACE, 92, KEY_UP_ARROW, 0}, //A1
      {KEY_PAGE_UP, KEY_HOME, KEY_INSERT, KEY_DELETE, KEY_END, KEY_PAGE_DOWN, KEY_DOWN_ARROW, KEY_RIGHT_CTRL, 254, KEY_RIGHT_SHIFT, 47, 46}, //A2
      {45, '0', '9', '8', '7', '6', '5', '4', '3', '2', '1', 'a'}, //A3
      {'f', 'g', 'y', 't', 'r', 'e', 'q', KEY_TAB, KEY_CAPS_LOCK, 's', 0, 0}, //A4
      {'b', 'n', 'h', 'j', 'k', 'l', 59, 39, KEY_RETURN, KEY_RIGHT_ARROW, 0, 0}, //A5
      {'c', 'x', 'z', KEY_LEFT_ALT, 'v', 32, 'm', 44, KEY_RIGHT_ALT, KEY_RIGHT_GUI, KEY_LEFT_ARROW, 0}, //A6
      {KEY_LEFT_GUI, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 'd', 0, 0, 0, 0, 0, 0, 0, 0}, //A7
      {'u', 'i', 'o', 'p', 91, 93, 0, 0, 0, 0, 0, 0} //A9
   }; 
   uint8_t pinPick[9] = {A0, A1, A2, A3, A4, A5, A6, A7, A9};
   uint8_t msc[88] = {
      0, 0, '1', '2', '3', '4', '5', '6', '7', '8',
      '9', '0', 45, 61, KEY_BACKSPACE, KEY_TAB, 'q', 'w', 'e', 'r',
      't', 'y', 'u', 'i', 'o', 'p', 91, 93, 92, KEY_CAPS_LOCK,
      'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 59,
      39, KEY_RETURN, KEY_LEFT_SHIFT, 'z', 'x', 'c', 'v', 'b', 'n', 'm',
      44, 46, 47, KEY_RIGHT_SHIFT, KEY_LEFT_CTRL, KEY_LEFT_GUI, 32, KEY_RIGHT_ALT, KEY_RIGHT_GUI, 254,
      KEY_RIGHT_CTRL, KEY_INSERT, KEY_DELETE, KEY_LEFT_ALT, KEY_HOME, KEY_END, KEY_UP_ARROW, KEY_DOWN_ARROW, KEY_PAGE_UP, KEY_PAGE_DOWN,
      KEY_RIGHT_ARROW, KEY_ESC, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8,
      KEY_F9, KEY_F10, KEY_F11, KEY_F12, 206, 207, 208, KEY_LEFT_ALT
   };
   for (i = 0; i < 9; i++) { //A0~A7, A9
      for (j = 0; j < 12; j++) { //각 저항
         if (analogRead(pinPick[i]) < readValue[j]) {
            Keyboard.press(exe[i][j]);
            pressed = 1;
            if (i == 4 && j == 8) caps_lock = (++caps_lock) % 2;
            else if (i == 6 && j == 8) han_eng = (++han_eng) % 2;
            for (k = 1; k < 88; k++) if (exe[i][j] == msc[k]) break;
            if (caps_lock + han_eng * 2 == 3) {
               if (k >= 16 && k <= 20) mp3_play(3000 + k);
               else if ((k >= 21 && k <= 25) || (k >= 30 && k <= 38) || (k >= 43 && k <= 49)) mp3_play(2000 + k);
               else if ((k >= 1 && k <= 13) || k == 39 || k == 40 || (k >= 50 && k <= 52)) mp3_play(1000 + k);
               else mp3_play(k);
            }
            else if (caps_lock + han_eng * 2 == 2) {
               if ((k >= 21 && k <= 25) || (k >= 30 && k <= 38) || (k >= 43 && k <= 49)) mp3_play(2000 + k);
               else mp3_play(k);
            }
            else if (caps_lock + han_eng * 2 == 1) {
              if ((k >= 1 && k <= 13) || k == 39 || k == 40 || (k >= 50 && k <= 52)) mp3_play(1000 + k);
              else mp3_play(k);
            }
            else if (!(caps_lock + han_eng * 2)) mp3_play(k);
            //mp3_play(k + (caps_lock + han_eng*2)*1000);
            break;
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
