#ifndef CONTROLLER_H
#define CONTROLLER_H

#pragma once
#include "snap7.h"
#include <iostream>
#include <string>
#include <QThread>
#include <QDebug>
#include <QString>
#include <QMutex>


class Controller : public QThread
{
public:
    static Controller* controller() {
        static Controller controller;
        return &controller;
        }
//    Controller(QString address, int rack, int slot);
//    Controller(QString address);

    ~Controller();

//    Controller(const Controller&);
//    Controller& operator=(const Controller&);

    void setAddress(QString address); //设定PLC地址
    bool connectPLC(); //连接PLC
    bool disconnectPLC(); //断开PLC

    double readVal(int Area, int DBNumber, int Start, int Amount, int WordLen, void* pUsrData);
    double writeVal(int Area, int DBNumber, int Start, int Amount, int WordLen, void* pUsrData);

    void run(); //按预先设定命令队列启动自动测量
    TS7Client* Client; //建立snap7通信协议客户端

private:
    Controller();
    int num = 0;

    QString Address;
    int Rack, Slot;
    bool connected; //PLC 连接状态 1 断开 0 连接

protected:

};

#endif // CONTROLLER_H
