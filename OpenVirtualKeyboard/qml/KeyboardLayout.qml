/**
 *  MIT License
 *  Copyright (c) Pavel Hromada
 *  See accompanying LICENSE file
 */

import QtQuick 2.12
import QtQuick.Layouts 1.12
import OpenVirtualKeyboard 1.0
import "style"

StackLayout {
    id: keyboardLayout

    property StyleComponents keyStyles
    property KeyboardLayoutModel layoutModel

    currentIndex: layoutModel.currentPage
    onVisibleChanged: layoutModel.currentPage = 0

    Repeater {
        model: layoutModel.pages
        delegate: Column {
            spacing: 0
            Layout.fillHeight: true
            Layout.fillWidth: true

            KeyboardRow {
                id: row1
                style: keyboardLayout.keyStyles
                model: modelData.length >= 1 ? modelData[0] : null
                adaptedStretch: layoutModel.adaptedStretchRow1
                height: parent.height / 4
                width: parent.width
            }

            KeyboardRow {
                id: row2
                style: keyboardLayout.keyStyles
                model: modelData.length >= 2 ? modelData[1] : null
                adaptedStretch: layoutModel.adaptedStretchRow2
                height: parent.height / 4
                width: parent.width
            }

            KeyboardRow {
                id: row3
                style: keyboardLayout.keyStyles
                model: modelData.length >= 3 ? modelData[2] : null
                adaptedStretch: layoutModel.adaptedStretchRow3
                height: parent.height / 4
                width: parent.width
            }

            KeyboardRow {
                id: row4
                style: keyboardLayout.keyStyles
                model: modelData.length >= 4 ? modelData[3] : null
                adaptedStretch: layoutModel.adaptedStretchRow4
                height: parent.height / 4
                width: parent.width
            }
        }
    }
}
