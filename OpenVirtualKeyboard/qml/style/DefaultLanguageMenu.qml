/**
 *  MIT License
 *  Copyright (c) Pavel Hromada
 *  See accompanying LICENSE file
 */

import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Templates 2.12 as T

T.Popup {
    id: popup

    width: parent.height * 4
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             contentHeight + topPadding + bottomPadding)
    margins: 0
    verticalPadding: 3

    enter: Transition {
        NumberAnimation { property: "scale"; from: 0.9; to: 1.0; easing.type: Easing.OutQuint; duration: 220 }
        NumberAnimation { property: "opacity"; from: 0.0; to: 1.0; easing.type: Easing.OutCubic; duration: 150 }
    }

    exit: Transition {
        NumberAnimation { property: "scale"; from: 1.0; to: 0.9; easing.type: Easing.OutQuint; duration: 220 }
        NumberAnimation { property: "opacity"; from: 1.0; to: 0.0; easing.type: Easing.OutCubic; duration: 150 }
    }

    background: Rectangle {
        width: popup.width
        implicitHeight: 40
        radius: 3
        color: "#eee"
        border.width: 1
        border.color: "#ccc"
    }

    contentItem: ListView {
        width: popup.width
        implicitHeight: contentHeight
        model: popup.parent.languagesModel
        interactive: Window.window ? contentHeight > Window.window.height : false
        clip: true
        delegate: T.ItemDelegate {
            id: item
            width: parent.width
            height: popup.parent.height * 0.86
            leftPadding: 12
            leftInset: 1
            rightInset: 1

            contentItem: Text {
                height: parent.height
                verticalAlignment: Text.AlignVCenter
                text: Qt.locale( modelData ).nativeLanguageName.length > 0
                      ? Qt.locale( modelData ).nativeLanguageName
                      : modelData
                font.pixelSize: popup.parent.height * 0.36
            }

            background: Rectangle {
                width: parent.width
                height: parent.height
                visible: item.down || index === popup.parent.selectedLanguageIndex
                color: item.down
                       ? "#d6d6d6"
                       : index === popup.parent.selectedLanguageIndex
                         ? "#ddd"
                         : "transparent"
            }
            onClicked: {
                popup.parent.selectedLanguageIndex = index
                popup.close()
            }
        }

        ScrollIndicator.vertical: ScrollIndicator {}
    }
}

