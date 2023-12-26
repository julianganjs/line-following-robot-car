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
int ENA = 0;
int ENB = 1;

/*IR Sensors*/
int Ls = 12;
int Rs = 13;

void setup()
{
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(Ls,INPUT);
  pinMode(Rs,INPUT);

  /*Motor Speed 130 is minimum speed*/
  analogWrite(ENA, 130);
  analogWrite(ENB, 130);

  /*Start Up sequence*/
  lcd.begin(16,2);
  lcd.print("All Systems");
  lcd.setCursor(0,1);
  lcd.print("Boot Up");
  delay(600);
  lcd.print(".");
  delay(600);
  lcd.print(".");
  delay(600);
  lcd.print(".");
  delay(600);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Timer Starts In:");
  lcd.setCursor(0,1);
  lcd.print("3s");
  delay(750);
  lcd.setCursor(0,1);
  lcd.print("  ");  
  delay(250);
  lcd.setCursor(0,1);
  lcd.print("2s");
  delay(750);
  lcd.setCursor(0,1);
  lcd.print("  ");  
  delay(250);
  lcd.setCursor(0,1);
  lcd.print("1s");
  delay(750);
  lcd.setCursor(0,1);
  lcd.print("  ");  
  delay(250);
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("Time (s):");
}

void loop()
{
   int c = 17;
   while (c==17)
   {
    int x;
    int y;
    delay(100);
    x = digitalRead(Ls);
    y = digitalRead(Rs);
    if (x==LOW && y==LOW)
    {
     left();
    }
    else if (x==HIGH && y==HIGH)
    {
     right();
    }
    else if (x==LOW && y==HIGH)
    {
     front();
    }
    else
    {
     c=18;
    }
    unsigned long totalTime = millis();
    int t = (totalTime - 5400) / 1000;
    lcd.setCursor(7,1);
    lcd.print(t);
   }
   lcd.setCursor(0,0);
   lcd.print(" Time taken(s):");
   while (c==18)
   {
    finish(); 
   }
}

/*Car stops after short delay due to minimum speed being too fast*/
void front()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(15);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void left()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(45);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void right()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(45);
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
