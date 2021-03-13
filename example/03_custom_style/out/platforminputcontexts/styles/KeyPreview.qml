import QtQuick 2.12

Rectangle {
    height: parent.keyHeight * 2
    width: parent.keyWidth
    radius: parent.height * 0.08
    color: "#222"
    border {
        width: 1
        color: "#242424"
    }

    Text {
        anchors {
            centerIn: parent
            verticalCenterOffset: -(parent.parent.keyHeight / 2)
        }
        font.pixelSize: parent.parent.keyHeight * 0.4
        text: parent.parent.keyText
        color: "white"
    }
}