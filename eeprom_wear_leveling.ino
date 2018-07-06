#include <EEPROM.h>

int address = 1;
int maxAddr = 512;
byte openByte = 100;
byte closeByte = 200;
byte data[5];
int value = 0;
boolean found = true;

unsigned long previousMillis = 0;
const long interval = 10000; // 1 sec

void setup() {
  Serial.begin(115200);
  Serial.println("START..");
  while (EEPROM.read(address) != openByte && EEPROM.read(address+4) != closeByte) {
    address++;
    Serial.print("Block:");Serial.println(address);
    if (address > maxAddr) {
      Serial.print("No data found");
      found = false;
      break;
    }  
 }
  delay(3000);
  if (found == true) {
    Serial.println("Data found, read out");
    for (int j=0;j<5;j++) {
      data[j] = EEPROM.read(address+j);
      Serial.print("Block:");Serial.print(address+j);Serial.print(" Data:");Serial.println(data[j]);
    }
  }
  delay(3000);
  

}

void loop() {
  unsigned long currentMillis = millis();
///////////////// EEPROM ////
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
  Serial.print("ADDR:");Serial.print(address);
  Serial.print(" DATA:");
  for (int k=0;k<5;k++) {
    Serial.print(data[k]);
    Serial.print(",");
  }
  Serial.println(" ");  

// WRITE TO EEPROM PERIODIC///
  Serial.print("Write new data");
  EEPROM.write(address, 0);
  EEPROM.write(address+1, openByte);
  EEPROM.write(address+2, 5);
  EEPROM.write(address+3, 10);
  EEPROM.write(address+4, 15);
  EEPROM.write(address+5, closeByte);

 }
//////////////////////////////

}
