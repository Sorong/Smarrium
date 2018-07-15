import QtQuick 2.0
import QtQuick.Controls 2.3
import SensorBaseType 1.0

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
                    delegate: ItemDelegate {
                        text: name
                        width: parent.width
                        onClicked: function() {
                            add.uuid = uuid;
                            add.config = configFactory.getConfig(type);
                        }
                        Component.onCompleted: this.onClicked()
                    }



                }

                RoundButton {
                    id: add
                    property string uuid: ""
                    property string config: ""
                    anchors.bottom: parent.bottom
                    icon { source:"/icons/svg/ic_add_48px.svg"}
                    onClicked: function() {
                        if(this.uuid === "" || this.config === "") {
                            return;
                        }
                        sensors.selectSensor(sensorAdd.currentIndex);
                        actuatorFactory.createActuatorConfig(this.uuid, this.config);
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
                Component.onCompleted: function() {
                    var component = undefined;
                    switch (type) {
                    case SensorBaseType.UV:
                        console.log("UV");
                        return  Qt.createComponent("uicomponents/sensorviews/uv.qml")
                    case SensorBaseType.LUX:
                        console.log("UV");
                        return  Qt.createComponent("uicomponents/sensorviews/lux.qml")
                    case SensorBaseType.HUMIDITY:
                        console.log("HUMIDITY");
                        return Qt.createComponent("uicomponents/sensorviews/humidity.qml")
                    case SensorBaseType.TEMPERATURE:
                        console.log("TEMPERATURE");
                        return Qt.createComponent("uicomponents/sensorviews/temperature.qml")
                    case SensorBaseType.CLOCK:
                        console.log("CLOCK");
                        return Qt.createComponent("uicomponents/sensorviews/clock.qml")
                    default:
                        console.log("default");
                        break;
                    }
                    if (component && component.status === Component.Ready) {
                        component.createObject(this);
                    }
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
