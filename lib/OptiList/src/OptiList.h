//
// Created by Max on 17.02.2023.
//

#ifndef OPRATORCONTROLLER_OPTILIST_H
#define OPRATORCONTROLLER_OPTILIST_H


class OptiList {
public:
    struct data {
        void * gyroInfo;
        OptiList::data * next;
    };
    OptiList();
    OptiList::data * firstElement;
    void push(void * data);
    void * getById(int id);
};


#endif //OPRATORCONTROLLER_OPTILIST_H
