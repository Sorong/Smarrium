import QtQuick 2.0
import QtCharts 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4


Row{

    Rectangle {
        width: sensorListPane.width * 0.2
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
        width: sensorListPane.width * 0.2
        height: sensorListPane.height * 0.5
        anchors.margins: 5
        border.color: "lightgray"
        color: "green"
        Text {
            text: "Description:"
        }
        ScrollView {
            anchors.fill: parent
            anchors.margins: 5

            TextArea {
                //anchors.verticalCenter: parent.verticalCenter
                text: '<b>Name:</b> ' + name
                style: TextAreaStyle {
                    backgroundColor : "white"
                }
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
}


