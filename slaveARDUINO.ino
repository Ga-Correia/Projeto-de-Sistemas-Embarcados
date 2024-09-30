/*
Gabriel Correia Granja  RA: 148521
João Vitor Terra    RA: 148118
Matheus Ossis de Lima  RA:148677

Trabalho Final de Sistemas Embarcados 2024/1 semestre
*/

// SLAVE
#include <Wire.h>
#include <LiquidCrystal.h> 
LiquidCrystal lcd(13, 12, 10, 9, 8, 7); 

const int led[] = {2, 3, 4, 5, 6};
//const int myadrss = 2;
int flag = 0;
int controle_temp = 0;

int buttonState = 0;
byte pwmValue = 0;

const int sensor_temp = A0;   //para temperatura
float temperatura = 0;
int temp_bruta = 0;

void setup()
{
  lcd.begin(16, 2); 
  Wire.begin(0x2C);
  Serial.begin(9600);
  Wire.setClock(80000);
  Wire.onReceive(receiveEvent);
  for(int x = 0; x < 5 ; x++){
    pinMode(led[x], OUTPUT);
  }
  lcd.print("DESLIGADO");
  //analogReference(INTERNAL1V1);   //para temperatura
    
}

void loop(){
  Serial.println(buttonState);
  Serial.println(pwmValue);
  if(pwmValue == 0){
    digitalWrite(led[0], LOW);
    digitalWrite(led[1], LOW);
    digitalWrite(led[2], LOW);
    digitalWrite(led[3], LOW);
    digitalWrite(led[4], LOW);

  }
  if(pwmValue>0 && pwmValue<=51){
    digitalWrite(led[4], LOW);
    digitalWrite(led[3], LOW);
    digitalWrite(led[2], LOW);
    digitalWrite(led[1], LOW);
    digitalWrite(led[0], HIGH);
  }
  if(pwmValue>51 && pwmValue<=102){
    digitalWrite(led[4], LOW);
    digitalWrite(led[3], LOW);
    digitalWrite(led[2], LOW);
    digitalWrite(led[0], HIGH);
    digitalWrite(led[1], HIGH);
  }
  if(pwmValue>102 && pwmValue<=153){
    digitalWrite(led[4], LOW);
    digitalWrite(led[3], LOW);
    digitalWrite(led[0], HIGH);
    digitalWrite(led[1], HIGH);
    digitalWrite(led[2], HIGH);
  }
  if(pwmValue>153 && pwmValue<=204){
    digitalWrite(led[4], LOW);
    digitalWrite(led[0], HIGH);
    digitalWrite(led[1], HIGH);
    digitalWrite(led[2], HIGH);
    digitalWrite(led[3], HIGH);
  }
  if(pwmValue>204 && pwmValue<=255){
    digitalWrite(led[0], HIGH);
    digitalWrite(led[1], HIGH);
    digitalWrite(led[2], HIGH);
    digitalWrite(led[3], HIGH);
    digitalWrite(led[4], HIGH);
  }
  
  
  if (buttonState == 1 && flag==0) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("LIGADO");   // Turn on the LED
    flag = 1;
    controle_temp = 1;
  }else if (buttonState == 0 && flag==1){
    lcd.clear();
    lcd.setCursor(0,0); 
    lcd.print("DESLIGADO");   // Turn off the LED
    flag = 0;
    controle_temp = 0;
  }
  if (controle_temp ==1){
    lcd.setCursor(0,1);
    temp_bruta = analogRead(sensor_temp);
    //temperatura = temp_bruta * 0.1075268817204301; 
    temperatura = temp_bruta * 0.48875855;
    lcd.print("Temp: ");
    lcd.print(temperatura,2);
    lcd.print(" C");
  }

}

void receiveEvent(int bytes)
{
/*  if (bytes == 2) {
    buttonState = Wire.read();  // Read first byte (pushbutton state)
    pwmValue = Wire.read();     // Read second byte (PWM value)
  }*/
  buttonState = Wire.read();
  pwmValue = Wire.read();
}
