// Copyright (c) 2018 All Rights Reserved WestBot

#include <QDebug>
#include <QStringBuilder>

#include <WestBot/HumanAfterAll/Category.hpp>

#include <WestBot/RPLidar/private/RPLidarPrivate.hpp>

using namespace rp::standalone::rplidar;
using namespace WestBot;
using namespace WestBot::RPLidar;

namespace
{
    HUMANAFTERALL_LOGGING_CATEGORY( LOG, "WestBot.RPLidar.RPLidar" )

    QString deviceInfoToString( rplidar_response_device_info_t deviceInfo )
    {
        QString info =
            QString( "RPLidar infos:\r\nModel: %1\r\nFirmware version: %2.%3\r\nHardware version: %4\r\n" )
                .arg( deviceInfo.model )
                .arg( deviceInfo.firmware_version >> 8 )
                .arg( deviceInfo.firmware_version & 0xFF )
                .arg( deviceInfo.hardware_version );

        QString serial;
        serial = "RPLIDAR S/N: ";

        for( int pos = 0; pos < 16 ; ++pos )
        {
            serial += QString( "%1" ).arg( deviceInfo.serialnum[ pos ], 2, 16, QChar( '0' ) ).toUpper();
        }

        info = QString( info % serial );
        return info;
    }

    QString rateInfoToString( rplidar_response_sample_rate_t rateInfo )
    {
        QString rate = 
            QString( "Sample duration: %1us Express sample duration: %2us" )
                .arg( rateInfo.std_sample_duration_us )
                .arg( rateInfo.express_sample_duration_us );
        return rate;
    }
}

RPLidarPrivate::RPLidarPrivate( const QString& port, quint32 baudrate )
    : _port( port )
    , _baudrate( baudrate )
    , _lidarDriver( RPlidarDriver::CreateDriver(
                        RPlidarDriver::DRIVER_TYPE_SERIALPORT ) )
{
}

RPLidarPrivate::~RPLidarPrivate()
{
    disconnect();
    RPlidarDriver::DisposeDriver( _lidarDriver );
}

bool RPLidarPrivate::connect()
{
    if( IS_FAIL( _lidarDriver->connect(
            _port.toStdString().c_str(), _baudrate ) ) )
    {
        qWarning()
            << "Error, cannot bind to the specified serial port:" << _port;
        return false;
    }

    return true;
}

void RPLidarPrivate::disconnect()
{
    _lidarDriver->disconnect();
}

bool RPLidarPrivate::isConnected()
{
    return _lidarDriver->isConnected();
}

bool RPLidarPrivate::reset( quint32 timeout )
{
    return IS_FAIL( _lidarDriver->reset( timeout ) );
}

bool RPLidarPrivate::setMotorPwm( quint16 pwm )
{
    return IS_FAIL( _lidarDriver->setMotorPWM( pwm ) );
}

bool RPLidarPrivate::startMotor()
{
    return IS_FAIL( _lidarDriver->startMotor() );
}

bool RPLidarPrivate::stopMotor()
{
    return IS_FAIL( _lidarDriver->stopMotor() );
}

bool RPLidarPrivate::checkMotorCtrlSupport( quint32 timeout )
{
    bool motorCtrlSupport;
    if( IS_FAIL( _lidarDriver->checkMotorCtrlSupport(
            motorCtrlSupport, timeout ) ) )
    {
        qWarning() << "Error, cannot check motor control support.";
        return false;
    }

    return motorCtrlSupport;
}

bool RPLidarPrivate::startScan( bool force , bool autoExpressMode )
{
    return IS_FAIL( _lidarDriver->startScan( force, autoExpressMode ) );
}

bool RPLidarPrivate::startScanNormal( bool force, quint32 timeout )
{
    return IS_FAIL( _lidarDriver->startScanNormal( force, timeout ) );
}

bool RPLidarPrivate::startScanExpress( bool fixedAngle, quint32 timeout )
{
    return IS_FAIL( _lidarDriver->startScanExpress( fixedAngle, timeout ) );
}

bool RPLidarPrivate::stopScan( quint32 timeout )
{
    return IS_FAIL( _lidarDriver->stop( timeout ) );
}

bool RPLidarPrivate::checkExpressScanSupported( quint32 timeout )
{
    bool expressScanSupport;
    if( IS_FAIL( _lidarDriver->checkExpressScanSupported(
            expressScanSupport, timeout ) ) )
    {
        qWarning() << "Error, cannot check express scan support.";
        return false;
    }

    return expressScanSupport;
}

bool RPLidarPrivate::checkHealth( quint32 timeout )
{
    u_result operationResult;
    rplidar_response_device_health_t healthInfo;

    operationResult = _lidarDriver->getHealth( healthInfo, timeout );
    if( IS_FAIL( operationResult ) )
    {
        qWarning() << "Error, cannot retrieve the lidar health code";
        return false;
    }

    qDebug() << "RPLidar health status:" << healthInfo.status;
    if( RPLIDAR_STATUS_ERROR == healthInfo.status )
    {
        qWarning() << "Error, rplidar internal error detected."
                      " Please reboot the device to retry.";
        reset( timeout ); // automatically reboot de device
        return false;
    }

    return true;
}

QString RPLidarPrivate::getDeviceInfo( quint32 timeout )
{
    u_result operationResult;
    rplidar_response_device_info_t deviceInfo;

    operationResult = _lidarDriver->getDeviceInfo( deviceInfo, timeout );

    if( IS_FAIL( operationResult ) )
    {
        qWarning() << "Error, cannot get device info.";
        return QString();
    }

    return deviceInfoToString( deviceInfo );
}

QString RPLidarPrivate::getSampleDurationUs( quint32 timeout )
{
    u_result operationResult;
    rplidar_response_sample_rate_t rateInfo;

    operationResult = _lidarDriver->getSampleDuration_uS( rateInfo, timeout );

    if( IS_FAIL( operationResult ) )
    {
        qWarning() << "Error, cannot get rate info.";
        return QString();
    }

    return rateInfoToString( rateInfo );
}

bool RPLidarPrivate::getFrequency(
    bool inExpressMode,
    size_t count,
    float& frequency,
    bool& is4kmode )
{
    return IS_FAIL( _lidarDriver->getFrequency(
        inExpressMode,
        count,
        frequency,
        is4kmode ) );
}

bool RPLidarPrivate::grabScanData(
    measurementNode_t* nodeBuffer,
    size_t & count,
    quint32 timeout )
{
    u_result operationResult;

    operationResult = _lidarDriver->grabScanData( ( rplidar_response_measurement_node_t* )nodeBuffer, count, timeout );

    if( IS_FAIL( operationResult ) )
    {
        qWarning() << "Error, cannot grab scan data";
        return false;
    }

    return true;
}

bool RPLidarPrivate::ascendScanData(
    measurementNode_t* nodeBuffer,
    size_t count )
{
    u_result operationResult;

    operationResult = _lidarDriver->ascendScanData( (rplidar_response_measurement_node_t*) nodeBuffer, count );

    if( IS_FAIL( operationResult ) )
    {
        qWarning() << "Error, cannot ascend scan data";
        return false;
    }

    return true;
}
