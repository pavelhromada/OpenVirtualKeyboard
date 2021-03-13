# OpenVirtualKeyboard

Virtual keyboard for Qt Quick based applications.

... In-process keyboard

* [Features](#features)
* [Integration](#integration)
    * [Basic usage](#basic-usage)
    * [Configuration](#configuration)
* [Customizing keyboard style](#customizing-keyboard-style)
    * [Customizing keyboard background](#customizing-keyboard-background)
    * [Customizing character preview](#customizing-character-preview)
    * [Customizing alternative characters preview](#customizing-alternative-characters-preview)
    * [Customizing default key](#customizing-default-key)
    * [Customizing Enter key](#customizing-enter-key)
    * [Customizing Backspace key](#customizing-backspace-key)
    * [Customizing Shift key](#customizing-shift-key)
    * [Customizing Space key](#customizing-space-key)
    * [Customizing Hide key](#customizing-hide-key)
    * [Customizing Symbol key](#customizing-symbol-key)
    * [Customizing Next Page key](#customizing-next-page-key)
    * [Customizing Language key](#customizing-language-key)
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
    - [ ] fix when contentItem is scrolled and and one clicks on another monitor and then into different TextField of window
    - [ ] fix when focus is in text field and tab is pressed, comntentItem is not scrolled
    - [ ] why keyboard in own window is not animated when first time shown (only on second monitor)
    - [x] injected keyboard: setParentItem( focusedWindow->contentItem() )
- [x] fix when application starts and keyboard is not loaded yet and someone clicks into TextFielkd
- [x] focus item overlap
    - [x] make focused input component visible even if keyboard overlaps it (scroll contentItem)
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
- [ ] optimizations
   - [ ] do not load all 4 layout rows if layout does not specify all rows
   - [ ] adapt height of keyboard based on count of keyboard rows

# Features

* works only with Qt Quick based UIs (not for widget based UIs)
* enter key actions
* shift + shift lock
* input method hints
* customization of style
* customization of layouts
* auto uppedrcase when new sentence starts
* contentItem is scrolled to make focused TextField visible (only for injected keyboard)
* TODO

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

TODO immediateLoading, ownWindow

# Customizing keyboard style

TODO components in 'styles' directory next to plugin or explicitly declared VirtualKeyboard in application and set styles
no need to provide all qml style components, if someone wants to customize just Enter key, thet just add EnterKey.qml into styes directory

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
            └─ LanguageKey.qml
```

## Customizing keyboard background
## Customizing character preview
## Customizing alternative characters preview
## Customizing default key
## Customizing Enter key
## Customizing Backspace key
## Customizing Shift key
## Customizing Space key
## Customizing Hide key
## Customizing Symbol key
## Customizing Next Page key
## Customizing Language key

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
