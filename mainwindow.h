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
#include <QtEndian>
#include "autocontrol.h"

#include "xmlparser.h"


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

    void on_startManualButton_released();

    void on_upButton_pressed();


    void on_leftButton_pressed();

    void on_backwardButton_pressed();

    void on_downButton_pressed();

    void on_forwardButton_pressed();

    void on_rightBtn_pressed();



    void on_returnZero_released();

    void on_manualRadioButton_clicked(bool checked);

    void on_autoRadioButton_clicked(bool checked);

    void on_pauseAutoButton_released();


    void on_generateCmdAction_triggered();

signals:
    void startReadStatus();
    void startAutoControl();

public slots:
    void synState();
    void progressBar(int progress);

private:
    Ui::MainWindow *ui;
    connectPLC subWinconnectPLC;
    QThread m_readThread;

    //Status Bar
    QLabel *PLCStatusLED;
    QLabel *PLCLabel;
    QLabel *DetectorStatusLED;
    QLabel *detLabel;

    QThread *autoThread;

    longword processReal(QString lineEdit);


};
#endif // MAINWINDOW_H
