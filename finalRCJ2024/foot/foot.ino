#include <Wire.h>



int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
const int MPU_addr = 0x68; // MPU-6050的i2c地址
float agx,agy,agz;
int agxn=0;
int agzn=0;
int sendfoot=0;
int beginx=0;

void setup() {
  Wire.begin();
  Serial2.begin(38400);
 Serial.begin(9600);
  pinMode(25, OUTPUT);                         
  pinMode(14, OUTPUT);
  digitalWrite(25,0);
  digitalWrite(25,0);
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B); 
  Wire.write(0); //启动mpu6050
  Wire.endTransmission(true);                         //初始化MPU6050
  delay(500);
}

void loop() {

  esp32MPU();
  jieshou();
  if(beginx==1)
{


  agx=-AcX/150;
  agxn=(agxn*4+agx)/5;
  if(agxn<-5)agxn=-5;
  if(agxn>45)agxn=45;
  agz=AcY/150;
  agzn=(agzn*4+agz)/5;
  if(agzn<-45)agzn=-45;
  if(agzn>45)agzn=45;
  Serial.print("Gyx = "); Serial.print(agxn);
  Serial.print(" | Gyy = "); Serial.print(agy);
  Serial.print(" | GyZ = "); Serial.println(agzn);
 // Serial.print(analogRead(39));Serial.print("    ");Serial.println(analogRead(36));
  if(analogRead(39)<3900) digitalWrite(25,1);else  digitalWrite(25,0);
  if(analogRead(36)<3900) digitalWrite(14,1);else  digitalWrite(14,0);
  if(analogRead(39)<3900) {if(analogRead(36)<3900) sendfoot==4; else sendfoot=2;} //4全踩，3前，2后，1没有
  else {if(analogRead(36)<3900) sendfoot==3; else sendfoot=1;}
  Serial2.write(254);
  Serial2.write(agxn+90);
  Serial2.write(agzn+90);
  Serial2.write(sendfoot);
  delay(200);
  
  }
}


void esp32MPU()
{
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers
  AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
 //    Serial.print("AcX = "); Serial.print(AcX);
  //   Serial.print(" | AcY = "); Serial.print(AcY);
  //   Serial.print(" | AcZ = "); Serial.println(AcZ);
//     Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53); //equation for temperature in degrees C from datasheet
//     Serial.print(" | GyX = "); Serial.print(GyX);
//     Serial.print(" | GyY = "); Serial.print(GyY);
//     Serial.print(" | GyZ = "); Serial.println(GyZ);
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
      if(zj1==5) {Serial.println("xx");  Serial2.write(254); Serial2.write(9);Serial2.write(9); Serial2.write(9);}
      if(zj1==10) beginx=1;
      if(zj1==20) beginx=0;
      
    }
  }
}
