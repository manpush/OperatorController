//
// Created by Max on 17.02.2023.
//
#include <Arduino.h>
#include <helper_3dmath.h>
#include "MPUGyro.h"

MPUGyro::MPUGyro(int ADOpin) {
    _mpuObject = (MPU6050(0x69)); //  инициализация гироскопа по адреу 0х69 (см README)
    ADO_pin = ADOpin;
    pinMode(ADO_pin, OUTPUT);
    digitalWrite(ADO_pin, 1); // выставляем ADO pin в 1 - это переведёт датчик в адрес 0х69
    _mpuObject.initialize(); //инициализация гироскопа
    _mpuObject.dmpInitialize(); //инициализация вычислительного модуля гироскопа
    _mpuObject.setDMPEnabled(true);
    _mpuObject.CalibrateGyro(10); //калибровка гироскопа в 10 проходов
    // заполнение массива оборотов по 3м осям начальными знаяениями
    countFlips[0]=0;
    countFlips[1]=0;
    countFlips[2]=0;
    startValFlag = true;// флаг для отличия первого тика от последующих
    _timer = millis();  // сброс таймера
    digitalWrite(ADO_pin, 0); //завершение работы с гироскопом
}
/**
 * Опрос датчика, вызывать как можно чаще
 */
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
            //получили данные с гироскопа прогнанные через встроенный механизм повышающий точность
            for (int i=0;i<3;i++) { //проверка на количество оборотов по всем осям
                if (data[i] > 170 && degrees(ypr[i]) < -170) {
                    countFlips[i]++;
                } else if ((degrees(ypr[i]) > 170 && data[i] < -170)){
                    countFlips[i]--;
                }
            }

            if (startValFlag){ // если это первый тик - запомнить стартовые значения углов по осям
                startVal[0] = degrees(ypr[0]);
                startVal[1] = degrees(ypr[1]);
                startVal[2] = degrees(ypr[2]);
                startValFlag = false;
                /*
                //debug
                Serial.print(startVal[1]);Serial.print(" ");
                Serial.print(degrees(ypr[1]));Serial.print(" ");
                Serial.println(countFlips[1]);
                */
            }
            //запись значений по трём осям
            data[0] = degrees(ypr[0]);
            data[1] = degrees(ypr[1]);
            data[2] = degrees(ypr[2]);

            // запись значений для работы "интерфейса"
            convertData[0] = slice((int) (startVal[0] - degrees(ypr[0]) + 360 * countFlips[0])/10, -3, 3);
            convertData[1] = slice((int) (startVal[1] - degrees(ypr[1]) + 360 * countFlips[1])/10, -3, 3);
            convertData[2] = slice((int) (startVal[2] - degrees(ypr[2]) + 360 * countFlips[2])/10, -3, 3);
        }
        _timer = millis();  // сброс таймера
        digitalWrite(ADO_pin, 0);
    }
}
/**
 * функция обрезания значения
 * @param val значение
 * @param from минимально возможное
 * @param to максимально  возможное
 * @return обрезанное значение
 */
int MPUGyro::slice(int val, int from, int to){
    if (val > to) return to;
    else if (val<from) return from;
    else return val;
}
/**
 * принт для отладки
 */
void MPUGyro::print() {
    Serial.print("X - "); Serial.print(data[0]);Serial.print(" - "); Serial.println(countFlips[0]);
    Serial.print("Y - "); Serial.print(data[1]);Serial.print(" - "); Serial.println(countFlips[1]);
    Serial.print("Z - "); Serial.print(data[2]);Serial.print(" - "); Serial.println(countFlips[2]);
    Serial.println();
}
/**
 * принт для отладки
 */
void MPUGyro::printPlot() {
    Serial.print(convertData[0] + countFlips[0]*360); Serial.print(" ");
    Serial.print(convertData[1]+ countFlips[1]*360); Serial.print(" ");
    Serial.println(convertData[2]+ countFlips[2]*360);
}



