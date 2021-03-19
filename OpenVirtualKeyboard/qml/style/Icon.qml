/**
 *  MIT License
 *  Copyright (c) Pavel Hromada
 *  See accompanying LICENSE file
 */

import QtQuick 2.12
import 'icon-names.js' as IconNames

Item {
    id: root

    property string name: ""
    property alias color: glyph.color
    property int size: 24

    width: size
    height: size

    implicitHeight: height
    implicitWidth: width

    FontLoader {
        id: iconsFont
        source: Qt.resolvedUrl( "fontello.ttf" )
    }

    Text {
        id: glyph
        anchors.fill: parent
        font.family: iconsFont.name
        font.weight: Font.Light
        text: IconNames.icons.hasOwnProperty( name ) ? IconNames.icons[ name ] : ""
        font.pixelSize: size
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
}
