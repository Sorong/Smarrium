QT += quick
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    frontend/example.cpp \
    logic/gpiomanager.cpp \
    frontend/actorfactory.cpp \
    frontend/sensorfactory.cpp \
    logic/gpiolist.cpp \
    logic/gpiomap.cpp \
    backend/Sensors/HumiditySensor/HumiditySensor.cpp \
    backend/Sensors/LightSensor/LightSensor.cpp \
    backend/Sensors/TemperatureSensor/TemperatureSensor.cpp \
    backend/Sensors/UVSensor/UVSensor.cpp \
    backend/Sensors/Bcm2835Interface.cpp \
    backend/Actuator/Actuator.cpp


RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

INCLUDEPATH += $$[QT_SYSROOT]/usr/local/include
LIBS += -L$$[QT_SYSROOT]/usr/local/lib -lwiringPi -lbcm2835

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    frontend/example.h \
    logic/gpio.h \
    logic/gpiomanager.h \
    frontend/actorfactory.h \
    frontend/sensorfactory.h \
    logic/gpiolist.h \
    logic/gpiomap.h \
    backend/Sensors/HumiditySensor/HumiditySensor.hpp \
    backend/Sensors/LightSensor/LightSensor.hpp \
    backend/Sensors/TemperatureSensor/TemperatureSensor.hpp \
    backend/Sensors/UVSensor/UVSensor.hpp \
    backend/Sensors/Bcm2835Interface.hpp \
    backend/Sensors/Sensor.h \
    logic/configmanager.h \
    backend/Actuator/Actuator.hpp

DISTFILES +=

target.path = /home/pi
INSTALLS += target
