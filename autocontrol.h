#ifndef AUTOCONTROL_H
#define AUTOCONTROL_H
#include <QObject>
#include <QDebug>
#include "controller.h"
#include "command.h"
#include <deque>
#include <queue>
#include "qeventloop.h"

class AutoControl : public QObject
{
    Q_OBJECT
public:
    AutoControl();

public slots:
    void StartAutoControl();
private:

    void sleep(float time);
signals:
    void autoProgress(int progress);
};

#endif // AUTOCONTROL_H
