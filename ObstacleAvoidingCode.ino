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

/*Ultrasonic sensor*/
int echoPin=2;
int trigPin=3;
long duration;
int distance;

void setup()
{
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(trigPin,OUTPUT);

  /*Motor Speed 130 is minimum speed*/
  analogWrite(ENA, 130);
  analogWrite(ENB, 130);

  /*Start Up sequence*/
  lcd.begin(16,2);
  lcd.print("Press 'SELECT'");
  lcd.setCursor(0,1);
  lcd.print("to start.");
}

void loop()
{
  int s = 16;
  int x;
  x= analogRead(0);
  if (x<800&&x>=600)
  {
    delay(2000);
    s=17;
    lcd.clear();
  }
  while (s==17)
  {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;
    if (distance<=6)
    {
      lcd.setCursor(0,0);
      lcd.print("Something Here!");
      reverse();
      delay(300);
      right();
      delay(200);
      front();
      front();
      front();
      front();
      front();
      front();
      delay(200);
      left();
      delay(200);
      front();
      front();
      front();
      front();
      front(); /*Multiple front() is to allow the car to move further*/
      front(); /*This is because code is restricted by minimum speed being too fast*/
      front();
      front();
      front();
      front();
      front();
      front();
      front();
      delay(200);
      left();
      delay(200);
      front();
      front();
      front();
      front();
      front();
      front();
      front();
      delay(200);
      right();
      delay(200);
    }
    else
    {
      lcd.setCursor(0,0);
      lcd.print("No Object Here!");
      front();
      delay(100);
    }
  
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
  delay(50);
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
  digitalWrite(IN4, HIGH);
  delay(150);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void left()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(150);
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
  delay(40);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
