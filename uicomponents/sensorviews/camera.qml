import QtQuick 2.0
import QtCharts 2.2
import QtQuick.Controls 1.4 as QSS1_4
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4


Row{

    Rectangle {
        width: sensorListPane.width * 0.15
        height: sensorListPane.height * 0.5
        border.color: "lightgray"
        color: "azure"
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            text: '<b>Name:</b> ' + name
        }

    }

    Rectangle {
        width: sensorListPane.width * 0.2
        height: sensorListPane.height * 0.5
        color: "azure"
        Image {
            id: camera
            width : parent.width
            height : parent.height
            Component.onCompleted: function() {
                console.log(this.source)
            }
            source: applicationPath + "/OpenCVScript/difference.ppm"
            Timer {
                interval: 600000; running: true; repeat: true;
                onTriggered: function() {
                    camera.source = applicationPath + "/OpenCVScript/difference.ppm";
                }
            }
        }
    }

//    Rectangle {
//        id: jsonPane
//        width: sensorListPane.width * 0.2
//        height: sensorListPane.height * 0.5
//        anchors.margins: 5
//        border.color: "black"
//        Text {
//            id: extendedConfig
//            text: "Erweiterte Konfigurationen:"
//        }
//        ScrollView {
//            anchors.top : extendedConfig.bottom
//            anchors.leftMargin: 5
//            //anchors.fill: jsonPane

//            QSS1_4.TextArea {
//                property var getJson : function() {
//                    var t = "";
//                    if(actuatorManager !== null) {
//                        t = actuatorManager.getConfig();
//                        if(t !== "") {
//                            t = JSON.stringify(JSON.parse(t), null, 2)
//                        }
//                    }
//                    if(t === "" ) {
//                        t = JSON.stringify(JSON.parse(configFactory.getConfig(type)), null, 2)
//                    }
//                    return t;
//                }
//                width: jsonPane.width - 10
//                height: jsonPane.height - extendedConfig.height - 10
//                id: jsonStringArea
//                text: getJson()

//                style: TextAreaStyle {
//                    backgroundColor : "white"
//                }
//                wrapMode: TextArea.NoWrap
//            }
//        }
//    }

    Rectangle {
        width: sensorListPane.width * 0.03
        height: sensorListPane.height * 0.5
        border.color: "lightgray"
        color: "azure"

//        RoundButton {
//            id: applyConfig
//            anchors.bottom: removeSensor.top
//            property int mode : 0
//            property int index: 0
//            property string sensor : ""
//            property string option: ""
//            icon { source:"/icons/svg/ic_save_48px.svg"}
//            onClicked: function() {
//                console.log(jsonStringArea.text)
//                try {
//                    var jsonObject = JSON.parse(jsonStringArea.text)
//                    jsonPane.border.color = "green"
//                    selectedSensors.changeConfig(uuid, jsonStringArea.text)
//                } catch(e) {
//                    jsonPane.border.color = "red"
//                }
//            }
//        }
        RoundButton {
            id: removeSensor
            anchors.bottom: parent.bottom
            property int mode : 0
            property int index: 0
            property string sensor : ""
            property string option: ""
            icon { source:"/icons/svg/ic_remove_circle_48px.svg"}
            onClicked: function() {

            }
        }

    }
}


