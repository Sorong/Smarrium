import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.3
Window {

    id: window
    visible: true
    width: 1280
    height: 480
    minimumHeight: 400
    minimumWidth: 640
    title: qsTr("Smarrium")
    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: Qt.resolvedUrl("start.qml")
        //initialItem:
    }
}
