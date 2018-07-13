import QtQuick 2.0
import QtQuick.Controls 2.3

Column {
    property bool checked: true
    property var text: qsTr("")
    Switch {
        checked: parent.checked
        rotation: -90
        onClicked: function()  {parent.checked = !parent.checked}
    }
    Label {
        anchors.horizontalCenter: parent.horizontalCenter
        text: parent.text
    }
}
