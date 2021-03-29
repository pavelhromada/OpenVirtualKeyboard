/**
 *  MIT License
 *  Copyright (c) Pavel Hromada
 *  See accompanying LICENSE file
 */

import QtQuick 2.12

Rectangle {
    radius: height * 0.1
    color: parent.pressed ? Qt.lighter( "#343434", 1.2 ) : "#343434"
    anchors {
        fill: parent
        margins: parent.height * 0.068
    }

    Text {
        anchors.centerIn: parent
        font.pixelSize: parent.height * 0.4
        color: "white"
        text: parent.parent.text
    }
}
