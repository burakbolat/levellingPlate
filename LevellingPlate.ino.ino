
#include <MPU6050_tockn.h>
#include <Wire.h>

#define motorX1 2
#define motorX2 3
#define motorY1 8
#define motorY2 9
#define motorXEnable 10
#define motorYEnable 11





double startingX = 0;
double startingY = 0;
double startingZ = 0;
double integrateX = 0;
double integrateY = 0;
double integrateZ = 0;
double error = 0.1;

int motorPower = 255;

MPU6050 mpu6050(Wire);
long timer = 0, timer1 = 0;
void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  for(int i=0; i < 2000; i++){
    mpu6050.update();
    startingX += mpu6050.getAngleX();
    startingY += mpu6050.getAngleY();
    startingZ += mpu6050.getAngleZ();
  }
    startingX /= 2000;
    startingY /= 2000;
    startingZ /= 2000;
 
/*
  startingX = 0.95;
  startingY = 5.20;
  startingZ = 0;*/
  Serial.println();
  Serial.println(startingX);
  Serial.println(startingY);
  Serial.println(startingZ);
  Serial.println();
  
}

void loop() {
  mpu6050.update();
  /*
  integrateX += mpu6050.getAngleX();
  integrateY += mpu6050.getAngleY();
  integrateZ += mpu6050.getAngleZ();
  
  if(millis()- timer > 1000){
    integrateX /= 250;
    integrateY /= 250;
    integrateZ /= 250;
    
    Serial.print("angleX : ");
    Serial.print(integrateX);
    Serial.print("\tangleY : ");
    Serial.print(integrateY);
    Serial.print("\tangleZ : ");
    Serial.println(integrateZ); 
    Serial.println("---------------------------");
    timer = millis();
  }*/
  
  if(millis()- timer > 1000){
    
    Serial.print("angleX : ");
    //Serial.print(startingX);
    Serial.print(mpu6050.getAngleX()-startingX);
    Serial.print("\tangleY : ");
    //Serial.print(startingY);
    Serial.print(mpu6050.getAngleY()-startingY);
    Serial.print("\tangleZ : ");
    //Serial.print(startingZ);
    Serial.println(mpu6050.getAngleZ()); 
    Serial.println("---------------------------");
    timer = millis();
  }

    digitalWrite(motorX1,LOW);
    digitalWrite(motorX2,LOW);
    digitalWrite(motorY1,LOW);
    digitalWrite(motorY2,LOW);
   analogWrite(motorXEnable,0);
   analogWrite(motorYEnable,0); 
  
  while(mpu6050.getAngleX() - startingX > error){
    Serial.print("error on X axis");
    Serial.println(mpu6050.getAngleX() - startingX );
    digitalWrite(motorX1,HIGH);
    digitalWrite(motorX2,LOW);
    digitalWrite(motorY1,LOW);
    digitalWrite(motorY2,LOW);
    analogWrite(motorXEnable, motorPower);
    analogWrite(motorYEnable, 0);
    mpu6050.update();
    delay(4);
  }

  while(startingX - mpu6050.getAngleX() > error){
    Serial.print("error on X axis");
    Serial.println(mpu6050.getAngleX() - startingX);
    digitalWrite(motorX1,LOW);
    digitalWrite(motorX2,HIGH);
    digitalWrite(motorY1,LOW);
    digitalWrite(motorY2,LOW);
    analogWrite(motorXEnable, motorPower);
    analogWrite(motorYEnable, 0);
    mpu6050.update();
    delay(4);
  }
  while(mpu6050.getAngleY() - startingY > error){
    //Serial.println("angle y is bigger");
    Serial.print("error on Y axis");
    Serial.println(mpu6050.getAngleY() - startingY);
    digitalWrite(motorX1,LOW);
    digitalWrite(motorX2,LOW);
    digitalWrite(motorY1,HIGH);
    digitalWrite(motorY2,LOW);
    analogWrite(motorYEnable, motorPower);
    analogWrite(motorXEnable, 0);
    mpu6050.update();
    delay(4);
  }
  while(startingY - mpu6050.getAngleY() > error){
    //Serial.println("anglex is less");
    Serial.print("error on Y axis");
    Serial.println(mpu6050.getAngleY() - startingY);
    digitalWrite(motorX1,LOW);
    digitalWrite(motorX2,LOW);
    digitalWrite(motorY1,LOW);
    digitalWrite(motorY2,HIGH);
    analogWrite(motorYEnable, motorPower);
    analogWrite(motorXEnable, 0);
    mpu6050.update();
    delay(4);
  }

  //if conditions
  /*
  if(mpu6050.getAngleX() - startingX > error){
    Serial.println(mpu6050.getAngleX() - startingX );
    digitalWrite(motorX1,HIGH);
    digitalWrite(motorX2,LOW);
    digitalWrite(motorY1,LOW);
    digitalWrite(motorY2,LOW);
    analogWrite(motorXEnable, motorPower);
    analogWrite(motorYEnable, 0);
    mpu6050.update();
    delay(4);
  }

  else if(startingX - mpu6050.getAngleX() > error){
    Serial.println(startingX - mpu6050.getAngleX());
    digitalWrite(motorX1,LOW);
    digitalWrite(motorX2,HIGH);
    digitalWrite(motorY1,LOW);
    digitalWrite(motorY2,LOW);
    analogWrite(motorXEnable, motorPower);
    analogWrite(motorYEnable, 0);
    mpu6050.update();
    delay(4);
  }
  else if(mpu6050.getAngleY() - startingY > error){
    //Serial.println("angle y is bigger");
    digitalWrite(motorX1,LOW);
    digitalWrite(motorX2,LOW);
    digitalWrite(motorY1,HIGH);
    digitalWrite(motorY2,LOW);
    analogWrite(motorYEnable, motorPower);
    analogWrite(motorXEnable, 0);
    mpu6050.update();
    delay(4);
  }
  else if(startingY - mpu6050.getAngleY() > error){
    //Serial.println("anglex is less");
    digitalWrite(motorX1,LOW);
    digitalWrite(motorX2,LOW);
    digitalWrite(motorY1,LOW);
    digitalWrite(motorY2,HIGH);
    analogWrite(motorYEnable, motorPower);
    analogWrite(motorXEnable, 0);
    mpu6050.update();
    delay(4);
  }
  */
}



