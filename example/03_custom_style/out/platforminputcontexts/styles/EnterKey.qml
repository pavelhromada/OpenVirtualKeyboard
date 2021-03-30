import QtQuick 2.12
import "components"

KeyBase {
    id: key
    color: enabled ? parent.active ? Qt.darker( "#3478f2", 1.1 ) : "#3478f2"
                   : Qt.lighter( "#3478f2", 1.2 )

//    Text {
//        text: "Search"
//        anchors.centerIn: parent
//        color: "white"
//        font.pixelSize: parent.height * 0.3
//    }

    Icon {
        id: icon
        anchors.centerIn: parent
        size: parent.height * 0.4
        color: key.parent.enabled ? "white" : "darkgrey"
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
