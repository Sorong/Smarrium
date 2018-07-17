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
            property var getTimerInterval : function() {
                var today = new Date(); //Berlin
                var m = today.getMinutes();
                if(m == 0) {
                    var hour = 1000 * 60 * 60; //1000Millisekunde * 60 Sekunden * 60 Minuten
                    refreshTimer.interval = hour;
                } else {
                    var nextHour = 1000 * 60 * (60-m);
                    refreshTimer.interval = nextHour;
                }
            }
            id : refreshTimer
            interval: interval; running: true; repeat: true;
            onTriggered: function () {
                lineSeriesTemp.refresh();
                this.getTimerInterval();
            }
        }


        ChartView {
            title: name
            anchors.fill: parent
            antialiasing: true
            ValueAxis {
                id: axisX
                min: 0
                max: 24
                tickCount: 1
                reverse: true
                titleText: "Aktuelle Uhrzeit -X Stunden"
            }

            ValueAxis {
                id: axisY
                min: 0
                max: 0
                titleText: "Lux"
            }

            property var refresh: function() {
                var data = log;
                removePoints(0, lineSeriesTemp.count)
                for(var i = 0; i < data.length; i++) {
                    if(data[i] >= axisY.max) {
                        axisY.max = data[i] +5
                    }
                    lineSeriesTemp.append(data.length - i, data[i]);
                    console.log("LogGraph Point added: " + (data.length - i) + " | " +  data[i])
                }
            }
        }
    }


    Rectangle {
        id: jsonPane
        width: sensorListPane.width * 0.2
        height: sensorListPane.height * 0.5
        anchors.margins: 5
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
        border.color: "lightgray"
        color: "azure"
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            text: "Controllpanel"
        }
        Image {
            width : parent.width
            height : parent.height
            source: "/images/images/default.ppm"
        }
    }

    Rectangle {
        width: sensorListPane.width * 0.18
        height: sensorListPane.height * 0.5
        color: "azure"
        ChartView {
            title: "Vorschau"
            anchors.fill: parent
            theme: ChartView.ChartThemeBrownSand

            BoxPlotSeries {
                id: plotSeries
                name: "Income"
                BoxSet { label: "Jan"; values: [3, 4, 5.1, 6.2, 8.5] }
                BoxSet { label: "Feb"; values: [5, 6, 7.5, 8.6, 11.8] }
                BoxSet { label: "Mar"; values: [3.2, 5, 5.7, 8, 9.2] }
                BoxSet { label: "Apr"; values: [3.8, 5, 6.4, 7, 8] }
                BoxSet { label: "May"; values: [4, 5, 5.2, 6, 7] }
            }
        }

    }
    Rectangle {
        width: sensorListPane.width * 0.03
        height: sensorListPane.height * 0.5
        border.color: "lightgray"
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


