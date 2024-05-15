
#include <Wire.h>
#include <AccelStepper.h>
#include <HardwareSerial.h>


#define IN1M 27
#define IN2M 33
#define PWMA 26
#define PWMB 32
#define DJ1 25
#define DJ2 15
#define STEPPER1_DIR_PIN 14
#define STEPPER1_STEP_PIN 13
AccelStepper stepper1(AccelStepper::DRIVER, STEPPER1_STEP_PIN, STEPPER1_DIR_PIN);





long stepmax=15000;
int xspeed=7500;
int zhuangtai=0;
int zhuandong=0;
int speedx=0;
long timer=0;


void setup() {

  
  Wire.begin();
  Serial2.begin(38400);
  pinMode(IN1M, OUTPUT);                         
  pinMode(IN2M, OUTPUT);
  pinMode(PWMA, OUTPUT);                        
  pinMode(PWMB, OUTPUT);  
  pinMode(DJ1, OUTPUT);                        
  pinMode(DJ2, OUTPUT);  
  ledcSetup(1, 100, 12);
  ledcSetup(2, 100, 12);
  ledcSetup(3, 50, 12);
  ledcSetup(4, 50, 12);

  ledcAttachPin(PWMA, 1);
  ledcAttachPin(PWMB, 2);
  ledcAttachPin(DJ1, 3);
  ledcAttachPin(DJ2, 4);

  digitalWrite(IN1M, 0);
  digitalWrite(IN2M, 0);
  ledcWrite(1, 0);
  ledcWrite(2, 0);
  servoclose();
  stepper1.setCurrentPosition (0);
  stepper1.setMaxSpeed(15000.0);

  //while(1)sportfx(0,1200);


  
  
while(1)
{
  jieshou();
  if(zhuangtai==5){zhuangtai=6;send(1);digitalWrite(13,1);autozero();}
  if(zhuangtai>=10)break;
}

while(1)
{
  jieshou();
  if(zhuangtai>=30)break;
}
 xgo(140000);
 servoopen();delay(1500);
send(40);
  timer=millis();
  while( millis()-timer<3000){sportfx(0,1200);}
  timer=millis();
    while( millis()-timer<2000){sportfx(0,-1200);}
  timer=millis();
  while( millis()-timer<3000){sportfx(30,1200);}
  timer=millis();
   while( millis()-timer<2000){sportfx(30,-1200);}
  timer=millis();
  while( millis()-timer<3000){sportfx(-30,1200);}
   timer=millis();
  while( millis()-timer<2000){sportfx(-30,-1200);}
  timer=millis();
  while( millis()-timer<3000){sportfx(0,0);}
sport(0,0);
while(1){}




}

void loop() {
 xgo(140000);
 servoopen();delay(2000);
 sport(1200,-1200);
 delay(50000);
 sport(0,0);
 while(1){}
 xgo(0);
 delay(10000);
}


void autozero()
{


    stepper1.setSpeed(-7000);
    while (analogRead(39)>400){  stepper1.runSpeed(); }
    delay(500);
    stepper1.setSpeed(500);
    while (analogRead(39)<700) {  stepper1.runSpeed(); }
    stepper1.setCurrentPosition (0);
    delay(500);
}

void xgo(long xweizhi)
{
  long nowx;
  nowx = stepper1.currentPosition();
  if(nowx>xweizhi)         {stepper1.moveTo(xweizhi); stepper1.setSpeed(-xspeed); while (stepper1.distanceToGo()!= 0) { stepper1.runSpeed();}}
  else if(nowx<xweizhi)    {stepper1.moveTo(xweizhi); stepper1.setSpeed(xspeed);  while (stepper1.distanceToGo()!= 0) { stepper1.runSpeed();}}
}

void sport(int a,int b){
  if (a >= 0) {
    digitalWrite(IN1M,LOW);
    ledcWrite(1, a);
  } else {
    digitalWrite(IN1M,HIGH);
    ledcWrite(1, -a);
  }
  //电机的正负输出判断        右电机判断
  if (b >= 0) {
    digitalWrite(IN2M,LOW);
    ledcWrite(2, b);
  } else {
    digitalWrite(IN2M,HIGH);
    ledcWrite(2, -b);
  }
  }

void servoclose()
{
  ledcWrite(3, 500);
  delay(1000);
  ledcWrite(4, 265);
  delay(1000);
 
}

void servoopen()
{
  ledcWrite(4, 495);
  delay(1000);
  ledcWrite(3, 275);
  delay(1500);
}


void jieshou()
{ 
  if(Serial2.available()> 0)
  {
    int zj1;
    if(Serial2.read()!=254) 
    {
    }
    else
    {
      delay(20); 
      zj1=Serial2.read();
      //Serial.println(zj1);
      if(zhuangtai<zj1) zhuangtai=zj1;
    }
  }
}

void send(int zbsj)
{
  Serial2.write(254);
  Serial2.write(zbsj);
}


void sportfx(int fx,int speed)
{
  int jiaoducha;
  zhuandong=(znzget()-fx+720)%360;
if(zhuandong>180)zhuandong=zhuandong-360;
zhuandong=zhuandong*40;
if(zhuandong>1000)zhuandong=1000;
if(zhuandong<-1000)zhuandong=-1000;
if(zhuandong<200&&zhuandong>-200)zhuandong=0;
if(zhuandong>600||zhuandong<-600)speedx=0; else speedx=speed;
sport(-speedx-zhuandong,speedx-zhuandong);
}



int znzget()
{
  int highpr = 99;
  int lowpr = 99;
  Wire.requestFrom(59, 2);
  while (Wire.available())
  {
    highpr = Wire.read();
    lowpr = Wire.read();
  }
  if (highpr == 11 && lowpr == 02) return 999;
  else if (highpr < 2)return highpr * 255 + lowpr;
  else return highpr;
}
