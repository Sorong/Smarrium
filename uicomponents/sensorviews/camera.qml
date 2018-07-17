import QtQuick 2.0
import QtCharts 2.2
import QtQuick.Controls 1.4 as QSS1_4
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4


Row{

    Rectangle {
        width: (sensorListPane.width-sensorListScrollBar.width) * 0.12
        height: sensorListPane.height * 0.5
        color: "azure"
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            text: name
        }

    }

    Rectangle {
        width: (sensorListPane.width-sensorListScrollBar.width) * 0.2
        height: sensorListPane.height * 0.5
        color: "azure"
        Image {
            id: camera
            width : parent.width
            height : parent.height
            source: applicationPath + "/OpenCVScript/difference.ppm"
            Timer {
                interval: 600000; running: true; repeat: true;
                onTriggered: function() {
                    camera.source = applicationPath + "/OpenCVScript/difference.ppm";
                }
            }
        }
    }

    Rectangle {
        width: (sensorListPane.width-sensorListScrollBar.width) * 0.63
        height: sensorListPane.height * 0.5
        color: "azure"
    }


    Rectangle {
        width: (sensorListPane.width-sensorListScrollBar.width) * 0.05
        height: sensorListPane.height * 0.5
        color: "azure"


        RoundButton {
            id: removeSensor
            anchors.bottom: parent.bottom
            property int mode : 0
            property int index: 0
            property string sensor : ""
            property string option: ""
            icon { source:"/icons/svg/ic_remove_circle_48px.svg"}
            onClicked: function() {
                selectedSensors.removeAt(listIndex);
            }
        }

    }
}


