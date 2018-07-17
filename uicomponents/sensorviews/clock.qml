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
        Timer {
            interval: 10000; running: true; repeat: true;
            onTriggered: textClock.timeChange()
        }
        Text {
            id: textClock
            property var timeChange : function() {
                var today = new Date();
                var h = today.getHours(); //Berlin
                var m = today.getMinutes();
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
            text : "--:--"
            Component.onCompleted: timeChange()
        }

    }

    Rectangle {
        id: jsonPane
        width: (sensorListPane.width-sensorListScrollBar.width) * 0.2
        height: sensorListPane.height * 0.5
        property var json : ({})
        property var jsonChange : function(json) {
            jsonStringArea.text = JSON.stringify(this.json, null, 2)
            this.json = json
            previewChart.refresh(json)
        }

        anchors.margins: 5
        color: "white"
        border.color: "azure"
        border.width: 4
        Column {
            Timer {
                id: resetColor
                interval: 5000; running: false; repeat: false;
                onTriggered: function() {
                    jsonPane.border = "azure";
                }
            }

            Text {
                id: extendedConfig
                text: "Erweiterte Konfigurationen:"
            }
            ScrollView {
                //anchors.fill: jsonPane
                width: jsonPane.width - 10
                height: jsonPane.height - extendedConfig.height - 10
                clip: true
                ScrollBar.vertical.policy: ScrollBar.AlwaysOn

                TextArea {
                    id: jsonStringArea
                    property var getJson : function() {
                        var t = "";
                        console.log("getJson");
                        if(actuatorManager !== null) {
                            t = actuatorManager.getConfig();
                            if(t !== "") {
                                jsonPane.json = JSON.parse(t)
                                t = JSON.stringify(jsonPane.json, null, 2)
                            }
                        }
                        if(t === "" ) {
                            jsonPane.json = JSON.parse(configFactory.getConfig(type))
                            t = JSON.stringify(jsonPane.json, null, 2)
                        }
                        previewChart.refresh(jsonPane.json)
                        return t;
                    }

                    //background: "white"
                    text: getJson()
                    wrapMode : TextEdit.NoWrap

                    onEditingFinished : function() {
                        try {
                            var jsonObject = JSON.parse(jsonStringArea.text)
                            jsonPane.border.color = "#C5E1A5" //okay grün
                            jsonPane.border.width = 3
                            jsoPane.json = jsonObject
                            previewChart.refresh(jsonObject)
                            resetColor.running = true

                        } catch(e) {
                            jsonPane.border.color = "#EF9A9A" //nicht okay rot
                            jsonPane.border.width = 3
                        }
                    }
                }
            }
        }
    }

    Rectangle {
        id: controlPane
        width: (sensorListPane.width-sensorListScrollBar.width) * 0.23
        height: sensorListPane.height * 0.5
        color: "azure"
        Column {
            Row {
                Column {
                    Text {
                        text: "Beginn: "
                    }
                    SpinBox {
                        id: from
                        from: 0
                        to: 23
                        editable: true
                    }
                }

                Column {
                    Text {
                        text: "Ende: "
                    }
                    SpinBox {
                        id: to
                        from: 0
                        to: 23
                        editable: true
                    }
                }


            }

            Button {
                icon { source:"/icons/svg/ic_save_48px.svg"}
                onClicked: function() {
                    var toInsert = jsonPane.json
                    toInsert["start"] = from.value
                    toInsert["stop"] = to.value
                    console.log(JSON.stringify(toInsert, null, 2))
                    jsonPane.jsonChange(toInsert)
                }
            }

        }
    }

    Rectangle {
        width: (sensorListPane.width-sensorListScrollBar.width) * 0.20
        height: sensorListPane.height * 0.5
        color: "azure"
        ChartView {
            id: previewChart
            title: "Vorschau"
            anchors.fill: parent
            property var refresh: function(json) {
                lineSeriesClock.removePoints(0, lineSeriesClock.count)
                var start = json["start"]
                var end = json["stop"]
                var today = new Date();
                var h = today.getHours();
                for(var i = 0; i < 24; i++) {
                    var offset = (h + i) % 24
                    if((start === end) || (i >= start && i <= end)) {
                        lineSeriesClock.append(i, 1)
                    } else if( (end < start) &&  !(i >= (end) && i <= start)){
                        lineSeriesClock.append(i, 1)
                    } else {
                        lineSeriesClock.append(i, 0)
                    }
                }
            }

            ValueAxis {
                id: axisXPreview
                min: 0
                max: 24
                tickCount: 1
                titleText: "Uhrzeit"
            }

            ValueAxis {
                id: axisYPreview
                min: 0
                max: 2
                titleText: "Aktiv/Inaktiv"
            }

            LineSeries {
                id : lineSeriesClock
                axisX: axisXPreview
                axisY: axisYPreview
                color: "#2196F3"
            }
        }
    }

    Rectangle {
        width: (sensorListPane.width-sensorListScrollBar.width) * 0.05
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
                    resetColor.running = true
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


