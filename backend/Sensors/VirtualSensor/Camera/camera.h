#ifndef ACTUATORCAMERA_H
#define ACTUATORCAMERA_H
#include <raspicam/raspicam.h>
#include <QTimer>
#include <QPicture>
#include <QImage>
#include <QProcess>
#include "./../virtualsensor.h"
#include "./../../Sensor.h"

#define CAMERA_WIDTH 1280
#define CAMERA_HEIGHT 920
#define EVENT_INTERVAL 1800000
class Camera : VirtualSensor
{
    Q_OBJECT
public:
    Camera();

    void takePicture(unsigned char *rawData);
    void takePicture();
    void takeReferncePicture();

    QImage getReferenceImage();
    QImage getImage();
    QImage retriveDifferencePicture();

    bool saveReference();
    bool saveImage();

    bool getEvent(sensors_event_t*) override;
    sensors_type_t getType() const override;
    SensorBaseType getRawType() override;
    QString getSort() override;

signals:

public slots:

private:
    unsigned char* referenceImageData;
    unsigned char* imageData;
    QImage referenceImage;
    QImage image;
    QImage differencePicture;

    QString directory = "/home/pi/OpenCVScript";

    raspicam::RaspiCam camera;

    QImage defaultImage;

};

#endif // ACTUATORCAMERA_H
