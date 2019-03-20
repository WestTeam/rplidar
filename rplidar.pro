# Copyright (c) 2018 All Rights Reserved WestBot

TARGET = RPLidar

QT += core
QT -= gui

TEMPLATE = lib

INCLUDEPATH += include

HEADERS += include/WestBot/RPLidar/private/RPLidarPrivate.hpp \
           include/WestBot/RPLidar/RPLidar.hpp

SOURCES += src/RPLidarPrivate.cpp \
           src/RPLidar.cpp 

INCLUDEPATH += ../HumanAfterAll/include/
LIBS += -L../rplidar/libs -lHumanAfterAll

INCLUDEPATH += ../rplidar/3rdparty/rplidar_sdk/sdk/sdk/src/
LIBS += -L../rplidar/3rdparty/rplidar_sdk/sdk/output/Linux/Release -lrplidar_sdk

DEFINES += WESTBOT_RPLIDARSHAREDLIB_LIBRARY

DEFINES += QT_DEPRECATED_WARNINGS
