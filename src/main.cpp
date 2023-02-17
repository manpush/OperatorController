#include "settings.h"
#include <Arduino.h>
#include <I2Cdev.h>
#include "MPU6050_6Axis_MotionApps20.h"
#include "nRF24L01.h"
#include "globalVariables.h"


void setup() {
    Serial.begin(9600);
    Wire.begin();
}

void loop() {
    Mpu1.tick();
    Gyro.tick();
}