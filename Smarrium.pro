QT += quick quickcontrols2 svg charts
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
    backend/Actuator/Actuator.cpp \
    backend/RCSwitch/RCSwitch.cpp \
    backend/Sensors/AnalogSensor/MoistureSensor/MoistureSensor.cpp \
    backend/Sensors/AnalogSensor/UVSensor/UVSensor.cpp \
    backend/Sensors/DigitalSensor/HumiditySensor/HumiditySensor.cpp \
    backend/Sensors/DigitalSensor/TemperatureSensor/TemperatureSensor.cpp \
    backend/Sensors/I2CSensor/InfraredTemperatureSensor/InfraredTemperatureSensor.cpp \
    backend/Sensors/I2CSensor/LightSensor/LightSensor.cpp \
    backend/Sensors/ADC.cpp \
    backend/Sensors/Bcm2835Interface.cpp \
    backend/Sensors/Sensor.cpp \
    logic/gpiolist.cpp \
    logic/gpiomanager.cpp \
    logic/gpiomap.cpp \
    main.cpp \
    logic/actuatorlist.cpp \
    logic/channelmanager.cpp \
    logic/channellist.cpp \
    logic/channelmap.cpp \
    logic/sensorlist.cpp \
    logic/sensormap.cpp \
    logic/sensorstringlist.cpp \
    logic/actuatormanager.cpp \
    logic/qmlcontextmanager.cpp \
    backend/Sensors/sensorbasetype.cpp \
    backend/Sensors/sensorconfig.cpp \
    factories/sensorfactory.cpp \
    factories/actuatorfactory.cpp \
    factories/configfactory.cpp \
    backend/Sensors/VirtualSensor/virtualsensor.cpp \
    backend/Sensors/VirtualSensor/Clock/clocksensor.cpp \
    backend/Sensors/VirtualSensor/Camera/camera.cpp \

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =
QMAKE_CXXFLAGS += -DRPI

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

INCLUDEPATH += $$[QT_SYSROOT]/usr/local/include
LIBS += -L$$[QT_SYSROOT]/usr/local/lib -lwiringPi -lbcm2835 -lraspicam

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    backend/Actuator/Actuator.hpp \
    backend/RCSwitch/RCSwitch.h \
    backend/Sensors/AnalogSensor/MoistureSensor/MoistureSensor.hpp \
    backend/Sensors/AnalogSensor/UVSensor/UVSensor.hpp \
    backend/Sensors/AnalogSensor/AnalogSensor.hpp \
    backend/Sensors/DigitalSensor/HumiditySensor/HumiditySensor.hpp \
    backend/Sensors/DigitalSensor/TemperatureSensor/TemperatureSensor.hpp \
    backend/Sensors/DigitalSensor/DigitalSensor.hpp \
    backend/Sensors/I2CSensor/InfraredTemperatureSensor/InfraredTemperatureSensor.hpp \
    backend/Sensors/I2CSensor/LightSensor/LightSensor.hpp \
    backend/Sensors/I2CSensor/I2CSensor.hpp \
    backend/Sensors/ADC.hpp \
    backend/Sensors/Bcm2835Interface.hpp \
    backend/Sensors/Sensor.h \
    logic/models/actuatorlist.h \
    logic/gpio.h \
    logic/gpiolist.h \
    logic/gpiomanager.h \
    logic/gpiomap.h \
    logic/actuatorlist.h \
    logic/channelmanager.h \
    logic/channel.h \
    logic/channellist.h \
    logic/channelmap.h \
    logic/sensorlist.h \
    logic/sensormap.h \
    logic/sensorstringlist.h \
    logic/actuatormanager.h \
    logic/qmlcontextmanager.h \
    backend/Sensors/sensorbasetype.h \
    backend/Sensors/sensorconfig.h \
    factories/sensorfactory.h \
    factories/actuatorfactory.h \
    factories/configfactory.h \
    backend/Sensors/VirtualSensor/virtualsensor.h \
    backend/Sensors/VirtualSensor/Clock/clocksensor.h \
    backend/Sensors/VirtualSensor/Camera/camera.h \


DISTFILES +=

target.path = /home/pi
INSTALLS += target


