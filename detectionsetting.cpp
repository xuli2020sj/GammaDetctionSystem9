#include "detectionsetting.h"
#include "ui_detectionsetting.h"

detectionSetting::detectionSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::detectionSetting)
{
    ui->setupUi(this);
}

detectionSetting::~detectionSetting()
{
    delete ui;
}
