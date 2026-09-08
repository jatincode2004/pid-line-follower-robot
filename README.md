# PID-Based Line Follower Robot

## Overview

A sensor-based autonomous line follower robot developed using Arduino, an Adafruit Motor Shield, five IR line sensors, and two DC motors.

The robot detects the position of a line using an array of five sensors and adjusts the speed and direction of the motors to follow the path. A PD control approach is used for smooth steering, along with dedicated logic for sharp turns and line-loss recovery.

## Features

- 5-sensor line detection
- PD-based steering control
- Adjustable proportional and derivative gains
- Sharp 90-degree turn handling
- High-speed pivot control
- Last-direction memory when the line is lost
- Motor speed limiting for stable operation

## Hardware

- Arduino-compatible microcontroller
- Adafruit Motor Shield
- 2 DC motors
- 5 digital line sensors
- Robot chassis
- Battery/power supply

## Software

- Arduino IDE
- Adafruit Motor Shield library (`AFMotor`)

## Control Parameters

| Parameter | Value |
|---|---:|
| Kp | 30 |
| Ki | 0 |
| Kd | 60 |
| Base Speed | 140 |
| Pivot Speed | 220 |
| Maximum Speed | 255 |

> Note: Although `Ki` is defined in the program, the current implementation does not accumulate an integral term. Therefore, the implemented controller is effectively a PD controller.

## How It Works

The five sensors continuously detect the position of the line.

The controller assigns an error based on which sensor detects the line:

- Left-side detection → negative error
- Center detection → zero error
- Right-side detection → positive error

The controller calculates the steering correction using the proportional and derivative terms.

For sharp left or right detection, the robot switches from smooth steering to a pivot motion. If all sensors lose the line, the robot uses the last known direction to search for the line.

## Project Structure

```text
pid-line-follower-robot/
├── README.md
└── src/
    └── line_follower.ino
