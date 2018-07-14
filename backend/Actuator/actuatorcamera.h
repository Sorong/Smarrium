#ifndef ACTUATORCAMERA_H
#define ACTUATORCAMERA_H
#include <raspicam/raspicam.h>
#include <QTimer>
#include <QPicture>
#include <QImage>
#include <QProcess>

class ActuatorCamera : public QTimer
{
    Q_OBJECT
public:
    ActuatorCamera();

    void takePicture();

    //QImage retriveDifferencePicture();

signals:

public slots:

private:
    QImage referncePicture;
    QImage differancePicture;
    QImage picture;

    raspicam::RaspiCam camera;

};

#endif // ACTUATORCAMERA_H
