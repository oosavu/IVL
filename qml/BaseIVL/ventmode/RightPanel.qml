import QtQuick 2.0
import "../styleTypes"

Item{

//    MouseArea{
//        anchors.fill: parent
//        onClicked: {
//            if(main.state == "graphics"){
//                main.state = "ventDialog"}
//        }
//    }
    property bool anyParamFocused: true/*(vdpd0.focus == true) ||
                                  (vdpd1.focus == true) ||
                                  (vdpd2.focus == true) ||
                                  (vdpd3.focus == true)*/
    onAnyParamFocusedChanged: console.log(anyParamFocused)

    VentDigitParameterDial{id: vdpd0;x:1; y:  1; param: dict.rulesVM[ventModeManager.ventMode][0]}
    VentDigitParameterDial{id: vdpd1;x:1; y:126; param: dict.rulesVM[ventModeManager.ventMode][1]}
    VentDigitParameterDial{id: vdpd2;x:1; y:251; param: dict.rulesVM[ventModeManager.ventMode][2]}
    VentDigitParameterDial{id: vdpd3;x:1; y:376; param: dict.rulesVM[ventModeManager.ventMode][3]}

}
