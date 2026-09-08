#include <AFMotor.h>

AF_DCMotor motorL(1); 
AF_DCMotor motorR(2);

// --- PID Constants ---
float Kp = 30;   // Increased Kp for faster reaction on edges
float Ki = 0;    
float Kd =60;   // Increased Kd to prevent overshooting after a sharp turn

// --- Speed Settings ---
int baseSpeed = 140; // Slightly lower base speed gives sensors more time to react
int maxSpeed = 255;  
int pivotSpeed = 220; // High speed for sharp 90-degree pivots

// --- Variables ---
float error = 0, lastError = 0;
float turnValue = 0;
int lastDirection = 0; // 1 for Right, -1 for Left

const int sensors[5] = {A0, A1, A2, A3, A4};

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 5; i++) pinMode(sensors[i], INPUT);

  motorL.setSpeed(baseSpeed);
  motorR.setSpeed(baseSpeed);
  
  // Startup Test
  motorL.run(FORWARD); motorR.run(FORWARD);
  delay(500);
  motorL.run(RELEASE); motorR.run(RELEASE);
}

void loop() {
  int v[5];
  bool onLine = false;

  for (int i = 0; i < 5; i++) {
    v[i] = digitalRead(sensors[i]);
    if (v[i] == 1) onLine = true;
  }

  // 1. SHARP EDGE OVERRIDE (Priority 1)
  // If only the far-left or far-right sensors hit, force a maximum pivot
  if (v[0] == 1 && v[1] == 0) {
    error = -2;
    lastDirection = -1; 
  }
  else if (v[4] == 1 && v[3] == 0) {
    error = 2;
    lastDirection = 1;
  }
  // 2. NORMAL PID WEIGHTING
  else if (v[1] == 1) error = -1;
  else if (v[3] == 1) error = 1;
  else if (v[2] == 1) error = 0;

  if (onLine) {
    // PID Calculation
    float derivative = error - lastError;
    turnValue = (Kp * error) + (Kd * derivative);
    lastError = error;

    int leftMotorSpeed = baseSpeed + turnValue;
    int rightMotorSpeed = baseSpeed - turnValue;

    // SHARP DIRECTION LOGIC
    if (error <= -1.5) { // Sharp Left Pivot
      motorL.setSpeed(pivotSpeed);
      motorR.setSpeed(pivotSpeed);
      motorL.run(BACKWARD);
      motorR.run(FORWARD);
    } 
    else if (error >= 1.5) { // Sharp Right Pivot
      motorL.setSpeed(pivotSpeed);
      motorR.setSpeed(pivotSpeed);
      motorL.run(FORWARD);
      motorR.run(BACKWARD);
    } 
    else { // PID Smooth Steering
      motorL.setSpeed(constrain(leftMotorSpeed, 0, maxSpeed));
      motorR.setSpeed(constrain(rightMotorSpeed, 0, maxSpeed));
      motorL.run(FORWARD);
      motorR.run(FORWARD);
    }
  } 
  else {
    // 3. MEMORY MODE: If line is lost, spin in the last known direction to find it
    if (lastDirection == -1) {
      motorL.setSpeed(pivotSpeed); motorR.setSpeed(pivotSpeed);
      motorL.run(BACKWARD); motorR.run(FORWARD);
    } 
    else if (lastDirection == 1) {
      motorL.setSpeed(pivotSpeed); motorR.setSpeed(pivotSpeed);
      motorL.run(FORWARD); motorR.run(BACKWARD);
    } 
    else {
      stopRobot();
    }
  }
}

void stopRobot() {
  motorL.run(RELEASE);
  motorR.run(RELEASE);
}
