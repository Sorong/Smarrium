import QtQuick 2.0
import QtQuick.Controls 2.3

Row {
    id: sensorCreator
    property var onSelectionChanged: function(item) {
        var mode = sensorOptions.typeChange(item)
        add.mode = mode
        add.sensor = item
        sensorOptionSelector.onCurrentIndexChanged()
    }

    property var onOptionChanged: function(item, index) {
        add.option = item
        add.index = index
        add.enabled = true;
    }

    Component.onCompleted: function() {
        this.onSelectionChanged(supportedSensors.at(sensorSelector.currentIndex))
    }

    spacing: 5
    Column {
        Text {
            text: "Sensortyp: "
        }

        ComboBox {
            id: sensorSelector
            textRole: "display"
            width: sensorCreatorPane.width * 0.30
            model: supportedSensors
            onCurrentIndexChanged: function() {
                if(currentIndex >= 0)
                    sensorCreator.onSelectionChanged(model.at(currentIndex))
            }
            property var refresh: function() {
                if(this.model.rowCount() > currentIndex) {
                    sensorCreator.onSelectionChanged(model.at(currentIndex))
                }
            }

        }
    }

    Column {
        id: sensorOptions
        property var typeChange: function(type) {
            var mode = 0
            if (sensorFactory.isAnalog(type)) {
                sensorOptionText.text = "Channel: "
                sensorOptionSelector.enabled = true
                mode = 0
                sensorOptionSelector.model = channelAvailable
            } else if (sensorFactory.isDigital(type)) {
                sensorOptionText.text = "GPIO: "
                mode = 1
                sensorOptionSelector.enabled = true
                sensorOptionSelector.model = gpioAvailable
            } else {
                sensorOptionText.text = "keine Optionen verfügbar"
                mode = 2
                sensorOptionSelector.enabled = false
                sensorOptionSelector.model = undefined
            }
            return mode
        }

        Text {
            id: sensorOptionText
            text: parent.type ? parent.type : ""
        }

        ComboBox {
            id: sensorOptionSelector
            textRole: "display"
            width: sensorCreatorPane.width * 0.30
            onCurrentIndexChanged: function() {
                if(model === undefined || currentIndex < 0) {
                    return
                }
                sensorCreator.onOptionChanged(model.at(currentIndex), currentIndex)
            }
        }
    }

    Column {
        Text {
            text: "Messintervall in Sekunden: "
        }

        SpinBox {
            id: sensorInterval
            from: 5
            to: 1200
            value: 30
            editable: true
            width: sensorCreatorPane.width * 0.10
            onValueChanged : function() {
                add.interval = this.value * 1000
            }
        }
    }


    RoundButton {
        id: add
        anchors.bottom: parent.bottom
        property int mode : 0
        property int index: 0
        property string sensor : ""
        property string option: ""
        property int interval : sensorInterval.value * 1000
        icon { source:"/icons/svg/ic_add_48px.svg"}
        onClicked: function() {
            switch(this.mode) {
            case 1: //Digital
                if (gpioAvailable.removeAt(this.index)) {
                    sensorFactory.addDigitalSensor(this.interval, this.option, this.sensor)
                    add.enabled = false;
                }
                break;
            case 2: //I2C
                sensorFactory.addI2CSensor(this.interval, this.sensor)
                break;
            default: //Analog
                if (channelAvailable.removeAt(this.index)) {
                    sensorFactory.addAnalogSensor(this.interval, this.option, this.sensor)
                    add.enabled = false;
                }
            }
            actorConfiguratorPane.reload();
            sensorSelector.refresh();
        }
    }
}
