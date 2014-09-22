import QtQuick 2.0
import "../styleTypes"
StyleRectangle{
    property var param
    property alias text: minmaxText.text

    width: 61
    height: 45
    color: "blue"
    StyleTextS{
        id: minmaxText

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.width/3
    }
    StyleTextL{
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        text: param.value
        height: 2*parent.width/3 - 5
    }
}
