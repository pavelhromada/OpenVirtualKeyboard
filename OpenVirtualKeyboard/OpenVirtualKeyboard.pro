QT          += core gui qml quick gui-private

TARGET      = openvirtualkeyboard
TEMPLATE    = lib
CONFIG      += plugin

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    commonpositioner.cpp \
    injectedkeyboardpositioner.cpp \
    key.cpp \
    keyalternativespreview.cpp \
    keyboardcreator.cpp \
    keyboardlayoutmodel.cpp \
    keyboardlayoutsprovider.cpp \
    keyboardstyle.cpp \
    keyboardwindowpositioner.cpp \
    keypressinterceptor.cpp \
    keypreview.cpp \
    openvirtualkeyboardinputcontext.cpp \
    openvirtualkeyboardplugin.cpp \
    utils.cpp

HEADERS += \
    abstractpositioner.h \
    commonpositioner.h \
    injectedkeyboardpositioner.h \
    key.h \
    keyalternativespreview.h \
    keyboardcreator.h \
    keyboardlayoutmodel.h \
    keyboardlayoutsprovider.h \
    keyboardlayouttype.h \
    keyboardstyle.h \
    keyboardwindowpositioner.h \
    keypressinterceptor.h \
    keypreview.h \
    loggingcategory.h \
    openvirtualkeyboardinputcontext.h \
    openvirtualkeyboardplugin.h \
    utils.h
DISTFILES += OpenVirtualKeyboard.json 

unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
    INSTALLS += target
}

RESOURCES += \
    qml.qrc
