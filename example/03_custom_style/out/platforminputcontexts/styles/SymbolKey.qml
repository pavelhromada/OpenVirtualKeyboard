import QtQuick 2.12
import "components"

KeyBase {
    color: enabled ? parent.active ? Qt.darker( "#abafba", 1.1 ) : "#abafba"
                   : Qt.lighter( "#abafba", 1.2 )
    Text {
        anchors.centerIn: parent
        font.pixelSize: parent.height * 0.3
        color: "black"
        text: parent.parent.text
    }
}
