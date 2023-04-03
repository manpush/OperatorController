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
    GyroSender(int ce, int csn);
    void tick();
    void createPkg(int val[9]);
    OptiList _gyroList; //список гироскопов
private:
    uint32_t send_data_tmr; //переменная таймера
    RF24 radio; // объект радиомодуля
    byte address[6][6]; //массив каналов передачи (нужен для библиотеки RF24)

};


#endif //OPRATORCONTROLLER_GYROSENDER_H
