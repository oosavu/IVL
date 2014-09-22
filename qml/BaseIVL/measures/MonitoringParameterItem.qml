import QtQuick 2.0
import "../styleTypes"
Item {
    width: 196
    height: 20
    property string nameStr
    property string unitStr
    property var param


    Row{
        anchors.fill: parent
        StyleTextS{
            anchors.top: parent.top
            anchors.bottom: parent.bottom

            text: nameStr + ":"
            width: 90
            horizontalAlignment: Text.AlignRight
        }
        StyleTextM{
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            text: param.value
            width: 40
        }
        StyleTextS{
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            horizontalAlignment: Text.AlignLeft
            font.pointSize:6
            wrapMode: Text.WordWrap

            text: unitStr
            width: 60
        }
    }
}
