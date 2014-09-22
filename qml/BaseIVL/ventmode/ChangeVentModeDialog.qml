import QtQuick 2.0
import CppImport 1.0
import "../styleTypes"
StyleCentralDialog{
    x: 3
    y: 3
    width: 442
    height: 392
    //property alias highlightItem: modeChoiseView.currentHelpText
    ListModel {
        id: modesModel
        ListElement {
            enumValue: 0//ventModeManager.CIVL_VENTMODE_CMV_VCV
        }
        ListElement {
            enumValue: 1//ventModeManager.CIVL_VENTMODE_CMV_PCV
        }
        ListElement {
            enumValue: 2//ventModeManager.CIVL_VENTMODE_SIMV_PC
        }
        ListElement {
            enumValue: 3//ventModeManager.CIVL_VENTMODE_SIMV_VC
        }
        ListElement {
            enumValue: 4//ventModeManager.CIVL_VENTMODE_CPAP
        }
        ListElement {
            enumValue: 5//ventModeManager.CIVL_VENTMODE_BISTEP
        }
        ListElement {
            enumValue: 6//ventModeManager.CIVL_VENTMODE_NIV
        }
        ListElement {
            enumValue: 7//ventModeManager.CIVL_VENTMODE_ISV
        }
        ListElement {
            enumValue: 8//ventModeManager.CIVL_VENTMODE_PCV_VG
        }
        ListElement {
            enumValue: 9//ventModeManager.CIVL_VENTMODE_SIMV_DC
        }
    }

    ListView{
        interactive: false
        //property string currentHelpText: model.get(currentIndex).description
//        onCurrentIndexChanged: {
//            ventModeManager.ventMode = model.get(currentIndex).enumValue
//        }

        id: modeChoiseView

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height - 50
        focus: true


        delegate: Component{
            Item{
                width: modeChoiseView.width
                height: modeChoiseView.height/12
                StyleRectangle{
                    color: if(modeChoiseView.currentIndex == index) "#444444"
                            else "black"
                    anchors.fill: parent
                    StyleTextM{
                        text: dict.ventModesStrs[enumValue]
                        anchors.centerIn: parent
                    }
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked:{
                        modeChoiseView.currentIndex = index
                    }
                }
            }
        }
        model: modesModel
    }


    onOkClicked:{
        ventModeManager.ventMode = modeChoiseView.model.get(modeChoiseView.currentIndex).enumValue
        ventModeCentralItem.state = "stateParamsVM"
    }
    onCancelClicked:{ ventModeCentralItem.state = "stateParamsVM" }

}
