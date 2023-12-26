/*Dog Mode*/

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

/*IR sensor(Tail)*/
int TAIL=11;

/*Ultrasonic sensor*/
int echoPin = 2;
int trigPin = 3;
long duration;
int distance;

/*Dog Face*/
byte dog11[10]
{
  B00000,B00000,B00001,B00110,B01001,B10010,B10010,B01010,
};
byte dog12[10]
{
  B01010,B00101,B00001,B00000,B00000,B00000,B00000,B00000,
};
byte dog21[10]
{
  B00000,B00000,B11111,B00000,B00000,B00000,B10001,B00000,
};
byte dog22[10]
{
  B00000,B01110,B00100,B10001,B01110,B00000,B00000,B00000,
};
byte dog31[10]
{
  B00000,B00000,B10000,B01100,B00010,B01001,B01001,B01010,
};
byte dog32[10]
{
  B01010,B10100,B10000,B00000,B00000,B00000,B00000,B00000,
};


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

  /*IR sensor(Tail)*/
  pinMode(TAIL,INPUT);

  /*Bluetooth Module*/
  Serial.begin(9600);

  /*Motor Speed 130 is minimum speed*/
  analogWrite(ENA, 130);
  analogWrite(ENB, 130);

  /*Start Up sequence*/
  lcd.begin(16, 2);
  
  /*Dog Face*/
  lcd.createChar(1,dog11);
  lcd.createChar(2,dog21);
  lcd.createChar(3,dog31);
  lcd.createChar(4,dog12);
  lcd.createChar(5,dog22);
  lcd.createChar(6,dog32);
  lcd.setCursor(0,0);
  lcd.write(1);
  lcd.setCursor(1,0);
  lcd.write(2);
  lcd.setCursor(2,0);
  lcd.write(3);
  lcd.setCursor(0,1);
  lcd.write(4);
  lcd.setCursor(1,1);
  lcd.write(5);
  lcd.setCursor(2,1);
  lcd.write(6);

  lcd.setCursor(13,0);
  lcd.write(1);
  lcd.setCursor(14,0);
  lcd.write(2);
  lcd.setCursor(15,0);
  lcd.write(3);
  lcd.setCursor(13,1);
  lcd.write(4);
  lcd.setCursor(14,1);
  lcd.write(5);
  lcd.setCursor(15,1);
  lcd.write(6);
  
  lcd.setCursor(6,0);
  lcd.print("DOG");
  lcd.setCursor(6,1);
  lcd.print("MODE");
}

char c;
void loop()
{
  c='A';
  c = Serial.read();
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  
  if (distance<=30 && distance>15) /*Treats*/
  { 
    front();
    delay(50);
  }
  
  if (distance<=2) /*Patting Head*/
  {
    headpat();
  }
  
  if (digitalRead(TAIL)==LOW) /*Tap tail(Behind you)*/
  {
    delay(600);
    cwturn();
    delay(600);
    left();
    delay(1000);
    right();
    delay(1000);
    wagleft();
    wagleft();
  }
  
  if (c == 'S') /*Spin in a circle*/
  {
    int z = 0;
    while (z==0)
    {
      spin();
      c = Serial.read();
      if (c=='H')
      {
        z=1;
      }
    }
    finish();
  }

  if (c=='G') /*Good boy*/
  {
    goodboy();
  }

  if (c=='W')/*Walk around*/
  {
    walkaround();
  }

  if (c=='D') /*Dance*/
  {
    dance();
  }

  if (c=='B')
  {
    lcd.setCursor(6,0);
    lcd.print("WOOF!");
    lcd.setCursor(6,1);
    lcd.print("    ");
  }
  
  else
  {
    finish();
    
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

void left()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(70);
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
  delay(70);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void wagleft()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(30);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void wagright()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(30);
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
  delay(50);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

/*Dog stops moving*/
void finish()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void cwturn()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(380);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void acwturn()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(380);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void spin()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void reversespin()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

/*Tricks*/
void headpat()
{
  reverse();
  delay(1000);
  front();
  delay(50);
  front();
  delay(50);
  finish();
  delay(1700);
  wagleft();
  delay(100);
  wagright();
  delay(100);
  wagleft();
  delay(100);
  wagright();
  delay(100);
  wagleft();
  delay(100);
  wagright();
  delay(100);
  wagleft();
  delay(100);
  wagright();
  delay(100);
  wagleft();
  delay(100);
  wagright();
  delay(100);
  wagleft();
  delay(100);
  wagright();
  delay(100);
  wagleft();
  delay(100);
  wagright();
  delay(100);
  wagleft();
  delay(100);
  wagright();
  delay(100);
}

void goodboy()
{
    spin();
    delay(1500);
    wagleft();
    delay(100);
    wagright();
    delay(100);
    wagleft();
    delay(100);
    wagright();
    delay(100);
    wagleft();
    delay(100);
    wagright();
    delay(100);
    wagleft();
    delay(100);
    wagright();
    delay(100);
    wagleft();
    delay(100);
    wagright();
    delay(100);
    wagleft();
    delay(100);
    wagright();
    delay(100);
    wagleft();
    delay(100);
    wagright();
    delay(100);
    wagleft();
    delay(100);
    wagright();
}

void walkaround()
{
    int m = 0;
    while(m==0)
    {
      c = Serial.read();
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      distance = duration * 0.034 / 2;
      if (distance<=6)
      {
        reverse();
        reverse();
        delay(200);
        left();
        delay(100);
        left();
        delay(100);
        left();
        delay(200);
      }
      if (c=='H')
      {
        m=1;
      }
      front();
      delay(100);
    }
    finish();
}

void dance()
{
  int d=0;
  while (d==0)
  {
    front();
    front();
    delay(200);
    front();
    front();
    delay(200);
    reverse();
    reverse();
    delay(200);
    reverse();
    reverse();
    delay(200);
    front();
    front();
    delay(200);
    front();
    front();
    delay(200);
    reverse();
    reverse();
    delay(200);
    reverse();
    reverse();
    delay(200);
    cwturn();
    delay(200);
    left();
    delay(100);
    right();
    delay(100);
    left();
    delay(200);
    acwturn();
    delay(200);
    left();
    delay(100);
    right();
    delay(100);
    left();
    delay(200);
    c = Serial.read();
    if (c=='H')
    {
      d=1;
    }
  }
  finish();
}
