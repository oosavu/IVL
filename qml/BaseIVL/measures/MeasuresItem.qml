import QtQuick 2.0
import "../styleTypes"

Item{
    property var paramsDict:[
               mpf_EtCO2mmHg    ,
               mpf_EtCO2persent ,
               mpf_FiO2         ,
               mpf_CR           ,
               mpf_PIPPEEP      ,
               mpf_MVMVspont    ,
               mpf_VexpVinsp    ,
               mpf_RBIE         ,
               mpf_LEAK         ,
               mpf_PPlato       ,
               mpf_FlowPEAK     ,
               mpf_fspont       ,
               mpf_AutoPEEP     ,
               mpf_PMean        ,
               mpf_MValvVd      ,
               mpf_ValvVdVexp   ,
               mpf_Empty
    ]
    property var map:[
                0,
                1,
                2,
                3,
                4,
    ]
    function synchronizeMap()
    {
        for(var i = 0; i < map.length; i++)
        {
            mpColumn.children[i].sourceComponent = paramsDict[map[i]]
        }
    }
    Component.onCompleted: synchronizeMap()



    Column{
        id: mpColumn
        spacing: 2
        x:1
        y:1
        width: 148
        MeasureParameterLoader{id: mpl0; position: 0; }
        MeasureParameterLoader{id: mpl1; position: 1; }
        MeasureParameterLoader{id: mpl2; position: 2; }
        MeasureParameterLoader{id: mpl3; position: 3; }
        MeasureParameterLoader{id: mpl4; position: 4; }
    }


    Component{
        id: mpf_EtCO2mmHg
        MeasureParameterField{
            measParam:currEtCO2p
            unitStr: "mmHg"
            nameStr: "EtCO2"
        }
    }

    Component{
        id: mpf_EtCO2persent
        MeasureParameterField{
            measParam:currEtCO2persent
            unitStr: "%"
            nameStr: "EtCO2/VCO2"
        }
    }

    Component{
        id: mpf_FiO2
        MeasureParameterField{
            measParam:currO2
            unitStr: "%"
            nameStr: "FiO2"
        }
    }

    Component{
        id: mpf_CR
        MeasureParameterField{
            measParam:currComplains
            unitStr: "popugais"
            nameStr: "C/R"
        }
    }

    Component{
        id: mpf_PIPPEEP
        MeasureParameterField{
            measParam:currPEEP
            unitStr: "cmH2O"
            nameStr: "PEEP"
        }
    }

    Component{
        id: mpf_MVMVspont
        MeasureParameterField{
            measParam:currMV
            unitStr: "L/min"
            nameStr: "MV"
        }
    }

    Component{
        id: mpf_VexpVinsp
        MeasureParameterField{
            measParam:currVexp
            unitStr: "mL"
            nameStr: "VExp"
        }
    }

    Component{
        id: mpf_RBIE
        MeasureParameterField{
            measParam:currRB
            unitStr: "1/min"
            nameStr: "RB"
        }
    }

    Component{
        id: mpf_LEAK
        MeasureParameterField{
            measParam:currLEAK
            unitStr: "L/min"
            nameStr: "LEAK"
        }
    }

    Component{
        id: mpf_PPlato
        MeasureParameterField{
            measParam:currPPlato
            unitStr: "cmH2O"
            nameStr: "PPlato"
        }
    }

    Component{
        id: mpf_FlowPEAK
        MeasureParameterField{
            measParam:currFlowPeak
            unitStr: "L/min"
            nameStr: "FLowPeak"
        }
    }

    Component{
        id: mpf_fspont
        MeasureParameterField{
            measParam:currFSpont
            unitStr: "1/min"
            nameStr: "FSpont"
        }
    }

    Component{
        id: mpf_AutoPEEP
        MeasureParameterField{
            measParam:currAutoPEEP
            unitStr: "cmH2O"
            nameStr: "AutoPEEP"
        }
    }

    Component{
        id: mpf_PMean
        MeasureParameterField{
            measParam:currPmean
            unitStr: "cmH2O"
            nameStr: "Pmean"
        }
    }

    Component{
        id: mpf_MValvVd
        MeasureParameterField{
            measParam:currMValv
            unitStr: "L/min"
            nameStr: "MValv"
        }
    }

    Component{
        id: mpf_ValvVdVexp
        MeasureParameterField{
            measParam:currVd
            unitStr: "mL"
            nameStr: "Valv/VdVexp"
        }
    }
    Component{
        id: mpf_Empty
        StyleRectangle {
            width: 123
            height: 98
        }
    }


}

