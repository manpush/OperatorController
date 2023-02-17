//
// Created by Max on 17.02.2023.
//
#include <Arduino.h>
#include <helper_3dmath.h>
#include "MPUGyro.h"

MPUGyro::MPUGyro(uint8_t ADOpin) {
    _mpuObject = (MPU6050(0x69));
    ADO_pin = ADOpin;
    _mpuObject.initialize();
    _mpuObject.dmpInitialize();
    _mpuObject.setDMPEnabled(true);
    _mpuObject.CalibrateGyro(10);
    pinMode(ADO_pin, OUTPUT);
    digitalWrite(ADO_pin, 1);
    if (_mpuObject.dmpGetCurrentFIFOPacket(fifoBuffer)) {
        Quaternion q;
        VectorFloat gravity;
        float ypr[3];
        // расчёты
        _mpuObject.dmpGetQuaternion(&q, fifoBuffer);
        _mpuObject.dmpGetGravity(&gravity, &q);
        _mpuObject.dmpGetYawPitchRoll(ypr, &q, &gravity);
        memcpy(data, ypr, sizeof(ypr));
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
                if (degrees(data[i]) > 170 && degrees(ypr[i]) < -170) {
                    countFlips[i]++;
                } else if ((degrees(ypr[i]) > 170 && degrees(data[i]) < -170)){
                    countFlips[i]--;
                }
            }
            memcpy(data, ypr, sizeof(ypr));
        }
        _timer = millis();  // сброс таймера
        digitalWrite(ADO_pin, 0);
    }
}

void MPUGyro::print(HardwareSerial serial) {
    serial.print("X - "); serial.print(data[0]);serial.print(" - "); serial.println(countFlips[0]);
    serial.print("Y - "); serial.print(data[1]);serial.print(" - "); serial.println(countFlips[1]);
    serial.print("Z - "); serial.print(data[2]);serial.print(" - "); serial.println(countFlips[2]);
    serial.println();
}

void MPUGyro::printPlot(HardwareSerial serial) {
    serial.print(data[0]); serial.print(" ");
    serial.print(data[1]); serial.print(" ");
    serial.println(data[2]);
}



