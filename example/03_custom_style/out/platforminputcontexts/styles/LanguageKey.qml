import QtQuick 2.12
import "components"

KeyBase {
    color: enabled ? parent.pressed ? Qt.darker( "#abafba", 1.1 ) : "#abafba"
                   : Qt.lighter( "#abafba", 1.2 )

    Icon {
        anchors.centerIn: parent
        size: parent.height * 0.4
        color: enabled ? "black" : "darkgrey"
        name: 'globe-1'
    }
}
