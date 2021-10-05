#ifndef COMMAND_H
#define COMMAND_H
#include "controller.h"
#include "snap7.h"


class Command
{
public:
    virtual bool execute() = 0;
protected:
    byte buffer;
    Controller* controller;

};

class startCommand : public Command
{
public:
    bool execute() {
        Controller *controller = Controller::controller();
        buffer = 22;
        return controller->writeVal(0x84, 1, 0, 3, 0x02, &buffer);
    }
};

class stopCommand : public Command
{
public:
    bool execute() {
        //writeVal(0x84, 1, 0, 3, 0x02, &buffer);
        return true;
    }
};

class restartCommand : public Command
{
public:
    bool execute() {
        //writeVal(0x84, 1, 0, 3, 0x02, &buffer);
        return true;
    }
};


#endif // COMMAND_H
