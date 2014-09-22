import QtQuick 2.0
import "styleTypes"
StyleRectangle {
    id: styleRectangle1
    width: 115
    height: 122

    Column{
        anchors.fill: parent

        StyleText{
            id: textTime
            width: parent.width
            height: parent.height/4
            text: Qt.formatDateTime(canManager.systemDateTime,"hh:mm:ss")
        }
        StyleText{
            id: textDate
            width: parent.width
            height: parent.height/4
            text: Qt.formatDateTime(canManager.systemDateTime,"dd/MM/yyyy")
        }
        StyleText{
            id: textAccLevel
            width: parent.width
            height: parent.height/4
            text: "бат: " + canUnitPower.chargeLevel
        }
        StyleText{
            id: textIsCharge
            width: parent.width
            height: parent.height/4
            text: if(canUnitPower.isCharging) "сеть вкл."
                  else "сеть выкл."
        }
    }
}
