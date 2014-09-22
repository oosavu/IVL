import QtQuick 2.0
import "../styleTypes"
import CppImport 1.0

StyleRectangle {
    StyleText{
        anchors.fill: parent
        text: if(eventManager.eventListCurrent.length != 0) dict.alarmStrs[eventManager.eventListCurrent[0].id]
        else " "
        wrapMode: Text.WordWrap
        color: if(eventManager.eventListCurrent.length != 0)
               {
                   if(eventManager.eventListCurrent[0].type == EventTypes.Info1) "#FFFFFF"
                   else if(eventManager.eventListCurrent[0].type == EventTypes.Info2) "#FFFFFF"
                   else if(eventManager.eventListCurrent[0].type == EventTypes.Info3) "#FFFFFF"
                   else if(eventManager.eventListCurrent[0].type == EventTypes.Low  ) "#00FF00"
                   else if(eventManager.eventListCurrent[0].type == EventTypes.Mid  ) "#FF9E00"
                   else if(eventManager.eventListCurrent[0].type == EventTypes.High ) "#FF0000"
               }
               else "white"
    }
}
