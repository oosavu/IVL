import QtQuick 2.0
import "../styleTypes"
import CppImport  1.0

Item{
    id: fullItem

    AddiditionalParamsItem{
        id: addiditionalParams
        height: 232+5
        anchors.bottom: parent.bottom
        anchors.right:  parent.right
        anchors.margins: 3
        anchors.bottomMargin: 1
        anchors.left: parent.left
    }

    Item {
        id: buttonsVM
        width: 690
        height: 52
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 3

        Row{
            anchors.fill: parent
            spacing: 3
            property int childrenWidth: width/4 - 2
            StyleButton{
                text: "Режим"
                height: parent.height
                width: parent.childrenWidth
                onClicked: {
                    if (fullItem.state == "dialogParamRegime") fullItem.state = "dialogRegime"
                    else if (fullItem.state == "dialogRegime") fullItem.state = "dialogParamRegime"
                }
            }
            StyleButton{
                height: parent.height
                text: "АПНОЭ"
                width: parent.childrenWidth
                onClicked: {
                    if (fullItem.state == "dialogParamRegime") fullItem.state = "dialogAPNEA"
                    else if  (fullItem.state == "dialogAPNEA") fullItem.state = "dialogParamRegime"
                }
            }
            StyleButton{
                height: parent.height
                text: "ПАЦИЕНТ"
                width: parent.childrenWidth
                onClicked: {
                    if (fullItem.state == "dialogParamRegime") fullItem.state = "dialogPatient"
                    else if  (fullItem.state == "dialogPatient") fullItem.state = "dialogParamRegime"
                }
            }
            StyleButton{
                height: parent.height
                text: "ДОПОЛНИТЕЛЬНО"
                width: parent.childrenWidth
                onClicked: {
                    if (fullItem.state == "dialogParamRegime") fullItem.state = "dialogOther"
                    else if  (fullItem.state == "dialogOther") fullItem.state = "dialogParamRegime"
                }
            }
        }
    }

    DialogRegime{
        id: dialogNewRegime
        anchors.top: buttonsVM.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 10
        visible: parent.state == "dialogRegime"
    }
    DialogAPNEA{
        id: dialogAPNEA
        anchors.top: buttonsVM.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 10
        visible: parent.state == "dialogAPNEA"
    }
    DialogPatient{
        id: dialogPatient
        anchors.top: buttonsVM.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 10
        visible: parent.state == "dialogPatient"
    }
    DialogAdd{
        id: dialogAdd
        anchors.top: buttonsVM.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 10
        visible: parent.state == "dialogOther"
    }
    StyleOkCancelButtons {
        visible: parent.state == "dialogParamRegime"
        id: keysOKCansel
//        x: 202
//        y: 141
//        width: 304
        height: 64
        anchors.bottom: dependParamsItem.top
        anchors.bottomMargin: 13
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        onCancelClicked: {
            ventModeManager.cancelModeVent()
            setParField.state = "hidden"
            ventModeManager.stopVent()
        }
        onOkClicked: {
            ventModeManager.acceptModeVent()
            setParField.state = "hidden"
        }
        okActive: ventModeManager.avilableChangeMode
    }
    Item{
        visible: parent.state == "dialogParamRegime"
        id: dependParamsItem
        height: 150
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: addiditionalParams.top
        anchors.margins: 3
        Row{
            height: parent.height-6
            anchors.centerIn: parent
            spacing: 3
            DependParamCanvas{ param: apTiTc     ; name: "TiTc"    }
            DependParamCanvas{ param: apFlow     ; name: "Flow"    }
            DependParamCanvas{ param: apFlowMax  ; name: "FlowMax" }
            DependParamCanvas{ param: apTexp     ; name: "TExp"    }
            DependParamCanvas{ param: apMV       ; name: "MV"      }
            DependParamCanvas{ param: apTramp    ; name: "Tramp"   }
        }
    }

    StyleText {
        visible: parent.state == "dialogParamRegime"
        id: text1
        x: 3
        y: 58
        width: 702
        height: 61
        text: qsTr("Задание параметров режима " + dict.ventModesStrs[ventModeManager.ventMode])
        font.pixelSize: 25
        anchors.topMargin: 3
        anchors.top: buttonsVM.bottom
    }

    state: "dialogParamRegime"
    //onStateChanged: console.log(state)
    states: [
        State {
            name: "dialogParamRegime"
        },
        State {
            name: "dialogRegime"
        },
        State {
            name: "dialogAPNEA"
        },
        State {
            name: "dialogPatient"
        },
        State {
            name: "dialogOther"
        }
    ]
}
