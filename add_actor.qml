import QtQuick 2.0
import QtQuick.Window 2.10
import QtQuick.Controls 2.3
import QtQuick.Controls.Styles 1.4

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
        text: qsTr("Aktor hinzufügen")
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
        model: actuators
        ScrollBar.vertical: ScrollBar {
                active: true
                }
        delegate: Component {
            Item {
                width: parent.width
                height: 40
                Rectangle {
                    //anchors.centerIn: parent
                    //Row {
                       anchors.fill: parent
                       border.color: "lightgray"
                       // anchors.horizontalCenter: parent.horizontalCenter
                        Text {                
                            anchors.verticalCenter: parent.verticalCenter
                            text: (index+1) + '. Adresse:  ' + code
                        }
                        RoundButton {
                            anchors.right: parent.right
                            anchors.verticalCenter: parent.verticalCenter
                            icon {
                                source:"/icons/svg/ic_delete_forever_48px.svg"
                            }
                            onClicked: function() {
                                actuators.removeAt(index)
                            }
                        }
                    //}
                }
            }
        }
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
            stackView.push("add_sensor.qml")
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
        id: actorSelector
        anchors.top: content.bottom
        anchors.topMargin: 20
        anchors.left: content.left
        width: parent.width * 2/3
        Row {
            id: switches

            Component.onCompleted: function() {
                var names = ["1", "2", "3", "4", "5", "A", "B","C", "D", "E"]
                for(var i = 0; i < names.length; i++) {
                    var component = Qt.createComponent("uicomponents/horizontal_switch.qml")
                    if (component.status === Component.Ready)
                        var sw = component.createObject(switches);
                        sw.text = qsTr(names[i])
                }
            }
        }
    }

    RoundButton {
        id: add
        anchors.topMargin: 20
        anchors.top: content.bottom
        anchors.left: actorSelector.right
        anchors.leftMargin: 10
        icon { source:"/icons/svg/ic_add_48px.svg"}
        spacing: 7
        onClicked: function() {
                var list = []
                for(var i = 0; i < switches.children.length; i++) {
                    list.push(switches.children[i].checked)
                }
                actuatorFactory.addActuator(list)
        }
    }
}
