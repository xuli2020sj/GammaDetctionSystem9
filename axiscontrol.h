#ifndef AXISCONTROL_H
#define AXISCONTROL_H

#include "snap7.h"
#include "qdebug.h"

class abstractAxisControl
{
public:
    abstractAxisControl();
    bool startAxisAbsolute();
    bool startAxisRelative();
    bool getIsAlert() const;

    void setIsAlert(bool newIsAlert);
    bool getIsReady() const;
    bool getIsZero() const;


    bool getIsCompleted() const;

    bool getInit() const;
    void setInit(bool newInit);

    void setStop(bool newStop);

    bool getStartAbsoluteMoation() const;
    void setStartAbsoluteMoation(bool newStartAbsoluteMoation);

    bool getStartRelativeMoation() const;
    void setStartRelativeMoation(bool newStartRelativeMoation);

    longword getCurrentSpeed() const;
    void setCurrentSpeed(longword newCurrentSpeed);

    longword getCurrentPosition() const;
    void setCurrentPosition(longword newCurrentPosition);

    longword getTargetSpeed() const;
    void setTargetSpeed(longword newTargetSpeed);

    longword getTargetAbsoltePosition() const;
    void setTargetAbsoltePosition(longword newTargetAbsoltePosition);

    longword getTargetRelativePosition() const;
    void setTargetRelativePosition(longword newTargetRelativePosition);

protected:
    bool isAlert;
    bool isReady;
    bool isZero;
    bool isCompleted;
    bool init;
    bool stop;
    bool startAbsoluteMoation;
    bool startRelativeMoation;
    longword currentSpeed;
    longword currentPosition;
    longword targetSpeed;
    longword targetAbsoltePosition;
    longword targetRelativePosition;
};

class xAxis : public abstractAxisControl
{
public:
    xAxis();
};

class yAxis : public abstractAxisControl
{
public:
    yAxis();
};

class zAxis : public abstractAxisControl
{
public:
    zAxis();
};

#endif // AXISCONTROL_H
