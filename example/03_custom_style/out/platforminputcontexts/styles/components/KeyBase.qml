import QtQuick 2.12

Item {
    id: key

    property alias color: keyBg.color

    anchors.fill: parent

    // shadow
    Rectangle {
        radius: keyBg.radius
        color: "#868789"
        height: parent.height - parent.height * 0.14
        width: parent.width - parent.height * 0.14
        anchors {
            centerIn: parent
            verticalCenter: parent.verticalCenter
            verticalCenterOffset: 2
        }
    }

    Rectangle {
        id: keyBg

        radius: height * 0.1
        color: "#fefefe"
        anchors {
            fill: parent
            margins: parent.height * 0.07
        }
    }
}
