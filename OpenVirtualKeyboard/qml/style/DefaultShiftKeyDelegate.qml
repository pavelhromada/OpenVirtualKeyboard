/**
 *  MIT License
 *  Copyright (c) Pavel Hromada
 *  See accompanying LICENSE file
 */

import QtQuick 2.12

DefaultSpecialKeyDelegate {
    id: key

    Icon {
        id: icon
        anchors.centerIn: parent
        size: parent.height * 0.5
        color: key.parent.enabled ? key.parent.shiftOn ? "gold" : "white"
                                  : key.parent.shiftOn ? Qt.darker( "gold", 2.0 ) : "grey"
        name: 'up'
    }

    Rectangle {
        height: parent.height * 0.08
        width: height
        radius: height / 2
        color: key.parent.enabled ? "gold" : Qt.darker( "gold", 2.0 )
        visible: key.parent.shiftLocked
        anchors {
            left: icon.left
            top: icon.top
        }
    }
}
