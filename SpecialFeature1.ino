/*IN THE BOX GAME*/
/*Up to 4 players*/
/*Keep the car in a box/play area, that's all!*/
/*Car rotates to a random direction after every bounce*/
/*Your bat cannot enter the box at all times*/

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
int echoPin = 2;
int trigPin = 3;
long duration;
int distance;

void setup()
{
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

  /*Motor Speed 130 is minimum speed*/
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);

  /*Start Up sequence*/
  lcd.begin(16, 2);
  lcd.print("  |IN THE BOX|"); /*Name of the game*/
  lcd.setCursor(0, 1);
  lcd.print("Press 'SELECT'!");
}

void loop()
{
  int player = 1;
  int s = 1; /*Number of players*/
  int x;
  int b=0;/*Make sure a selection is made*/
  x = analogRead(0);
  if (x < 800 && x >= 600)
  {
    lcd.clear();
    int p=0;
    while (p==0) /*Player no. selection*/
    {
      char a = 0x7F;
      lcd.setCursor(0,0);
      lcd.print("No. of Players?");
      if(s>1 && s<4)
      {
        lcd.setCursor(3,1);
        lcd.print(a);
        lcd.setCursor(7,1);
        lcd.print(s);
        lcd.setCursor(11,1);
        lcd.print("~");  
      }
      if (s==1)
      {
        lcd.setCursor(3,1);
        lcd.print(" ");
        lcd.setCursor(7,1);
        lcd.print(s);
        lcd.setCursor(11,1);
        lcd.print("~");
      }
      if (s==4)
      {
        lcd.setCursor(3,1);
        lcd.print(a);
        lcd.setCursor(7,1);
        lcd.print(s);
        lcd.setCursor(11,1);
        lcd.print(" ");
      }
      x= analogRead(0);
      if (x<60)
      {
        s=4;
        b=1;
      }
      if (x>=60 && x<200)
      {
        s=2;
        b=1;
      }
      if (x>=200 && x<400)
      {
        s=3;
        b=1;
      }
      if (x>=400 && x<600)
      {
        s=1;
        b=1;
      }
      if (x>=600 && x<800 && b==1)
      {
        p=1;
      }
      
    }
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Game Starts In:");
    lcd.setCursor(6,1);
    lcd.print("3s");
    delay(750);
    lcd.setCursor(6,1);
    lcd.print("  ");  
    delay(250);
    lcd.setCursor(6,1);
    lcd.print("2s");
    delay(750);
    lcd.setCursor(6,1);
    lcd.print("  ");  
    delay(250);
    lcd.setCursor(6,1);
    lcd.print("1s");
    delay(750);
    lcd.setCursor(6,1);
    lcd.print("  ");  
    delay(250);
    lcd.clear();
  }

  /*1 player*/
  int points = 0;
  while (s == 1 && b==1)
  {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;
    lcd.setCursor(2, 0);
    lcd.print("Hit It Back!");
    lcd.setCursor(3,1);
    lcd.print("~   ~   ~");
    if (distance <= 10 && distance >= 4)
    {
      points +=1;
      lcd.clear();
      lcd.setCursor(5, 0);
      lcd.print("BOUNCE!");
      reverse();
      delay(50);
      right();
      delay(50);
      lcd.clear();
    }
    else if (distance < 4)
    {
      s = 0;
      finish();
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("GAME OVER!");
      lcd.setCursor(0, 1);
      lcd.print("You Got ");
      lcd.print(points);
      lcd.print(" Points!");
    }
    else
    {
      front();
      delay(20);
    }

  }

  /*2 players*/
  while (s == 2)
  {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;
    lcd.setCursor(0, 0);
    lcd.print("Player ");
    lcd.setCursor(7,0);
    lcd.print(player);
    lcd.setCursor(8,0);
    lcd.print("'s");
    lcd.setCursor(11,0);
    lcd.print("turn!");
    lcd.setCursor(3,1);
    lcd.print("~   ~   ~");
    if (distance <= 10 && distance >= 4)
    {
      lcd.clear();
      lcd.setCursor(5, 0);
      lcd.print("BOUNCE!");
      reverse();
      delay(50);
      right();
      delay(50);
      if (player == 1)
      {
        player = 2;
      }
      else if (player == 2)
      {
        player = 1;
      }
      lcd.clear();
    }
    else if (distance < 4)
    {
      s = 0;
      finish();
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("GAME OVER!");
      lcd.setCursor(0, 1);
      lcd.print("Player ");
      lcd.setCursor(7,1);
      lcd.print(player);
      lcd.setCursor(9,1);
      lcd.print("loses!");
    }
    else
    {
      front();
      delay(20);
    }

  }

  /*3 players*/
  while (s == 3)
  {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;
    lcd.setCursor(0, 0);
    lcd.print("Player ");
    lcd.setCursor(7,0);
    lcd.print(player);
    lcd.setCursor(8,0);
    lcd.print("'s");
    lcd.setCursor(11,0);
    lcd.print("turn!");
    lcd.setCursor(3,1);
    lcd.print("~   ~   ~");
    if (distance <= 10 && distance >= 4)
    {
      lcd.clear();
      lcd.setCursor(5, 0);
      lcd.print("BOUNCE!");
      reverse();
      delay(50);
      right();
      delay(50);
      if (player == 1)
      {
        player = 2;
      }
      else if (player == 2)
      {
        player = 3;
      }
      else if (player ==3)
      {
        player = 1;
      }
      lcd.clear();
    }
    else if (distance < 4)
    {
      s = 0;
      finish();
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("GAME OVER!");
      lcd.setCursor(0, 1);
      lcd.print("Player ");
      lcd.setCursor(7,1);
      lcd.print(player);
      lcd.setCursor(9,1);
      lcd.print("loses!");
    }
    else
    {
      front();
      delay(20);
    }

  }

  /*4 players*/
  while (s == 4)
  {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;
    lcd.setCursor(0, 0);
    lcd.print("Player ");
    lcd.setCursor(7,0);
    lcd.print(player);
    lcd.setCursor(8,0);
    lcd.print("'s");
    lcd.setCursor(11,0);
    lcd.print("turn!");
    lcd.setCursor(3,1);
    lcd.print("~   ~   ~");
    if (distance <= 10 && distance >= 4)
    {
      lcd.clear();
      lcd.setCursor(5, 0);
      lcd.print("BOUNCE!");
      reverse();
      delay(50);
      right();
      delay(50);
      if (player == 1)
      {
        player = 2;
      }
      else if (player == 2)
      {
        player = 3;
      }
      else if (player ==3)
      {
        player = 4;
      }
      else if (player==4)
      {
        player = 1;
      }
      lcd.clear();
    }
    else if (distance < 4)
    {
      s = 0;
      finish();
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("GAME OVER!");
      lcd.setCursor(0, 1);
      lcd.print("Player ");
      lcd.setCursor(7,1);
      lcd.print(player);
      lcd.setCursor(9,1);
      lcd.print("loses!");
    }
    else
    {
      front();
      delay(20);
    }

  }
}

/*Directions*/
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
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(800);
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
