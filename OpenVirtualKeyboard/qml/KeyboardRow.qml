import QtQuick 2.12
import QtQuick.Templates 2.12 as T
import Qt.labs.qmlmodels 1.0
import OpenVirtualKeyboard 1.0
import "style"

Row {
    id: root
    property alias model: repeater.model
    property StyleComponents style
    readonly property real baseWidth: width / repeater.count
    property real adaptedStretch: 1.0

    spacing: 0

    Repeater {
        id: repeater
        delegate: DelegateChooser {
            role: "type"

            DelegateChoice {
                roleValue: "key"
                Key {
                    id: keyButton
                    property real __stretch: modelData.hasOwnProperty( "stretch" ) ? modelData.stretch : 1
                    property string __text: modelData.hasOwnProperty( "text" ) ? modelData.text : ""
                    alternatives: modelData.hasOwnProperty( "alternatives" )
                                  ? modelData.alternatives
                                  : ""
                    text: InputContext.shiftOn ? __text.toUpperCase() : __text
                    delegate: style.key.createObject( keyButton )
                    type: Key.KeyDefault
                    height: root.height
                    width: __stretch * adaptedStretch * baseWidth
                    Component.onDestruction: delegate.destroy()
                }
            }
            DelegateChoice {
                roleValue: "backspace"
                Key {
                    id: backspaceButton
                    property real __stretch: modelData.hasOwnProperty( "stretch" ) ? modelData.stretch : 1
                    delegate: style.backspaceKey.createObject( backspaceButton )
                    type: Key.Backspace
                    height: root.height
                    width: __stretch * adaptedStretch * baseWidth
                    Component.onDestruction: delegate.destroy()
                }
            }
            DelegateChoice {
                roleValue: "enter"
                Key {
                    id: enterButton
                    property real __stretch: modelData.hasOwnProperty( "stretch" ) ? modelData.stretch : 1
                    readonly property bool enterKeyActionEnabled: InputContext.enterKeyActionEnabled
                    readonly property int enterKeyAction: InputContext.enterKeyAction
                    enabled: enterKeyActionEnabled
                    delegate: style.enterKey.createObject( enterButton )
                    type: Key.Enter
                    height: root.height
                    width: __stretch * adaptedStretch * baseWidth
                    Component.onDestruction: delegate.destroy()
                }
            }
            DelegateChoice {
                roleValue: "shift"
                Key {
                    id: shiftButton
                    property real __stretch: modelData.hasOwnProperty( "stretch" ) ? modelData.stretch : 1
                    readonly property bool shiftOn: InputContext.shiftOn
                    readonly property bool shiftLocked: InputContext.shiftLocked
                    enabled: InputContext.shiftEnabled
                    delegate: style.shiftKey.createObject( shiftButton )
                    type: Key.Shift
                    height: root.height
                    width: __stretch * adaptedStretch * baseWidth
                    Component.onDestruction: delegate.destroy()
                }
            }
            DelegateChoice {
                roleValue: "symbol"
                Key {
                    id: symbolButton
                    property real __stretch: modelData.hasOwnProperty( "stretch" ) ? modelData.stretch : 1
                    text: modelData.hasOwnProperty( "text" ) ? modelData.text : ""
                    delegate: style.symbolKey.createObject( symbolButton )
                    type: Key.Symbol
                    height: root.height
                    width: __stretch * adaptedStretch * baseWidth
                    Component.onDestruction: delegate.destroy()
                }
            }
            DelegateChoice {
                roleValue: "language"
                Key {
                    id: languageButton
                    property real __stretch: modelData.hasOwnProperty( "stretch" ) ? modelData.stretch : 1
                    property var languagesModel: InputContext.layoutProvider.layoutsList
                    property int selectedLanguageIndex: InputContext.layoutProvider.selectedLayoutIndex
                    onSelectedLanguageIndexChanged: InputContext.layoutProvider.selectedLayoutIndex
                                                    = selectedLanguageIndex
                    property T.Popup languageMenu: style.languageMenu.createObject( languageButton )
                    type: Key.Language
                    delegate: style.languageKey.createObject( languageButton )
                    enabled: InputContext.layoutProvider.layoutsCount > 1
                    height: root.height
                    width: __stretch * adaptedStretch * baseWidth
                    onClicked: languageMenu.open()
                    Component.onDestruction: {
                        languageMenu.destroy()
                        delegate.destroy()
                    }
                }
            }
            DelegateChoice {
                roleValue: "space"
                Key {
                    id: spaceButton
                    property real __stretch: modelData.hasOwnProperty( "stretch" ) ? modelData.stretch : 1
                    readonly property string selectedLayout: InputContext.layoutProvider.selectedLayout
                    delegate: style.spaceKey.createObject( spaceButton )
                    type: Key.Space
                    height: root.height
                    width: __stretch * adaptedStretch * baseWidth
                    Component.onDestruction: delegate.destroy()
                }
            }
            DelegateChoice {
                roleValue: "hide"
                Key {
                    id: hideButton
                    property real __stretch: modelData.hasOwnProperty( "stretch" ) ? modelData.stretch : 1
                    delegate: style.hideKey.createObject( hideButton )
                    type: Key.Hide
                    height: root.height
                    width: __stretch * adaptedStretch * baseWidth
                    Component.onDestruction: delegate.destroy()
                }
            }
            DelegateChoice {
                roleValue: "page"
                Key {
                    id: pageButton
                    property real __stretch: modelData.hasOwnProperty( "stretch" ) ? modelData.stretch : 1
                    text: modelData.hasOwnProperty( "text" ) ? modelData.text : ""
                    delegate: style.nextPageKey.createObject( pageButton )
                    type: Key.NextPage
                    height: root.height
                    width: __stretch * adaptedStretch * baseWidth
                    Component.onDestruction: delegate.destroy()
                }
            }
            DelegateChoice {
                roleValue: "filler"
                Item {
                    property real __stretch: modelData.hasOwnProperty( "stretch" ) ? modelData.stretch : 1
                    height: root.height
                    width: __stretch * adaptedStretch * baseWidth
                }
            }
        }
    }
}
