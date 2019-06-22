#include "pitches.h"
int latchPin = 8;
int clockPin = 12;
int dataPin = 11;
int buttonPin = 2;
int buttonState = 0;
int cnt = 0;
int noteDuration = 0;
int pauseBetweenNotes = 0;
int startTime = 0;
int RecordTime = 0; //上一次開始的時間
bool imgChange = false;
int tonePin = 9;
bool next_tone = true;
//----------------------------------旋律---------------------------
int melody[] = {
  NOTE_B0, NOTE_C1, NOTE_D1, NOTE_E1, NOTE_F1, NOTE_G1, NOTE_A1, NOTE_B1
};

int melody2[] = {
  NOTE_C4, NOTE_B3, 0, NOTE_G3, NOTE_A3, NOTE_G3, NOTE_G3, NOTE_C4
};

int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};
//----------------------------------變數---------------------------
//----------------------------------img---------------------------
byte colDataMatrix[8] = {
  B01111111,
  B10111111,
  B11011111,
  B11101111,
  B11110111,
  B11111011,
  B11111101,
  B11111110
};

byte rowDataMatrix[8] = { 
  B11111111,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B11111111
};

byte rowData2Matrix[8] = { 
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111
};
//-----------------------------img----------------------------
void setup() {
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  //---------------------讀取按鈕--------------------------------
  buttonState = digitalRead(buttonPin);
  if(buttonState==HIGH){
    if(imgChange==0){imgChange=1;cnt=0;}else{imgChange=0;cnt=0;}
  }
  //---------------------讀取按鈕--------------------------------
//---------------------圖片切換------------------------------
if(imgChange){
 //---------------------音樂切換------------------------------
      if(next_tone){
          noteDuration = 1000 / noteDurations[cnt];
          tone(tonePin, melody[cnt], noteDuration);
          pauseBetweenNotes = noteDuration * 1.30;
          next_tone=false;
      }
      startTime=millis();
      if(startTime-RecordTime>pauseBetweenNotes){
        cnt++;
        RecordTime=startTime;
        next_tone=true;
      }
    
      if(cnt>=8){
        cnt=0;
        imgChange=0;
      }
  //---------------------音樂切換------------------------------
    for(int i = 0; i < 8 ; i++){
      digitalWrite(latchPin,LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, colDataMatrix[i]);
      shiftOut(dataPin, clockPin, MSBFIRST, rowDataMatrix[i]);
      digitalWrite(latchPin,HIGH);
    }    
  }else{
 //---------------------音樂切換------------------------------
      if(next_tone){
          noteDuration = 1000 / noteDurations[cnt];
          tone(tonePin, melody2[cnt], noteDuration);
          pauseBetweenNotes = noteDuration * 1.30;
          next_tone=false;
      }
      startTime=millis();
      if(startTime-RecordTime>pauseBetweenNotes){
        cnt++;
        RecordTime=startTime;
        next_tone=true;
      }
    
      if(cnt>=8){
        cnt=0;
        imgChange=1;
      }
  //---------------------音樂切換------------------------------
    
    for(int i = 0; i < 8 ; i++){
      digitalWrite(latchPin,LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, colDataMatrix[i]);
      shiftOut(dataPin, clockPin, MSBFIRST, rowData2Matrix[i]);
      digitalWrite(latchPin,HIGH);
    }
  }
//---------------------圖片切換------------------------------
}
