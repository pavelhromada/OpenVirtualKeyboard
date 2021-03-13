import QtQuick 2.12

Rectangle {
    radius: height * 0.08
    color: enabled ? parent.pressed ? Qt.lighter( "#c94c4c", 1.1 ) : "#c94c4c"
                   : Qt.darker( "#c94c4c", 1.2 )
    anchors {
        fill: parent
        margins: parent.height * 0.07
    }
    
    Text {
        text: "←"
        verticalAlignment: Text.AlignVCenter
        anchors.centerIn: parent
        anchors.verticalCenterOffset: -(parent.height * 0.1)
        color: "white"
        font.pixelSize: parent.width * 0.5
    }
}
