import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.5
import OpenVirtualKeyboard 1.0
import "style"

Item {
    id: keyboard
    
    property real padding: width * 0.05
    property real leftPadding: width * 0.05
    property real rightPadding: width * 0.05
    property real topPadding: width * 0.005
    property real bottomPadding: width * 0.045
    property KeyboardStyle style: KeyboardStyle {}

    objectName: "keyboard"
    width: parent ? parent.width : 0
    height: width / 3

    Component.onCompleted: InputContext.informKeyboardCreated()

    StyleComponents {
        id: styles
        key: Qt.createComponent( style.keyUrl )
        enterKey: Qt.createComponent( style.enterKeyUrl )
        backspaceKey: Qt.createComponent( style.backspaceKeyUrl )
        shiftKey: Qt.createComponent( style.shiftKeyUrl )
        spaceKey: Qt.createComponent( style.spaceKeyUrl )
        hideKey: Qt.createComponent( style.hideKeyUrl )
        symbolKey: Qt.createComponent( style.symbolKeyUrl )
        languageKey: Qt.createComponent( style.languageKeyUrl )
        nextPageKey: Qt.createComponent( style.nextPageKeyUrl )
        keyPreview: Qt.createComponent( style.keyPreviewUrl )
        keyAlternativesPreview: Qt.createComponent( style.keyAlternativesPreviewUrl )
        languageMenu: Qt.createComponent( style.languageMenuUrl )
    }

    MouseArea {
        anchors.fill: parent // to avoid clicks propagate through the background
    }

    Loader {
        anchors.fill: parent
        source: style.backgroundUrl
    }

    Item {
        id: keyboardContent
        anchors {
            fill: parent
            margins: keyboard.padding
            topMargin: keyboard.topPadding
            bottomMargin: keyboard.bottomPadding
            leftMargin: keyboard.leftPadding
            rightMargin: keyboard.rightPadding
        }

        Item {
            id: layoutsContainer
            anchors.fill: parent

            KeyboardLayout {
                visible: InputContext.layoutType == KeyboardLayoutType.Alphabet
                anchors.fill: parent
                keyStyles: styles
                layoutModel: InputContext.layoutProvider.alphabetModel
            }

            KeyboardLayout {
                visible: InputContext.layoutType == KeyboardLayoutType.Symbols
                anchors.fill: parent
                keyStyles: styles
                layoutModel: InputContext.layoutProvider.symbolsModel
            }

            KeyboardLayout {
                visible: InputContext.layoutType == KeyboardLayoutType.Dial
                anchors.fill: parent
                keyStyles: styles
                layoutModel: InputContext.layoutProvider.dialModel
            }

            KeyboardLayout {
                visible: InputContext.layoutType == KeyboardLayoutType.Numbers
                anchors.fill: parent
                keyStyles: styles
                layoutModel: InputContext.layoutProvider.numbersModel
            }

            KeyboardLayout {
                visible: InputContext.layoutType == KeyboardLayoutType.Digits
                anchors.fill: parent
                keyStyles: styles
                layoutModel: InputContext.layoutProvider.digitsModel
            }
        }

        KeyPressInterceptor {
            objectName: "keyInterceptor"
            anchors.fill: parent
            forwardTo: layoutsContainer
        }

        KeyPreview {
            id: keyPreview
            objectName: "keyPreview"
            delegate: styles.keyPreview.createObject( keyPreview )
        }

        KeyAlternativesPreview {
            id: alternativesPreview
            objectName: "keyAlternatives"
            uppercase: InputContext.shiftOn
            delegate: styles.keyAlternativesPreview.createObject( alternativesPreview )
        }
    }
}
