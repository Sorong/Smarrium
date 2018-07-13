import QtQuick 2.0
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.2

Item {
    id: start_
    //anchors.fill: parent

    Label {
        id: titleStart
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent ? parent.width/5*4 : 0
        text: qsTr("Willkommen")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Label {
        id: content
        anchors.top: titleStart.bottom
        anchors.topMargin: 20
        text: qsTr("ALorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.   \n\nDuis autem vel eum iriure dolor in hendrerit in vulputate velit esse molestie consequat, vel illum dolore eu feugiat nulla facilisis at vero eros et accumsan et iusto odio dignissim qui blandit praesent luptatum zzril delenit augue duis dolore te feugait nulla facilisi. Lorem ipsum dolor sit amet,")
        font.pointSize: 8
        lineHeight: 1
        fontSizeMode: Text.FixedSize
        anchors.left: titleStart.left
        anchors.right: titleStart.right
        wrapMode: Text.WordWrap
        font.weight: Font.Light
    }

    Button {
        id: btnNewConfig
        height: 40
        text: qsTr("Neue Konfiguration anlegen")
        anchors.leftMargin: 0
        anchors.left: content.left
        anchors.bottom: btnExistingConfig.top
        anchors.bottomMargin: 20
        anchors.right: content.right
        anchors.rightMargin: 0
        onClicked: {
            stackView.push("add_actor.qml")
        }
    }

    Button {
        id: btnExistingConfig
        height: 40
        text: qsTr("Existierende Konfiguration ändern")
        anchors.leftMargin: 0
        anchors.left: content.left
        anchors.bottom: btnReview.top
        anchors.bottomMargin: 20
        anchors.right: content.right
        anchors.rightMargin: 0
        onClicked: {
            stackView.push("overview.qml")
        }
    }

    Button {
        id: btnReview
        height: 40
        text: qsTr("24h Rückblick betrachten")
        anchors.leftMargin: 0
        anchors.left: content.left
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.right: content.right
        anchors.rightMargin: 0
        anchors.topMargin: 6
        onClicked: {
            stackView.push("overview.qml")
        }
    }

}

