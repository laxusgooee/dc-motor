#ifndef LXG_DC_MOTOR_DRIVER_H
#define LXG_DC_MOTOR_DRIVER_H

#include "Arduino.h"

class LXG_Motor {
private:
  int ENABLE;
  int FORWARD;
  int BACKWARD;
  int _speed;
  bool _isAttached;
  bool _isStarted;
  bool _isMoving;
  bool _movingForward;

public:
  // Constructor
  LXG_Motor();

  // Destructor
  ~LXG_Motor();

  // Attach motor to pins
  void attach(int enablePin, int forwardPin, int backwardPin);

  // Toggle motor on/off
  void toggle();

  // Start motor with default settings
  void start();

  // Start motor with specific speed
  void start(int initialSpeed);

  // Move motor forward
  void forward();

  // Move motor backward
  void reverse();

  // Stop motor
  void stop();

  // Set motor speed (0-255)
  void setSpeed(int newSpeed);

  // Accelerate motor
  void accelerate(int increment = 25);

  // Decelerate motor
  void brake(int decrement = 25);

  // get current speed
  int speed() const;

  // Check if motor is attached
  bool isReady() const;

  // Check if motor is started
  bool isRunning() const;

  // Check if motor is moving in any direction
  bool isMoving() const;

  // Check if motor is moving forward
  bool isMovingForward() const;

  // Check if motor is moving backwards
  bool isReversing() const;
};

#endif
