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

    ComboBox {
        id: content
        anchors.top: titleActor.bottom
        anchors.topMargin: 20
        anchors.left: titleActor.left
        anchors.right: titleActor.right
        width: parent.width * 2/3
        model: actuators
        onCurrentIndexChanged: function() {
            if(currentIndex >= 0)
                sensorList.model = model.at(currentIndex).getManager().getSensors();
        }
       Component.onCompleted: onCurrentIndexChanged()
    }

    ListView {
        id: sensorList
        width: 200; height: 250
        anchors.top: content.bottom
        anchors.topMargin: 20
        anchors.left: content.left
        anchors.right: content.right
        model: ""
        delegate: Component {
            Item {
                width: parent.width
                height: 40
                Column {
                    //anchors.centerIn: parent
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: 'Pin: ' + display
                    }
                }
                Column {
                    Text {
                        text: 'Configuration: '
                    }

                    TextArea {

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
