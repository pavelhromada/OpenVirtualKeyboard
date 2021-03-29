/**
 *  MIT License
 *  Copyright (c) Pavel Hromada
 *  See accompanying LICENSE file
 */

import QtQuick 2.12
import QtQml 2.12

Rectangle {
    id: bg
    radius: parent.height * 0.08
    color: parent.pressed ? Qt.lighter( "#343434", 1.2 ) : "#343434"
    anchors {
        fill: parent
        margins: parent.height * 0.068
    }

    Icon {
        visible: !languageName.visible
        anchors {
            centerIn: bg
            verticalCenterOffset: bg.height * 0.2
        }
        size: bg.height * 0.3
        color: "white"
        name: 'myspace'
    }

    Text {
        id: languageName
        visible: contentWidth < bg.width + 20
        anchors.centerIn: parent
        font.pixelSize: parent.height * 0.4
        color: "dimgray"
        text: Qt.locale( parent.parent.selectedLayout ).nativeLanguageName
    }
}
