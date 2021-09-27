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

};

class startCommand : public abstractCommand
{
public:
    bool execute() {
        //writeVal(0x84, 1, 0, 3, 0x02, &buffer);
        return true;
    }
};



#endif // COMMAND_H
