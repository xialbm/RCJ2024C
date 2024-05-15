#include <Servo.h>

Servo myservo;  
Servo myservo2;        
//电机自定义
int zhuangtai=0;

void setup() {
Serial.begin(9600);
myservo.attach(A3);
myservo2.attach(A1);
Serial2.begin(38400);
duoji(0);
while(1)
{
  jieshou();
  if(zhuangtai==5){zhuangtai=6;send(2);}
  if(zhuangtai>=50)break;
}
delay(2000);
fangxiang(1);
delay(3000);
dianji(0,0,0,0);
delay(3000);
fangxiang(2);
delay(3000);
dianji(0,0,0,0);
delay(2000);
fangxiang(2);
delay(3000);
dianji(0,0,0,0);
delay(2000);
fangxiang(1);
delay(3000);
dianji(0,0,0,0);
delay(9000);
duoji(1);
while(1){delay(2000);}
}

void loop(){






fangxiang(1);
duoji(1);
delay(2000);
fangxiang(3);
delay(1000);
fangxiang(2);
duoji(2);
delay(2000);
fangxiang(4);
delay(1000);

}

void fangxiang(int fx){
if(fx==1){dianji(-90,-90,90,90);}
if(fx==2){dianji(90,90,-90,-90);}



}

void dianji(int sd1,int sd2,int sd3,int sd4) {
  if (sd1 > 255) sd1 = 255;
  if (sd1 < -255) sd1 = -255;
  if (sd2 < -255) sd2 = -255;
  if (sd2 > 255) sd2 = 255;
  if (sd3 > 255) sd3 = 255;
  if (sd3 < -255) sd3 = -255;
  if (sd4 < -255) sd4 = -255;
  if (sd4 > 255) sd4 = 255;



  if (sd1 > 0) {
    digitalWrite(7, 0);
    analogWrite(6, sd1);
  } else if (sd1 < 0) {
    digitalWrite(7, 1);
    analogWrite(6, 255+sd1);
  } else {

    digitalWrite(7, 0);
    digitalWrite(6, 0);
  }


  if (sd2 > 0) {
    digitalWrite(8, 0);
    analogWrite(9, sd2);
  } else if (sd2 < 0) {

    digitalWrite(8, 1);
    analogWrite(9, 255 + sd2);
  } else {
    digitalWrite(9, 0);
    digitalWrite(8, 0);
  }

    if (sd3 > 0) {
    digitalWrite(4, 0);
    analogWrite(5, sd3);
  } else if (sd3 < 0) {

    digitalWrite(4, 1);
    analogWrite(5, 255 + sd3);
  } else {
    digitalWrite(4, 0);
    digitalWrite(5, 0);
  }

  if (sd4 > 0) {
    digitalWrite(10, 0);
    analogWrite(11, sd4);
  } else if (sd4 < 0) {

    digitalWrite(10, 1);
    analogWrite(11, 255 + sd4);
  } else {
    digitalWrite(11, 0);
    digitalWrite(10, 0);
  }
}



void duoji(int open) {
  int val;
             
  if(open==1){
    val = 500;
    val = map(val, 0, 1023, 0, 180);
  myservo.write(val); 
  myservo2.write(val);
}else{
  val = 0;
  val = map(val, 0, 1023, 0, 180);
  myservo.write(val);  
  val = 1000;
  val = map(val, 0, 1023, 0, 180);
  myservo2.write(val);
}
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


/*示例
舵机:
duoji(1);     //向上
delay(2000);  //等2000ms
duoji(2);     //向前(落)
delay(2000);  //等2000ms
*/


