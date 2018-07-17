import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3
import SensorBaseType 1.0

Window {

    id: window
    property alias sensorListPane: sensorListPane
    width: 1680
    height: 1050
    visible: true
    title: qsTr("Smarrium")
    ColumnLayout {
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
                lineHeight: 1
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
                    actorConfiguratorPane.reload()
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
            property var reload : function() {
                if(actorSelect.model.rowCount() > 0) {
                    actorSelect.currentIndex = 0;
                }
                if(sensorAdd.model.rowCount() > 0) {
                    sensorAdd.currentIndex = 0;
                }

            }

            Column {
                ComboBox {
                    id: actorSelect
                    width: actorConfiguratorPane.width
                    textRole: "code"
                    model: actuators
                    onCurrentIndexChanged: function() {
                        if(currentIndex >= 0) {
                            model.selectActuator(currentIndex);
                            console.log("sensorList.model")
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
                            if(selectedSensors !== undefined) {
                                sensorList.model = selectedSensors
                            }


                        }
                    }
                }
            }
        }

        Rectangle {
            id: sensorListPane
            anchors.top: actorConfiguratorPane.bottom
            //anchors.fill: parent
            //anchors.bottom: window.bottom
            anchors.topMargin: 20
            anchors.left: actorConfiguratorPane.left
            anchors.right: actorConfiguratorPane.right
            //color: "red"
            Layout.fillHeight: true
            //Layout.fillHeight: true
            ListView {
                id: sensorList
                anchors.fill: parent
                ScrollBar.vertical: ScrollBar {
                    id: sensorListScrollBar
                    policy: ScrollBar.AlwaysOn
                }
                delegate: Rectangle {
                    height: sensorListPane.height * 0.5
                    //                    Rectangle { color: "red"; width: 50; height: 50 }
                    //                    Rectangle { color: "green"; width: 20; height: 50 }
                    //                    Rectangle { color: "blue"; width: 50; height: 20 }
                    //                    Row{

                    //                        Rectangle {
                    //                            width: sensorListPane.height * 0.5
                    //                            height: sensorListPane.height * 0.5
                    //                            border.color: "lightgray"
                    //                            color: "red"
                    //                            Text {
                    //                                anchors.verticalCenter: parent.verticalCenter
                    //                                text: '<b>Name:</b> ' + name
                    //                            }

                    //                        }
                    //                        Rectangle {
                    //                            width: sensorListPane.height * 0.5
                    //                            height: sensorListPane.height * 0.5
                    //                            color: "blue"
                    //                            //anchors.verticalCenter: parent.verticalCenter
                    //                            border.color: "blue"
                    Component.onCompleted: function() {
                        var component = undefined;
                        switch (type) {
                        case SensorBaseType.UV:
                            component = Qt.createComponent("uicomponents/sensorviews/uv.qml")
                            break;
                        case SensorBaseType.LUX:
                            component =Qt.createComponent("uicomponents/sensorviews/lux.qml")
                            break;
                        case SensorBaseType.REF_HUMIDITY:
                            component = Qt.createComponent("uicomponents/sensorviews/relhumidity.qml")
                            break;
                        case SensorBaseType.SUBSTRAT_HUMIDITY:
                            component = Qt.createComponent("uicomponents/sensorviews/substrathumidity.qml")
                            break;
                        case SensorBaseType.TEMPERATURE:
                            component = Qt.createComponent("uicomponents/sensorviews/temperature.qml")
                            break;
                        case SensorBaseType.CLOCK:
                            component = Qt.createComponent("uicomponents/sensorviews/clock.qml")
                            break;
                        case SensorBaseType.CAMERA:
                            component = Qt.createComponent("uicomponents/sensorviews/camera.qml")
                            break;
                        default:
                            console.log("default");
                            break;
                        }
                        if (component && component.status === Component.Ready) {
                            component.createObject(this);
                        }
                    }

                    //  }




                    //                    }

                    // }
                }
            }
        }
    }

}
