//
// Created by Max on 16.02.2023.
//

#ifndef OPRATORCONTROLLER_GLOBALVARIABLES_H
#define OPRATORCONTROLLER_GLOBALVARIABLES_H


#include <Arduino.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "settings.h"
#include "../lib/MPUGyro/src/MPUGyro.h"
#include "../lib/GyroSenderRF24/src/GyroSender.h"
#include <stdlib.h>

/* объекты гироскопов */
#ifdef MPU1
MPUGyro * Mpu1;
#endif

#ifdef MPU2
MPUGyro * Mpu2;
#endif

#ifdef MPU3
MPUGyro * Mpu3;
#endif
/* объект пеердатчика данных */
GyroSender * Gyro;

#endif //OPRATORCONTROLLER_GLOBALVARIABLES_H
