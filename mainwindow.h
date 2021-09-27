#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include "connectplc.h"
#include "controller.h"
#include "QLabel"
#include "utilities.h"

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

private:
    Ui::MainWindow *ui;
    connectPLC subWinconnectPLC;

    //Status Bar
    QLabel *PLCStatusLED;
    QLabel *PLCLabel;
    QLabel *DetectorStatusLED;
    QLabel *detLabel;


};
#endif // MAINWINDOW_H
