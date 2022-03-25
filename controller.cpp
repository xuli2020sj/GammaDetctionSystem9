#include "controller.h"

Controller::Controller()
{
    Rack = 0;
    Slot = 1;
    connected = 0;
    Client = new TS7Client();


}

Controller::~Controller()
{

}

void Controller::setAddress(QString address)
{
    Address = address;
}

bool Controller::connectPLC()
{
    //qDebug() << "connecting plc";
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

void Controller::startRead()
{
//    emit startReadCycle();
}



void  Controller::run()
{
    Controller *controller = Controller::controller();
    while(true)
    {
        if (Client->Connected())
        {

            //QMutexLocker locker(&mutex); //线程锁
            //executCmdQueue(); //执行命令队列

            byte RBuffer[64] = {};
            for (int index = 0; index < 64 ; index++) {
                controller->readVal(0x84, 1, index, 3, 0x02, &RBuffer[index]);
                //qDebug() << QString("%1").arg(QString::number(RBuffer[index],10).toUInt(), 8, 2, QLatin1Char('0'));
            }
        }
        else {
            connectPLC();
        }

        //qDebug() << "sleep";
    }
}

