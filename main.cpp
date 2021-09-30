#include "mainwindow.h"

#include <QApplication>
#include "xmlparser.h"

#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    auto xml = new xmlParser;
    cout << xml->createXML() << endl;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
