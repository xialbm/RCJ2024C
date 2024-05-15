#include <Wire.h>
#include <LiquidCrystal_I2C.h>




LiquidCrystal_I2C lcd(0x27,16,2);

int showx=0;
int zj1,zj2,zj3,zj4,zj5;
int anniu1=1000;
long timer=0;
int get1,get2,get3,get4,get5;

void setup() {
  lcd.init();                    
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Prepare...");
  Serial2.begin(38400);delay(50);
  Serial.begin(9600);
  lcd.setCursor(0, 0);
  lcd.print("wait...   ");
  timer=millis();
  while(1)
  {
    get1=jieshou1();

    if(get1==1){get1=0;lcd.setCursor(0, 1);lcd.print("*1");}
    if(get1==2){get1=0;lcd.setCursor(2, 1);lcd.print("*2");}
    if(get1==3){get1=0;lcd.setCursor(4, 1);lcd.print("*3");}
    if(get1==4){get1=0;lcd.setCursor(6, 1);lcd.print("*4");}
    if(get1==5){get1=0;lcd.setCursor(8, 1);lcd.print("*5");}
    if(get1==6){get1=0;lcd.setCursor(10, 1);lcd.print("*6");}
    anniu1=(anniu1*29+analogRead(A0))/30;
    if(millis()-timer>1000){timer=millis();send1(5);}
    if(anniu1<200){lcd.clear();delay(200);showx=1;break;}
  }

  send1(10);

  lcd.setCursor(0, 0);lcd.print("foot   ");  //鞋和手的动作
  timer=millis();
  while(1)
  {
    get1=jieshou1();
    if(get1>=20){break;}
      if(millis()-timer>21000){lcd.setCursor(0, 1);lcd.print("T");break;}
  }
  send1(30);
  lcd.setCursor(0, 0);lcd.print("ball    ");//球变形
  timer=millis();
  while(1)
  {
    get3=jieshou1();
    if(get3>=40){break;}
      if(millis()-timer>22000){lcd.setCursor(0, 1);lcd.print("T");break;}
  }
  delay(300);
  send1(50);
  lcd.setCursor(0, 0);lcd.print("door     ");//球和门一起动
  delay(20000);
delay(500);
  send1(60);
  lcd.setCursor(0, 0);lcd.print("check1     ");//前锋的作弊
delay(500);
  delay(15000);
  send1(70);
  lcd.setCursor(0, 0);lcd.print("check2    ");//门将的作弊


  
  delay(20000);
  send1(80);
  lcd.setCursor(0, 0);lcd.print("succeed    ");//结束

}

void loop() {


}





int jieshou1()
{ 
  zj1=0;
  if(Serial2.available()> 0)
  {
    if(Serial2.read()!=254) 
    {
    }
    else
    {
      delay(20); 
      zj1=Serial2.read();
    }
  }
  if(showx==1&&zj1>0){lcd.setCursor(0, 2);lcd.print("U1:   ");lcd.setCursor(3, 2);lcd.print(zj1);}
  return zj1;
}






void send1(int zbsj)
{
  Serial2.write(254);
  Serial2.write(zbsj);
  if(showx==1){lcd.setCursor(2, 3);lcd.print("S1:   ");lcd.setCursor(5, 3);lcd.print(zbsj);}
}


