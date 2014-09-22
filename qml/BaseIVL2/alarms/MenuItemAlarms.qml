import QtQuick 2.0
import "../styleTypes"
import CppImport 1.0
StyleMenu {
    id: menuAlarms
    StyleText {
        id: titleText
        text: qsTr("Журнал событий")
        anchors.right: parent.right
        anchors.rightMargin: 1
        font.pixelSize: 25
        anchors.topMargin: 1
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.leftMargin: 1
    }

    Item{
        id: eventListChoiseItem
        height: 53
        width: parent.width*2/3
        anchors.horizontalCenter: parent.horizontalCenter

        anchors.top: titleText.bottom
        state: "current"
        states:[
            State{
                name: "current"
            },
            State{
                name: "unwatched"
            },
            State{
                name: "all"
            }
        ]
        Row{
            anchors.margins: 3
            anchors.fill: parent
            property int itemWidth: width/3 - 3
            spacing: 3
            StyleButton{
                height: parent.height-1; width: parent.itemWidth; text: "Текущие" + " (" + eventManager.eventListCurrent.length + ")"    ;
                onClicked: eventListChoiseItem.state = "current"
                color: if (eventListChoiseItem.state == "current") mainItem.buttonColor
                        else  mainItem.okColor
            }
            StyleButton{
                height: parent.height-1; width: parent.itemWidth; text: "Отложенные" + " (" + eventManager.eventListUnwatched.length + ")"  ;
                onClicked: eventListChoiseItem.state = "unwatched"
                color: if (eventListChoiseItem.state == "unwatched")  mainItem.buttonColor
                       else  mainItem.okColor
            }
            StyleButton{
                height: parent.height-1; width: parent.itemWidth; text: "Журнал" + " (" + eventManager.eventListAll.length + ")"      ;
                onClicked: eventListChoiseItem.state = "all"
                color: if (eventListChoiseItem.state == "all")  mainItem.buttonColor
                       else  mainItem.okColor
            }
        }
    }

    StyleRectangle{
        anchors.top: eventListChoiseItem.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: botButtons.top
        anchors.margins: 5


        ListView{
            clip: true
            //contentHeight: parent.height - 80
            //interactive: false
            id: eventView
            anchors.fill: parent
            anchors.margins: 3

            property int dispIndex
            onModelChanged: dispIndex = 0
            onDispIndexChanged: eventView.positionViewAtIndex( dispIndex, ListView.Beginning )

            model: if(eventListChoiseItem.state == "current"  ) eventManager.eventListCurrent
              else if(eventListChoiseItem.state == "unwatched") eventManager.eventListUnwatched
              else eventManager.eventListAll

            delegate: Item{
                width: eventView.width
                height: 43
                Rectangle{
                    radius: 4
                    anchors.fill: parent
                    anchors.margins: 2
                    color: if(modelData.type == EventTypes.Info1) "#333333"
                      else if(modelData.type == EventTypes.Info2) "#333333"
                      else if(modelData.type == EventTypes.Info3) "#333333"
                      else if(modelData.type == EventTypes.Low  ) "#33FF33"
                      else if(modelData.type == EventTypes.Mid  ) "#FF9E00"
                      else if(modelData.type == EventTypes.High ) "#FF3333"
                    StyleText{
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.left: parent.left
                        width: parent.width/6
                        id: startDTtext
                        text: Qt.formatDateTime(modelData.startDT," hh:mm:ss")
                    }
                    StyleText{
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.left: startDTtext.right
                        width: parent.width/6
                        id: endDTtext
                        text: if(!modelData.isOpened && modelData.type != EventTypes.Info2)Qt.formatDateTime(modelData.endDT,"hh:mm:ss")
                        else "--:--:--"
                    }

                    StyleText{
                        wrapMode: Text.WordWrap
                        //font.pixelSize: 8
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.left: endDTtext.right
                        anchors.right: parent.right
                        text: dict.alarmStrs[modelData.id] + " (" + modelData.id + ")"
                    }
                }
            }
        }
    }

    Item{
        id: botButtons
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.margins: 3
        height: 50

        StyleButton {
            id: butWatch
            text: "отчитстить список"
            visible: eventListChoiseItem.state == "unwatched"

            anchors.left: parent.left
            anchors.bottom: parent.bottom
            onClicked: {
                eventManager.watchAllAlarms()
            }
        }
        StyleButton {
            id: butAdd
            text: "add random"
            anchors.right: butScrollDown.left
            anchors.bottom: parent.bottom
                onClicked: {
                    eventManager.openEvent(Math.floor(Math.random() * EventIDs.AlarmBatteryFail ));
            }
        }

        StyleButton {
            id: butScrollDown
            text: "<<"
            anchors.right: parent.horizontalCenter
            anchors.bottom: parent.bottom
                onClicked: {
                    if(eventView.dispIndex > 0) eventView.dispIndex--
            }
        }
        StyleButton {
            id: butScrollUp
            text: ">>"
            anchors.left: parent.horizontalCenter
            anchors.bottom: parent.bottom
                onClicked: {
                    if(eventView.dispIndex < eventView.count - 10) eventView.dispIndex++

            }
        }

        StyleButton {
            id: butOK
            text: "OK"
            anchors.right: parent.right
            anchors.bottom: parent.bottom
                onClicked: {
                menuAlarms.visible = false
            }
        }

    }



}
