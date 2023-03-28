//
// Created by Max on 17.02.2023.
//
#include <Arduino.h>
#include <helper_3dmath.h>
#include "MPUGyro.h"

MPUGyro::MPUGyro(int ADOpin) {
    Serial.println(122);
    _mpuObject = (MPU6050(0x69));
    ADO_pin = ADOpin;
    pinMode(ADO_pin, OUTPUT);
    digitalWrite(ADO_pin, 1);
    _mpuObject.initialize();
    _mpuObject.dmpInitialize();
    _mpuObject.setDMPEnabled(true);
    _mpuObject.CalibrateGyro(10);
    countFlips[0]=0;
    countFlips[1]=0;
    countFlips[2]=0;
    if (_mpuObject.dmpGetCurrentFIFOPacket(fifoBuffer)) {
        Quaternion q;
        VectorFloat gravity;
        float ypr[3];
        // расчёты
        _mpuObject.dmpGetQuaternion(&q, fifoBuffer);
        _mpuObject.dmpGetGravity(&gravity, &q);
        _mpuObject.dmpGetYawPitchRoll(ypr, &q, &gravity);
        data[0] = degrees(ypr[0]);
        data[1] = degrees(ypr[1]);
        data[2] = degrees(ypr[2]);
    }
    _timer = millis();  // сброс таймера
    digitalWrite(ADO_pin, 0);
}

void MPUGyro::tick() {
    if (millis() - _timer >= 11) {  // таймер на 11 мс (на всякий случай)
        digitalWrite(ADO_pin, 1);
        if (_mpuObject.dmpGetCurrentFIFOPacket(fifoBuffer)) {
            Quaternion q;
            VectorFloat gravity;
            float ypr[3];
            // расчёты
            _mpuObject.dmpGetQuaternion(&q, fifoBuffer);
            _mpuObject.dmpGetGravity(&gravity, &q);
            _mpuObject.dmpGetYawPitchRoll(ypr, &q, &gravity);
            for (int i=0;i<3;i++) { //проверка на количество оборотов по всем осям
                if (data[i] > 170 && degrees(ypr[i]) < -170) {
                    countFlips[i]++;
                } else if ((degrees(ypr[i]) > 170 && data[i] < -170)){
                    countFlips[i]--;
                }
            }
            data[0] = degrees(ypr[0]);
            data[1] = degrees(ypr[1]);
            data[2] = degrees(ypr[2]);
        }
        _timer = millis();  // сброс таймера
        digitalWrite(ADO_pin, 0);
    }
}

void MPUGyro::print() {
    Serial.print("X - "); Serial.print(data[0]);Serial.print(" - "); Serial.println(countFlips[0]);
    Serial.print("Y - "); Serial.print(data[1]);Serial.print(" - "); Serial.println(countFlips[1]);
    Serial.print("Z - "); Serial.print(data[2]);Serial.print(" - "); Serial.println(countFlips[2]);
    Serial.println();
}

void MPUGyro::printPlot() {
    Serial.print(data[0] + countFlips[0]*360); Serial.print(" ");
    Serial.print(data[1]+ countFlips[1]*360); Serial.print(" ");
    Serial.println(data[2]+ countFlips[2]*360);
}



