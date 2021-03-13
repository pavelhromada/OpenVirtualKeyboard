import QtQuick 2.12

DefaultSpecialKeyDelegate {
    id: key

    Text {
        anchors.centerIn: parent
        font.pixelSize: parent.height * 0.3
        color: "white"
        text: key.parent.text
    }
}
