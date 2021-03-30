import QtQuick 2.12
import "components"

KeyBase {
    id: key

    color: enabled ? parent.active ? Qt.darker( "#abafba", 1.1 ) : "#abafba"
                   : Qt.lighter( "#abafba", 1.2 )

    Icon {
        id: icon
        anchors.centerIn: parent
        size: parent.height * 0.4
        color: key.parent.enabled ? key.parent.shiftOn ? "#3478f2" : "black"
                                  : key.parent.shiftOn ? Qt.darker( "#3478f2", 2.0 ) : "grey"
        name: 'up'
    }

    Rectangle {
        height: parent.height * 0.08
        width: height
        radius: height / 2
        color: key.parent.enabled ? "#3478f2" : Qt.darker( "#3478f2", 2.0 )
        visible: key.parent.shiftLocked
        anchors {
            left: icon.left
            top: icon.top
        }
    }
}
