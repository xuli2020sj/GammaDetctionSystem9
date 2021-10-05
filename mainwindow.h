#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include "connectplc.h"
#include "controller.h"
#include "command.h"
#include "QLabel"
#include "utilities.h"
#include "manager.h"
#include <QObject>
#include <QMutex>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Controller *controller;

private slots:
    void on_actionConnect_PLC_triggered();
    void subWinEventConnectPLC(QString);
    void subWinEventDisconnectPLC();

    void on_readButton_released();

    void on_writeButton_released();

    void on_readAllButton_released();

    void on_upButton_released();

    void on_leftButton_released();

    void on_rightBtn_released();

    void on_downButton_released();

    void on_stopButton_released();

    void on_forwardButton_released();

    void on_backwardButton_released();

    void on_resetButton_released();



    void on_startAutoButton_released();

    void on_stopAutoButton_released();

    void on_synButton_released();

signals:
    void startReadStatus();

private:
    Ui::MainWindow *ui;
    connectPLC subWinconnectPLC;
    QThread m_readThread;

    //Status Bar
    QLabel *PLCStatusLED;
    QLabel *PLCLabel;
    QLabel *DetectorStatusLED;
    QLabel *detLabel;


};
#endif // MAINWINDOW_H
