import QtQuick 2.0
import QtCharts 2.2
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import SensorBaseType 1.0


Row{

    Rectangle {
        width: (sensorListPane.width-sensorListScrollBar.width) * 0.12
        height: sensorListPane.height * 0.6
        color: "azure"
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            text: name
        }

    }

    Rectangle {
        width: (sensorListPane.width-sensorListScrollBar.width) * 0.2
        height: sensorListPane.height * 0.6
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
            interval: sensorinterval; running: true; repeat: true;
            onTriggered: function () {
                lineSeriesLux.refresh();
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

            LineSeries {
                id : lineSeriesLux
                axisX: axisX
                axisY: axisY
                property var refresh: function() {
                    var data = log;
                    removePoints(0, lineSeriesLux.count)
                    for(var i = 0; i < data.length; i++) {
                        if(data[i] >= axisY.max) {
                            axisY.max = data[i] +5
                        }
                        lineSeriesLux.append(data.length - i, data[i]);
                        console.log("LogGraph Point added: " + (data.length - i) + " | " +  data[i])
                    }
                }
            }
        }
    }

    Rectangle {
        id: jsonPane
        width: (sensorListPane.width-sensorListScrollBar.width) * 0.2
        height: sensorListPane.height * 0.6
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
        Component.onCompleted: {
            jsonStringArea.text = jsonStringArea.getJson();
        }

        Column {
            Timer {
                id: resetColor
                interval: 5000; running: false; repeat: false;
                onTriggered: function() {
                    jsonPane.border.color = "azure";
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
                        //console.log("getJson");
                        if(actuatorManager !== null) {
                            t = actuatorManager.getConfig(uuid);
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
                    wrapMode : TextEdit.NoWrap
                    text : ""

                    onEditingFinished : function() {
                        try {
                            var jsonObject = JSON.parse(jsonStringArea.text)
                            jsonPane.border.color = "#C5E1A5" //okay grün
                            jsonPane.border.width = 3
                            jsonPane.json = jsonObject
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
        height: sensorListPane.height * 0.6
        color: "azure"
        Column {
            Row {
                Column {
                    Text {
                        text: "Startuhrzeit: "
                    }
                    SpinBox {
                        id: from
                        from: 0
                        to: 24
                        editable: true
                    }
                }

                Column {
                    Text {
                        text: "Enduhrzeit: "
                    }
                    SpinBox {
                        id: to
                        from: 0
                        to: 24
                        editable: true
                    }
                }


            }

            Row {
                Column {
                    Text {
                        anchors.leftMargin: 5
                        text: "Min. LUX: "
                    }

                    SpinBox {
                        id: min
                        from: last/2
                        to: last !== 0 ? last*2 : 500
                        value : last !== 0 ? last :250
                        editable: true
                    }

                }
            }


            Row {

                CheckBox {
                    id: ignore
                    checked: true
                    text: qsTr("Nur Aufzeichnen")
                }
            }
            Button {
                icon { source:"/icons/svg/ic_save_48px.svg"}
                onClicked: function() {
                    var toInsert = jsonPane.json
                    for(var i = from.value; i != to.value + 1; i++) {
                        if(i == 25) {
                            i %= 25;
                        }
                        toInsert[i] = {"min" : min.value}

                    }
                    toInsert["ignore"] = ignore.checked
                    //console.log(JSON.stringify(toInsert, null, 2))
                    jsonPane.jsonChange(toInsert)
                }
            }

        }
    }

    Rectangle {
        width: (sensorListPane.width-sensorListScrollBar.width) * 0.20
        height: sensorListPane.height * 0.6
        color: "azure"
        ChartView {
            id: previewChart
            title: "Vorschau"
            anchors.fill: parent
            property var refresh: function(json) {
                axisYPreview.min = 1000000000
                axisYPreview.max = 0
                lineSeriesLuxPreview.removePoints(0, lineSeriesLuxPreview.count)
                for(var i = 0; i <= 24 || json[i] !== undefined; i++) {
                    if(json[i]["min"] < axisYPreview.min) {
                        axisYPreview.min = (json[i]["min"]-1)
                    }
                    lineSeriesLuxPreview.append(i, json[i]["min"])
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
                min: 1000000000
                max: 0
                titleText: "mW/cm²"
            }

            LineSeries {
                id : lineSeriesLuxPreview
                axisX: axisXPreview
                axisY: axisYPreview
                color: "#2196F3"
            }

        }
    }

    Rectangle {
        width: (sensorListPane.width-sensorListScrollBar.width) * 0.05
        height: sensorListPane.height * 0.6
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
                selectedSensors.removeAt(listIndex);
            }
        }

    }
}


