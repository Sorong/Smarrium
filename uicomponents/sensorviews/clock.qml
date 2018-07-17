import QtQuick 2.0
import QtCharts 2.2
import QtQuick.Controls 1.4 as QSS1_4
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4


Row{

    Rectangle {
        width: sensorListPane.width * 0.15
        height: sensorListPane.height * 0.5
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
        Timer {
            interval: 500; running: true; repeat: true;
            onTriggered: textClock.timeChange()
        }
        Text {
            id: textClock
            property var timeChange : function() {
                var today = new Date();
                var h = today.getHours(); //Berlin
                var m = today.getMinutes();s
                h = checkTime(h);
                m = checkTime(m);
                textClock.text = h + ":" + m + "  Uhr (UTC)";
            }
            property var checkTime: function(i) {
                if (i < 10) {i = "0" + i};  // add zero in front of numbers < 10
                return i;
            }
            font.pointSize: 24
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            text : ""
        }

    }


    Rectangle {
        id: jsonPane
        width: sensorListPane.width * 0.2
        height: sensorListPane.height * 0.5
        anchors.margins: 5
        color: "azure"
        Text {
            id: extendedConfig
            text: "Erweiterte Konfigurationen:"
        }
        ScrollView {
            anchors.top : extendedConfig.bottom
            anchors.leftMargin: 5
            //anchors.fill: jsonPane

            QSS1_4.TextArea {
                property var getJson : function() {
                    var t = "";
                    if(actuatorManager !== null) {
                        t = actuatorManager.getConfig();
                        if(t !== "") {
                            t = JSON.stringify(JSON.parse(t), null, 2)
                        }
                    }
                    if(t === "" ) {
                        t = JSON.stringify(JSON.parse(configFactory.getConfig(type)), null, 2)
                    }
                    return t;
                }
                width: jsonPane.width - 10
                height: jsonPane.height - extendedConfig.height - 10
                id: jsonStringArea
                text: getJson()

                style: TextAreaStyle {
                    backgroundColor : "white"
                }
                wrapMode: TextArea.NoWrap
            }
        }
    }

    Rectangle {
        width: sensorListPane.width * 0.2
        height: sensorListPane.height * 0.5
        color: "azure"
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            text: "Controllpanel"
        }
    }
    Rectangle {
        width: sensorListPane.width * 0.03
        height: sensorListPane.height * 0.5
        color: "azure"

        RoundButton {
            id: applyConfig
            anchors.bottom: removeSensor.top
            property int mode : 0
            property int index: 0
            property string sensor : ""
            property string option: ""
            icon { source:"/icons/svg/ic_save_48px.svg"}
            onClicked: function() {
                console.log(jsonStringArea.text)
                try {
                    var jsonObject = JSON.parse(jsonStringArea.text)
                    jsonPane.border.color = "green"
                    selectedSensors.changeConfig(uuid, jsonStringArea.text)
                } catch(e) {
                    jsonPane.border.color = "red"
                }
            }
        }
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


