#include "controller.h"


Controller::Controller(QString address, int rack, int slot)
{
    Address = address;
    Rack = rack;
    Slot = slot;
    connected = 0;
    Client = new TS7Client();
}

Controller::~Controller()
{
    std::cout<<"destructor"<<std::endl;
}

void Controller::setAddress(QString address)
{
    Address = address;
}

Controller::Controller(QString address)
{
    Controller(address, 0, 1);
}

bool Controller::connectPLC()
{
    qDebug() << "connecting plc";
    if ( !Client->Connected() )
    {
        return Client->ConnectTo(Address.toStdString().c_str(), Rack, Slot);
    }
    else {
        return Client->Connected();
    }
}

bool Controller::disconnectPLC()
{
    if ( Client->Connected() )
    {
        return Client->Disconnect();
    }
    else {
        return Client->Connected();
    }
}

double Controller::readVal(int Area, int DBNumber, int Start, int Amount, int WordLen, void* pUsrData)
{
    int rflag = Client->ReadArea(Area, DBNumber, Start, Amount, WordLen, pUsrData);
    return rflag;
}

double Controller::writeVal(int Area, int DBNumber, int Start, int Amount, int WordLen, void *pUsrData)
{
    int wflag = Client->WriteArea(Area, DBNumber, Start, Amount, WordLen, pUsrData);

    return wflag;
}

void  Controller::autoRun()
{
    while(true)
    {
        if (Client->Connected())
        {
            //QMutexLocker locker(&mutex); //线程锁
            //executCmdQueue(); //执行命令队列
        }
        else {
            connectPLC();
        }
        this->sleep(ulong(0.1*10e-6));// 100000us=100ms
    }
}

