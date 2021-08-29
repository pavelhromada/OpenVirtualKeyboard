project(OpenVirtualKeyboardProj)
cmake_minimum_required(VERSION 3.20)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CXX_STANDARD 17)

option(USE_QTQUICKCOMPILED_RESOURCES OFF)

if(${USE_QTQUICKCOMPILED_RESOURCES})
    find_package(Qt5QuickCompiler)
    set(PROJECT_ADD_RESOURCES qtquick_compiler_add_resources)
else()
    set(PROJECT_ADD_RESOURCES qt5_add_resources)
endif()

find_package(Qt5 COMPONENTS Quick Core Gui REQUIRED)

cmake_language(CALL ${PROJECT_ADD_RESOURCES} KEYBOARD_LIBRARY_RESOURCES ${CMAKE_CURRENT_LIST_DIR}/OpenVirtualKeyboard/qml.qrc)


add_library(OpenVirtualKeyboard SHARED
    ${CMAKE_CURRENT_LIST_DIR}/OpenVirtualKeyboard/commonpositioner.cpp
    ${CMAKE_CURRENT_LIST_DIR}/OpenVirtualKeyboard/injectedkeyboardpositioner.cpp
    ${CMAKE_CURRENT_LIST_DIR}/OpenVirtualKeyboard/key.cpp
    ${CMAKE_CURRENT_LIST_DIR}/OpenVirtualKeyboard/keyalternativespreview.cpp
    ${CMAKE_CURRENT_LIST_DIR}/OpenVirtualKeyboard/keyboardcreator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/OpenVirtualKeyboard/keyboardlayoutmodel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/OpenVirtualKeyboard/keyboardlayoutsprovider.cpp
    ${CMAKE_CURRENT_LIST_DIR}/OpenVirtualKeyboard/keyboardstyle.cpp
    ${CMAKE_CURRENT_LIST_DIR}/OpenVirtualKeyboard/keyboardwindowpositioner.cpp
    ${CMAKE_CURRENT_LIST_DIR}/OpenVirtualKeyboard/keypressinterceptor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/OpenVirtualKeyboard/keypreview.cpp
    ${CMAKE_CURRENT_LIST_DIR}/OpenVirtualKeyboard/openvirtualkeyboardinputcontext.cpp
    ${CMAKE_CURRENT_LIST_DIR}/OpenVirtualKeyboard/openvirtualkeyboardplugin.cpp
    ${CMAKE_CURRENT_LIST_DIR}/OpenVirtualKeyboard/utils.cpp

    ${CMAKE_CURRENT_LIST_DIR}/OpenVirtualKeyboard/abstractpositioner.h
    ${CMAKE_CURRENT_LIST_DIR}/OpenVirtualKeyboard/commonpositioner.h
    ${CMAKE_CURRENT_LIST_DIR}/OpenVirtualKeyboard/injectedkeyboardpositioner.h
    ${CMAKE_CURRENT_LIST_DIR}/OpenVirtualKeyboard/key.h
    ${CMAKE_CURRENT_LIST_DIR}/OpenVirtualKeyboard/keyalternativespreview.h
    ${CMAKE_CURRENT_LIST_DIR}/OpenVirtualKeyboard/keyboardcreator.h
    ${CMAKE_CURRENT_LIST_DIR}/OpenVirtualKeyboard/keyboardlayoutmodel.h
    ${CMAKE_CURRENT_LIST_DIR}/OpenVirtualKeyboard/keyboardlayoutsprovider.h
    ${CMAKE_CURRENT_LIST_DIR}/OpenVirtualKeyboard/keyboardlayouttype.h
    ${CMAKE_CURRENT_LIST_DIR}/OpenVirtualKeyboard/keyboardstyle.h
    ${CMAKE_CURRENT_LIST_DIR}/OpenVirtualKeyboard/keyboardwindowpositioner.h
    ${CMAKE_CURRENT_LIST_DIR}/OpenVirtualKeyboard/keypressinterceptor.h
    ${CMAKE_CURRENT_LIST_DIR}/OpenVirtualKeyboard/keypreview.h
    ${CMAKE_CURRENT_LIST_DIR}/OpenVirtualKeyboard/loggingcategory.h
    ${CMAKE_CURRENT_LIST_DIR}/OpenVirtualKeyboard/openvirtualkeyboardinputcontext.h
    ${CMAKE_CURRENT_LIST_DIR}/OpenVirtualKeyboard/openvirtualkeyboardplugin.h
    ${CMAKE_CURRENT_LIST_DIR}/OpenVirtualKeyboard/utils.h

    ${KEYBOARD_LIBRARY_RESOURCES}
)

target_include_directories(
    OpenVirtualKeyboard
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/OpenVirtualKeyboard
    ${Qt5Gui_PRIVATE_INCLUDE_DIRS}
    ${Qt5Quick_PRIVATE_INCLUDE_DIRS}
)
set_target_properties(OpenVirtualKeyboard
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/platforminputcontexts
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/platforminputcontexts
)

target_link_libraries(OpenVirtualKeyboard PRIVATE Qt5::Core Qt5::Quick Qt5::Gui)
