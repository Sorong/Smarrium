#include "actuatorcamera.h"
#include <QDebug>
#include <fstream>
#include <iostream>
#include <QThread>
ActuatorCamera::ActuatorCamera() : defaultImage(CAMERA_WIDTH, CAMERA_HEIGHT, QImage::Format_RGBA8888)
{
    defaultImage.fill(Qt::GlobalColor::blue);
    this->referenceImageData = new unsigned char[camera.getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB)];
    this->imageData = new unsigned char[camera.getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB)];
    this->camera.open();
}

void ActuatorCamera::takeReferncePicture(){
    this->takePicture(this->referenceImageData);
    QImage image(this->referenceImageData, CAMERA_WIDTH, CAMERA_HEIGHT, QImage::Format_RGB888);
    this->referenceImage = image.copy();

}
void ActuatorCamera::takePicture(unsigned char* rawData)
{

    this->camera.grab();
    this->camera.retrieve( rawData, raspicam::RASPICAM_FORMAT_RGB);
}

void ActuatorCamera::takePicture(){
    this->camera.grab();
    this->camera.retrieve( this->imageData, raspicam::RASPICAM_FORMAT_RGB);
    QImage imageTemp(this->imageData, CAMERA_WIDTH, CAMERA_HEIGHT, QImage::Format_RGB888);
    this->image = imageTemp.copy();
}

QImage ActuatorCamera::getReferenceImage(){
    if(this->referenceImage.format() == QImage::Format_Invalid){
        return this->defaultImage;
    }
    return this->referenceImage;
}

QImage ActuatorCamera::getImage(){
    if(this->image.format() == QImage::Format_Invalid){
        return this->defaultImage;
    }
    return this->image;
}

bool ActuatorCamera::saveReference(){
    if(!this->referenceImage.save(directory + "/referenz.ppm")){
        qDebug() << "Refernze nicht gespeichert";
        return false;
    }
    return true;
}

bool ActuatorCamera::saveImage(){
    if(!this->image.save(directory + "/image.ppm")){
        qDebug() << "Image nicht gespeichert";
        return false;
    }
    return true;
}



QImage ActuatorCamera::retriveDifferencePicture()
{
    QString returnSuccess = "Done\n";

    QProcess pythonScript;
    QString program = "python";
    QStringList params;
    params << directory + "/script.py" << "-f" << directory + "/referenz.ppm" << "-s" << directory + "/image.ppm" << "-o" <<directory + "/diference.ppm";
    if(!saveReference()){
        return this->defaultImage;
    }
    if(!saveImage()){
        return this->defaultImage;
    }
    pythonScript.start(program, params);
    pythonScript.waitForFinished(-1);
    QString returnString = pythonScript.readAllStandardOutput();
    QString errorString = pythonScript.readAllStandardError();
    qDebug() << errorString;
    if( !returnString.compare(returnSuccess, Qt::CaseInsensitive) ){
        return this->defaultImage;
    }
    QImage image(directory + "/difference.ppm");
    this->differencePicture = image.copy();
    return this->differencePicture;
}

