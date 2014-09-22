import QtQuick 2.0
import "../styleTypes"

StyleRectangle{

    clip: true
    property int count: 12

    ListView{
        spacing: 0
        anchors.margins: 0
        anchors.fill: parent
        id: rightPanel
        delegate: Item{
            Loader{
                anchors.fill: parent
                sourceComponent: if( paramNum == 0  ) mpf_EtCO2mmHg
                            else if( paramNum == 1  ) mpf_EtCO2persent
                            else if( paramNum == 2  ) mpf_FiO2
                            else if( paramNum == 3  ) mpf_CR
                            else if( paramNum == 4  ) mpf_PIPPEEP
                            else if( paramNum == 5  ) mpf_MVMVspont
                            else if( paramNum == 6  ) mpf_VexpVinsp
                            else if( paramNum == 7  ) mpf_RBIE
                            else if( paramNum == 8  ) mpf_LEAK
                            else if( paramNum == 9  ) mpf_PPlato
                            else if( paramNum == 10 ) mpf_FlowPEAK
                            else if( paramNum == 11 ) mpf_fspont
                            else if( paramNum == 12 ) mpf_AutoPEEP
                            else if( paramNum == 13 ) mpf_PMean
                            else if( paramNum == 14 ) mpf_MValvVd
                            else if( paramNum == 15 ) mpf_ValvVdVexp
                            else  mpf_Empty
            }
            width: rightPanel.width
            height: (rightPanel.height)/(rightPanel.model.count)
        }
        model: if(miRightPanelDialog.currModel == "recomended")model_CMV_VCV
          else if(miRightPanelDialog.currModel == "user1")model_user1
          else if(miRightPanelDialog.currModel == "user2")model_user2
          else if(miRightPanelDialog.currModel == "maximum")model_maximum
    }

        Component{
            id: mpf_EtCO2mmHg
            MPOldItem{
                mp1:currEtCO2_mm
                unit1: "mmHg"
                name1: "EtCO2"
                el1min: elEtCO2mmMin
                el1max: elEtCO2mmMax
            }
        }

        Component{
            id: mpf_EtCO2persent
            MPOldItem{
                mp1:currEtCO2_pr
                unit1: "%"
                name1: "EtCO2"
                el1min: elEtCO2prMin
                el1max: elEtCO2prMax
                //TODO здесь еще VCO2
            }
        }

        Component{
            id: mpf_FiO2

//            MPOldItem{
//                mp1:currO2
//                unit1: "%"
//                name1: "FiO2"
//                el1min: elEtCO2prMin
//                el1max: elEtCO2prMax
//                //TODO здесь еще VO2
//            }

            MeasureParameterField{


                measParam:currO2
                unitStr: "%"
                nameStr: "FiO2"
            }
        }

        Component{
            id: mpf_CR
            MeasureParameterField{
                measParam:currC_stat
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
                measParam:currVE
                unitStr: "L/min"
                nameStr: "MV"
            }
        }

        Component{
            id: mpf_VexpVinsp
            MeasureParameterField{
                measParam:currVE
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
                measParam:currPplato
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
                measParam:currFlowPeak// TODO currFSpont
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




//    Component{
//        id: mpf_EtCO2mmHg
//        MeasureParameterField{
//            measParam:currEtCO2_mm
//            unitStr: "mmHg"
//            nameStr: "EtCO2"
//        }
//    }

//    Component{
//        id: mpf_EtCO2persent
//        MeasureParameterField{
//            measParam:currEtCO2_pr
//            unitStr: "%"
//            nameStr: "EtCO2/VCO2"
//        }
//    }

//    Component{
//        id: mpf_FiO2
//        MeasureParameterField{
//            measParam:currO2
//            unitStr: "%"
//            nameStr: "FiO2"
//        }
//    }

//    Component{
//        id: mpf_CR
//        MeasureParameterField{
//            measParam:currC_stat
//            unitStr: "popugais"
//            nameStr: "C/R"
//        }
//    }

//    Component{
//        id: mpf_PIPPEEP
//        MeasureParameterField{
//            measParam:currPEEP
//            unitStr: "cmH2O"
//            nameStr: "PEEP"
//        }
//    }

//    Component{
//        id: mpf_MVMVspont
//        MeasureParameterField{
//            measParam:currVE
//            unitStr: "L/min"
//            nameStr: "MV"
//        }
//    }

//    Component{
//        id: mpf_VexpVinsp
//        MeasureParameterField{
//            measParam:currVE
//            unitStr: "mL"
//            nameStr: "VExp"
//        }
//    }

//    Component{
//        id: mpf_RBIE
//        MeasureParameterField{
//            measParam:currRB
//            unitStr: "1/min"
//            nameStr: "RB"
//        }
//    }

//    Component{
//        id: mpf_LEAK
//        MeasureParameterField{
//            measParam:currLEAK
//            unitStr: "L/min"
//            nameStr: "LEAK"
//        }
//    }

//    Component{
//        id: mpf_PPlato
//        MeasureParameterField{
//            measParam:currPplato
//            unitStr: "cmH2O"
//            nameStr: "PPlato"
//        }
//    }

//    Component{
//        id: mpf_FlowPEAK
//        MeasureParameterField{
//            measParam:currFlowPeak
//            unitStr: "L/min"
//            nameStr: "FLowPeak"
//        }
//    }

//    Component{
//        id: mpf_fspont
//        MeasureParameterField{
//            measParam:currFlowPeak// TODO currFSpont
//            unitStr: "1/min"
//            nameStr: "FSpont"
//        }
//    }

//    Component{
//        id: mpf_AutoPEEP
//        MeasureParameterField{
//            measParam:currAutoPEEP
//            unitStr: "cmH2O"
//            nameStr: "AutoPEEP"
//        }
//    }

//    Component{
//        id: mpf_PMean
//        MeasureParameterField{
//            measParam:currPmean
//            unitStr: "cmH2O"
//            nameStr: "Pmean"
//        }
//    }

//    Component{
//        id: mpf_MValvVd
//        MeasureParameterField{
//            measParam:currMValv
//            unitStr: "L/min"
//            nameStr: "MValv"
//        }
//    }

//    Component{
//        id: mpf_ValvVdVexp
//        MeasureParameterField{
//            measParam:currVd
//            unitStr: "mL"
//            nameStr: "Valv/VdVexp"
//        }
//    }
//    Component{
//        id: mpf_Empty
//        StyleRectangle {
//            width: 123
//            height: 98
//        }
//    }
}

