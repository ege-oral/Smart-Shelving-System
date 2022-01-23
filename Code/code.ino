// For ultrasonic sensor
#include "NewPing.h"
// For weight sensor
#include "HX711.h"
// For stepper motor
#include <Stepper.h> 

// Variables for ultrasonic sensor.
float distance;
int MAX_DISTANCE = 30;
int ultrasonic_trigger_pin = 8;
int ultrasonic_eco_pin = 9;
NewPing sonar(ultrasonic_trigger_pin, ultrasonic_eco_pin, MAX_DISTANCE);

// Variables for weight sensor.
float calibration_factor = 807;
float weight;
int weight_sensor_pin1 = 5;
int weight_sensor_pin2 = 4;
HX711 scale;

// Variables for stepper motor.
int stepsPerRevolution = 100;
int stepperMotorSpeed = 50;
Stepper myStepper(stepsPerRevolution, 13, 12, 11, 10);

void setup() 
{
  Serial.begin(9600);
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");
  scale.begin(weight_sensor_pin1,weight_sensor_pin2);
  scale.set_scale();
  scale.tare();
  myStepper.setSpeed(stepperMotorSpeed);
}
void loop() 
{
  scale.set_scale(calibration_factor); 
  weight = scale.get_units();
  Serial.print("Weight: ");
  Serial.print(weight);
  Serial.print(" grams"); 
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();
  
  if(weight <= 2){
    Serial.println("There is no ITEM on the platform.");
  }
  else{
    distance = sonar.ping_cm();
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println(" cm");
    if(distance <= 5 && distance >= 1){
      Serial.println("THERE IS AN OBJECT");
    }
    else{
      myStepper.step(stepsPerRevolution);
      Serial.println();
    }
  }
  delay(1000);

  // For calibration purposes
  
  if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      calibration_factor += 1;
    else if(temp == '-' || temp == 'z')
      calibration_factor -= 1;
  }
  
}
