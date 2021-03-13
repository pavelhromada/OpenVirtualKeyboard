import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

TextField {
    property bool enterKeyActionEnabled: text.length > 0
    property int enterKeyAction: Qt.EnterKeyDefault
    placeholderText: {
        if (enterKeyAction === Qt.EnterKeyDefault)
            return "Qt.EnterKeyDefault"
        else if (enterKeyAction === Qt.EnterKeyReturn)
            return "Qt.EnterKeyReturn"
        else if (enterKeyAction === Qt.EnterKeyDone)
            return "Qt.EnterKeyDone"
        else if (enterKeyAction === Qt.EnterKeyGo)
            return "Qt.EnterKeyGo"
        else if (enterKeyAction === Qt.EnterKeySend)
            return "Qt.EnterKeySend"
        else if (enterKeyAction === Qt.EnterKeySearch)
            return "Qt.EnterKeySearch"
        else if (enterKeyAction === Qt.EnterKeyNext)
            return "Qt.EnterKeyNext"
        else
            return "Qt.EnterKeyPrevious"
    }
    Layout.fillWidth: true
}
