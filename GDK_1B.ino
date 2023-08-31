
#include<SoftwareSerial.h>

#define BT_RX 9
#define BT_TX 10
SoftwareSerial BT(BT_RX, BT_TX);

#include <Wire.h>
/*
* Arduino analog input 5 - I2C SCL
* Arduino analog input 4 - I2C SDA
*
* Command List
* 0xA0 :: Reset
* 0xB3 :: Read Measuring Value (1time_min avg / 1time_min update)
*/
int addr = 0x1B;
byte buffer[2] = {0,0};

void setup() {
  BT.begin(9600);
  Serial.begin(9600);
  Wire.begin();
  Gamma_Mod_Read(0xA0);
}

void loop() {
  BT.write(20);
  if(BT.available()){
    Serial.write(BT.read());
  }
  if(Serial.available()){
    BT.write(Serial.read());
  }
  delay(1000);
  Gamma_Mod_Read(0xB3);
}

void Gamma_Mod_Read(int cmd){
  Wire.beginTransmission(addr);
  Wire.write(cmd);
  Wire.endTransmission();
  delay(10);

  Wire.requestFrom(addr, 2);
  byte i = 0;
  
  while(Wire.available())
  {
    buffer[i] = Wire.read();
    i++;
  }

  Print_Result(cmd);
}

void Print_Result(int cmd){
  float value = 0.0f;
  switch(cmd){    
    case 0xB3:
      value = buffer[0] + (float)buffer[1]*5;
      if(value != 0.00){
        Serial.println(value);
        BT.print(value);
      }
    break;
  }
}
