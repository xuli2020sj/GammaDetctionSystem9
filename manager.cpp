#include "manager.h"
#include "qeventloop.h"
#include "qtimer.h"


Manager::Manager()
{

}



void Manager::readStatus()
{
    Controller *controller = Controller::controller();
    while(true)
    {
        std::vector<QString> RBString;
        RBString.resize(68);
        if (controller->Client->Connected())
        {
            controller->readVal(0x84, 1, 0, 68, 0x02, &RBuffer);
            for (int index = 0; index < 68 ; index++) {
                //controller->readVal(0x84, 1, index, 1, 0x02, &RBuffer[index]);
                RBString[index] = QString("%1").arg(QString::number(RBuffer[index],10).toUInt(), 8, 2, QLatin1Char('0'));
            }
        }
        else {
            controller->connectPLC();
        }

    dataProcessing(RBString);
    emit stateReady();
    sleep(500);
    }
}

void Manager::sleep(float time)
{
    QEventLoop loop;
    QTimer::singleShot(time, &loop, SLOT(quit()));
    loop.exec();
}

void Manager::dataProcessing(std::vector<QString> dbData)
{
    Controller *controller = Controller::controller();

    auto dbs2 = dbData[43];

    auto dbX0 = dbData[0];
    auto dbX1 = dbData[1];
    auto dbX3 = dbData[3];
    auto dbX4 = dbData[4];
    auto dbX5 = dbData[5];

    auto currentXPos = dbData[44] + dbData[45] + dbData[46] +dbData[47];
    controller->xAxis.setCurrentPosition(binToFloat(currentXPos));
    auto currentYPos = dbData[48] + dbData[49] + dbData[50] +dbData[51];
    controller->yAxis.setCurrentPosition(binToFloat(currentYPos));
    auto currentZPos = dbData[52] + dbData[53] + dbData[54] +dbData[55];
    controller->zAxis.setCurrentPosition(binToFloat(currentZPos));

    auto currentXSpeed = dbData[56] + dbData[57] + dbData[58] + dbData[59];
    controller->xAxis.setCurrentSpeed(binToFloat(currentXSpeed));
    auto currentYSpeed = dbData[60] + dbData[61] + dbData[62] + dbData[63];
    controller->yAxis.setCurrentSpeed(binToFloat(currentYSpeed));
    auto currentZSpeed = dbData[64] + dbData[65] + dbData[66] + dbData[67];
    controller->zAxis.setCurrentSpeed(binToFloat(currentZSpeed));

    auto targetXAbsolutePos = dbData[6] + dbData[7] + dbData[8] + dbData[9];
    controller->xAxis.setTargetAbsoltePosition(binToFloat(targetXAbsolutePos));
    auto targetYAbsolutePos = dbData[10] + dbData[11] + dbData[12] + dbData[13];
    controller->yAxis.setTargetAbsoltePosition(binToFloat(targetYAbsolutePos));
    auto targetZAbsolutePos = dbData[14] + dbData[15] + dbData[16] + dbData[17];
    controller->zAxis.setTargetAbsoltePosition(binToFloat(targetZAbsolutePos));

    auto targetXRelativePos = dbData[18] + dbData[19] + dbData[20] + dbData[21];
    controller->xAxis.setTargetRelativePosition(binToFloat(targetXRelativePos));
    auto targetYRelativePos = dbData[22] + dbData[23] + dbData[24] + dbData[25];
    controller->yAxis.setTargetRelativePosition(binToFloat(targetYRelativePos));
    auto targetZRelativePos = dbData[26] + dbData[27] + dbData[28] + dbData[29];
    controller->zAxis.setTargetRelativePosition(binToFloat(targetZRelativePos));

    auto targetXSpeed = dbData[30] + dbData[31] + dbData[32] + dbData[33];
    controller->xAxis.setTargetSpeed(binToFloat(targetXSpeed));
    auto targetYSpeed = dbData[30] + dbData[31] + dbData[32] + dbData[33];
    controller->yAxis.setTargetSpeed(binToFloat(targetYSpeed));
    auto targetZSpeed = dbData[30] + dbData[31] + dbData[32] + dbData[33];
    controller->zAxis.setTargetSpeed(binToFloat(targetZSpeed));

    controller->xAxis.setIsReady(dbData[42].mid(3,1).toInt());
    controller->yAxis.setIsReady(dbData[42].mid(2,1).toInt());
    controller->zAxis.setIsReady(dbData[42].mid(1,1).toInt());

    controller->xAxis.setIsAlert(dbData[42].mid(6, 1).toInt());
    controller->yAxis.setIsAlert(dbData[42].mid(5, 1).toInt());
    controller->zAxis.setIsAlert(dbData[42].mid(4, 1).toInt());

    controller->xAxis.setIsZero(dbs2.mid(7, 1).toInt());
    controller->yAxis.setIsZero(dbs2.mid(6, 1).toInt());
    controller->zAxis.setIsZero(dbs2.mid(5, 1).toInt());

    controller->xAxis.setIsCompleted(dbs2.mid(4,1).toInt());
    controller->yAxis.setIsCompleted(dbs2.mid(3,1).toInt());
    controller->zAxis.setIsCompleted(dbs2.mid(2,1).toInt());

    controller->xAxis.setStop(dbX0.mid(4,1).toInt());
    controller->yAxis.setStop(dbX0.mid(3,1).toInt());
    controller->zAxis.setStop(dbX0.mid(2,1).toInt());

    controller->xAxis.setIsAbsoluteMoationManual(dbX1.mid(7,1).toInt());
    controller->yAxis.setIsAbsoluteMoationManual(dbX1.mid(6,1).toInt());
    controller->zAxis.setIsAbsoluteMoationManual(dbX1.mid(5,1).toInt());
    controller->xAxis.setIsRelativeMoationManual(dbX1.mid(4,1).toInt());
    controller->yAxis.setIsRelativeMoationManual(dbX1.mid(3,1).toInt());
    controller->zAxis.setIsRelativeMoationManual(dbX1.mid(2,1).toInt());

    controller->xAxis.setIsJogPlus(dbData[2].mid(7,1).toInt());
    controller->yAxis.setIsJogPlus(dbData[2].mid(5,1).toInt());
    controller->zAxis.setIsJogPlus(dbData[2].mid(3,1).toInt());
    controller->xAxis.setIsJogNegative(dbData[2].mid(6,1).toInt());
    controller->yAxis.setIsJogNegative(dbData[2].mid(4,1).toInt());
    controller->zAxis.setIsJogNegative(dbData[2].mid(2,1).toInt());

    controller->xAxis.setIsAbsoluteMoationAuto(dbX3.mid(7,1).toInt());
    controller->yAxis.setIsAbsoluteMoationAuto(dbX3.mid(6,1).toInt());
    controller->zAxis.setIsAbsoluteMoationAuto(dbX3.mid(5,1).toInt());
    controller->xAxis.setIsRelativeMoationAuto(dbX3.mid(4,1).toInt());
    controller->yAxis.setIsRelativeMoationAuto(dbX3.mid(3,1).toInt());
    controller->zAxis.setIsRelativeMoationAuto(dbX3.mid(2,1).toInt());



    controller->xAxis.setUpLimit(dbX4.mid(7,1).toInt());
    controller->yAxis.setUpLimit(dbX4.mid(6,1).toInt());
    controller->zAxis.setUpLimit(dbX4.mid(5,1).toInt());
    controller->xAxis.setDownLimit(dbX4.mid(4,1).toInt());
    controller->yAxis.setDownLimit(dbX4.mid(3,1).toInt());
    controller->zAxis.setDownLimit(dbX4.mid(2,1).toInt());

    controller->xAxis.setInit(dbX5.mid(7,1).toInt());
    controller->yAxis.setInit(dbX5.mid(6,1).toInt());
    controller->zAxis.setInit(dbX5.mid(5,1).toInt());
    
    controller->xAxis.setLocalOrRemote(dbX0.mid(7,1).toInt());
    controller->xAxis.setStopAllAxis(dbX0.mid(6,1).toInt());
    controller->xAxis.setResetAllAxis(dbX0.mid(5,1).toInt());
    controller->xAxis.setLocalOrRemoteState(dbData[42].mid(7,1).toInt());
}



float Manager::binToFloat(const QString &data)
{
    bool ok;
    int sign = 1;
    QByteArray array = data.toUtf8();
    //array = QByteArray::number(array.toLongLong(&ok,16),2); //convert hex to binary -you don't need this since your incoming data is binary
    if(array.length()==32) {
        if(array.at(0)=='1')  sign =-1;                       // if bit 0 is 1 number is negative
        array.remove(0,1);                                     // remove sign bit
    }
    QByteArray fraction =array.right(23);   //get the fractional part
    double mantissa = 0;
    for(int i=0;i<fraction.length();i++)     // iterate through the array to claculate the fraction as a decimal.
        if(fraction.at(i)=='1')     mantissa += 1.0/(pow(2,i+1));
    int exponent = array.left(array.length()-23).toLongLong(&ok,2)-127;     //claculate the exponent
    auto res = QString::number( sign*pow(2,exponent)*(mantissa+1.0),'f', 5 );
    return res.toDouble();

}

static QString toHex(quint32 value, bool bigEndian)
{
    QByteArray ba;
    if (bigEndian) {
        ba.append(char(value >> 24));
        ba.append(char(value >> 16));
        ba.append(char(value >>  8));
        ba.append(char(value >>  0));
    } else {
        ba.append(char(value >>  0));
        ba.append(char(value >>  8));
        ba.append(char(value >> 16));
        ba.append(char(value >> 24));
    }
    return ba.toHex().toUpper();
}


