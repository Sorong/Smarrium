import QtQuick 2.0

Item {
    property var selectMode: function(type) {
        switch (type) {
            case SensorBaseType.UV:
                console.log("UV");
                break;
            default:
                console.log("default");
                break;
        }
    }
}
