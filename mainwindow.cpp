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
    Command *sc = new startCommand();
    sc->execute();
}


void MainWindow::on_leftButton_released()
{

}


void MainWindow::on_rightBtn_released()
{

}


void MainWindow::on_downButton_released()
{

}


void MainWindow::on_stopButton_released()
{

}


void MainWindow::on_forwardButton_released()
{

}


void MainWindow::on_backwardButton_released()
{

}


void MainWindow::on_resetButton_released()
{

}


void MainWindow::on_startAutoButton_released()
{
    Controller *controller = Controller::controller();
    controller->start();
}


void MainWindow::on_stopAutoButton_released()
{
    Controller *controller = Controller::controller();
    controller->terminate();
}


void MainWindow::on_synButton_released()
{
    emit startReadStatus();
}

