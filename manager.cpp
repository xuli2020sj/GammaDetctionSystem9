#include "manager.h"
#include "qeventloop.h"
#include "qtimer.h"

Manager::Manager()
{

}

void Manager::readStatus()
{
    qDebug() << "read status";
    Controller *controller = Controller::controller();
    while(true)
    {
        if (controller->Client->Connected())
        {

            //QMutexLocker locker(&mutex); //线程锁
            //executCmdQueue(); //执行命令队列

            byte RBuffer[64] = {};
            for (int index = 0; index < 64 ; index++) {
                controller->readVal(0x84, 1, index, 3, 0x02, &RBuffer[index]);
                qDebug() << QString("%1").arg(QString::number(RBuffer[index],10).toUInt(), 8, 2, QLatin1Char('0'));
            }

        }
        else {
            controller->connectPLC();
        }

        QEventLoop loop;
        QTimer::singleShot(5000, &loop, SLOT(quit()));
        loop.exec();
    }
}
