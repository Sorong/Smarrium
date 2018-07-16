#include "camera.h"
#include <QDebug>
#include <fstream>
#include <iostream>
#include <QThread>

Camera::Camera() : defaultImage(":/images/images/default.ppm"), VirtualSensor(EVENT_INTERVAL)
{
    this->referenceImageData = new unsigned char[camera.getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB)];
    this->imageData = new unsigned char[camera.getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB)];
    this->camera.open();
}

void Camera::takeReferncePicture(){
    this->takePicture(this->referenceImageData);
    QImage image(this->referenceImageData, CAMERA_WIDTH, CAMERA_HEIGHT, QImage::Format_RGB888);
    this->referenceImage = image.copy();

}
void Camera::takePicture(unsigned char* rawData)
{

    this->camera.grab();
    this->camera.retrieve( rawData, raspicam::RASPICAM_FORMAT_RGB);
}

void Camera::takePicture(){
    this->camera.grab();
    this->camera.retrieve( this->imageData, raspicam::RASPICAM_FORMAT_RGB);
    QImage imageTemp(this->imageData, CAMERA_WIDTH, CAMERA_HEIGHT, QImage::Format_RGB888);
    this->image = imageTemp.copy();
}

QImage Camera::getReferenceImage(){
    if(this->referenceImage.format() == QImage::Format_Invalid){
        return this->defaultImage;
    }
    return this->referenceImage;
}

QImage Camera::getImage(){
    if(this->image.format() == QImage::Format_Invalid){
        return this->defaultImage;
    }
    return this->image;
}

bool Camera::saveReference(){
    if(!this->referenceImage.save(directory + "/referenz.ppm")){
        qDebug() << "Refernze nicht gespeichert";
        return false;
    }
    return true;
}

bool Camera::saveImage(){
    if(!this->image.save(directory + "/image.ppm")){
        qDebug() << "Image nicht gespeichert";
        return false;
    }
    return true;
}



QImage Camera::retriveDifferencePicture()
{
    QString returnSuccess = "Done\n";

    QProcess pythonScript;
    QString program = "python";
    QStringList params;
    params <<  directory + "script.py" << "-f" << directory + "/referenz.ppm" << "-s" << directory + "/image.ppm" << "-o" <<directory + "/diference.ppm";
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

sensors_type_t Camera::getType() const{
    return SENSOR_TYPE_CAMERA;
}

bool Camera::getEvent(sensors_event_t *event)
{

    memset(event, 0, sizeof(sensors_event_t));

    event->version   = sizeof(sensors_event_t);
    event->sensor_id = _id;
    event->type      = SENSOR_TYPE_CAMERA;
    event->timestamp = QTime::currentTime();

    if (event->light == 65536) {
        return false;
    }
    return true;
}

QString Camera::getSort(){
    return "Camera";
}


SensorBaseType Camera::getRawType(){
    return SensorBaseType::CAMERA;
}

QImage Camera::getDefaultImage(){
    return this->defaultImage;
}
