//
// Created by Max on 17.02.2023.
//

#ifndef OPRATORCONTROLLER_OPTILIST_H
#define OPRATORCONTROLLER_OPTILIST_H


#include "../../MPUGyro/src/MPUGyro.h"

class OptiList {
public:
    struct data {
        MPUGyro * gyroInfo;
        OptiList::data * next;
    };
    OptiList();
    OptiList::data * firstElement;
    int Count;
    void push(MPUGyro * data);
    MPUGyro * getById(int id);
};


#endif //OPRATORCONTROLLER_OPTILIST_H
