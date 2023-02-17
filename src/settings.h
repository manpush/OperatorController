//
// Created by Max on 16.02.2023.
//

#ifndef OPERATOR_CONTROLLER_SETTINGS_H
#define OPERATOR_CONTROLLER_SETTINGS_H

#include "../lib/MPUGyro/src/MPUGyro.h"

/*============================== GIROSCOPES ======================*/

/* ado pins */
#define MPU1 A2
//#define MPU2 A1
//#define MPU3 A0

/* other settings */
#define CHANNEL 0x70
#define POWER_LEVEL RF24_PA_MAX
#define SEND_SPEED RF24_1MBPS


//============================ RADIO =============================
// CE CSN pins
#define CE 6
#define CSN 10


#endif //OPERATOR_CONTROLLER_SETTINGS_H
