import QtQuick 2.12

Rectangle {
    radius: height * 0.08
    color: parent.pressed ? Qt.lighter( "#333", 1.2 ) : "#333"
    anchors {
        fill: parent
        margins: parent.height * 0.07
    }

    Text {
        anchors.centerIn: parent
        font.pixelSize: parent.height * 0.4
        color: "white"
        text: parent.parent.text
    }
}
