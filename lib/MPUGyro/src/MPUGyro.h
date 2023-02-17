//
// Created by Max on 17.02.2023.
//

#ifndef OPRATORCONTROLLER_MPUGYRO_H
#define OPRATORCONTROLLER_MPUGYRO_H


#include "MPU6050_6Axis_MotionApps20.h"

class MPUGyro {
public:
    MPUGyro(uint8_t ADOpin);
    void print(HardwareSerial serial);
    void printPlot(HardwareSerial serial);
    void tick();
    uint8_t ADO_pin;
    uint8_t data[3];
private:
    MPU6050 _mpuObject;
    uint32_t _timer;
    uint8_t fifoBuffer[45];
    uint8_t countFlips[3];
};


#endif //OPRATORCONTROLLER_MPUGYRO_H
