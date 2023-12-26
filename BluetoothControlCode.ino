#include <LiquidCrystal.h>

/*LCD*/
const int pin_RS = 8; 
const int pin_EN = 9; 
const int pin_d4 = 4; 
const int pin_d5 = 5; 
const int pin_d6 = 6; 
const int pin_d7 = 7; 
const int pin_BL = 10; 
LiquidCrystal lcd( pin_RS,  pin_EN,  pin_d4,  pin_d5,  pin_d6,  pin_d7);

/*Motors*/
int IN1 = A1;
int IN2 = A2;
int IN3 = A3;
int IN4 = A4;
int ENA = 12;
int ENB = 13;

void setup()
{
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);

  /*Bluetooth Module*/
  Serial.begin(9600);

  /*Motor Speed 130 is minimum speed*/
  analogWrite(ENA, 130);
  analogWrite(ENB, 130);

  lcd.begin(16,2);
}

void loop()
{
  char c;
  c='A';
  if(Serial.available())
  {
   c = Serial.read();
   Serial.print(c);
  }
  if (c=='F')
  {
    lcd.setCursor(0,0);
    lcd.print("FRONT");
    front();
  }
  else if (c=='B')
  {
    lcd.setCursor(0,0);
    lcd.print("BACK ");
    reverse();
  }
  else if (c=='R')
  {
    lcd.setCursor(0,0);
    lcd.print("RIGHT");
    right();
  }
  else if (c=='L')
  {
    lcd.setCursor(0,0);
    lcd.print("LEFT ");
    left();
  }
  else
  {
    finish();
  }
}

/*Movements*/
/*Car stops after short delay due to minimum speed being too fast*/
void front()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(100);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void right()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(100);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void left()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(100);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void reverse()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(100);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void finish()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
