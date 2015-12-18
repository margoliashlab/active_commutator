/* 
 *  Copyright 2015 Kyler Brown
 *  This program is distributed under the terms of the 
 *  GNU General Public License 
 */

#include <Servo.h>

int servopin = 9;
Servo myservo;  // create servo object to control a servo
int estimate = 0;
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  myservo.attach(servopin);  // attaches the servo on pin 9 to the servo object
}

float middle = 500.0;
float velocity_multiplier = .08;
int max_pos_speed = 110;
int max_neg_speed = 70;
int min_speed = 2 ;
// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  estimate = sensorValue * 0.5 + estimate * 0.5;
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  // print out the value you read:
  
  int servo_command = velocity_multiplier * (middle - estimate);
  if (servo_command > max_pos_speed){
    //servo_command = max_pos_speed;
  }
  else if (servo_command < max_neg_speed){
    //servo_command = max_neg_speed;
  }

  if ( abs(servo_command) < min_speed){
    myservo.detach();
  }
  else{
    myservo.attach(servopin);
    myservo.write(servo_command+90);
  }
  Serial.println(servo_command);
}
