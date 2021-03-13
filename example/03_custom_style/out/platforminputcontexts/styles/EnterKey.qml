import QtQuick 2.12

Rectangle {
    radius: height * 0.08
    color: enabled ? parent.pressed ? Qt.lighter( "#034f84", 1.1 ) : "#034f84"
                   : Qt.darker( "#034f84", 1.2 )
    anchors {
        fill: parent
        margins: parent.height * 0.07
    }

    Text {
        text: "Enter"
        anchors.centerIn: parent
        color: "white"
        font.pixelSize: parent.height * 0.3
    }
}
