import QtQuick 2.0
import "../styleTypes"
Item{
    anchors.fill: parent

    VentDigitParameterDial{x:249; y:3   ; param: dict.rulesVM[ventModeManager.ventMode][ 5]
        width: 96
        height: 121}
    VentDigitParameterDial{x:349; y:3   ; param: dict.rulesVM[ventModeManager.ventMode][ 6]
        width: 96
        height: 121}
    VentDigitParameterDial{x:449; y:3   ; param: dict.rulesVM[ventModeManager.ventMode][ 7]
        width: 96
        height: 121}
    VentDigitParameterDial{x:249; y:127 ; param: dict.rulesVM[ventModeManager.ventMode][ 8]
        width: 96
        height: 121}
    VentDigitParameterDial{x:349; y:127 ; param: dict.rulesVM[ventModeManager.ventMode][ 9]
        width: 96
        height: 121}
    VentDigitParameterDial{x:449; y:127 ; param: dict.rulesVM[ventModeManager.ventMode][10]
        width: 96
        height: 121}

}
