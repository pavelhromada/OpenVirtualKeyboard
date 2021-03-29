/**
 *  MIT License
 *  Copyright (c) Pavel Hromada
 *  See accompanying LICENSE file
 */

import QtQuick 2.12

Rectangle {
    radius: parent.height * 0.08
    color: parent.enabled ? parent.pressed ? Qt.lighter( "#212121", 1.1 ) : "#212121"
                          : Qt.darker( "#212121", 1.2 )
    anchors {
        fill: parent
        margins: parent.height * 0.07
    }
}
