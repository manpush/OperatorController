//
// Created by Max on 16.02.2023.
//
#include <Arduino.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "settings.h"
#include "../lib/MPUGyro/src/MPUGyro.h"
#include "../lib/GyroSenderRF24/src/GyroSender.h"

#ifdef MPU1
MPUGyro Mpu1(MPU1);
#endif

#ifdef MPU2
MPUGyro mpu2(MPU2);
#endif

#ifdef MPU3
MPUGyro mpu3(MPU3);
#endif

GyroSender Gyro();


                                                          // модуль связи на пинах 9 и 10
