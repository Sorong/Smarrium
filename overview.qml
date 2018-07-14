import QtQuick 2.0
import QtQuick.Controls 2.3

Item {
    id: addActor
    //anchors.fill: parent

    Label {
        id: titleActor
        anchors.topMargin: 10
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width/5*4
        text: qsTr("Übersicht")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Pane {
        id: content
        anchors.top: titleActor.bottom
        anchors.topMargin: 20
        anchors.left: titleActor.left
        anchors.right: titleActor.right
        width: parent.width * 2/3
        Column {
            ComboBox {
                width: content.width
                textRole: "code"
                model: actuators
                onCurrentIndexChanged: function() {
                    if(currentIndex >= 0) {
                        model.selectActuator(currentIndex);
                        sensorList.model = selectedSensors
                    }

                }
                Component.onCompleted: onCurrentIndexChanged()
            }
            Row {
                ComboBox {
                    id: sensorAdd
                    width: content.width - add.width
                    textRole: "name"
                    model: sensors

                }

                RoundButton {
                    id: add
                    anchors.bottom: parent.bottom
                    icon { source:"/icons/svg/ic_add_48px.svg"}
                    onClicked: function() {
                        sensors.selectSensor(sensorAdd.currentIndex);
                    }
                }
            }
        }
    }





    ListView {
        id: sensorList
        width: 200; height: 250
        anchors.top: content.bottom
        anchors.topMargin: 20
        anchors.left: content.left
        anchors.right: content.right
        delegate: Component {
            Item {
                width: parent.width
                height: 40
                Column {
                    //anchors.centerIn: parent
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: (index + 1) + ' ' + name + ', Interval: ' + interval + ', UUID: ' + uuid
                    }
                }
//                Column {
//                    Text {
//                        text: 'Configuration: '
//                    }

//                    TextArea {

//                    }
//                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: sensorList.currentIndex = index
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
        id: btnNewActor
        height: 40
        text: qsTr("Fertig")
        anchors.leftMargin: 0
        anchors.left: content.left
        anchors.bottom: btnBack.top
        anchors.bottomMargin: 20
        anchors.right: content.right
        anchors.rightMargin: 0
        onClicked: {
            stackView.pop(stackView.get(0))
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
}
