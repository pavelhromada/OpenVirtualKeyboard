import QtQuick 2.12
import "components"

KeyBase {
    color: enabled ? parent.active ? Qt.darker( "#fefefe", 1.1 ) : "#fefefe"
                   : Qt.lighter( "#fefefe", 1.2 )

    Text {
        anchors.centerIn: parent
        font.pixelSize: parent.height * 0.3
        color: "black"
        text: parent.parent.text
    }
}
