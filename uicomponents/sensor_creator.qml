import QtQuick 2.0
import QtQuick.Controls 2.3

Row {
    id: sensorCreator
    property var onSelectionChanged: function(item) {
        sensorOptions.typeChange(item)
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
            width: sensorCreatePane.width * 0.25
            model: supportedSensors
            onCurrentIndexChanged: sensorCreator.onSelectionChanged(model.at(currentIndex))
        }
    }

    Column {
        id: sensorOptions
        property var typeChange: function(type) {
            if (sensorFactory.isAnalog(type)) {
                sensorOptionText.text = "Channel: "
                sensorOptionSelector.enabled = true
                sensorOptionSelector.model = availableChannels
            } else if (sensorFactory.isDigital(type)) {
                sensorOptionText.text = "GPIO: "
                sensorOptionSelector.enabled = true
                sensorOptionSelector.model = availablePins
            } else {
                sensorOptionText.text = "keine Optionen verfügbar"
                sensorOptionSelector.enabled = false
                sensorOptionSelector.model = undefined
            }
        }

        Text {
            id: sensorOptionText
            text: parent.type ? parent.type : ""
        }

        ComboBox {
            id: sensorOptionSelector
            textRole: "display"
            width: sensorCreatePane.width * 0.25
        }
    }

    RoundButton {
        id: add
        anchors.bottom: parent.bottom
        icon { source:"/icons/svg/ic_add_48px.svg"}
        onClicked: {
            actuators.setSender(availablePins.at(gpioSelector.currentIndex))
            availablePins.removeAt(gpioSelector.currentIndex)
        }
    }
}
