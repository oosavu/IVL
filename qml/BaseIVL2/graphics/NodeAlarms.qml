import QtQuick 2.0
import "../styleTypes"
import CppImport 1.0
NodeEmpty {
    id: nodeAlarms
    titleText: qsTr("Тревоги")

    frameItem.children: [
        ListView{
            interactive: false
            id: alarmView
            anchors.fill: parent
            anchors.margins: 2
            clip: true
            delegate: Item{
                id: alarmLine
                width: alarmView.width
                height: if(nodeAlarms.height < 400)frameItem.height/6 - 1
                else frameItem.height/12
                Rectangle{
                    radius: 4
                    anchors.fill: parent
                    anchors.margins: 2

                    color:"#333333"/* if(modelData.type == EventTypes.Info1) "#000000"
                      else if(modelData.type == EventTypes.Info2) "#333333"
                      else if(modelData.type == EventTypes.Info3) "#333333"
                      else if(modelData.type == EventTypes.Low  ) "#33FF33"
                      else if(modelData.type == EventTypes.Mid  ) "#FF9E00"
                      else if(modelData.type == EventTypes.High ) "#FF3333"*/



                    StyleText{
                        font.pixelSize: 13
                        wrapMode: Text.WordWrap
                        anchors.fill: parent
//                        anchors.leftMargin: 3
                        color: if(modelData.type == EventTypes.Info1) "#FFFFFF"
                          else if(modelData.type == EventTypes.Info2) "#FFFFFF"
                          else if(modelData.type == EventTypes.Info3) "#FFFFFF"
                          else if(modelData.type == EventTypes.Low  ) "#00FF00"
                          else if(modelData.type == EventTypes.Mid  ) "#FF9E00"
                          else if(modelData.type == EventTypes.High ) "#FF0000"
                        text: dict.alarmStrs[modelData.id]
                    }
                }
            }
            model: eventManager.eventListCurrent
        }
    ]




}
