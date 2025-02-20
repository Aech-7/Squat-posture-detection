#include <Wire.h>
#include "SparkFun_BNO080_Arduino_Library.h" 
BNO080 myIMU;

const int buzzer = 9;
const int LED_GREEN = 8;
const int LED_RED = 7;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("BNO080 Read Example");

  Wire.begin();

  if (myIMU.begin() == false)
  {
    Serial.println(F("BNO080 not detected at default I2C address. Check your jumpers and the hookup guide. Freezing..."));
    while (1)
      ;
  }

  Wire.setClock(400000); 
  myIMU.enableRotationVector(50); 

  Serial.println(F("Rotation vector enabled"));
  Serial.println(F("Output in form roll, pitch, yaw"));

  pinMode(buzzer, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
}

void loop()
{

  if (myIMU.dataAvailable() == true)
  {
    float roll = (myIMU.getRoll()) * 180.0 / PI; 
    float pitch = (myIMU.getPitch()) * 180.0 / PI; 
    float yaw = (myIMU.getYaw()) * 180.0 / PI; 

 
    Serial.print("Pitch: ");
    Serial.print(pitch, 1);
    Serial.println();

    int plotValue = 0; 


    if (pitch < 15)
    {
      Serial.println("Incorrect Squat Detected!");
      tone(buzzer, 1000);
      digitalWrite(LED_RED, HIGH);
      delay(1000);
      noTone(buzzer);
      digitalWrite(LED_RED, LOW);
      plotValue = -1;
    }
 
    else if ( pitch <= 10)
    {
      Serial.println("Incorrect Squat Detected (Range 5-10)");
      tone(buzzer, 1000);
      digitalWrite(LED_RED, HIGH);
      delay(1000);
      noTone(buzzer);
      digitalWrite(LED_RED, LOW);
      plotValue = -2; 
    }
   
    else
    {
      Serial.println("Correct Squat Detected!");
      digitalWrite(LED_GREEN, HIGH);
      delay(500);
      digitalWrite(LED_GREEN, LOW);
      plotValue = 1; 
    }


    Serial.print("Plot: ");
    Serial.println(plotValue); 

    delay(100); 
  }
}
