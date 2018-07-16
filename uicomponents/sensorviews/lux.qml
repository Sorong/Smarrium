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
        color: "red"
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            text: '<b>Name:</b> ' + name
        }

    }

    Rectangle {
        width: sensorListPane.width * 0.2
        height: sensorListPane.height * 0.5
        color: "blue"
        border.color: "blue"
        ChartView {
            title: name
            anchors.fill: parent
            antialiasing: true

            ValueAxis {
                id: valueAxis
                min: 2000
                max: 2011
                tickCount: 12
                labelFormat: "%.0f"
            }

            AreaSeries {
                axisX: valueAxis
                upperSeries: LineSeries {
                    XYPoint { x: 2000; y: 1 }
                    XYPoint { x: 2001; y: 1 }
                    XYPoint { x: 2002; y: 1 }
                    XYPoint { x: 2003; y: 1 }
                    XYPoint { x: 2004; y: 1 }
                    XYPoint { x: 2005; y: 0 }
                    XYPoint { x: 2006; y: 1 }
                    XYPoint { x: 2007; y: 1 }
                    XYPoint { x: 2008; y: 4 }
                    XYPoint { x: 2009; y: 3 }
                    XYPoint { x: 2010; y: 2 }
                    XYPoint { x: 2011; y: 1 }
                }
            }
        }
    }

    Rectangle {
        id: jsonPane
        width: sensorListPane.width * 0.2
        height: sensorListPane.height * 0.5
        anchors.margins: 5
        border.color: "lightgray"
        color: "green"
        Text {
            id: extendedConfig
            text: "Erweiterte Konfigurationen:"
        }
        ScrollView {
            //anchors.top : extendedConfig.bottom

            QSS1_4.TextArea {
//                width: jsonPane.width - 10
//                height: jsonPane.height - extendedConfig.height - 10
                //anchors.fill: jsonPane
                id: jsonStringArea
                text: JSON.stringify(JSON.parse(configFactory.getConfig(type)), null, 2)
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
        color: "red"
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            text: "Controllpanel"
        }

    }

    Rectangle {
        width: sensorListPane.width * 0.18
        height: sensorListPane.height * 0.5
        color: "blue"
        border.color: "blue"
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
        color: "red"

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
                var jsonString = JSON.parse(jsonStringArea.text)

                console.log(jsonString.json);
                // expected output: 42

                console.log(jsonString.json);
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


