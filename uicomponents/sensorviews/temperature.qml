import QtQuick 2.0
import QtCharts 2.2
import QtQuick.Controls 1.4 as QSS1_4
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4


Row{

    Rectangle {
        width: (sensorListPane.width-sensorListScrollBar.width) * 0.13
        height: sensorListPane.height * 0.5
        color: "azure"
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            text: '<b>Name:</b> \n' + name
        }

    }

    Rectangle {
        width: (sensorListPane.width-sensorListScrollBar.width) * 0.2
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
            interval: 5*interval; running: true; repeat: true;
            onTriggered: function () {
                console.log("refreshTimer")
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
                titleText: "C°"
            }

            LineSeries {
                id : lineSeriesTemp
                axisX: axisX
                axisY: axisY
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
    }

    Rectangle {
        id: jsonPane
        width: (sensorListPane.width-sensorListScrollBar.width) * 0.2
        height: sensorListPane.height * 0.5
        property var json : ({})
        property var jsonChange : function(json) {
            jsonStringArea.text = JSON.stringify(this.json, null, 2)
            this.json = json
        }

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
                id: jsonStringArea
                property var getJson : function() {
                    var t = "";
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
                    return t;
                }
                width: jsonPane.width - 10
                height: jsonPane.height - extendedConfig.height - 10
                anchors.leftMargin: 5

                text: getJson()

                style: TextAreaStyle {
                    id: testAreaStyle
                }
                wrapMode: TextArea.NoWrap
                onEditingFinished : function() {
                    try {
                        var jsonObject = JSON.parse(jsonStringArea.text)
                        jsonPane.border.color = "#C5E1A5" //okay grün
                        jsonPane.border.width = 3
                        jsoPane.json = jsonObject
                        selectedSensors.changeConfig(uuid, jsonStringArea.text)
                    } catch(e) {
                        jsonPane.border.color = "#EF9A9A" //nicht okay rot
                        jsonPane.border.width = 3
                    }
                }
            }
        }
    }

    Rectangle {
        id: controlPane
        width: (sensorListPane.width-sensorListScrollBar.width) * 0.25
        height: sensorListPane.height * 0.5
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
                        to: 23
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
                        to: 23
                        editable: true
                    }
                }


            }

            Row {
                Column {
                    Text {
                        anchors.leftMargin: 5
                        text: "Min. Temperatur: "
                    }

                    SpinBox {
                        id: min
                        from: 0
                        to: 80
                        editable: true
                        onValueChanged: {
                            max.from = this.value
                            if(max.value < this.value) {
                                max.value = this.value
                            }
                        }
                    }

                }
                Column {
                    Text {
                        text: "Max. Temperatur: "
                    }
                    SpinBox {
                        id: max
                        from: 0
                        to: 80
                        editable: true
                    }
                }
            }


            Row {

                RadioButton {
                    id: onMin
                    checked: true
                    text: qsTr("Minimum")
                }
                RadioButton {
                    id: onMax
                    text: qsTr("Maximum")
                }

            }
            Button {
                icon { source:"/icons/svg/ic_save_48px.svg"}
                onClicked: function() {
                    var toInsert = jsonPane.json
                    for(var i = from.value; i != to.value; i++) {
                        if(i == 24) {
                            i %= 24;
                        }
                        toInsert[i] = {"min" : min.value, "max" : max.value}

                    }
                    toInsert["min_is_off"] = onMax.checked
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
        width: (sensorListPane.width-sensorListScrollBar.width) * 0.02
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


