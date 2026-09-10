# PID-Based Line Follower Robot

An autonomous line-following robot built using Arduino, an Adafruit Motor Shield, five IR line sensors, and two DC motors. The robot uses PD control to continuously detect and follow a black line while handling curves, sharp turns, and temporary line loss.

---

## 📌 Project Overview

The objective of this project is to design and develop an autonomous line follower robot capable of following a predefined black path without manual control.

Five IR line sensors are arranged at the front of the robot to detect the position of the line. Based on the sensor readings, the controller calculates the deviation of the robot from the desired path and adjusts the speed of the left and right motors accordingly.

A **Proportional-Derivative (PD) control algorithm** is used to achieve responsive and stable steering. Additional logic is implemented for sharp turns and line-loss recovery.

---

## ✨ Features

- 5-sensor IR line detection
- PD-based steering control
- Adjustable proportional and derivative gains
- Smooth correction during normal line tracking
- Sharp 90° turn handling
- High-speed pivot control
- Last-direction memory for line-loss recovery
- Motor speed limiting
- Autonomous operation
- Tested on curved line-following tracks

---

## 🔧 Hardware Components

| Component | Quantity |
|---|---:|
| Arduino-compatible microcontroller | 1 |
| Adafruit Motor Shield | 1 |
| DC Motors | 2 |
| IR Line Sensors | 5 |
| Robot Chassis | 1 |
| Battery / Power Supply | 1 |
| Connecting Wires | As required |

---

## 💻 Software & Libraries

- **Arduino IDE**
- **Arduino C/C++**
- **Adafruit Motor Shield Library (`AFMotor`)**

---

## ⚙️ Control Parameters

The current controller uses the following parameters:

| Parameter | Value |
|---|---:|
| Kp | 30 |
| Ki | 0 |
| Kd | 60 |
| Base Speed | 140 |
| Pivot Speed | 220 |
| Maximum Speed | 255 |

> **Note:** Although `Ki` is defined in the program, the current implementation does not accumulate an integral term. Therefore, the implemented controller is effectively a **PD controller**.

---

## 🧠 Working Principle

The five IR sensors continuously monitor the surface beneath the robot and determine the position of the black line.

The sensor arrangement can be represented as:

```text
S1    S2    S3    S4    S5
 |     |     |     |     |
 ←──────── LINE ─────────→
