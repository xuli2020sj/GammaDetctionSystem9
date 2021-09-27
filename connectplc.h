#ifndef CONNECTPLC_H
#define CONNECTPLC_H

#include <QWidget>

namespace Ui {
class connectPLC;
}

class connectPLC : public QWidget
{
    Q_OBJECT

public:
    explicit connectPLC(QWidget *parent = nullptr);
    ~connectPLC();

private slots:
    void on_connectPLCButton_released();

    void on_disconnectPLCButton_released();

private:
    Ui::connectPLC *ui;

signals:
    void connectPLCEvent(QString ip);
    void disconnectPLCEvent();
};

#endif // CONNECTPLC_H
