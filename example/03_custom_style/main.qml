import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("OpenVirtualKeyboard - custom style")

    ColumnLayout {
        spacing: 20
        width: parent.width * 0.8
        anchors.top: parent.top
        anchors.margins: 20
        anchors.horizontalCenter: parent.horizontalCenter

        Label {
            text: "Tap to enter text with and see keyboard with custom style.<br><br>"
                  + "Styles can be found in ./out/platforminputcontexts/styles"
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
            font.pixelSize: 18
        }
        TextField {
            id: defaultTextField
            Layout.fillWidth: true
        }
    }
}
