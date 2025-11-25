#include <LXG_DC_Motor_driver.h>

// Define motor control pins
const int ENABLE_PIN = 9;
const int FORWARD_PIN = 8;
const int BACKWARD_PIN = 7;

// Create a motor instance
LXG_Motor myMotor;

void setup() {
  Serial.begin(9600);
  
  // Attach the motor to its control pins
  myMotor.attach(ENABLE_PIN, FORWARD_PIN, BACKWARD_PIN);
  
  // Start the engine (enables it but does not move it yet)
  // Think of this as turning the key in a car
  myMotor.start(); 
}

void loop() {
  Serial.println("Shifting to Drive and accelerating...");
  myMotor.forward(); // Shift to Drive
  for (int i = 0; i < 5; i++) {
    myMotor.accelerate(50); // Accelerate
    delay(500);
    Serial.print("Speed: ");
    Serial.println(myMotor.currentSpeed());
  }
  
  Serial.println("Decelerating...");
  for (int i = 0; i < 5; i++) {
    myMotor.decelerate(50); // Decelerate
    delay(500);
    Serial.print("Speed: ");
    Serial.println(myMotor.currentSpeed());
  }

  Serial.println("Braking...");
  myMotor.brake(); // Full stop and shift to Park
  delay(2000);
  
  Serial.println("Shifting to Reverse and accelerating...");
  myMotor.reverse(); // Shift to Reverse
  myMotor.setSpeed(150); // Set a specific speed
  delay(2000);

  Serial.println("Stopping the engine.");
  myMotor.stop(); // Turn off the engine
  delay(2000);
}