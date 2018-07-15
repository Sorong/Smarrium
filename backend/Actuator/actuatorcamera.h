#ifndef ACTUATORCAMERA_H
#define ACTUATORCAMERA_H
#include <raspicam/raspicam.h>
#include <QTimer>
#include <QPicture>
#include <QImage>
#include <QProcess>

#define CAMERA_WIDTH 1280
#define CAMERA_HEIGHT 920
class ActuatorCamera : public QTimer
{
    Q_OBJECT
public:
    ActuatorCamera();

    void takePicture(unsigned char *rawData);
    void takePicture();
    void takeReferncePicture();

    QImage getReferenceImage();
    QImage getImage();
    QImage retriveDifferencePicture();

    bool saveReference();
    bool saveImage();

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
