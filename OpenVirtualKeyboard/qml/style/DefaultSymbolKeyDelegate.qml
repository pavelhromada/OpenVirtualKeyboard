import QtQuick 2.12

DefaultSpecialKeyDelegate {
    Text {
        anchors.centerIn: parent
        font.pixelSize: parent.height * 0.3
        color: "white"
        text: parent.parent.text
    }
}
