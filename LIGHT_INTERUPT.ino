#include <LiquidCrystal.h>
#include <LowPower.h>
const byte pin = A0;
int rawValue = 0;
int minutes = 0;
int hours = 0;
int seconds = 0;
LiquidCrystal lcd(12, 11, 5, 4, 3, 6);
int state = 0;
const byte backlight = 13;
byte batterySaver;
int timer;
void setup() {
  // put your setup code here, to run once:
initializeVariables();
pinMode(2, INPUT);
pinMode(backlight, OUTPUT);
digitalWrite(backlight, HIGH);
attachInterrupt(digitalPinToInterrupt(2), interuption, FALLING);
lcd.begin(16, 2);
lcd.setCursor(0, 0);
lcd.print("STARTED");
lcd.setCursor(0, 1);
lcd.print("PRESS BUTTON");
}

void loop() {
  // put your main code here, to run repeatedly:
switch(state){
  case 0:
    initialState();
    break;
  case 1:
    reader();
    LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_ON);
    break;
  case 2:
    endScreen();
    break;
}
}
void initialState(){
  //displaying initial message from setup
}
void reader(){
  //start reader code
  rawValue = analogRead(pin);
  delay(5);
  if(rawValue >= 1010){
    timer += 1;
  }
  if(batterySaver == 0){
    lcd.noDisplay();
    digitalWrite(backlight, LOW);
  }
  else{
    batterySaver--;
    lcd.display();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Reading: ");
    lcd.print(rawValue);
    lcd.setCursor(0, 1);
    lcd.print("SunTime: ");
    lcd.print(timer);
  }         
  //end reader code
}
void endScreen(){
  //print final results
  seconds = timer;
  minutes = seconds / 60;
  hours = minutes / 60;
  seconds = timer - (minutes * 60);
  minutes = minutes - (hours * 60);
  digitalWrite(backlight, HIGH);
  lcd.display();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Final Sun Time: ");
  lcd.setCursor(0, 1);
  lcd.print(hours);
  lcd.print("hrs ");
  lcd.print(minutes);
  lcd.print("mins ");
  lcd.print(seconds);
  lcd.print("s");
  delay(1000);
}
void interuption(){
  if(state != 1){
    state = 1;
    initializeVariables();
  }
  else{
    state = 2;
  }
}
void initializeVariables(){
  timer = 0;
  batterySaver = 5;
}