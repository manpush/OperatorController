//
// Created by Max on 16.02.2023.
//

#ifndef OPERATOR_CONTROLLER_SETTINGS_H
#define OPERATOR_CONTROLLER_SETTINGS_H

#define MPU1 A2
//#define mpu2 A1
//#define mpu3 A0

#ifdef MPU1
MPU6050 mpu1(0x69);
#endif

#ifdef MPU2
MPU6050 mpu2(0x69);
#endif

#ifdef MPU3
MPU6050 mpu3(0x69);
#endif

#ifdef MPU1
float ypr1[3][2];
#endif

#ifdef MPU2
float ypr2[3][2];
#endif

#ifdef MPU3
float ypr3[3][2];
#endif

#ifdef MPU1
uint8_t fifoBuffer1[45];
#endif

#ifdef MPU2
uint8_t fifoBuffer2[45];
#endif

#ifdef MPU3
uint8_t fifoBuffer3[45];
#endif

#ifdef MPU1
uint32_t tmr1;
#endif

#ifdef MPU2
uint32_t tmr2;
#endif

#ifdef MPU3
uint32_t tmr3;
#endif
#endif //OPERATOR_CONTROLLER_SETTINGS_H
