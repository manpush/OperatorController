//
// Created by Max on 17.02.2023.
//

#ifndef OPRATORCONTROLLER_GYROSENDER_H
#define OPRATORCONTROLLER_GYROSENDER_H
#include <Arduino.h>
#include <RF24.h>
#include "../../OptiList/src/OptiList.h"


class GyroSender {
public:
    GyroSender();
    void tick();
    void createPkg(uint8_t val[9]);
private:
    uint32_t send_data_tmr;
    RF24 radio;
    byte address[6][6];
    OptiList _gyroList;
};


#endif //OPRATORCONTROLLER_GYROSENDER_H
