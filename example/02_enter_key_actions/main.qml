import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("OpenVirtualKeyboard - enter key actions")

    ColumnLayout {
        width: parent.width * 0.8
        height: parent.height
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom

        Label {
            text: "Tap fields to enter text with various enter key actions"
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
            font.pixelSize: 18
        }
        Label {
            id: actionLabel
            property string lastAction
            text: "Last action: " + lastAction
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
            font.pixelSize: 18
        }
        EnterActionTextField {
            enterKeyAction: Qt.EnterKeyDefault
            onAccepted: {
                actionLabel.lastAction = "default enter..."
                searchingField.focus = true
            }
        }
        EnterActionTextField {
            id: searchingField
            enterKeyAction: Qt.EnterKeySearch
            onAccepted: {
                actionLabel.lastAction = "searching..."
                goField.focus = true
            }
        }
        EnterActionTextField {
            id: goField
            enterKeyAction: Qt.EnterKeyGo
            onAccepted: {
                actionLabel.lastAction = "go..."
                sendField.focus = true
            }
        }
        EnterActionTextField {
            id: sendField
            enterKeyAction: Qt.EnterKeySend
            onAccepted: {
                actionLabel.lastAction = "send..."
                nextField.focus = true
            }
        }
        EnterActionTextField {
            id: nextField
            enterKeyAction: Qt.EnterKeyNext
            onAccepted: {
                actionLabel.lastAction = "next..."
                previousField.focus = true
            }
        }
        EnterActionTextField {
            id: previousField
            enterKeyAction: Qt.EnterKeyPrevious
            onAccepted: {
                actionLabel.lastAction = "previous..."
                doneField.focus = true
            }
        }
        EnterActionTextField {
            id: doneField
            enterKeyAction: Qt.EnterKeyDone
            onAccepted: actionLabel.lastAction = "done..."
        }
    }
}
