import QtQuick 2.0
import "../styleTypes"
StyleRectangle {
    color: "#444444"
    property var measParam
    property var unitStr
    property var nameStr
    width: 148
    height: 73

    StyleTextM{
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        text: nameStr
    }
    StyleTextL{
        anchors.centerIn: parent
        text: measParam.value
    }

    StyleTextS{
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        text: unitStr
    }



}
