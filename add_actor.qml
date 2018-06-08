import QtQuick 2.0
import QtQuick.Window 2.10
import QtQuick.Controls 2.3

Item {
    id: addActor
    property alias content: content
    //anchors.fill: parent

    Label {
        id: titleActor
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width/5*4
        text: qsTr("Modul hinzufügen")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Label {
        id: content
        anchors.top: titleActor.bottom
        anchors.topMargin: 20
        text: qsTr("ALorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.   \n\nDuis autem vel eum iriure dolor in hendrerit in vulputate velit esse molestie consequat, vel illum dolore eu feugiat nulla facilisis at vero eros et accumsan et iusto odio dignissim qui blandit praesent luptatum zzril delenit augue duis dolore te feugait nulla facilisi. Lorem ipsum dolor sit amet,")
        //text: availablePins.data(0)
        font.pointSize: 8
        lineHeight: 1
        fontSizeMode: Text.FixedSize
        anchors.left: titleActor.left
        anchors.right: titleActor.right
        wrapMode: Text.WordWrap
        font.weight: Font.Light
    }
    Button {
        id: btnNewActor
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

    ComboBox {
        id: gpioSelector
        textRole: "display"
        anchors.top: content.bottom
        anchors.topMargin: 20
        model: availablePins
        anchors.left: content.left
        //delegate: add
    }

   RoundButton {
        id: add
        anchors.topMargin: 20
        anchors.top: content.bottom
        anchors.left: gpioSelector.right
        anchors.leftMargin: 10
        text: "+"
        onClicked: {
            availablePins.removeAt(gpioSelector.currentIndex)
        }
    }
/*
    RoundButton {
        id: add
        anchors.top: content.bottom
        anchors.topMargin: 20
        anchors.left: gpioSelector.right
        anchors.leftMargin: 10
        text: "+"
        onClicked: {
            gpioSelector.de
        }
    }
*/

}
