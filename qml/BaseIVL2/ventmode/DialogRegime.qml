import QtQuick 2.0
import "../styleTypes"

StyleRectangle {
    StyleText{
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 61
        text: "Выберете новый режим вентиляции:"
        font.pixelSize: 25
        id: titleRegime
    }

    Component.onCompleted: {
        syncOptionRegime(5 ,optBiSTEP.trueValue)
        syncOptionRegime(6 ,optNIV.trueValue)
        syncOptionRegime(7 ,optAPRV.trueValue)
        syncOptionRegime(8 ,optPCV_VG.trueValue)
        syncOptionRegime(9 ,optSIMV_DC.trueValue)
        syncOptionRegime(10,optISV.trueValue)
    }

    Connections{
        target: optBiSTEP
        onTrueValueChanged:{
            syncOptionRegime(5,optBiSTEP.trueValue)
        }
    }
    Connections{
        target: optNIV
        onTrueValueChanged:{
            syncOptionRegime(6,optNIV.trueValue)
        }
    }
    Connections{
        target: optAPRV
        onTrueValueChanged:{
            syncOptionRegime(7,optAPRV.trueValue)
        }
    }
    Connections{
        target: optPCV_VG
        onTrueValueChanged:{
            syncOptionRegime(8,optPCV_VG.trueValue)
        }
    }
    Connections{
        target: optSIMV_DC
        onTrueValueChanged:{
            syncOptionRegime(9,optSIMV_DC.trueValue)
        }
    }
    Connections{
        target: optISV
        onTrueValueChanged:{
            syncOptionRegime(10,optISV.trueValue)
        }
    }

    function syncOptionRegime(enumVal, optionIsOn)
    {
        if(optionIsOn)
        {
            for(var i = 0; i < modesModel.count; i++)
            {
                if(modesModel.get(i).enumValue == enumVal) return
            }
            for(var i = 0; i < modesModel.count; i++)
            {
                if(modesModel.get(i).enumValue == enumVal-1)
                {
                    modesModel.insert(i,{ "enumValue": enumVal })
                    return
                }
            }
        }
        else{
            for(var i = 0; i < modesModel.count; i++)
            {
                if(modesModel.get(i).enumValue == enumVal)
                    modesModel.remove(i)
            }
        }
    }

    ListModel {
        id: modesModel
        ListElement {
            enumValue: 0  //ventModeManager.CIVL_VENTMODE_CMV_VCV
        }
        ListElement {
            enumValue: 1  //ventModeManager.CIVL_VENTMODE_CMV_PCV
        }
        ListElement {
            enumValue: 2  //ventModeManager.CIVL_VENTMODE_SIMV_PC
        }
        ListElement {
            enumValue: 3  //ventModeManager.CIVL_VENTMODE_SIMV_VC
        }
        ListElement {
            enumValue: 4  //ventModeManager.CIVL_VENTMODE_CPAP
        }
        ListElement {
            enumValue: 5  //ventModeManager.CIVL_VENTMODE_BISTEP
        }
        ListElement {
            enumValue: 6  //ventModeManager.CIVL_VENTMODE_NIV
        }
        ListElement {
            enumValue: 7  //ventModeManager.CIVL_VENTMODE_APRV
        }
        ListElement {
            enumValue: 8  //ventModeManager.CIVL_VENTMODE_PCV_VG
        }
        ListElement {
            enumValue: 9  //ventModeManager.CIVL_VENTMODE_SIMV_DC
        }
        ListElement {
            enumValue: 10 //ventModeManager.CIVL_VENTMODE_ISV
        }
    }

    GridView{
        interactive: false
        id: modeChoiseView
        anchors.top: titleRegime.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: dialogKeysOKCansel.top
        anchors.margins: 20
        cellHeight: width/6
        cellWidth: width/6

        delegate: Component{
            Item{
                width: modeChoiseView.width/7
                height: modeChoiseView.width/7
                StyleRectangle{
                    color: if(modeChoiseView.currentIndex == index) "green"
                           else if (ventModeManager.ventMode == index) "lightgreen"
                           else "gray"
                    anchors.fill: parent
                    StyleText{
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

    StyleOkCancelButtons {
        id: dialogKeysOKCansel
        width: 304
        height: 70

        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: 3
        onOkClicked: {
            ventModeManager.ventMode = modeChoiseView.model.get(modeChoiseView.currentIndex).enumValue
            fullItem.state = "dialogParamRegime"
        }
        onCancelClicked:
        {
            //optNIV.trueValue = !optNIV.trueValue
            //modesModel.remove(3)
            //fullItem.state = "dialogParamRegime"
        }
        okActive: modeChoiseView.currentIndex != ventModeManager.ventMode
    }

    onVisibleChanged: {

        if(visible == true) modeChoiseView.currentIndex = ventModeManager.ventMode
    }


}
