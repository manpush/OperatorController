#include "settings.h"
#include <Arduino.h>
#include <I2Cdev.h>
#include "nRF24L01.h"
#include "globalVariables.h"


void setup() {

    Serial.begin(9600);
//    Serial.println(1);

    Wire.begin();

#ifdef MPU1
    Mpu1 = new MPUGyro(MPU1);

#endif

#ifdef MPU2
    Mpu2 = new MPUGyro(MPU2);
#endif

#ifdef MPU3
    Mpu3 = new MPUGyro(MPU3);
#endif

 Gyro = new GyroSender(CE, CSN);

#ifdef MPU1
    Gyro->_gyroList.push(Mpu1);
#endif
#ifdef MPU2
    Gyro._gyroList.push(Mpu2);
#endif
#ifdef MPU3
    Gyro._gyroList.push(Mpu3);
#endif

}

void loop() {
    Mpu1->tick();
    Gyro->tick();
//    Mpu1->printPlot();
}