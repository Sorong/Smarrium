import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3
import SensorBaseType 1.0

Window {

    id: window
    visible: true
    title: qsTr("Smarrium")
    RowLayout {
        id: layout
        anchors.fill: parent
        spacing: 10
        Rectangle {
            id: header
            color: 'azure'
            anchors.top: parent.top
            anchors.left: layout.left
            anchors.right: layout.right
            Layout.fillWidth: true
            Layout.preferredHeight: 100
            Text {
                anchors.centerIn: parent
                text: "Smarriumkonfigurator"
            }
        }

        Rectangle {
            id: actorCreatorPane
            anchors.top: header.bottom
            anchors.left: header.left
            anchors.right: header.right
            Layout.fillWidth: true
            Layout.preferredHeight: 100
            border.width: 1
            //color: "blue"
            Row {
                id: switches

                Component.onCompleted: function() {
                    var names = ["1", "2", "3", "4", "5", "A", "B","C", "D", "E"]
                    for(var i = 0; i < names.length; i++) {
                        var component = Qt.createComponent("uicomponents/_actuatorcreator.qml")
                        if (component.status === Component.Ready)
                            var sw = component.createObject(switches);
                        sw.text = qsTr(names[i])
                    }
                }

            }
            RoundButton {
                id: addActor
                anchors.topMargin: 20
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: switches.right
                anchors.leftMargin: 10
                spacing: 7
                icon { source:"/icons/svg/ic_add_48px.svg"}
                onClicked: function() {
                    var list = []
                    for(var i = 0; i < switches.children.length; i++) {
                        list.push(switches.children[i].checked)
                    }
                    actuatorFactory.addActuator(list)
                }
            }
        }
        Rectangle {
            id: sensorCreatorPane
            anchors.top: actorCreatorPane.bottom
            anchors.left: actorCreatorPane.left
            anchors.right: actorCreatorPane.right
            Layout.fillWidth: true
            Layout.preferredHeight: 100
            border.width: 1
            //color: "blue"
            Component.onCompleted: function() {
                var component = Qt.createComponent("uicomponents/_sensorcreator.qml")
                if (component.status === Component.Ready)
                    component.createObject(sensorCreatorPane);
            }
        }
        Rectangle {
            id: actorConfiguratorPane
            anchors.top: sensorCreatorPane.bottom
            anchors.left: sensorCreatorPane.left
            anchors.right: sensorCreatorPane.right
            Layout.fillWidth: true
            Layout.preferredHeight: 100
            Column {
                ComboBox {
                    width: actorConfiguratorPane.width
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
                        width: actorConfiguratorPane.width - addSensor.width
                        textRole: "name"
                        model: sensors
                        delegate: ItemDelegate {
                            text: name
                            width: parent.width
                            onClicked: function() {
                                addSensor.uuid = uuid;
                                addSensor.config = configFactory.getConfig(type);
                            }
                            Component.onCompleted: this.onClicked()
                        }



                    }

                    RoundButton {
                        id: addSensor
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

        Rectangle {
            id: sensorListPane
            Layout.fillHeight: true
            anchors.top: actorConfiguratorPane.bottom
            anchors.topMargin: 20
            anchors.left: actorConfiguratorPane.left
            anchors.right: actorConfiguratorPane.right
            //color: "red"
            ListView {
                id: sensorList
                anchors.top: parent.top
                anchors.fill:parent
                anchors.topMargin: 20
                anchors.left: parent.left
                anchors.right: parent.right
                ScrollBar.vertical: ScrollBar {
                    id: sensorListScrollBar
                }
                delegate: Component {
                    Item {
                        width: parent.width - sensorListScrollBar.width
                        height: sensorList.height * 0.5

                        Row {
                            //Rectangle { color: "red"; width: 50; height: 50 }
                            //Rectangle { color: "green"; width: 20; height: 50 }
                            //Rectangle { color: "blue"; width: 50; height: 20 }

                            Rectangle {
                                width: sensorList.width * 0.2
                                height: sensorList.height * 0.5
                                border.color: "lightgray"
                                color: "red"
                                Text {
                                    anchors.verticalCenter: parent.verticalCenter
                                    text: '<b>Name:</b> ' + name
                                }

                            }
                            Rectangle {
                                width: sensorList.height * 0.5
                                height: sensorList.height * 0.5
                                color: "blue"
                                //anchors.verticalCenter: parent.verticalCenter
                                border.color: "blue"
                                Component.onCompleted: function() {
                                    var component = undefined;
                                    switch (type) {
                                    case SensorBaseType.UV:
                                        console.log("UV");
                                        component = Qt.createComponent("uicomponents/sensorviews/uv.qml")
                                        break;
                                    case SensorBaseType.LUX:
                                        console.log("UV");
                                        component =Qt.createComponent("uicomponents/sensorviews/lux.qml")
                                        break;
                                    case SensorBaseType.HUMIDITY:
                                        console.log("HUMIDITY");
                                        component = Qt.createComponent("uicomponents/sensorviews/humidity.qml")
                                        break;
                                    case SensorBaseType.TEMPERATURE:
                                        console.log("TEMPERATURE");
                                        component = Qt.createComponent("uicomponents/sensorviews/temperature.qml")
                                        break;
                                    case SensorBaseType.CLOCK:
                                        console.log("CLOCK");
                                        component = Qt.createComponent("uicomponents/sensorviews/clock.qml")
                                        break;
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
        }
    }

}
