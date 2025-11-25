# LXG_DC_Motor_driver

A simple and efficient Arduino library to control DC motors using an H-bridge or similar motor driver, with a car-like interface.

## Features

- **Car-like Interface**: Control your motor like a car, with `start`, `stop`, `forward` (Drive), `reverse`, `accelerate`, `decelerate`, and `brake` commands.
- **Gear System**: Includes `PARK`, `DRIVE`, and `REVERSE` gears for intuitive control.
- **Speed Control**: Smoothly accelerate, decelerate, or set a specific speed.
- **State Tracking**: Easily query the motor's current speed, gear, and running state.
- **Lightweight**: Minimal memory and processing overhead.

## Installation

### Via Arduino Library Manager
1. Open the Arduino IDE.
2. Go to **Sketch** > **Include Library** > **Manage Libraries...**.
3. Search for `LXG_DC_Motor_driver`.
4. Click **Install**.

### Manual Installation
1. Download the latest release ZIP file from the repository.
2. Open the Arduino IDE.
3. Go to **Sketch** > **Include Library** > **Add .ZIP Library...**.
4. Select the downloaded ZIP file.

## Usage

### Wiring
Connect your motor driver (e.g., L298N) to your Arduino:
- **Enable Pin**: Connect to a PWM-capable pin (e.g., `~9`).
- **Forward Pin**: Connect to any digital pin (e.g., `8`).
- **Backward Pin**: Connect to any digital pin (e.g., `7`).

### Example Code

```cpp
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
```

## API Reference

### Setup
- `LXG_Motor()`
  The constructor. Creates a new motor object.

- `void attach(int enablePin, int forwardPin, int backwardPin)`
  Attaches the motor to the specified control pins. Must be called before any other methods.

### Core Control
- `void start()`
  Starts the engine. The motor is in `PARK` gear and does not move.

- `void stop()`
  Stops all motor activity and turns off the engine. Resets speed and gear.

### Movement
- `void forward()`
  Shifts the gear to `DRIVE`.

- `void reverse()`
  Shifts the gear to `REVERSE`.

- `void accelerate(int increment)`
  Increases the motor's current speed by a given amount.

- `void decelerate(int decrement)`
  Decreases the motor's current speed by a given amount.

- `void brake()`
  Brings the motor to a full stop and shifts the gear to `PARK`.

- `void setSpeed(int newSpeed)`
  Sets the motor's speed (0-255).

### State Queries
- `Gear currentGear() const`
  Returns the current gear (`PARK`, `DRIVE`, or `REVERSE`).

- `int currentSpeed() const`
  Returns the current speed (0-255).

- `bool isReady() const`
  Returns `true` if the motor has been attached to pins.

- `bool isRunning() const`
  Returns `true` if the engine is running.

- `bool isDriving() const`
  Returns `true` if the motor is in `DRIVE` and moving.

- `bool isReversing() const`
  Returns `true` if the motor is in `REVERSE` and moving.

- `bool isParked() const`
  Returns `true` if the motor is in `PARK`.

## License

This project is open source and available under the MIT License.