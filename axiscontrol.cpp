#include "axiscontrol.h"


abstractAxisControl::abstractAxisControl()
{
    isAlert = false;
    isReady = false;
    isZero = false;
    isCompleted = false;
}

bool abstractAxisControl::getIsAlert() const
{
    return isAlert;
}

void abstractAxisControl::setIsAlert(bool newIsAlert)
{
    isAlert = newIsAlert;
}

bool abstractAxisControl::getIsReady() const
{
    return isReady;
}

bool abstractAxisControl::getIsZero() const
{
    return isZero;
}

bool abstractAxisControl::getIsCompleted() const
{
    return isCompleted;
}

bool abstractAxisControl::getInit() const
{
    return init;
}

void abstractAxisControl::setInit(bool newInit)
{
    init = newInit;
}

void abstractAxisControl::setStop(bool newStop)
{
    stop = newStop;
}

bool abstractAxisControl::getStartAbsoluteMoation() const
{
    return startAbsoluteMoation;
}

void abstractAxisControl::setStartAbsoluteMoation(bool newStartAbsoluteMoation)
{
    startAbsoluteMoation = newStartAbsoluteMoation;
}

bool abstractAxisControl::getStartRelativeMoation() const
{
    return startRelativeMoation;
}

void abstractAxisControl::setStartRelativeMoation(bool newStartRelativeMoation)
{
    startRelativeMoation = newStartRelativeMoation;
}

longword abstractAxisControl::getCurrentSpeed() const
{
    return currentSpeed;
}

void abstractAxisControl::setCurrentSpeed(longword newCurrentSpeed)
{
    currentSpeed = newCurrentSpeed;
}

longword abstractAxisControl::getCurrentPosition() const
{
    return currentPosition;
}

void abstractAxisControl::setCurrentPosition(longword newCurrentPosition)
{
    currentPosition = newCurrentPosition;
}

longword abstractAxisControl::getTargetSpeed() const
{
    return targetSpeed;
}

void abstractAxisControl::setTargetSpeed(longword newTargetSpeed)
{
    targetSpeed = newTargetSpeed;
}

longword abstractAxisControl::getTargetAbsoltePosition() const
{
    return targetAbsoltePosition;
}

void abstractAxisControl::setTargetAbsoltePosition(longword newTargetAbsoltePosition)
{
    targetAbsoltePosition = newTargetAbsoltePosition;
}

longword abstractAxisControl::getTargetRelativePosition() const
{
    return targetRelativePosition;
}

void abstractAxisControl::setTargetRelativePosition(longword newTargetRelativePosition)
{
    targetRelativePosition = newTargetRelativePosition;
}

xAxis::xAxis()
{
    abstractAxisControl();
    qDebug() << "xAxis constructor";
}
