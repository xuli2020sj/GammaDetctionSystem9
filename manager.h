#ifndef MANAGER_H
#define MANAGER_H
#include "axiscontrol.h"
#include <QObject>
#include <QMutex>
#include <QDebug>
#include "controller.h"
#include <vector>


class Manager : public QObject
{
    Q_OBJECT
public:
    Manager();
private:
    byte RBuffer[64];

    void sleep(float time);
    void dataProcessing(std::vector<QString> dbData);

    QString getDB(int index);

    float binToFloat(const QString &data);
public slots:
    void readStatus();

signals:
    void resultReady(const QString &result);
    void stateReady();
};

#endif // MANAGER_H
