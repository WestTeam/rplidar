// Copyright (c) 2018 All Rights Reserved WestBot

#ifndef WESTBOT_RPLIDAR_RPLIDARPRIVATE_HPP_
#define WESTBOT_RPLIDAR_RPLIDARPRIVATE_HPP_

#include <QString>

#include <3rdparty/rplidar_sdk/include/rplidar.h>

#include "../RPLidar.hpp"

namespace WestBot {
namespace RPLidar {

class RPLidarPrivate
{
public:
    RPLidarPrivate( const QString& port, quint32 baudrate = 115200 );
    ~RPLidarPrivate();

    bool connect();
    void disconnect();

    bool isConnected();

    bool reset( quint32 timeout );

    bool setMotorPwm( quint16 pwm );
    bool startMotor();
    bool stopMotor();
    bool checkMotorCtrlSupport( quint32 timeout );

    bool startScan( bool force = false, bool autoExpressMode = true );
    bool startScanNormal( bool force, quint32 timeout );
    bool startScanExpress( bool fixedAngle, quint32 timeout );
    bool stopScan( quint32 timeout );
    bool checkExpressScanSupported( quint32 timeout );

    bool checkHealth( quint32 timeout );
    QString getDeviceInfo( quint32 timeout );
    QString getSampleDurationUs( quint32 timeout );

    bool getFrequency(
        bool inExpressMode,
        size_t count,
        float& frequency,
        bool& is4kmode );

    bool grabScanData(
        measurementNode_t* nodeBuffer,
        size_t & count,
        quint32 timeout );

    bool ascendScanData( measurementNode_t* nodeBuffer, size_t count );

private:
    const QString _port;
    quint32 _baudrate;
    rp::standalone::rplidar::RPlidarDriver* _lidarDriver;
};

}
}

#endif // WESTBOT_RPLIDAR_RPLIDARPRIVATE_HPP_
