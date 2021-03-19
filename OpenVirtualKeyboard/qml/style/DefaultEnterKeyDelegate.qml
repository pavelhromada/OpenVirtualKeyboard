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
        color: key.parent.enabled ? "white" : "grey"
        name: {
            if (key.parent.enterKeyAction === Qt.EnterKeySearch)
                return "search"
            else if (key.parent.enterKeyAction === Qt.EnterKeyDone)
                return "ok"
            else if (key.parent.enterKeyAction === Qt.EnterKeyGo)
                return "link-ext"
            else if (key.parent.enterKeyAction === Qt.EnterKeySend)
                return "paper-plane"
            else if (key.parent.enterKeyAction === Qt.EnterKeyNext)
                return "right-open"
            else if (key.parent.enterKeyAction === Qt.EnterKeyPrevious)
                return "left-open"
            else
                return "level-down"
        }
        rotation: key.parent.enterKeyAction === Qt.EnterKeyDefault
                  || key.parent.enterKeyAction === Qt.EnterKeyReturn ? 90 : 0
    }
}
