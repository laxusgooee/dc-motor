#ifndef LXG_DC_MOTOR_DRIVER_H
#define LXG_DC_MOTOR_DRIVER_H

#include "Arduino.h"

enum Gear { PARK, DRIVE, REVERSE };

class LXG_Motor {
private:
  int ENABLE;
  int FORWARD;
  int BACKWARD;
  int _speed;
  bool _isAttached;
  bool _isStarted;
  Gear _gear;

public:
  // Constructor
  LXG_Motor();

  // Destructor
  ~LXG_Motor();

  // Attach motor to pins
  void attach(int enablePin, int forwardPin, int backwardPin);

  // Start engine (doesn't move the car)
  void start();

  // Stop engine (turn off completely)
  void stop();

  // Shift to Drive (forward gear)
  void forward();

  // Shift to Reverse
  void reverse();

  // Press accelerator (increases speed)
  void accelerate(int increment = 25);

  // Ease off accelerator (reduces speed gradually)
  void decelerate(int decrement = 25);

  // Apply brake (stops car and shifts to PARK)
  void brake();

  // Set specific speed (direct control - like cruise control)
  void setSpeed(int newSpeed);

  // Get current gear
  Gear currentGear() const;

  // Get current speed
  int currentSpeed() const;

  // Check if motor is attached
  bool isReady() const;

  // Check if engine is running
  bool isRunning() const;

  // Check if driving forward
  bool isDriving() const;

  // Check if reversing
  bool isReversing() const;

  // Check if in park
  bool isParked() const;
};

#endif