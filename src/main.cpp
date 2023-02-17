#include <Arduino.h>
#include <I2Cdev.h>
#include "MPU6050_6Axis_MotionApps20.h"
#include "nRF24L01.h"
#include "RF24.h"
#include "globalVariables.h"
#include "settings.h"

void setup() {
    pinMode(A2, OUTPUT);
    digitalWrite(A2, HIGH);
    // digitalWrite(MPU1, 1);
    // digitalWrite(MPU1, 1);
    Serial.begin(115200);

    radio.begin();                      // активировать модуль
    radio.setAutoAck(true);                // режим подтверждения приёма, 1 вкл 0 выкл
    radio.setRetries(0, 15);            // (время между попыткой достучаться, число попыток)
    radio.enableAckPayload();           // разрешить отсылку данных в ответ на входящий сигнал
    radio.setPayloadSize(16);           // размер пакета, в байтах
    radio.openWritingPipe(address[0]);  // мы - труба 0, открываем канал для передачи данных
    radio.setChannel(0x70);             // выбираем канал (в котором нет шумов!)
    radio.setPALevel(
            RF24_PA_MAX);      // уровень мощности передатчика. На выбор RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
    radio.setDataRate(RF24_1MBPS);      // скорость обмена. На выбор RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
    // должна быть одинакова на приёмнике и передатчике!
    // при самой низкой скорости имеем самую высокую чувствительность и дальность!!
    // ВНИМАНИЕ!!! enableAckPayload НЕ РАБОТАЕТ НА СКОРОСТИ 250 kbps!
    radio.powerUp();        // начать работу
    radio.stopListening();  // не слушаем радиоэфир, мы передатчик

    Wire.begin();


    // инициализация DMP
#ifdef MPU1
    mpu1.initialize();
    mpu1.dmpInitialize();
    mpu1.setDMPEnabled(true);
    mpu1.CalibrateGyro(15);
#endif

#ifdef MPU2
    mpu2.initialize();
    mpu2.dmpInitialize();
    mpu2.setDMPEnabled(true);
    mpu2.CalibrateGyro(15);
#endif

#ifdef MPU3
    mpu3.initialize();
    mpu3.dmpInitialize();
    mpu3.setDMPEnabled(true);
    mpu3.CalibrateGyro(15);
#endif

    send_data_tmr = millis();
}

void mpu_tick(MPU6050 mpu, uint32_t *tmr, float ypr[3], uint8_t fifoBuffer[45], int index) {

    if (millis() - *tmr >= 11) {  // таймер на 11 мс (на всякий случай)

        if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) {
            Quaternion q;
            VectorFloat gravity;
            // расчёты
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
        }
        *tmr = millis();  // сброс таймера
    }
}

void loop() {
    float values[3][3] = {
#ifdef MPU1
            {(float)degrees(ypr1[0][0]), (float)degrees(ypr1[1][0]), (float)degrees(ypr1[2][0])},
#endif
#ifndef MPU1
            { 0, 0, 0 },
#endif
#ifdef MPU2
            { degrees(ypr2[0][0]), degrees(ypr2[1][0]), degrees(ypr2[2][0]) },
#endif
#ifndef MPU2
            {0, 0, 0},
#endif
#ifdef MPU3
            { degrees(ypr3[0][0]), degrees(ypr3[1][0]), degrees(ypr3[2][0]) }
#endif
#ifndef MPU3
            {0, 0, 0}
#endif
    };
    //       uint8_t values[3][3] = {
    // #ifdef MPU1
    //       { map(degrees(ypr1[0]), -180, 180, 0, 7), map(degrees(ypr1[1]), -180, 180, 0, 7), map(degrees(ypr1[2]), -180, 180, 0, 7) },
    // #endif
    // #ifndef MPU1
    //       { 0, 0, 0 },
    // #endif
    // #ifdef MPU2
    //       { map(degrees(ypr2[0]), -180, 180, 0, 7), map(degrees(ypr2[1]), -180, 180, 0, 7), map(degrees(ypr2[2]), -180, 180, 0, 7) },
    // #endif
    // #ifndef MPU2
    //       { 0, 0, 0 },
    // #endif
    // #ifdef MPU3
    //       { map(degrees(ypr3[0]), -180, 180, 0, 7), map(degrees(ypr3[1]), -180, 180, 0, 7), map(degrees(ypr3[2]), -180, 180, 0, 7) }
    // #endif
    // #ifndef MPU3
    //       { 0, 0, 0 }
    // #endif
    //     };
    Serial.print(values[0][0]);
    Serial.print(",");
    Serial.print(values[0][1]);
    Serial.print(",");
    Serial.println(values[0][2]);
    digitalWrite(MPU1, HIGH);                  //изменяем адрес первого гироскопа для работы с ним
    mpu_tick(mpu1, &tmr1, reinterpret_cast<float *>(ypr1), fifoBuffer1, 0);  //получаем данные в ypr
    if (millis() - send_data_tmr > 300) {      //отправляем данные получателю каждые 300мс


        uint32_t last_time = micros();
        if (radio.write(values, 9)) {  // отправляем значение датчиков
            if (!radio.available()) {    // если получаем пустой ответ
                Serial.print("Empty, ");
                Serial.print(" Time: ");
                Serial.print(micros() - last_time);
                Serial.println(" microseconds");
                Serial.println();
            } else {
                while (radio.available()) {  // если в ответе что-то есть

                    Serial.print(" Time: ");
                    Serial.print(micros() - last_time);
                    Serial.println(" microseconds");
                    Serial.println();
                    counter++;
                }
            }
        } else {
            // Serial.println("Fail");
        }
        send_data_tmr = millis();
    }
    // if (millis - glob_tmr > 100){
    // Serial.print(degrees(ypr[0])); // вокруг оси Z0
    //   Serial.print(',');
    //   Serial.print(degrees(ypr[1])); // вокруг оси Y1
    //   Serial.print(',');
    //   Serial.print(degrees(ypr[2])); // вокруг оси X2
    //   Serial.println();
    //     glob_tmr = millis();
    // }
}