#include <U8g2lib.h>
#include <Wire.h>
#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial SSSerial4(9, 8);
Servo servo1;
Servo servo2;
int larx, lary, larid;
long larxt, laryt;
unsigned long outtimex = 0;
int outtime = 300;
int agxn = 0;
int agzn = 0;
int sendfoot = 0;
int zhuangtai = 0;
long timer=0;

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

int ledshow[16][16];
int ceshix[8];
int ceshi1, ceshi2, ceshi3, ceshi4, ceshi5, ceshi6, ceshi7, ceshi8, ceshi9, ceshi10, ceshi11, ceshi12, ceshi13, ceshi14, ceshi15, ceshi16;
void setup() {
  servo1.attach(38);
  servo2.attach(22);
  Serial.begin(9600);
  Serial2.begin(38400);//摄像头
  Serial3.begin(38400);//收球鞋数据
  Serial1.begin(38400);//主通信蓝牙
  SSSerial4.begin(38400);//软串口走分数机数据
  u8g2.begin();
  servo1.write(90);
  servo2.write(90);
  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 16; j++) {
      ledshow[i][j] = 0;
    }
  }

timer=millis();
while(1)
{
  jieshou();
  if(zhuangtai==5||zhuangtai==6)
  {
    if(zhuangtai==5){send(3);digitalWrite(13,1);zhuangtai=6;}
    if(millis()-timer>1000){timer=millis();Serial3.write(254);Serial3.write(5);}
    if (Serial3.available()) {
      while (Serial3.available()) {
        if (Serial3.read() == 254) {
          delay(20);
          if(Serial3.read()==9)
          {
          Serial3.read();
          Serial3.read();
          send(4);
          }
        }
      }
    }

  }
  if(zhuangtai>=10)break;
}








  if (zhuangtai == 10) {
    Serial3.write(254);
    Serial3.write(10);
    while (zhuangtai == 10) {
    jieshou();
    if (Serial3.available()) {
      while (Serial3.available()) {
        if (Serial3.read() == 254) {
          delay(20);
          agxn = Serial3.read();
          agzn = Serial3.read();
          sendfoot = Serial3.read();
          if(agxn>=200) {zhuangtai=11;send(20);}
          else
          {
          servo1.write(agxn);
          servo2.write(agzn);
          }
        }
      }
    }
  }
}

while(1)
{
  jieshou();
  if(zhuangtai>=70)break;
}

SSSerial4.write(254);SSSerial4.write(10);
while(1)
{
  jieshou();
  if(zhuangtai>=80)break;
 getapril();
 Serial.println("nnn");
  larxt = larx;
  laryt = lary;
  if (larxt > 170) larxt = 170;
  if (larxt < 50) larxt = 50;
  larxt = (larxt - 50) * 246 / 120;
  if (laryt > 200) laryt = 200;
  if (laryt < 60) laryt = 60;
  laryt = (laryt - 60) * 246 / 140;
  if (larx != 0 || lary != 0) {
    if (ledshow[15 - int(laryt / 16)][int((larxt) / 16)] < 2)
      ledshow[15 - int(laryt / 16)][int((larxt) / 16)] = ledshow[15 - int(laryt / 16)][int((larxt) / 16)] + 1;
    if (ledshow[15 - int(laryt / 16)][int((larxt) / 16)] == 2) {
      SSSerial4.write(254);
      SSSerial4.write(15 - int(laryt / 16));
      SSSerial4.write(int((larxt) / 16));
      u8g2.clearBuffer();
      for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
          if (ledshow[i][j] == 2) {
            u8g2.drawBox(30 + i * 4, (16 - j) * 4, 3, 3);
          }
        }
      }

      u8g2.sendBuffer();
    }
  }

  Serial.print(15 - int(laryt / 16));
  Serial.print("  ");
  Serial.print(int((larxt) / 16));
  Serial.print("  ");
  Serial.print(larx);
  Serial.print("  ");
  Serial.print(lary);
  Serial.print("  ");
  Serial.print(larid);
  Serial.println("");


  /*

    for(int i=0;i<8;i++)
    {
      ceshix[i]=(ceshi8>>i)%2;
    }
    for(int i=0;i<8;i++)
    {
     // Serial.print(ceshix[i]);
     
    }



        for(int i=0;i<8;i++)
    {
      Serial.print(ledshow[0][i]);
     
    }
        for(int i=0;i<8;i++)
    {
      Serial.print(ledshow[0][i+8]);
     
    }
Serial.println("");
    for(int i=0;i<8;i++)
    {
      Serial.print(ledshow[1][i]);
     
    }
        for(int i=0;i<8;i++)
    {
      Serial.print(ledshow[1][i+8]);
     
    }
Serial.println("");
    for(int i=0;i<8;i++)
    {
      Serial.print(ledshow[2][i]);
     
    }
        for(int i=0;i<8;i++)
    {
      Serial.print(ledshow[2][i+8]);
     
    }
Serial.println("");
    for(int i=0;i<8;i++)
    {
      Serial.print(ledshow[3][i]);
     
    }
        for(int i=0;i<8;i++)
    {
      Serial.print(ledshow[3][i+8]);
     
    }
Serial.println("");
    for(int i=0;i<8;i++)
    {
      Serial.print(ledshow[4][i]);
     
    }
        for(int i=0;i<8;i++)
    {
      Serial.print(ledshow[4][i+8]);
     
    }
    Serial.println("");*/
  delay(100);

}

}

void loop() {












 
}



void getapril() {
  Serial2.write(250);
  larid = 99;
  outtimex = millis();
  while (!Serial2.available()) {
    if (millis() > outtimex + outtime) { break; }
  }
  delay(10);
  while (Serial2.available()) {
    if (Serial2.read() == 254) {
      delay(20);
      larx = (Serial2.read());
      lary = (Serial2.read());
      larid = (Serial2.read());
      break;
    } else {
      larid = 88;
    }
  }
}


void jieshou()
{ 
  if(Serial1.available()> 0)
  {
    int zj1;
    if(Serial1.read()!=254) 
    {
    }
    else
    {
      delay(20); 
      zj1=Serial1.read();
      //Serial.println(zj1);
      if(zhuangtai<zj1) zhuangtai=zj1;
    }
  }
}
void send(int zbsj)
{
  Serial1.write(254);
  Serial1.write(zbsj);
}