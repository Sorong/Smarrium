import QtQuick 2.0
import QtQuick.Window 2.10
import QtQuick.Controls 2.3

Item {
    id: addActor
    property alias content: content
    //anchors.fill: parent

    Label {
        id: titleActor
        anchors.topMargin: 10
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width/5*4
        text: qsTr("Digitalen Sensor hinzufügen")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }
    //Test

    ListView {
        id: content
        width: 200; height: 250
        anchors.top: titleActor.bottom
        anchors.topMargin: 20
        anchors.left: titleActor.left
        anchors.right: titleActor.right
        model: sensors
        delegate: Component {
            Item {
                width: content.width
                height: 40
                Column {
                    //anchors.centerIn: parent
                    //width: parent.width
                    Text {
                        text: name + ', Interval: ' + interval + ', UUID: ' + uuid
                    }
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: content.currentIndex = index
                }
            }
        }
        highlight: Rectangle {
            color: 'lightgrey'
            Text {
                anchors.centerIn: parent
                color: 'white'
            }
        }
        focus: true
        //onCurrentItemChanged: console.log(model.at(content.currentIndex) + ' selected')

    }

    Button {
        id: btnNewSensor
        height: 40
        text: qsTr("Weiter")
        anchors.leftMargin: 0
        anchors.left: content.left
        anchors.bottom: btnBack.top
        anchors.bottomMargin: 20
        anchors.right: content.right
        anchors.rightMargin: 0
        onClicked: {
            stackView.push("overview.qml")
        }
    }

    Button {
        id: btnBack
        height: 40
        text: qsTr("Zurück")
        anchors.leftMargin: 0
        anchors.left: content.left
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.right: content.right
        anchors.rightMargin: 0
        onClicked: {
            stackView.pop()
        }
    }
    Pane {
        id: sensorCreatePane
        anchors.top: content.bottom
        anchors.topMargin: 20
        anchors.left: content.left
        width: parent.width * 2/3
        Component.onCompleted: function() {
            var component = Qt.createComponent("uicomponents/sensor_creator.qml")
            if (component.status === Component.Ready)
                component.createObject(sensorCreatePane);
        }
    }




}
