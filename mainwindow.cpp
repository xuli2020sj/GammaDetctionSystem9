#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //单例模式（饿汉模式） 创建controller实例
    Controller *controller = Controller::controller();

    PLCStatusLED = new QLabel;
    DetectorStatusLED = new QLabel;
    PLCLabel = new QLabel;
    detLabel = new QLabel;

    PLCStatusLED->setText("");
    Utilities::setLED(PLCStatusLED, 1, 8);
    statusBar()->addWidget(PLCStatusLED);

    PLCLabel->setText("PLC");
    statusBar()->addWidget(PLCLabel);

    DetectorStatusLED->setText("");
    Utilities::setLED(DetectorStatusLED, 1, 8);
    statusBar()->addWidget(DetectorStatusLED);

    detLabel->setText("HPGe探测器");
    statusBar()->addWidget(detLabel);

    //create syn thread
    auto readThread = new QThread();
    auto manager = new Manager();
    manager->moveToThread(readThread);

    connect(readThread, &QThread::finished, readThread, &QObject::deleteLater);
    connect(readThread, &QThread::finished, manager, &QObject::deleteLater);
    connect(this, &MainWindow::startReadStatus, manager, &Manager::readStatus);

    readThread->start();

    connect(manager, &Manager::stateReady, this, &MainWindow::synState);

    //create auto control thread
    autoThread = new QThread();
    auto autoControld = new AutoControl();
    autoControld->moveToThread(autoThread);

    connect(autoThread, &QThread::finished, autoThread, &QObject::deleteLater);
    connect(autoThread, &QThread::finished, autoControld, &QObject::deleteLater);
    connect(this, &MainWindow::startAutoControl, autoControld, &AutoControl::StartAutoControl);

    autoThread->start();

    connect(autoControld, &AutoControl::autoProgress, this, &MainWindow::progressBar);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_actionConnect_PLC_triggered()
{
    subWinconnectPLC.show();
    connect(&subWinconnectPLC, SIGNAL(connectPLCEvent(QString)), this, SLOT(subWinEventConnectPLC(QString)));
    connect(&subWinconnectPLC, SIGNAL(disconnectPLCEvent()), this, SLOT(subWinEventDisconnectPLC()));
}

void MainWindow::subWinEventConnectPLC(QString ip)
{
    Controller *controller = Controller::controller();
    controller->setAddress(ip);
    controller->connectPLC();
    Utilities::setLED(PLCStatusLED , 2, 8);
    subWinconnectPLC.close();
}

void MainWindow::subWinEventDisconnectPLC()
{
    Controller *controller = Controller::controller();
    controller->disconnectPLC();
    Utilities::setLED(PLCStatusLED , 1, 8);
}

void MainWindow::on_readButton_released()
{
    Controller *controller = Controller::controller();
    byte RBuffer[3] = {};
    controller->readVal(0x84, 1, 0, 3, 0x02, &RBuffer);
    ui->devLog->append("Read length: " + ui->typeCombo1->currentText());
    ui->devLog->append("val: " + QString::number(RBuffer[0]));
    ui->devLog->append("bin : " +QString("%1").arg(QString::number(RBuffer[0],10).toUInt(), 8, 2, QLatin1Char('0')));
    ui->devLog->append("hex : " + QString::number(RBuffer[0],16));
}


void MainWindow::on_writeButton_released()
{
    Controller *controller = Controller::controller();
    int addr1, index;
    unsigned int num1;
    QString Qindex;
    num1 = ui->valEdit1->text().toLongLong();
    addr1 = ui->addEdit1->text().toInt();
    Qindex = ui->typeCombo1->currentText();
    if (Qindex == "Byte") {
        index = 0x02;
    } else {
        index = 0x08;
    }
    ui->devLog->append("Write length: " + ui->typeCombo1->currentText());
    ui->devLog->append("val: " + QString::number(num1));
    ui->devLog->append("bin : " +QString("%1").arg(QString::number(num1,10).toUInt(), 8, 2, QLatin1Char('0')));
    ui->devLog->append("hex : " + QString::number(num1,16));
    //byte WBuffer[3] = { num1 };
    longword WBuffer2[3] = {num1};

    controller->writeVal(0x84, 1, addr1, 1, index, &WBuffer2); //double write(int Area, int DBNumber, int Start, int Amount, int WordLen, void* pUsrData);
}

// development tool
void MainWindow::on_readAllButton_released()
{
    Controller *controller = Controller::controller();
    byte RBuffer[60] = {};
    for (int index = 0; index < 60 ; index++) {
        controller->readVal(0x84, 1, index, 3, 0x02, &RBuffer[index]);
        ui->devLog->append(QString::number(index) + ":" + QString::number(RBuffer[index]));
        ui->dataTable->setItem(index, 0, new QTableWidgetItem(QString::number(RBuffer[index])));
        ui->dataTable->setItem(index, 1, new QTableWidgetItem(QString::number(RBuffer[index],16)));
        ui->dataTable->setItem(index, 2, new QTableWidgetItem(QString("%1").arg(QString::number(RBuffer[index],10).toUInt(), 8, 2, QLatin1Char('0'))));
    }
}


void MainWindow::on_upButton_released()
{
    Command *cmd = new startZJogPlusR();
    cmd->execute();
}


void MainWindow::on_leftButton_released()
{
    Command *cmd = new startXJogMinusR();
    cmd->execute();
}


void MainWindow::on_rightBtn_released()
{
    Command *cmd = new startXJogPlusR();
    cmd->execute();
}


void MainWindow::on_downButton_released()
{
    Command *cmd = new startZJogMinusR();
    cmd->execute();
}


void MainWindow::on_stopButton_released()
{
    Command *cmd = new stopCommand();
    cmd->execute();
}


void MainWindow::on_forwardButton_released()
{
    Command *cmd = new startYJogPlusR();
    cmd->execute();
}


void MainWindow::on_backwardButton_released()
{
    Command *cmd = new startYJogMinusR();
    cmd->execute();
}

void MainWindow::on_resetButton_released()
{
    Command *cmdR = new resetXYZR();
    Command *cmd = new resetXYZ();
    cmdR->execute();
    cmd->execute();
}


void MainWindow::on_startAutoButton_released()
{


    emit startAutoControl();
}


void MainWindow::on_stopAutoButton_released()
{
    Controller *controller = Controller::controller();
    Command *cmd1 = new stopCommandR();
    Command *cmd2 = new stopCommand();
    cmd1->execute();
    cmd2->execute();
    controller->TerminateFlag =1;
}


void MainWindow::on_synButton_released()
{
    emit startReadStatus();
}

void MainWindow::synState()
{
    Controller *controller = Controller::controller();

    ui->stateTableWidget->setItem(0,0,new QTableWidgetItem(QString("%1").arg(controller->xAxis.getIsAlert())));
    ui->stateTableWidget->setItem(1,0,new QTableWidgetItem(QString("%1").arg(controller->xAxis.getIsReady())));
    ui->stateTableWidget->setItem(2,0,new QTableWidgetItem(QString("%1").arg(controller->xAxis.getIsZero())));
    ui->stateTableWidget->setItem(3,0,new QTableWidgetItem(QString("%1").arg(controller->xAxis.getIsCompleted())));
    ui->stateTableWidget->setItem(4,0,new QTableWidgetItem(QString("%1").arg(controller->xAxis.getCurrentSpeed())));
    ui->stateTableWidget->setItem(5,0,new QTableWidgetItem(QString("%1").arg(controller->xAxis.getCurrentPosition())));
    ui->stateTableWidget->setItem(6,0,new QTableWidgetItem(QString("%1").arg(controller->xAxis.getTargetSpeed())));
    ui->stateTableWidget->setItem(7,0,new QTableWidgetItem(QString("%1").arg(controller->xAxis.getTargetAbsoltePosition())));
    ui->stateTableWidget->setItem(8,0,new QTableWidgetItem(QString("%1").arg(controller->xAxis.getTargetRelativePosition())));
    ui->stateTableWidget->setItem(9,0,new QTableWidgetItem(QString("%1").arg(controller->xAxis.getInit())));
    ui->stateTableWidget->setItem(10,0,new QTableWidgetItem(QString("%1").arg(controller->xAxis.getStop())));
    ui->stateTableWidget->setItem(11,0,new QTableWidgetItem(QString("%1").arg(controller->xAxis.getIsAbsoluteMoationAuto())));
    ui->stateTableWidget->setItem(12,0,new QTableWidgetItem(QString("%1").arg(controller->xAxis.getIsRelativeMoationAuto())));
    ui->stateTableWidget->setItem(13,0,new QTableWidgetItem(QString("%1").arg(controller->xAxis.getIsJogPlus())));
    ui->stateTableWidget->setItem(14,0,new QTableWidgetItem(QString("%1").arg(controller->xAxis.getIsJogNegative())));
    ui->stateTableWidget->setItem(15,0,new QTableWidgetItem(QString("%1").arg(controller->xAxis.getIsAbsoluteMoationManual())));
    ui->stateTableWidget->setItem(16,0,new QTableWidgetItem(QString("%1").arg(controller->xAxis.getIsRelativeMoationManual())));
    ui->stateTableWidget->setItem(17,0,new QTableWidgetItem(QString("%1").arg(controller->xAxis.getUpLimit())));
    ui->stateTableWidget->setItem(18,0,new QTableWidgetItem(QString("%1").arg(controller->xAxis.getDownLimit())));

    ui->stateTableWidget->setItem(19,0,new QTableWidgetItem(QString("%1").arg(controller->xAxis.getLocalOrRemote())));
    ui->stateTableWidget->setItem(20,0,new QTableWidgetItem(QString("%1").arg(controller->xAxis.getStopAllAxis())));
    ui->stateTableWidget->setItem(21,0,new QTableWidgetItem(QString("%1").arg(controller->xAxis.getResetAllAxis())));
    ui->stateTableWidget->setItem(22,0,new QTableWidgetItem(QString("%1").arg(controller->xAxis.getLocalOrRemoteState())));

    ui->stateTableWidget->setItem(0,1,new QTableWidgetItem(QString("%1").arg(controller->yAxis.getIsAlert())));
    ui->stateTableWidget->setItem(1,1,new QTableWidgetItem(QString("%1").arg(controller->yAxis.getIsReady())));
    ui->stateTableWidget->setItem(2,1,new QTableWidgetItem(QString("%1").arg(controller->yAxis.getIsZero())));
    ui->stateTableWidget->setItem(3,1,new QTableWidgetItem(QString("%1").arg(controller->yAxis.getIsCompleted())));
    ui->stateTableWidget->setItem(4,1,new QTableWidgetItem(QString("%1").arg(controller->yAxis.getCurrentSpeed())));
    ui->stateTableWidget->setItem(5,1,new QTableWidgetItem(QString("%1").arg(controller->yAxis.getCurrentPosition())));
    ui->stateTableWidget->setItem(6,1,new QTableWidgetItem(QString("%1").arg(controller->yAxis.getTargetSpeed())));
    ui->stateTableWidget->setItem(7,1,new QTableWidgetItem(QString("%1").arg(controller->yAxis.getTargetAbsoltePosition())));
    ui->stateTableWidget->setItem(8,1,new QTableWidgetItem(QString("%1").arg(controller->yAxis.getTargetRelativePosition())));
    ui->stateTableWidget->setItem(9,1,new QTableWidgetItem(QString("%1").arg(controller->yAxis.getInit())));
    ui->stateTableWidget->setItem(10,1,new QTableWidgetItem(QString("%1").arg(controller->yAxis.getStop())));
    ui->stateTableWidget->setItem(11,1,new QTableWidgetItem(QString("%1").arg(controller->yAxis.getIsAbsoluteMoationAuto())));
    ui->stateTableWidget->setItem(12,1,new QTableWidgetItem(QString("%1").arg(controller->yAxis.getIsRelativeMoationAuto())));
    ui->stateTableWidget->setItem(13,1,new QTableWidgetItem(QString("%1").arg(controller->yAxis.getIsJogPlus())));
    ui->stateTableWidget->setItem(14,1,new QTableWidgetItem(QString("%1").arg(controller->yAxis.getIsJogNegative())));
    ui->stateTableWidget->setItem(15,1,new QTableWidgetItem(QString("%1").arg(controller->yAxis.getIsAbsoluteMoationManual())));
    ui->stateTableWidget->setItem(16,1,new QTableWidgetItem(QString("%1").arg(controller->yAxis.getIsRelativeMoationManual())));
    ui->stateTableWidget->setItem(17,1,new QTableWidgetItem(QString("%1").arg(controller->yAxis.getUpLimit())));
    ui->stateTableWidget->setItem(18,1,new QTableWidgetItem(QString("%1").arg(controller->yAxis.getDownLimit())));

    ui->stateTableWidget->setItem(0,2,new QTableWidgetItem(QString("%1").arg(controller->zAxis.getIsAlert())));
    ui->stateTableWidget->setItem(1,2,new QTableWidgetItem(QString("%1").arg(controller->zAxis.getIsReady())));
    ui->stateTableWidget->setItem(2,2,new QTableWidgetItem(QString("%1").arg(controller->zAxis.getIsZero())));
    ui->stateTableWidget->setItem(3,2,new QTableWidgetItem(QString("%1").arg(controller->zAxis.getIsCompleted())));
    ui->stateTableWidget->setItem(4,2,new QTableWidgetItem(QString("%1").arg(controller->zAxis.getCurrentSpeed())));
    ui->stateTableWidget->setItem(5,2,new QTableWidgetItem(QString("%1").arg(controller->zAxis.getCurrentPosition())));
    ui->stateTableWidget->setItem(6,2,new QTableWidgetItem(QString("%1").arg(controller->zAxis.getTargetSpeed())));
    ui->stateTableWidget->setItem(7,2,new QTableWidgetItem(QString("%1").arg(controller->zAxis.getTargetAbsoltePosition())));
    ui->stateTableWidget->setItem(8,2,new QTableWidgetItem(QString("%1").arg(controller->zAxis.getTargetRelativePosition())));
    ui->stateTableWidget->setItem(9,2,new QTableWidgetItem(QString("%1").arg(controller->zAxis.getInit())));
    ui->stateTableWidget->setItem(10,2,new QTableWidgetItem(QString("%1").arg(controller->zAxis.getStop())));
    ui->stateTableWidget->setItem(11,2,new QTableWidgetItem(QString("%1").arg(controller->zAxis.getIsAbsoluteMoationAuto())));
    ui->stateTableWidget->setItem(12,2,new QTableWidgetItem(QString("%1").arg(controller->zAxis.getIsRelativeMoationAuto())));
    ui->stateTableWidget->setItem(13,2,new QTableWidgetItem(QString("%1").arg(controller->zAxis.getIsJogPlus())));
    ui->stateTableWidget->setItem(14,2,new QTableWidgetItem(QString("%1").arg(controller->zAxis.getIsJogNegative())));
    ui->stateTableWidget->setItem(15,2,new QTableWidgetItem(QString("%1").arg(controller->zAxis.getIsAbsoluteMoationManual())));
    ui->stateTableWidget->setItem(16,2,new QTableWidgetItem(QString("%1").arg(controller->zAxis.getIsRelativeMoationManual())));
    ui->stateTableWidget->setItem(17,2,new QTableWidgetItem(QString("%1").arg(controller->zAxis.getUpLimit())));
    ui->stateTableWidget->setItem(18,2,new QTableWidgetItem(QString("%1").arg(controller->zAxis.getDownLimit())));
}

void MainWindow::progressBar(int progress)
{
    ui->progressBar->setValue(progress);
}

void MainWindow::on_startManualButton_released()
{
    Controller *controller = Controller::controller();



    longword xPosBuffer = processReal(ui->targetXPosEdit->text());
    longword yPosBuffer = processReal(ui->targetYPosEdit->text());
    longword zPosBuffer = processReal(ui->targetZPosEdit->text());

    longword speed = processReal(ui->speedSelect->currentText());
    controller->writeVal(0x84, 1, 30, 1, 0x08, &speed); //x轴速度
    controller->writeVal(0x84, 1, 34, 1, 0x08, &speed); //y轴速度
    controller->writeVal(0x84, 1, 38, 1, 0x08, &speed); //z轴速度

    controller->writeVal(0x84, 1, 6, 1, 0x08, &xPosBuffer);
    controller->writeVal(0x84, 1, 10, 1, 0x08, &yPosBuffer);
    controller->writeVal(0x84, 1, 14, 1, 0x08, &zPosBuffer);

    Command *cmdSAXR = new startXAutoCommandR();
    Command *cmdSAYR = new startYAutoCommandR();
    Command *cmdSAZR = new startZAutoCommandR();
    cmdSAXR->execute();
    cmdSAYR->execute();
    cmdSAZR->execute();

    Command *cmdSAX = new startXAutoCommand();
    Command *cmdSAY = new startYAutoCommand();
    Command *cmdSAZ = new startZAutoCommand();
    cmdSAX->execute();
    cmdSAY->execute();
    cmdSAZ->execute();


    Command *cmdIX = new initXCommand();
    Command *cmdIY = new initYCommand();
    Command *cmdIZ = new initZCommand();
    cmdIX->execute();
    cmdIY->execute();
    cmdIZ->execute();
}

longword MainWindow::processReal(QString lineEdit)
{
    float targetXPosSF = lineEdit.toFloat();
    longword buffer = *((long *)&targetXPosSF);
    buffer = qToBigEndian(buffer);
    //qDebug() << QString("%1").arg(buffer, 8, 16, QLatin1Char('0'));
    return buffer;
}

void MainWindow::on_upButton_pressed()
{
    Command *cmd = new startZJogPlus();
    cmd->execute();
}

void MainWindow::on_leftButton_pressed()
{
    Command *cmd = new startXJogMinus();
    cmd->execute();
}

void MainWindow::on_backwardButton_pressed()
{
    Command *cmd = new startYJogMinus();
    cmd->execute();
}

void MainWindow::on_downButton_pressed()
{
    Command *cmd = new startZJogMinus();
    cmd->execute();
}

void MainWindow::on_forwardButton_pressed()
{
    Command *cmd = new startYJogPlus();
    cmd->execute();
}

void MainWindow::on_rightBtn_pressed()
{
    Command *cmd = new startXJogPlus();
    cmd->execute();
}

void MainWindow::on_returnZero_released()
{
    Command *cmd = new resetXYZ();
    Command *cmdR = new resetXYZ();
    cmdR->execute();
    cmd->execute();
}


void MainWindow::on_manualRadioButton_clicked(bool checked)
{
    if (checked == true) {
        Command *cmd = new manualCmd();
        cmd->execute();
    }
}

void MainWindow::on_autoRadioButton_clicked(bool checked)
{
    if (checked == true) {
        Command *cmd = new AutoCmd();
        cmd->execute();
    }
}


void MainWindow::on_pauseAutoButton_released()
{
    Controller *controller = Controller::controller();
    QString str = QString("继续");
    if (str ==  ui->pauseAutoButton->text()){
        ui->pauseAutoButton->setText("暂停");
        controller->runFlag = 1;
} else {
    ui->pauseAutoButton->setText("继续");
        controller->runFlag = 0;
}

}


void MainWindow::on_generateCmdAction_triggered()
{
    qDebug() << "init xml";
    xmlParser xmlP;
    xmlP.createXML();
}

