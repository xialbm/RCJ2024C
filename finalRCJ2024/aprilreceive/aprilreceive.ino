#include <U8g2lib.h>
#include <Wire.h>
#include <HardwareSerial.h>
#include <Adafruit_NeoPixel.h>
#include <HardwareSerial.h>

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
Adafruit_NeoPixel pixels1= Adafruit_NeoPixel(256, 33, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2= Adafruit_NeoPixel(256, 32, NEO_GRB + NEO_KHZ800);
HardwareSerial MySerial(1);
int ledshow[16][16];
int ceshi1,ceshi2,ceshi3,ceshi4,ceshi5,ceshi6,ceshi7,ceshi8,ceshi9,ceshi10,ceshi11,ceshi12,ceshi13,ceshi14,ceshi15,ceshi16;
int beginx=0;
int zhuangtai=0;

459561437
void setup() {
  Serial.begin(9600);
  Serial2.begin(38400);//来自手的蓝牙
   MySerial.begin(38400, SERIAL_8N1, 27, 26);
    pixels1.begin();
    for(int ledi=1;ledi<256;ledi++) 
    {
      pixels1.setPixelColor(ledi-1, pixels1.Color(0,0,0));
      pixels2.setPixelColor(ledi-1, pixels2.Color(0,0,0));
      pixels1.setPixelColor(ledi, pixels1.Color(0,0,3));
      pixels2.setPixelColor(ledi, pixels2.Color(0,0,3));
      delay(10);
      pixels1.show();
  pixels2.show();
    }
    for(int ledi=0;ledi<256;ledi++) 
    {
      pixels1.setPixelColor(ledi, pixels1.Color(0,0,0));
      pixels2.setPixelColor(ledi, pixels2.Color(0,0,0));
    }


   pixels1.show();
  pixels2.show();

  u8g2.begin();

  for(int i=0;i<16;i++)
  {
    for(int j=0;j<16;j++)
    {
      ledshow[i][j]=0;
    }
  }

while(1)
{
  jieshoux();
  if(zhuangtai==5){zhuangtai=6;sendx(5);}
  if(zhuangtai>=10)break;
}

Serial.println("xxx");


}

void loop() {
if(beginx==0)jieshou();

  if(beginx==1)
{

readxxx();

    u8g2.clearBuffer();
      for(int i=0;i<16;i++)
      {
        for(int j=0;j<16;j++)
        {
          if (ledshow[i][j]==1)
          {
            u8g2.drawBox(i*4,(16-j)*4,3,3);
          }
        }
      }
    
    u8g2.sendBuffer();

}
}



void readxxx()
{
    while (Serial2.available()) {
    if(Serial2.read()==254)
    {
      delay(20);
      ceshi1=Serial2.read();
      ceshi2=Serial2.read();
      ledshow[15-ceshi1][ceshi2]=1;



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
Serial.println("");
ledshowx();




      break;
    }
  }

}



void ledshowx()
{
      /*  for(int i=0;i<16;i++)
      {
        ledshow[i][3]=1;
        ledshow[i][9]=1;
      }*/
  
  
  
  for(int i=0;i<16;i++)
  {
    for(int j=0;j<16;j++)
    {
      if(ledshow[i][j]==1)
        {
          if(i<8&&j<8) pixels1.setPixelColor(i+j*8, pixels1.Color(0,0,20));
          if(i>=8&&j<8) pixels1.setPixelColor(64+i-8+j*8, pixels1.Color(0,0,20));
          if(i<8&&j>=8) pixels1.setPixelColor(128+i+(j-8)*8, pixels1.Color(0,0,20));
          if(i>=8&&j>=8) pixels1.setPixelColor(192+i-8+(j-8)*8, pixels1.Color(0,0,20));
        }
        
    }
  }

pixels1.show();

/*

  for(int ledi=0;ledi<256;ledi++) 
    {
      pixels1.setPixelColor(ledi-1, pixels1.Color(0,0,0));
      pixels1.setPixelColor(ledi, pixels1.Color(5,0,0));
       pixels1.show();
      delay(100);

    }*/

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
      Serial.println(zj1);
      if(zj1==10) {Serial.println("xxxxxxxxxx"); beginx=1;}
      
      
    }
  }
}

void send(int zbsj)
{
  Serial2.write(254);
  Serial2.write(zbsj);
}



void jieshoux()
{ 
  if(MySerial.available()> 0)
  {
    
    int zj1;
    if(MySerial.read()!=254) 
    {
    }
    else
    {
      delay(20); 
      zj1=MySerial.read();
      //Serial.println(zj1);
      if(zhuangtai<zj1) zhuangtai=zj1;
    }
  }
}

void sendx(int zbsj)
{
  MySerial.write(254);
  MySerial.write(zbsj);
}

