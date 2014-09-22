import QtQuick 2.0
import "../styleTypes"

StyleCentralDialog{
    EditMinMaxElField{
        x:5
        y:5
        width: 91
        minEL: elMVmin
        maxEL: elMVmax
        param: currMV
        unit: "л/мин"
        titletext: "MV"
    }
    EditMinMaxElField{
        x:100
        y:5
        minEL: elVExpMin
        maxEL: elVExpMax
        param: currVexp
        unit: "мл"
        titletext: "MV"
    }
    EditMinMaxElField{
        x:200
        y:5
        minEL: elRBmin
        maxEL: elRBmax
        param: currRB
        unit: "1/sec"
        titletext: "RB"
    }
    EditMinMaxElField{
        x:300
        y:5
        minEL: elEtCO2minP
        maxEL: elEtCO2maxP
        param: currEtCO2p
        unit: "mmHg"
        titletext: "EtCO2"
    }
    EditMinMaxElField{
        x:300
        y:205
        width: 91
        minEL: elEtCO2minPersent
        maxEL: elEtCO2maxPersent
        param: currEtCO2p
        unit: "%"
        titletext: "EtCO2%"
    }
    EditMinMaxElField{
        x:5
        y:205
        width: 91
        minEL: elSpO2min
        maxEL: elSpO2max
        param: currO2
        unit: "%"
        titletext: "SpO2"
    }
    EditMinMaxElField{
        x:100
        y:205
        minEL: elPRmin
        maxEL: elPRmax
        param: elPRmax
        unit: "1/min"
        titletext: "PR"
    }
    EditFiO2Field{
        x:200
        y:205
    }



}
