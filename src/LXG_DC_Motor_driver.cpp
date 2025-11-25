#include "LXG_DC_Motor_driver.h"

// Constructor
LXG_Motor::LXG_Motor()
    : _speed(0), _isAttached(false), _isStarted(false), _movingForward(false),
      _isMoving(false) {}

// Destructor
LXG_Motor::~LXG_Motor() { stop(); }

// Attach motor to pins
void LXG_Motor::attach(int enablePin, int forwardPin, int backwardPin) {
  if (_isAttached) {
    Serial.println(F("Motor already attached"));
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

// Toggle motor on/off
void LXG_Motor::toggle() {
  if (_isStarted) {
    stop();
  } else {
    start();
  }
}

// Start motor with default settings
void LXG_Motor::start() {
  if (!_isAttached) {
    Serial.println(F("Error: Motor not attached"));
    return;
  }

  if (_isStarted) {
    Serial.println(F("Motor already running"));
    return;
  }

  _speed = 255;
  _isStarted = true;
  _isMoving = false;

  digitalWrite(FORWARD, LOW);
  digitalWrite(BACKWARD, LOW);
  analogWrite(ENABLE, _speed);
}

// Start motor with specific speed
void LXG_Motor::start(int initialSpeed) {
  if (!_isAttached) {
    Serial.println(F("Error: Motor not attached"));
    return;
  }

  if (_isStarted) {
    Serial.println(F("Motor already running"));
    return;
  }

  _speed = constrain(initialSpeed, 0, 255);
  _isStarted = true;
  _isMoving = false;

  digitalWrite(FORWARD, LOW);
  digitalWrite(BACKWARD, LOW);
  analogWrite(ENABLE, _speed);
}

// Move motor forward
void LXG_Motor::forward() {
  if (!_isAttached) {
    Serial.println(F("Error: Motor not attached"));
    return;
  }

  if (!_isStarted) {
    Serial.println(F("Error: Motor not started. Call start() first."));
    return;
  }

  _movingForward = true;
  _isMoving = true;
  digitalWrite(FORWARD, HIGH);
  digitalWrite(BACKWARD, LOW);
}

// Move motor backward
void LXG_Motor::reverse() {
  if (!_isAttached) {
    Serial.println(F("Error: Motor not attached"));
    return;
  }

  if (!_isStarted) {
    Serial.println(F("Error: Motor not started. Call start() first."));
    return;
  }

  _movingForward = false;
  _isMoving = true;
  digitalWrite(FORWARD, LOW);
  digitalWrite(BACKWARD, HIGH);
}

// Stop motor
void LXG_Motor::stop() {
  if (!_isStarted)
    return;

  analogWrite(ENABLE, 0);
  digitalWrite(FORWARD, LOW);
  digitalWrite(BACKWARD, LOW);

  _isStarted = false;
  _isMoving = false;
  _speed = 0;
}

// Set motor speed (0-255)
void LXG_Motor::setSpeed(int newSpeed) {
  if (!_isAttached) {
    Serial.println(F("Error: Motor not attached"));
    return;
  }

  _speed = constrain(newSpeed, 0, 255);

  if (_isStarted) {
    analogWrite(ENABLE, _speed);
  }
}

// Accelerate motor
void LXG_Motor::accelerate(int increment) {
  if (!_isAttached || !_isStarted)
    return;

  _speed = constrain(_speed + increment, 0, 255);
  analogWrite(ENABLE, _speed);
}

// Decelerate motor
void LXG_Motor::brake(int decrement) {
  if (!_isAttached || !_isStarted)
    return;

  _speed = constrain(_speed - decrement, 0, 255);
  analogWrite(ENABLE, _speed);

  // Auto-stop if speed reaches 0
  if (_speed == 0) {
    stop();
  }
}

// get current speed
int LXG_Motor::speed() const { return _speed; }

// Check if motor is attached
bool LXG_Motor::isReady() const { return _isAttached; }

// Check if motor is started
bool LXG_Motor::isRunning() const { return _isStarted; }

// Check if motor is moving in any direction
bool LXG_Motor::isMoving() const { return _isMoving; }

// Check if motor is moving forward
bool LXG_Motor::isMovingForward() const { return _isMoving && _movingForward; }

// Check if motor is moving backwards
bool LXG_Motor::isReversing() const { return _isMoving && !_movingForward; }