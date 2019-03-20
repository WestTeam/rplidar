// Copyright (c) 2018 All Rights Reserved WestBot

#ifndef WESTBOT_RPLIDAR_RPLIDAR_HPP_
#define WESTBOT_RPLIDAR_RPLIDAR_HPP_

#include <QString>

namespace
{
    const quint32 DEFAULT_TIMEOUT =  2000;
}

namespace WestBot {
namespace RPLidar {

typedef struct measurementNode
{
    quint8    sync_quality;      // syncbit:1;syncbit_inverse:1;quality:6;
    quint16   angle_q6_checkbit; // check_bit:1;angle_q6:15;
    quint16   distance_q2;
    qint16    pos_x;
    qint16    pos_y;
    qint16    pos_teta;
} __attribute__((packed)) measurementNode_t;

class RPLidarPrivate;

class RPLidar
{
public:
    RPLidar( const QString& port, quint32 baudrate = 256000 );
    ~RPLidar();

    bool connect();
    void disconnect();

    bool isConnected();

    bool reset( quint32 timeout = DEFAULT_TIMEOUT );

    bool setMotorPwm( quint16 pwm );
    bool startMotor();
    bool stopMotor();
    bool checkMotorCtrlSupport( quint32 timeout = DEFAULT_TIMEOUT );

    bool startScan( bool force = false, bool autoExpressMode = true );
    bool startScanNormal( bool force, quint32 timeout = DEFAULT_TIMEOUT );
    bool startScanNormalRobotPos( bool force, quint32 timeout = DEFAULT_TIMEOUT  );

    bool startScanExpress(
        bool fixedAngle,
        quint32 timeout = DEFAULT_TIMEOUT );
    bool stopScan( quint32 timeout = DEFAULT_TIMEOUT );
    bool checkExpressScanSupported( quint32 timeout = DEFAULT_TIMEOUT );

    bool checkHealth( quint32 timeout = DEFAULT_TIMEOUT );
    QString getDeviceInfo( quint32 timeout = DEFAULT_TIMEOUT );
    QString getSampleDurationUs( quint32 timeout = DEFAULT_TIMEOUT );

    bool getFrequency(
        bool inExpressMode,
        size_t count,
        float& frequency,
        bool& is4kmode );

    bool grabScanData(
        measurementNode_t* nodeBuffer,
        size_t& count,
        quint32 timeout = DEFAULT_TIMEOUT );

    bool ascendScanData( measurementNode_t* nodeBuffer, size_t count );

private:
    RPLidarPrivate* _d;
};

}
}

#endif // WESTBOT_RPLIDAR_RPLIDAR_HPP_
