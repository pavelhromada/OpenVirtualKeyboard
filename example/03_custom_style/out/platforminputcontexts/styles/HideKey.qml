import QtQuick 2.12
import "components"

KeyBase {
    color: enabled ? parent.active ? Qt.darker( "#abafba", 1.1 ) : "#abafba"
                   : Qt.lighter( "#abafba", 1.2 )

    Icon {
        anchors {
            centerIn: parent
            verticalCenterOffset: -parent.height * 0.12
        }
        size: parent.height * 0.4
        color: "black"
        name: 'keyboard'
    }

    Icon {
        anchors {
            centerIn: parent
            verticalCenterOffset: parent.height * 0.2
        }
        size: parent.height * 0.3
        color: "black"
        name: 'down-open'
    }
}
