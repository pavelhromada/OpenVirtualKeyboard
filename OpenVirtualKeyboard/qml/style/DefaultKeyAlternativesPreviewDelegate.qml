/**
 *  MIT License
 *  Copyright (c) Pavel Hromada
 *  See accompanying LICENSE file
 */

import QtQuick 2.12

Rectangle {
    id: bubble
    height: parent.keyHeight * 2
    width: parent.keyWidth * parent.alternatives.length
    radius: parent.height * 0.08
    color: "#444"
    border {
        width: 1
        color: "#222"
    }

    ListView {
        anchors.fill: parent
        orientation: ListView.Horizontal
        interactive: false
        model: bubble.parent.alternatives
        currentIndex: bubble.parent.alternativeIndex
        delegate: Item {
            width: bubble.parent.keyWidth
            height: bubble.parent.keyHeight * 2

            Text {
                text: modelData
                color: "white"
                font.pixelSize: bubble.parent.keyHeight * 0.4
                anchors {
                    centerIn: parent
                    verticalCenterOffset: -(bubble.parent.keyHeight / 2)
                }
            }
        }
        highlightMoveVelocity: -1
        highlight: Rectangle {
            color: "#222"
            radius: height * 0.08
        }
    }
}
