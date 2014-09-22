import QtQuick 2.0
import "../styleTypes"
NodeEmpty {
    id: nodeMonit
    titleText: qsTr("Мониторинг")


    ListModel{
        id: monitModel1
        ListElement{monParam:  0 ; name:   "PEEPtot"   ; unit:    "cmH2O"  }
        ListElement{monParam:  1 ; name:   "AutoPEEP"  ; unit:    "cmH2O"  }
        ListElement{monParam:  2 ; name:   "ExpEndFlow"; unit:    "L/min"  }
        ListElement{monParam:  3 ; name:   "RCExp"     ; unit:    "sec"    }
        ListElement{monParam:  4 ; name:   "RCInsp"    ; unit:    "sec"    }
        ListElement{monParam:  5 ; name:   "SI"        ; unit:    ""       }
        ListElement{monParam:  6 ; name:   "WVent"     ; unit:    "Дж/л"   }
        ListElement{monParam:  7 ; name:   "WSpont"    ; unit:    "Дж/л"   }
    }

    ListModel{
        id: monitModel2
        ListElement{monParam:  8 ; name: "Ti"     ; unit:  "sec"           }
        ListElement{monParam:  9 ; name: "TiTtot" ; unit:  ""              }
        ListElement{monParam: 10 ; name: "MVspMV" ; unit:  ""              }
        ListElement{monParam: 11 ; name: "RExp"   ; unit:  "cmH2O/(1/sec)" }
        ListElement{monParam: 12 ; name: "E"      ; unit:  ""              }
        ListElement{monParam: 13 ; name: "RCirc"  ; unit:  "cmH2O/(1/sec)" }
        ListElement{monParam: 14 ; name: "CCirc"  ; unit:  "ml/cmH2O"      }
        ListElement{monParam: 15 ; name: "CDyn"   ; unit:  "Дж/л"          }
    }

    frameItem.children: [
        ListView{
            clip: true
            interactive: false
            id: monitView
            anchors.fill: parent
            anchors.margins: 2
            delegate: Component{
                    id: monitLine
                    Rectangle{
                        color: if(index%2 == 0) "#008800"
                            else "#000088"
                        width: monitView.width
                        height: frameItem.height/8 - 1
                        Item{
                            id: valItem
                            anchors.left: parent.left
                            anchors.top: parent.top
                            anchors.bottom: parent.bottom
                            width: parent.width/3
                            Text{
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignLeft
                                anchors.centerIn: parent
                                color: "white"
                                text: parList[monParam].value
                                font.pixelSize: 25
                            }
                        }
                        Item{
                            anchors.right: parent.right
                            anchors.top: parent.top
                            anchors.bottom: parent.bottom
                            anchors.left:valItem.right
                            Text{
                                anchors.rightMargin: 3
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignRight
                                color: "white"
                                anchors.top: parent.top
                                anchors.left: parent.left
                                anchors.bottom: parent.verticalCenter
                                anchors.right: parent.right
                                text: name
                                font.pixelSize: 14
                            }
                            Text{
                                anchors.rightMargin: 3
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignRight
                                color: "white"
                                anchors.top: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.bottom: parent.bottom
                                anchors.right: parent.right
                                text: unit
                                font.pixelSize: 13
                            }
                        }

                    }
                }
            model: monitModel1
        }
    ]


    property var parList:
    {
         0:currPEEPtot,
         1:currAutoPEEP,
         2:currExpEndFlow,
         3:currRCExp,
         4:currRCInsp,
         5:currSI,
         6:currWVent,
         7:currWSpont,
         8:currTi,
         9:currTi_Ttot,
        10:currMVsp_MV,
        11:currRExp,
        12:currElastence,
        13:currRCirc,
        14:currCCirc,
        15:currCDyn,
    }


}
