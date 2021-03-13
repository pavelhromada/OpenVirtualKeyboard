import QtQuick 2.12

DefaultSpecialKeyDelegate {
    Icon {
        anchors.centerIn: parent
        size: parent.height * 0.5
        color: enabled ? "white" : "#333"
        name: 'globe'
    }
}
