import QtQuick 2.0
import CppImport 1.0
import "../styleTypes"

StyleMenu {
    id: menuService
    StyleText {
        id: titleText
        text: qsTr("Сервисное меню")
        anchors.right: parent.right
        anchors.rightMargin: 1
        font.pixelSize: 25
        anchors.topMargin: 1
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.leftMargin: 1
    }
    ItemOptions{
        id: iOpt
        anchors.top: titleText.bottom
        anchors.bottom: styleBut.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 20
    }
    StyleOkCancelButtons {
        id: styleBut
        anchors.right: parent.right
        anchors.rightMargin: 3
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 3
        onOkClicked: {
            iOpt.acceptChanges()
            menuService.visible = false
        }
        onCancelClicked: {
            iOpt.restoreChanges()
            menuService.visible = false
        }
    }
}
