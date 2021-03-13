import QtQuick 2.12

Rectangle {
    radius: height * 0.08
    color: enabled ? parent.pressed ? Qt.lighter( "#86af49", 1.1 ) : "#86af49"
                   : Qt.darker( "#86af49", 1.2 )
    anchors {
        fill: parent
        margins: parent.height * 0.07
    }

    Text {
        anchors.centerIn: parent
        anchors.verticalCenterOffset: -(parent.height * 0.1)
        font.pixelSize: parent.height * 0.5
        color: enabled ? parent.parent.shiftOn ? "red" : "black"
                       : parent.parent.shiftOn ? Qt.darker( "red", 2.0 ) : "grey"
        text: "↑"
    }

    Rectangle {
        height: parent.height * 0.08
        width: height
        radius: height / 2
        color: enabled ? "red" : Qt.darker( "red", 2.0 )
        visible: parent.parent.shiftLocked
        anchors {
            left: parent.left
            top: parent.top
            leftMargin: parent.width / 3
            topMargin: parent.height / 3
        }
    }
}
