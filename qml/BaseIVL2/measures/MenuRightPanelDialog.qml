import QtQuick 2.0
import "../styleTypes"
StyleMenu {
    id: menuRightPanel

    property string currModel: "recomended"
    ListModel{
        id: nodeModel
        ListElement{num: 0  ; description: "CO2 mmHg"     ; displayed: 0; }
        ListElement{num: 1  ; description: "CO2 %"        ; displayed: 0; }
        ListElement{num: 2  ; description: "FiO2"         ; displayed: 0; }
        ListElement{num: 3  ; description: "CR"           ; displayed: 0; }
        ListElement{num: 4  ; description: "PIPPEEP"      ; displayed: 0; }
        ListElement{num: 5  ; description: "MVMVspont"    ; displayed: 0; }
        ListElement{num: 6  ; description: "VexpVinsp"    ; displayed: 0; }
        ListElement{num: 7  ; description: "RBIE"         ; displayed: 0; }
        ListElement{num: 8  ; description: "LEAK"         ; displayed: 0; }
        ListElement{num: 9  ; description: "PPlato"       ; displayed: 0; }
        ListElement{num: 10 ; description: "FlowPEAK"     ; displayed: 0; }
        ListElement{num: 11 ; description: "fspont"       ; displayed: 0; }
        ListElement{num: 12 ; description: "AutoPEEP"     ; displayed: 0; }
        ListElement{num: 13 ; description: "PMean"        ; displayed: 0; }
        ListElement{num: 14 ; description: "MValvVd"      ; displayed: 0; }
        ListElement{num: 15 ; description: "ValvVdVexp"   ; displayed: 0; }
        ListElement{num: -1 ; description: "Empty"        ; displayed: 0; }
    }
    ListModel{
        id: currLiftModel
    }
    function copyModel(from,  to)
    {
        to.clear()
        for(var i = 0; i < from.count; i++ )
        {
            to.append({"paramNum": from.get(i).paramNum})
        }
    }
    function syncNodeModel()
    {
        for(var i = 0; i < nodeModel.count; i++ )
        {
            nodeModel.get(i).displayed = 0
        }
        for(var i = 0; i < currLiftModel.count; i++ )
        {
            if(currLiftModel.get(i).paramNum!= -1) nodeModel.get(currLiftModel.get(i).paramNum).displayed +=1
        }

    }

    Text {
        id: titleText
        height: 31
        color: "#ffffff"
        text: qsTr("Настройка правой панели")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 23
        anchors.topMargin: 3
        anchors.top: parent.top
    }

    Item {
        id: patternItem
        height: 53
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: titleText.bottom
        anchors.margins: 3
        onStateChanged: {
            if(state == "user1")        copyModel(model_user1,currLiftModel)
            else if(state == "user2")   copyModel(model_user2,currLiftModel)
            else if(state == "maximum")   copyModel(model_maximum,currLiftModel)
            else if(state == "recomended")   copyModel(model_CMV_VCV,currLiftModel)
            syncNodeModel()
        }

        state: "recomended"
        states: [
            State{
                name: "recomended"
            },
            State{
                name: "maximum"
            },
            State{
                name: "user1"
            },
            State{
                name: "user2"
            }
        ]

        Row{
            anchors.margins: 3
            anchors.fill: parent
            property int itemWidth: width/4 - 3
            spacing: 3
            StyleButton{
                height: parent.height-1; width: parent.itemWidth; text: "Рекомендуемое"             ;
                onClicked: patternItem.state = "recomended"
                color: if (patternItem.state == "recomended") "green"
                        else "gray"
            }
            StyleButton{
                height: parent.height-1; width: parent.itemWidth; text: "максимальное колличество"  ;
                onClicked: patternItem.state = "maximum"
                color: if (patternItem.state == "maximum") "green"
                        else "gray"
            }
            StyleButton{
                height: parent.height-1; width: parent.itemWidth; text: "пользовательское 1"        ;
                onClicked: patternItem.state = "user1"
                color: if (patternItem.state == "user1") "green"
                        else "gray"
            }
            StyleButton{
                height: parent.height-1; width: parent.itemWidth; text: "пользовательское 2"        ;
                onClicked: patternItem.state = "user2"
                color: if (patternItem.state == "user2") "green"
                        else "gray"
            }
        }
    }

    StyleOkCancelButtons {
        id: styleBut
        anchors.right: parent.right
        anchors.rightMargin: 3
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 3
        onOkClicked: {
            if(patternItem.state == "user1")             copyModel(currLiftModel,model_user1  )
            else if(patternItem.state == "user2")        copyModel(currLiftModel,model_user2  )
            else if(patternItem.state == "maximum")      copyModel(currLiftModel,model_maximum)
            else if(patternItem.state == "recomended")   copyModel(currLiftModel,model_CMV_VCV)
            currModel = patternItem.state
            menuRightPanel.visible = false
        }
        onCancelClicked: {
            menuRightPanel.visible = false
        }
    }

    Item {
        id: lift
        width: 135
        anchors.margins: 3
        anchors.bottom: styleBut.top
        anchors.left: parent.left
        anchors.top: patternItem.bottom
        ListView{
            id: liftView
            anchors.margins: 3
            anchors.bottom: addremoveCells.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            model: currLiftModel




            delegate: StyleButton{
                color: if(index == liftView.currentIndex) "green"
                       else "#CC7E00"
                width: parent.width
                height: liftView.height/currLiftModel.count
                text: if     ( paramNum == 0  ) "EtCO2mmHg"
                      else if( paramNum == 1  ) "EtCO2persent"
                      else if( paramNum == 2  ) "FiO2"
                      else if( paramNum == 3  ) "CR"
                      else if( paramNum == 4  ) "PIPPEEP"
                      else if( paramNum == 5  ) "MVMVspont"
                      else if( paramNum == 6  ) "VexpVinsp"
                      else if( paramNum == 7  ) "RBIE"
                      else if( paramNum == 8  ) "LEAK"
                      else if( paramNum == 9  ) "PPlato"
                      else if( paramNum == 10 ) "FlowPEAK"
                      else if( paramNum == 11 ) "fspont"
                      else if( paramNum == 12 ) "AutoPEEP"
                      else if( paramNum == 13 ) "PMean"
                      else if( paramNum == 14 ) "MValvVd"
                      else if( paramNum == 15 ) "ValvVdVexp"
                      else                      "Empty"
                onClicked:{
                    liftView.currentIndex = index
                    //syncNodeModel()
                    //gvParams.currentIndex = paramNum
                }
            }
        }

        Item {
            id: addremoveCells
            height: 59
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            StyleButton{
                anchors.margins: 3
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.horizontalCenter
                anchors.bottom: parent.bottom
                text: "-"
                active: true
                onClicked: {
                    syncNodeModel()
                    if(liftView.model.count>5) liftView.model.remove(liftView.model.count-1)
                }
            }
            StyleButton{
                anchors.margins: 3
                anchors.top: parent.top
                anchors.left: parent.horizontalCenter
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                text: "+"
                onClicked: {
                    syncNodeModel()
                    if(liftView.model.count<14) liftView.model.append({"paramNum":-1})
                }
            }
        }
    }

    Item {
        id: cellsItem
        x: 202
        y: 83
        width: 490
        height: 430
        anchors.topMargin: 3
        anchors.bottomMargin: 3
        anchors.right:  styleBut.right
        anchors.bottom: styleBut.top
        anchors.leftMargin: 3
        anchors.left: lift.right
        anchors.top: patternItem.bottom

        GridView{
            id: gvParams
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 10
            cellWidth: 130
            cellHeight: 60

            currentIndex: if(liftView.currentIndex!= -1)liftView.model.get(liftView.currentIndex).paramNum
            else -1

            focus: true
            delegate: Component{
                StyleRectangle{
                    width: 120
                    height: 50
                    color:   if(gvParams.currentIndex == index) "green"
                        else if(displayed>=2) "red"
                        else if(displayed==1) "#CC7E00"
                        else                  "gray"
                    StyleText{
                        text: description
                        anchors.centerIn: parent
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            liftView.model.get(liftView.currentIndex).paramNum = num;
                            syncNodeModel()
                        }
                    }
                }

            }
            model: nodeModel
        }
    }
}

