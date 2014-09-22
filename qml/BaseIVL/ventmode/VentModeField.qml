import QtQuick 2.0
import "../styleTypes"
StyleRectangle{
    StyleTextL{
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        text: dict.ventModesStrs[ventModeManager.ventMode]
    }
    StyleTextS{
        text: "МУЖ"
        anchors.top: parent.verticalCenter
        anchors.left: parent.left
        anchors.right: parent.horizontalCenter
        anchors.bottom: parent.bottom
    }
    StyleTextS{
        text: "70 кг"
        anchors.top: parent.verticalCenter
        anchors.left: parent.horizontalCenter
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }

    MouseArea{
        anchors.fill: parent
        onClicked:{

            if(main.state == "graphics") main.state = "ventDialog"
            else main.state = "graphics"
        }
    }
}
