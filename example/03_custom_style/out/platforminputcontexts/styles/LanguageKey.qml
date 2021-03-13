import QtQuick 2.12

Rectangle {
    radius: height * 0.08
    color: enabled ? parent.pressed ? Qt.lighter( "#222", 1.1 ) : "#222"
                   : Qt.darker( "#222", 1.2 )
    anchors {
        fill: parent
        margins: parent.height * 0.07
    }

    Text {
        text: "LNG"
        anchors.centerIn: parent
        color: "white"
        font.pixelSize: parent.height * 0.3
    }
}
