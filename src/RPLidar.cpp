// Copyright (c) 2018 All Rights Reserved WestBot

#include <WestBot/RPLidar/RPLidar.hpp>

#include <WestBot/RPLidar/private/RPLidarPrivate.hpp>

using namespace WestBot::RPLidar;

RPLidar::RPLidar( const QString& port, quint32 baudrate )
    : _d( new RPLidarPrivate( port, baudrate ) )
{
}

RPLidar::~RPLidar()
{
    delete _d;
}

bool RPLidar::connect()
{
    return _d->connect();
}

void RPLidar::disconnect()
{
    _d->disconnect();
}

bool RPLidar::isConnected()
{
    return _d->isConnected();
}

bool RPLidar::reset( quint32 timeout )
{
    return _d->reset( timeout );
}

bool RPLidar::setMotorPwm( quint16 pwm )
{
    return _d->setMotorPwm( pwm );
}

bool RPLidar::startMotor()
{
    return _d->startMotor();
}

bool RPLidar::stopMotor()
{
    return _d->stopMotor();
}

bool RPLidar::checkMotorCtrlSupport( quint32 timeout )
{
    return _d->checkMotorCtrlSupport( timeout );
}

bool RPLidar::startScan( bool force , bool autoExpressMode )
{
    return _d->startScan( force, autoExpressMode );
}

bool RPLidar::startScanNormal( bool force, quint32 timeout )
{
    return _d->startScanNormal( force, timeout );
}

bool RPLidar::startScanNormalRobotPos( bool force, quint32 timeout )
{
    return _d->startScanNormalRobotPos( force, timeout );
}

bool RPLidar::startScanExpress( bool fixedAngle, quint32 timeout )
{
    return _d->startScanExpress( fixedAngle, timeout );
}

bool RPLidar::stopScan( quint32 timeout )
{
    return _d->stopScan( timeout );
}

bool RPLidar::checkExpressScanSupported( quint32 timeout )
{
    return _d->checkExpressScanSupported( timeout );
}

bool RPLidar::checkHealth( quint32 timeout )
{
    return _d->checkHealth( timeout );
}

QString RPLidar::getDeviceInfo( quint32 timeout )
{
    return _d->getDeviceInfo( timeout );
}

QString RPLidar::getSampleDurationUs( quint32 timeout )
{
    return _d->getSampleDurationUs( timeout );
}

bool RPLidar::getFrequency(
    bool inExpressMode,
    size_t count,
    float& frequency,
    bool& is4kmode )
{
    return _d->getFrequency( inExpressMode, count, frequency, is4kmode );
}

bool RPLidar::grabScanData(
    measurementNode_t* nodeBuffer,
    size_t & count,
    quint32 timeout )
{
    return _d->grabScanData( nodeBuffer, count, timeout );
}

bool RPLidar::ascendScanData( measurementNode_t* nodeBuffer, size_t count )
{
    return _d->ascendScanData( nodeBuffer, count );
}
