/**
 *  MIT License
 *  Copyright (c) Pavel Hromada
 *  See accompanying LICENSE file
 */

import QtQuick 2.12

Item {
    id: key

    readonly property real margin: parent.keyHeight * 0.068

    height: parent.keyHeight * 2.4
    width: (parent.keyWidth - 2 * margin) * parent.alternatives.length + 2 * margin

    Rectangle {
        anchors {
            fill: parent
            margins: key.margin
        }
        radius: key.parent.keyWidth * 0.1
        color: "#555"

        ListView {
            anchors.fill: parent
            orientation: ListView.Horizontal
            interactive: false
            model: key.parent.alternatives
            currentIndex: key.parent.alternativeIndex
            delegate: Item {
                width: key.parent.keyWidth - (key.margin * 2)
                height: key.parent.keyHeight * 2.4 - (key.margin * 2)

                Text {
                    text: modelData
                    color: "white"
                    font.pixelSize: key.parent.keyHeight * 0.44
                    anchors {
                        centerIn: parent
                        verticalCenterOffset: -(key.parent.keyHeight / 2)
                    }
                }
            }
            highlightMoveVelocity: -1
            highlight: Rectangle {
                color: "#444"
                radius: width * 0.1
            }
        }
    }
}
