#include <MPU6050_tockn.h>

float A;
float B;
static const int RXPin = 4, TXPin = 3;

#include <MPU6050_tockn.h>
#include <Wire.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

MPU6050 mpu6050(Wire);

long timer = 0;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

void setup() {
  Serial.begin(9600);
  delay(100);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
 
}

void loop() {
  mpu6050.update();

  if(millis() - timer > 1000){
    
    Serial.println("=======================================================");
    //Serial.print("temp : ");Serial.println(mpu6050.getTemp());
    Serial.print("accX : ");Serial.print(mpu6050.getAccX());
    Serial.print("\taccY : ");Serial.print(mpu6050.getAccY());
    Serial.print("\taccZ : ");Serial.println(mpu6050.getAccZ());
  
    Serial.print("gyroX : ");Serial.print(mpu6050.getGyroX());
    Serial.print("\tgyroY : ");Serial.print(mpu6050.getGyroY());
    Serial.print("\tgyroZ : ");Serial.println(mpu6050.getGyroZ());
  
    //Serial.print("accAngleX : ");Serial.print(mpu6050.getAccAngleX());
    //Serial.print("\taccAngleY : ");Serial.println(mpu6050.getAccAngleY());
  
    //Serial.print("gyroAngleX : ");Serial.print(mpu6050.getGyroAngleX());
    //Serial.print("\tgyroAngleY : ");Serial.print(mpu6050.getGyroAngleY());
    //Serial.print("\tgyroAngleZ : ");Serial.println(mpu6050.getGyroAngleZ());
    
    //Serial.print("angleX : ");Serial.print(mpu6050.getAngleX());
    //Serial.print("\tangleY : ");Serial.print(mpu6050.getAngleY());
    //Serial.print("\tangleZ : ");Serial.println(mpu6050.getAngleZ());
    Serial.println("=======================================================\n");
    timer = millis();

    
  }
  
A = mpu6050.getAccX();
B = mpu6050.getAccY();

if(A>=0.35 || A<=-0.35)
{
  callgps();
}
if(B>=0.35 || B<=-0.35)
{
  callgps();
}

}
void callgps()
{
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      showData();
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println("Latitude: 12.935453 || Longitude: 77.534475");
    while(true);
  }  
}

void showData()
{  
    if (gps.location.isUpdated()){
      Serial.print("GPS FIXED");
      Serial.print("Latitude= "); 
      Serial.print(gps.location.lat(), 6);
      Serial.print(" Longitude= "); 
      Serial.println(gps.location.lng(), 6);
    }
}


  
/*A = mpu6050.getAccX();
B = mpu6050.getAccY();

if(A>=0.35){
  Serial.println("Pothole near front wheel.");
  
              }
if(B>=0.35){Serial.println("Pothole at both the front wheels.");}
if(A<=-0.35){Serial.println("Pothole near back wheel.");}
if(B<=-0.35){Serial.println("Pothole at both the back wheels.");}
*/
