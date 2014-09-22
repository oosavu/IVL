import QtQuick 2.0
import "../styleTypes"

StyleCentralDialog{

    okActive: ventModeManager.avilableChangeMode && state == "stateParamsVM"
    cancelActive: state == "stateParamsVM"
    visibleOkCancel: state == "stateParamsVM"
    onOkClicked: {
        ventModeManager.acceptModeVent()
        main.state = "graphics"
    }
    onCancelClicked: {
        ventModeManager.stopVent()
        main.state = "graphics"
    }

    StyleButton{text: "РЕЖИМ"    ; onClicked: ventModeCentralItem.state = "stateVM"        ;
        x:5; y:5 ; width: 139; height: 44 }
    StyleButton{text: "Дополнит."; onClicked: ventModeCentralItem.state = "stateParamsMore";
        x:5; y:54; width: 139; height: 44 }
    StyleButton{text: "ПАЦЦИЕНТ" ; onClicked: ventModeCentralItem.state = "statePatient"   ;
        x:5; y:103; width: 139; height: 44 }
    StyleButton{text: "АПНОЭ"    ; onClicked: ventModeCentralItem.state = "stateAPNEA"     ;
        x:5; y:152; width: 139; height: 44 }


    Item{
        visible: false
        anchors.fill: parent
        id: editParamsVM
        DependenceParamsItem{x:5; y:200; width: parent.width - 10; height: 196}
        ParamsItem{}
    }
    Item{
        visible: false
        anchors.fill: parent
        id: editVM
        ChangeVentModeDialog{}

    }
    Item{
        visible: false
        anchors.fill: parent
        id: editPatient
        PatientDialog{}
    }
    Item{
        visible: false
        anchors.fill: parent
        id: editAPNEA
        ApneaDialog{}
    }
    Item{
        visible: false
        anchors.fill: parent
        id: editParamsMore
        ParametersMoreDialog{}

    }

    state: "stateParamsVM"
    states:[
        State {
            name: "stateParamsMore"
            PropertyChanges {
                target: editParamsMore
                visible: true
            }
        },
        State {
            name: "stateParamsVM"
            PropertyChanges {
                target: editParamsVM
                visible: true
            }
        },
        State {
            name: "stateVM"
            PropertyChanges {
                target: editVM
                visible: true
            }
        },
        State {
            name: "statePatient"
            PropertyChanges {
                target: editPatient
                visible: true
            }
        },
        State {
            name: "stateAPNEA"
            PropertyChanges {
                target: editAPNEA
                visible: true
            }
        }
    ]
    onVisibleChanged: state = "stateParamsVM"

}
