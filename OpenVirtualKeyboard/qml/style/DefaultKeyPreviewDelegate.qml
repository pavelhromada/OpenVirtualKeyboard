/**
 *  MIT License
 *  Copyright (c) Pavel Hromada
 *  See accompanying LICENSE file
 */

import QtQuick 2.12

Item {
    id: key

    height: parent.keyHeight * 2.4
    width: parent.keyWidth

    Rectangle {
        anchors {
            fill: parent
            margins: key.parent.keyHeight * 0.068
        }
        radius: key.parent.keyHeight * 0.1
        color: "#555"

        Text {
            anchors {
                centerIn: parent
                verticalCenterOffset: -(key.parent.keyHeight / 2)
            }
            font.pixelSize: key.parent.keyHeight * 0.44
            text: key.parent.keyText
            color: "white"
        }
    }
}
