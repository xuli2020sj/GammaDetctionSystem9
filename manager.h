#ifndef MANAGER_H
#define MANAGER_H
#include "axiscontrol.h"
#include <QObject>
#include <QMutex>
#include <QDebug>
#include "controller.h"



class Manager : public QObject
{
//    Q_OBJECT
public:
//    xAxis xAxis;
//    yAxis yAxis;
//    zAxis zAxis;

    Manager();

public slots:
    void readStatus();
};

#endif // MANAGER_H
