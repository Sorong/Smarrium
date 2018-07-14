#include "actuatorcamera.h"
#include <QDebug>
#include <fstream>
#include <iostream>
#include <QThread>
ActuatorCamera::ActuatorCamera()
{

}


void ActuatorCamera::takePicture()
{
    this->camera.open();
    QThread::sleep(3);
    this->camera.grab();
    unsigned char* rawData = new unsigned char[ camera.getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB)];
    this->camera.retrieve( rawData, raspicam::RASPICAM_FORMAT_RGB);
    this->picture.load("/home/pi/raspicam_image.ppm", "PPM");
    std::ofstream outFile ( "/home/pi/raspicam_image.ppm",std::ios::binary );
    outFile<<"P6\n"<<this->camera.getWidth() <<" "<<this->camera.getHeight() <<" 255\n";
    outFile.write ( ( char* ) rawData, this->camera.getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB ) );
    if(this->picture.save("/home/pi/test.jpg", NULL, 100)){
        qDebug() << "Saved";
    }
    else{
        qDebug() << "Failed";
    }

}

QImage ActuatorCamera::retrivePicture()
{
    QProcess pythonScript;
    QStringList params;
    params << "script.py -arg1 picture1, -arg2 picture2";
    pythonScript.start("python", params);
    pythonScript.waitForFinished(-1);
    QString p_stdout = p.readAll();
    qDebug() << p_stdout;
    return QVariant();
}

