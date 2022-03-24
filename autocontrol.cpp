#include "autocontrol.h"
#include "qtimer.h"

AutoControl::AutoControl()
{
}

void AutoControl::StartAutoControl()
{
    Controller *controller = Controller::controller();
    controller->runFlag = 1;
    controller->TerminateFlag = 0;
    startXYZCombo cmd1 = startXYZCombo(QString::number(10), QString::number(10),QString::number(10),
                                     QString::number(10),QString::number(10),QString::number(10));
    startXYZCombo cmd2 = startXYZCombo(QString::number(20), QString::number(20),QString::number(20),
                                     QString::number(9),QString::number(9),QString::number(9));
    startXYZCombo cmd3 = startXYZCombo(QString::number(10), QString::number(10),QString::number(10),
                                     QString::number(8),QString::number(8),QString::number(8));
    startXYZCombo cmd4 = startXYZCombo(QString::number(40), QString::number(20),QString::number(10),
                                     QString::number(6),QString::number(6),QString::number(6));
    startXYZCombo cmd5 = startXYZCombo(QString::number(10), QString::number(10),QString::number(20),
                                     QString::number(5),QString::number(5),QString::number(5));
    std::vector<startXYZCombo> cmdQueue;
    cmdQueue.push_back(cmd1);
    cmdQueue.push_back(cmd2);
    cmdQueue.push_back(cmd3);
    cmdQueue.push_back(cmd4);
    cmdQueue.push_back(cmd5);
    size_t index = 0;
    size_t cmdSum = cmdQueue.size();
    while(index < cmdSum){
        if (controller->TerminateFlag ==1) return;
        // 断线重连机制
        if (controller->Client->Connected())
        {
            if (!controller->xAxis.getIsCompleted() && !controller->yAxis.getIsCompleted() && !controller->xAxis.getIsCompleted()) {
                if(controller->runFlag == 0) continue;
                cmdQueue.at(index).execute(); // 执行指令
                int res = ((index + 1) / cmdSum) * 100;
                emit autoProgress(res); // 用户界面显示运行进度
                index++;
            }
        }
        else {
            controller->connectPLC();
        }
    sleep(1000);
    }
}

void AutoControl::sleep(float time)
{
    QEventLoop loop;
    QTimer::singleShot(time, &loop, SLOT(quit()));
    loop.exec();
}
