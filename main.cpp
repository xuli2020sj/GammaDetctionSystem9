#include "mainwindow.h"

#include <QApplication>
#include "xmlparser.h"
#include "log.h"

#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
//    auto xml = new xmlParser;
//    cout << xml->createXML() << endl;
    auto log = new Log;
    delete log;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
