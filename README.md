# OpenVirtualKeyboard

Virtual keyboard used for Qt Quick applications. Implemented as in-process keyboard
(loaded as plugin into your application). Even though it is not packed with many features
(handwriting, word suggestion, etc.), you may find it right fit for your project. It gives
you an option to customize style, layouts, appearance behaviour and some more features. Plus
it's free (MIT) and you can use it even in your commercial projects. Implemented against and
works with Qt 5.12 as minimal version.

* [Features](#features)
* [Integration](#integration)
    * [Basic usage](#basic-usage)
    * [Configuration](#configuration)
       * [animateRollout](#animaterollout)
       * [ownWindow](#ownwindow)
       * [immediateLoading](#immediateloading)
       * [noContentScrolling](#nocontentscrolling)
    * [Direct usage of Keyboard component in your app window](#direct-usage-of-keyboard-component-in-your-app-window)
* [Customizing keyboard style](#customizing-keyboard-style)
    * [Customizing keyboard background](#customizing-keyboard-background)
    * [Customizing default key](#customizing-default-key)
    * [Customizing Enter key](#customizing-enter-key)
       * [Enter key actions manipulation](#enter-key-actions-manipulation)
    * [Customizing Backspace key](#customizing-backspace-key)
    * [Customizing Shift key](#customizing-shift-key)
    * [Customizing Space key](#customizing-space-key)
    * [Customizing Hide key](#customizing-hide-key)
    * [Customizing Symbol key](#customizing-symbol-key)
    * [Customizing Next Page key](#customizing-next-page-key)
    * [Customizing Language key](#customizing-language-key)
    * [Customizing language menu](#customizing-language-menu)
    * [Customizing character preview](#customizing-character-preview)
    * [Customizing alternative characters preview](#customizing-alternative-characters-preview)
* [Customizing layouts](#customizing-layouts)
* [Logging](#logging)
* [Inspiration](#inspiration)
* [License](#license)

# **<span style="color:red">WARNING:</span>** work in progress

Even though the OpenVirtualKeyboard is already usable, I still need to implement some features. From
the top of my head, this is the todo list.

- [x] use logging category
- [x] load custom styles from *styles* directory next to plugin
- [ ] custom layouts
    - [x] load custom layouts from *layouts* directory next to plugin
    - [ ] validate scheme of custom layouts
    - [x] language switch
    - [x] language switch disabled for user when only one layout available
    - [x] Space key should be feed with name of current layout (language) selected
- [x] key alternatives uppercase
- [x] disallow shift change when Qt::ImhUppercaseOnly hint is recognized
- [x] special action on Enter key
- [x] add default icons for enter key actions
- [x] lazy loading vs immediate loading of keyboard (configuration parameter QT_IM_MODULE=openvirtualkeyboard:immediateLoading)
- [x] keyboard in own top level window vs. keyboard component "injected" into applications window (configuration parameter QT_IM_MODULE=openvirtualkeyboard:ownWindow)
    - [x] show keyboard window on screen where focused TextInput window is located ?
    - [x] fix when contentItem is scrolled and and one clicks on another monitor and then into different TextField of window
    - [x] fix when focus is in text field and tab is pressed, comntentItem is not scrolled
    - [ ] why keyboard in own window is not animated when first time shown (only on second monitor)
    - [x] fix position of keyboard when displayed and one clicks another window and then back onto keyboard window but into different input (animationRollout enabled) 
    - [x] injected keyboard: setParentItem( focusedWindow->contentItem() )
- [x] fix when application starts and keyboard is not loaded yet and someone clicks into TextFielkd
- [x] focus item overlap
    - [x] make focused input component visible even if keyboard overlaps it (scroll contentItem)
    - [x] make contentItem scrolling optional (QT_IM_MODULE=openvirtualkeyboard:noContentScrolling)
    - [x] use mapToItem when handling overlap
    - [x] animated keyboard show/hide (configuration parameter QT_IM_MODULE=openvirtualkeyboard:animateRollout)
- [ ] fullscreen mode
    - [ ] show embedded input field on keyboard if focused item will not fit into window (or based on aspect ratio of window)
    - [ ] follow settings of focused input field (Qt::ImhHiddenText (password) etc.)
- [x] try Drawer instead of item for keyboard panel (not neccessary)
- [x] alternative key characters
- [x] pressed key popup
- [ ] test pressed key popup on touch based device
- [x] repeating press
- [x] follow Qt::ImhNoAutoUppercase hint
- [x] press and hold for shift lock
- [ ] clean-up default en-US layout (alternative characters, ...)
- [ ] optimizations
   - [ ] allow disabling of some layout types (e.g. just use alphabet type and do not load dial, digits, ...) to optimize keyboard loading time
   - [ ] do not load all 4 layout rows if layout does not specify all rows
   - [ ] adapt height of keyboard based on count of keyboard rows

# Features

So far it is not feature rich as Android keyboard or original Qt virtual keyboard, but the list
of features it provides may be found at least interresting :)

* works with Qt Quick based UIs (not for widget based UIs)
* support for special enter key actions (search, done, go, next, send, ...)
* shift and shift lock feature
* follows input method hints (different layouts for alphabet, dial, digits, numbers or symbols)
* key preview and key alternatives preview bubbles
* customization of style (every single key type can be customized)
* customization of layouts (add your own custom layouts or different language layouts)
* auto uppercase when new sentence starts (follows Qt::ImhNoAutoUppercase hint)
* roll out animation of keyboard panel (can be turned on/off)
* keyboard panel in own window or injected into focused application window (configurable feature)
* immediate vs. lazy loading of keyboard during application start (configurable)
* auto scrolling of window contentItem to make focused input field visible (only for injected keyboard)
* implementation is javascript free, key handling is done on C++ side and principle of Qt Quick Controls 2 is followed
* ...

# Integration

## Basic usage

OpenVirtualKeyboard is ment to be out-of-the-box solution which in its base does not require
to write any additional code into target application. Therefore basic integration is just
a two step process:
1. deploy OpenVirtualKeyboard plugin in *platforminputcontexts* folder next to your application executable
```
    ├─ yourApplication(.exe)
    └─ platforminputcontexts
        └─ openvirtualkeyboard(.dll|.so)
```
2. set *QT_IM_MODULE* environment variable like this `QT_IM_MODULE=openvirtualkeyboard`

## Configuration

Behaviour of the keyboard can be tweaked by additional optional parameters provided as colon
separated values as part of QT_IM_MODULE environment variable. Full list of supported values
looks like this `QT_IM_MODULE=openvirtualkeyboard:animateRollout:ownWindow:immediateLoading`, 
but you can just use the values you want, not all of them.

### `animateRollout`

When set, keyboard roll out animation will be used when show/hide happens. If not set (default),
animation won't be used.

![Alt text](img/animate-rollout.gif?raw=true)

### `ownWindow`

When set, keyboard will be rendered in own window and fills full width of the screen where
it is shown. Keyboard in own window always follows the screen where focused input field window
is displayed. Therefore if you have multiple screens and move focused window from one screen
to another, keyboard will render itself on that screen as well. If `ownWindow` is not set (default),
keyboard will be "injected" into window where input field was focused. Injected keyboard always
follows focused window and therefore works properly also for multi-windowed applications.

### `immediateLoading`

Because this keyboard is implemented as in-process type of keyboard and is loaded as plugin when
application is about to start, it may slightly affect loading time of the application. You have
an option to tweak the behaviour based on your requirements. By default (`immediateLoading` not set),
keyboard component is loaded when first time requested by application (input field focused). Loading
of keyboard component means loading of all QMLs which defines keyboard UI and all the layouts. So
in this case, when input field is focused for the first time, there may be a short time visible until
keyboard is loaded and displayed.

On the other hand, when `immediateLoading` is set, start time of application may be affected little bit,
but keyboard is then displayed instantly when requested by application, even when it is displaying for
the first time.

### `noContentScrolling`

> **Note:** This has effect only when `ownWindow` is not defined.

When keyboard by its height overlaps focused text input, contentItem of the window is scrolled
so that the text input is still visible. This automatic scrolling can be disabled by setting
`noContentScrolling` into list of additional parameters set to QT_IM_MODULE environment variable.

## Direct usage of Keyboard component in your app window

TODO document + test + add example

# Customizing keyboard style

Style of keyboard is fully customizable, which means that you can provide your own style for every
key type, keyboard background, key and key alternatives preview bubbles and layout (language)
selection menu. You don't have to provide style for all of these mentioned, but if you're interested
in changing style for e.g. enter button only, you just create style for that key type and the default
style will be used for all the rest.

To define new style you just have to add subdirectory `styles` with specific QML files next to keyboard
plugin library as following.

```
    ├─ yourApplication(.exe)
    └─ platforminputcontexts
        ├─ openvirtualkeyboard(.dll|.so)
        └─ styles
            ├─ Background.qml
            ├─ Key.qml
            ├─ EnterKey.qml
            ├─ BackspaceKey.qml
            ├─ ShiftKey.qml
            ├─ SpaceKey.qml
            ├─ HideKey.qml
            ├─ SymbolKey.qml
            ├─ NextPageKey.qml
            ├─ KeyPreview.qml
            ├─ KeyAlternativesPreview.qml
            ├─ LanguageKey.qml
            └─ LanguageMenu.qml
```
Particular style components may be provided with specific parent properties which should be used in
style implementation (text property for plain key style, shift state etc.). See sections below.

> **Example:** for complete example of how to implement own style, you can inspire yourself with
`example/03_custom_style/out/platforminputcontexts/styles`. Keyboard from the example looks
like following.

![Alt text](img/custom-style.png?raw=true)

## Customizing keyboard background

It defines whole background of keyboard panel. Simplest style would be just colored rectangle. But
image may work as well. 

<table>
  <tr>
    <th>Style file name</th>
    <td><code>Background.qml</code></td>
  </tr>
  <tr>
    <th>Available parent properties</th>
    <td><code><i>none</i></code></td>
  </tr>
</table>

```qml
import QtQuick 2.12

Rectangle {
    color: "#cfd2d9"
}
```

## Customizing default key

Defines the style for plain non special key with character (alphabet, number or symbol).

<table>
  <tr>
    <th>Style file name</th>
    <td><code>Key.qml</code></td>
  </tr>
  <tr>
    <th>Available parent properties</th>
    <td><code>parent.active (key pressed and hovered)<br>parent.text</code></td>
  </tr>
</table>

```qml
import QtQuick 2.12

Rectangle {
    color: parent.active ? Qt.lighter( "#343434", 1.2 ) : "#343434"
    anchors.fill: parent

    Text {
        anchors.centerIn: parent
        font.pixelSize: parent.height * 0.4
        color: "white"
        text: parent.parent.text
    }
}
```

## Customizing Enter key

<table>
  <tr>
    <th>Style file name</th>
    <td><code>EnterKey.qml</code></td>
  </tr>
  <tr>
    <th>Available parent properties</th>
    <td><code>parent.active (bool - key pressed and hovered)<br>parent.enterKeyActionEnabled
     (bool, same as parent.enabled)<br>parent.enterKeyAction (int - one of Qt::EnterKeyType enum values)</code></td>
  </tr>
</table>

```qml
import QtQuick 2.12

Rectangle {
    id: key
    color: enabled ? parent.active ? Qt.darker( "#3478f2", 1.1 ) : "#3478f2"
                   : Qt.lighter( "#3478f2", 1.2 )
    anchors.fill: parent

    Text {
        anchors.centerIn: parent
        color: "white"
        font.pixelSize: parent.height * 0.3
        text: {
            if (key.parent.enterKeyAction === Qt.EnterKeySearch)
                return "Search"
            else if (key.parent.enterKeyAction === Qt.EnterKeyDone)
                return "Done"
            else if (key.parent.enterKeyAction === Qt.EnterKeyGo)
                return "Go"
            else if (key.parent.enterKeyAction === Qt.EnterKeySend)
                return "Send"
            else if (key.parent.enterKeyAction === Qt.EnterKeyNext)
                return "->"
            else if (key.parent.enterKeyAction === Qt.EnterKeyPrevious)
                return "<-"
            else
                return "Enter"
        }
    }
}
```

### Enter key actions manipulation

From your application you can provide hint about special Enter key handling by keyboard via
definition of two additional properties (`enterKeyActionEnabled` and `enterKeyAction`) to text
input component. Virtual keyboard will check if these properties are defined on focused text 
input field and uses their values to visualise state of Enter key properly.

Example:
```qml
TextField {
    property bool enterKeyActionEnabled: text.length > 0 // Enter key will be disabled
                                                         // on virtual keyboard and also Enter
                                                         // key style should properly display
                                                         // disabled state

    property int enterKeyAction: Qt.EnterKeySearch // virtual keyboard's Enter key style should
                                                   // display 'Search' text or appropriate icon
}
```

## Customizing Backspace key

<table>
  <tr>
    <th>Style file name</th>
    <td><code>BackspaceKey.qml</code></td>
  </tr>
  <tr>
    <th>Available parent properties</th>
    <td><code>parent.active (bool - key pressed and hovered)</code></td>
  </tr>
</table>

Style for bckspace key should just display backspace icon or backspace text, no more no less.

## Customizing Shift key
## Customizing Space key
## Customizing Hide key
## Customizing Symbol key
## Customizing Next Page key
## Customizing Language key
## Customizing language menu
## Customizing character preview
## Customizing alternative characters preview

# Customizing layouts

TODO describe layout types (alpha, numeric, ..) and explain json structure for each

# Logging

*OpenVirtualKeyboard* plugin uses logging category with name 'openvirtualkeyboard'. By default
logs are disabled. To enable them, just configure logging filter in your appication before you
instantiate *QCoreApplication* class.

```cpp
QLoggingCategory::setFilterRules( "openvirtualkeyboard=true" );

QGuiApplication app( argc, argv );
...
```

# Inspiration

<https://www.kdab.com/qt-input-method-virtual-keyboard/>  
<https://github.com/githubuser0xFFFF/QtFreeVirtualKeyboard>  

# License

Distributed under the MIT License. See *LICENSE* file for more information.
