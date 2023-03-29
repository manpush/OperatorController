//
// Created by Max on 17.02.2023.
//

#ifndef OPRATORCONTROLLER_MPUGYRO_H
#define OPRATORCONTROLLER_MPUGYRO_H


#include "MPU6050_6Axis_MotionApps20.h"

class MPUGyro {
public:
    MPUGyro(int ADOpin);
    void print();
    int slice(int val, int from, int to);
    void printPlot();
    void tick();
    uint8_t ADO_pin;
    int data[3];
    int convertData[3];
    int startVal[3];
private:
    MPU6050 _mpuObject;
    uint32_t _timer;
    uint8_t fifoBuffer[45];
    int8_t countFlips[3];
    bool startValFlag;
};


#endif //OPRATORCONTROLLER_MPUGYRO_H
