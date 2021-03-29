/**
 *  MIT License
 *  Copyright (c) Pavel Hromada
 *  See accompanying LICENSE file
 */

import QtQuick 2.12

DefaultSpecialKeyDelegate {
    Icon {
        anchors {
            centerIn: parent
            verticalCenterOffset: -parent.height * 0.12
        }
        size: parent.height * 0.5
        color: "white"
        name: 'keyboard'
    }

    Icon {
        anchors {
            centerIn: parent
            verticalCenterOffset: parent.height * 0.2
        }
        size: parent.height * 0.3
        color: "white"
        name: 'down-open'
    }
}
