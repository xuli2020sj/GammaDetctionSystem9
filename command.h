#ifndef COMMAND_H
#define COMMAND_H
#include "controller.h"
#include "snap7.h"


class abstractCommand
{
public:
    virtual bool execute() = 0;
protected:
    byte buffer;
    Controller controller;

};

class startCommand : public abstractCommand
{
public:
    bool execute() {
        auto controller = new Controller("192.168.13.162", 0, 1);
        return controller->writeVal(0x84, 1, 0, 3, 0x02, &buffer);
    }
};

class stopCommand : public abstractCommand
{
public:
    bool execute() {
        //writeVal(0x84, 1, 0, 3, 0x02, &buffer);
        return true;
    }
};

class restartCommand : public abstractCommand
{
public:
    bool execute() {
        //writeVal(0x84, 1, 0, 3, 0x02, &buffer);
        return true;
    }
};


#endif // COMMAND_H
