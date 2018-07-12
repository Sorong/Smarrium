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
        model: unavailablePins
        delegate: Component {
                    Item {
                        width: parent.width
                        height: 40
                        Column {
                            anchors.centerIn: parent
                            Text {
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: 'Pin: ' + display
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
                onCurrentItemChanged: console.log(model.at(content.currentIndex) + ' selected')

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
            stackView.push("configure.qml")
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

    ComboBox {
        id: gpioSelector
        textRole: "display"
        anchors.top: content.bottom
        anchors.topMargin: 20
        model: availablePins
        anchors.left: content.left
        width: parent.width * 2/3
    }

   RoundButton {
        id: add
        anchors.topMargin: 20
        anchors.top: content.bottom
        anchors.left: gpioSelector.right
        anchors.leftMargin: 10
        icon { source:"/icons/svg/ic_add_48px.svg"}
        onClicked: {
            actuators.setSender(availablePins.at(gpioSelector.currentIndex))
            availablePins.removeAt(gpioSelector.currentIndex)
        }
    }
}
