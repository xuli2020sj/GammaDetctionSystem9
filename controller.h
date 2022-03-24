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
#include "manager.h"


class Controller : public QObject
{

public:
    static Controller* controller() {
        static Controller controller;
        return &controller;
    }

    ~Controller();

    void setAddress(QString address); //设定PLC地址
    bool connectPLC(); //连接PLC
    bool disconnectPLC(); //断开 PLC

    double readVal(int Area, int DBNumber, int Start, int Amount, int WordLen, void* pUsrData);
    double writeVal(int Area, int DBNumber, int Start, int Amount, int WordLen, void* pUsrData);

    bool readBitVal(int Area, int DBNumber, int Start, int Amount, int WordLen, void* pUsrData);
    bool writeBitVal(int Area, int DBNumber, int Start, int Amount, int WordLen, void* pUsrData);

    void startRead();
    void run(); //按预先设定命令队列启动自动测量
    TS7Client* Client; //建立snap7通信协议客户端

    // 保存轴状态信息
    xAxis xAxis;
    yAxis yAxis;
    zAxis zAxis;

    //控制线程状态控制
    int TerminateFlag; //1 terminate
    int runFlag; // 0 stop 1 run
private:
    Controller();
    int num = 0;

    QString Address;
    int Rack, Slot;
    bool connected; //PLC 连接状态 1 断开 0 连接

public slots:


protected:

};

#endif // CONTROLLER_H
