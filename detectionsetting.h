#ifndef DETECTIONSETTING_H
#define DETECTIONSETTING_H

#include <QWidget>

namespace Ui {
class detectionSetting;
}

class detectionSetting : public QWidget
{
    Q_OBJECT

public:
    explicit detectionSetting(QWidget *parent = nullptr);
    ~detectionSetting();

private:
    Ui::detectionSetting *ui;
};

#endif // DETECTIONSETTING_H
