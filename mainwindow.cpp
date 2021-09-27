#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    controller = new Controller("192.168.13.162", 0, 1);

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
    qDebug() << ip;
    controller->setAddress(ip);
    controller->connectPLC();
    Utilities::setLED(PLCStatusLED , 2, 8);
}

void MainWindow::subWinEventDisconnectPLC()
{
    controller->disconnectPLC();
    Utilities::setLED(PLCStatusLED , 1, 8);
}

void MainWindow::on_readButton_released()
{
    byte RBuffer[3] = {};
    controller->readVal(0x84, 1, 0, 3, 0x02, &RBuffer);
    ui->devLog->append("Read length: " + ui->typeCombo1->currentText());
    ui->devLog->append("val: " + QString::number(RBuffer[0]));
    ui->devLog->append("bin : " +QString("%1").arg(QString::number(RBuffer[0],10).toUInt(), 8, 2, QLatin1Char('0')));
    ui->devLog->append("hex : " + QString::number(RBuffer[0],16));
}


void MainWindow::on_writeButton_released()
{
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
    byte RBuffer[60] = {};
    for (int index = 0; index < 60 ; index++) {
        controller->readVal(0x84, 1, index, 3, 0x02, &RBuffer[index]);
        ui->devLog->append(QString::number(index) + ":" + QString::number(RBuffer[index]));
        ui->dataTable->setItem(index, 0, new QTableWidgetItem(QString::number(RBuffer[index])));
        ui->dataTable->setItem(index, 1, new QTableWidgetItem(QString::number(RBuffer[index],16)));
        ui->dataTable->setItem(index, 2, new QTableWidgetItem(QString("%1").arg(QString::number(RBuffer[index],10).toUInt(), 8, 2, QLatin1Char('0'))));
    }
}

