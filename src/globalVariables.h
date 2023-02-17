//
// Created by Max on 16.02.2023.
//
#include <Arduino.h>
#include "nRF24L01.h"
#include "RF24.h"

RF24 radio(6, 10);                                                             // модуль связи на пинах 9 и 10
byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"};  //возможные номера труб
byte counter;

uint32_t send_data_tmr;
int rotates = 0;