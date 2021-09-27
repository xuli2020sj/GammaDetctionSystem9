#include "connectplc.h"
#include "ui_connectplc.h"
#include "QDebug"

connectPLC::connectPLC(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::connectPLC)
{
    ui->setupUi(this);
}

connectPLC::~connectPLC()
{
    delete ui;
}



void connectPLC::on_connectPLCButton_released()
{
    QString IP = ui->ipEdit->text();
    emit connectPLCEvent(IP);
}


void connectPLC::on_disconnectPLCButton_released()
{
    emit disconnectPLCEvent();
}

