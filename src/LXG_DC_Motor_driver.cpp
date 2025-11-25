#include "LXG_DC_Motor_driver.h"

// Constructor
LXG_Motor::LXG_Motor()
    : _speed(0), _isAttached(false), _isStarted(false), _gear(PARK) {}

// Destructor
LXG_Motor::~LXG_Motor() { stop(); }

// Attach motor to pins
void LXG_Motor::attach(int enablePin, int forwardPin, int backwardPin) {
  if (_isAttached) {
    return;
  }

  ENABLE = enablePin;
  FORWARD = forwardPin;
  BACKWARD = backwardPin;

  pinMode(ENABLE, OUTPUT);
  pinMode(FORWARD, OUTPUT);
  pinMode(BACKWARD, OUTPUT);

  // Initialize all pins to LOW
  analogWrite(ENABLE, 0);
  digitalWrite(FORWARD, LOW);
  digitalWrite(BACKWARD, LOW);

  _isAttached = true;
}

// Start engine (doesn't move the car)
void LXG_Motor::start() {
  if (!_isAttached || _isStarted) {
    return;
  }

  _isStarted = true;
  _speed = 0;
  _gear = PARK;

  digitalWrite(FORWARD, LOW);
  digitalWrite(BACKWARD, LOW);
  analogWrite(ENABLE, 0);
}

// Stop engine (turn off completely)
void LXG_Motor::stop() {
  if (!_isStarted) {
    return;
  }

  analogWrite(ENABLE, 0);
  digitalWrite(FORWARD, LOW);
  digitalWrite(BACKWARD, LOW);

  _isStarted = false;
  _speed = 0;
  _gear = PARK;
}

// Shift to Drive (forward gear)
void LXG_Motor::forward() {
  if (!_isAttached || !_isStarted) {
    return;
  }

  // Can only shift when completely stopped
  if (!isParked() && _speed > 0) {
    return;
  }

  _gear = DRIVE;
  digitalWrite(FORWARD, HIGH);
  digitalWrite(BACKWARD, LOW);
}

// Shift to Reverse
void LXG_Motor::reverse() {
  if (!_isAttached || !_isStarted) {
    return;
  }

  // Can only shift when completely stopped
  if (!isParked() && _speed > 0) {
    return;
  }

  _gear = REVERSE;
  digitalWrite(FORWARD, LOW);
  digitalWrite(BACKWARD, HIGH);
}

// Press accelerator (increases speed)
void LXG_Motor::accelerate(int increment) {
  if (!_isAttached || !_isStarted || _gear == PARK) {
    return;
  }

  _speed = constrain(_speed + increment, 0, 255);
  analogWrite(ENABLE, _speed);
}

// Ease off accelerator (reduces speed gradually)
void LXG_Motor::decelerate(int decrement) {
  if (!_isAttached || !_isStarted || _gear == PARK) {
    return;
  }

  _speed = constrain(_speed - decrement, 0, 255);
  analogWrite(ENABLE, _speed);
}

// Apply brake (stops car and shifts to PARK)
void LXG_Motor::brake() {
  if (!_isAttached || !_isStarted) {
    return;
  }

  // Immediate stop
  _speed = 0;
  _gear = PARK;

  digitalWrite(FORWARD, LOW);
  digitalWrite(BACKWARD, LOW);
  analogWrite(ENABLE, 0);
}

// Set specific speed (direct control - like cruise control)
void LXG_Motor::setSpeed(int newSpeed) {
  if (!_isAttached || !_isStarted || _gear == PARK) {
    return;
  }

  _speed = constrain(newSpeed, 0, 255);
  analogWrite(ENABLE, _speed);
}

// Get current gear
Gear LXG_Motor::currentGear() const { return _gear; }

// Get current speed
int LXG_Motor::currentSpeed() const { return _speed; }

// Check if motor is attached
bool LXG_Motor::isReady() const { return _isAttached; }

// Check if engine is running
bool LXG_Motor::isRunning() const { return _isStarted; }

// Check if driving forward
bool LXG_Motor::isDriving() const { return _gear == DRIVE && _speed > 0; }

// Check if reversing
bool LXG_Motor::isReversing() const { return _gear == REVERSE && _speed > 0; }

// Check if in park
bool LXG_Motor::isParked() const { return _gear == PARK; }