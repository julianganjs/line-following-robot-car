#include <LiquidCrystal.h>
#include <math.h>

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

/*Encoder Sensor*/
unsigned int counter=0;
void count()
{
  counter++;
}

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

  /*Encoder Sensor*/
  attachInterrupt(digitalPinToInterrupt(2),count,RISING);

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
  lcd.print("Vehicle Will");
  lcd.setCursor(0,1);
  lcd.print("Move In:");
  lcd.setCursor(10,1);
  lcd.print("3s");
  delay(750);
  lcd.setCursor(10,1);
  lcd.print("  ");  
  delay(250);
  lcd.setCursor(10,1);
  lcd.print("2s");
  delay(750);
  lcd.setCursor(10,1);
  lcd.print("  ");  
  delay(250);
  lcd.setCursor(10,1);
  lcd.print("1s");
  delay(750);
  lcd.setCursor(10,1);
  lcd.print("  ");  
  delay(250);
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Distance (m):");
}

void loop()
{
   int c = 17;
   while (c==17)
   {
    int x;
    int y;
    delay(100);
    float rotation = (counter/20);
    float distance = ((2*M_PI*0.033) * rotation)*(30.0/100.0); /*Distance travelled*/
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
      c=18; /*Stops the car at the finish line*/
    }
    lcd.setCursor(5,1);
    lcd.print(distance,2);
   }
   while (c==18)
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
  delay(13);
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
  delay(37);
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
  delay(37);
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
