#include <Arduino.h>
#include <HTTPClient.h>
#define RED 26
#define RED_BUTTON 2
#define GREEN 33
#define GREEN_BUTTON 0
#define YELLOW 25
#define YELLOW_BUTTON 12
int check = 0;
int check_1 = 0;
int check_2 = 0;


void click();
void click_1();
void click_2();



void setup() {
  Serial.begin(115200);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
}

int state = 0;
int state_1 = 0;
int state_2 = 0;
int touch_red;
int touch_yellow;
int touch_green;


void loop() {
  touch_red = touchRead(RED_BUTTON);
  touch_yellow = touchRead(YELLOW_BUTTON);
  //Serial.println(touchRead(YELLOW_BUTTON));
  touch_green = touchRead(GREEN_BUTTON);

  if(touch_red < 50)
  {
    click();
  }
  else{
    check =0;
  }
  if(touch_yellow < 47)
  {
    click_1();
  }
  else{
    check_1 = 0;
  }
  if(touch_green < 38)
  {
    click_2();
  }
  else{
    check_2 = 0;
  }
  delay(10);
}


void click(){
  if(check){
    return;
  }
  if (state == 0){
    digitalWrite(RED, 1);
    state = 1;
  }else{
    digitalWrite(RED, 0);
    state = 0;
  }
   check =1;
}

void click_1(){
  if(check_1){
    return;
  }
  if (state_1 == 0){
    digitalWrite(YELLOW, 1);
    state_1 = 1;
  }else{
    digitalWrite(YELLOW, 0);
    state_1 = 0;
  }
   check_1 =1;
}

void click_2(){
  if(check_2){
    return;
  }
  if (state_2 == 0){
    digitalWrite(GREEN, 1);
    state_2 = 1;
  }else{
    digitalWrite(GREEN, 0);
    state_2 = 0;
  }
   check_2 =1;
}