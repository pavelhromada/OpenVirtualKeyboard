import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import QtQuick.Templates 2.12 as T

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("OpenVirtualKeyboard - basic")

    ColumnLayout {
        width: parent.width * 0.8
        height: parent.height// * 0.6
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom

        Label {
            text: "Tap fields to enter text with various keyboard layouts"
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
            font.pixelSize: 18
        }

        TextField {
            id: defaultTextField
            placeholderText: "default"
            Layout.fillWidth: true
        }

        TextArea {
            id: control
            placeholderText: "default multi-line"
            Layout.fillWidth: true
            Layout.preferredHeight: defaultTextField.height * 1.5
            background: Rectangle {
                border.width: control.activeFocus ? 2 : 1
                color: control.palette.base
                border.color: control.activeFocus ? control.palette.highlight : control.palette.mid
            }
        }

        TextField {
            placeholderText: "Qt::ImhPreferUppercase"
            inputMethodHints: Qt.ImhPreferUppercase
            Layout.fillWidth: true
        }

        TextField {
            placeholderText: "Qt.ImhUppercaseOnly"
            inputMethodHints: Qt.ImhUppercaseOnly
            Layout.fillWidth: true
        }

        TextField {
            placeholderText: "Qt.ImhDialableCharactersOnly"
            inputMethodHints: Qt.ImhDialableCharactersOnly
            Layout.fillWidth: true
        }

        TextField {
            placeholderText: "Qt.ImhFormattedNumbersOnly"
            inputMethodHints: Qt.ImhFormattedNumbersOnly
            Layout.fillWidth: true
        }

        TextField {
            placeholderText: "Qt.ImhDigitsOnly"
            inputMethodHints: Qt.ImhDigitsOnly
            Layout.fillWidth: true
        }

        TextField {
            placeholderText: "Qt.ImhDate | Qt.ImhTime"
            inputMethodHints: Qt.ImhDate | Qt.ImhTime
            Layout.fillWidth: true
        }

        TextField {
            placeholderText: "Qt.ImhNoAutoUppercase"
            inputMethodHints: Qt.ImhNoAutoUppercase
            Layout.fillWidth: true
        }
    }
}
