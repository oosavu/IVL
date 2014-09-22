import QtQuick 2.0
import "../styleTypes"
import CppImport  1.0

Item{
     visible: parent.state == "dialogParamRegime"

    Grid {
        anchors.fill: parent
        rows:2
        EditedParameter {
           // tp:  tpVInsp;         name:"Vinsp"        ; unit:     "мл"
            tpScope: ({
                tp: tpFiO2,
                name: "fio2",
                unit: "%",
            })
        }
        EditedParameter {tp:  tpTInsp;         name:"Tinsp"        ; unit:     "сек"       }
        EditedParameter {tp:  tpPTrig;         name:"PTrig"        ; unit:     "смH2O"     }
        EditedParameter {tp:  tpTrigWnd;       name:"TrigWnd"      ; unit:     "%"         }

        EditedParameter {
            //tp:  tpPlato;         name:"Plato"        ; unit:     "%"
            tpScope:
                if(ventModeManager.ventMode == VentModeManager.CIVL_VENTMODE_PCV_VG)
                    ({
                        tp: tpPTrig,
                        name: "PTrig",
                        unit: "смH2O",
                    })
                else if(ventModeManager.ventMode == VentModeManager.CIVL_VENTMODE_NIV )
                    ({})
                else
                {
                    if(tpTrigMode.currValue == 0) //по давлению
                    ({
                        tp: tpPTrig,
                        name: "PTrig",
                        unit: "смH2O",
                    })
                    else //по потоку
                    ({
                        tp: tpFTrig,
                        name: "FTrig",
                        unit: "todo",
                    })
                }
        }
        EditedParameter {
            tpScope:
                if(ventModeManager.ventMode == VentModeManager.CIVL_VENTMODE_CPAP ||
                   ventModeManager.ventMode == VentModeManager.CIVL_VENTMODE_NIV)
                ({})
                else if(ventModeManager.ventMode == VentModeManager.CIVL_VENTMODE_BISTEP||
                    ventModeManager.ventMode == VentModeManager.CIVL_VENTMODE_APRV)
                ({
                     tp: tpPHigh,
                     name: "PHigh",
                     unit: "cmH2O"
                })
                else
                ({
                     tp: tpTrigWnd,
                     name: "TrigWnd",
                     unit: "%"
                })
        }
        EditedParameter {
            tpScope:
                if(ventModeManager.ventMode == VentModeManager.CIVL_VENTMODE_PCV_VG ||
                   ventModeManager.ventMode == VentModeManager.CIVL_VENTMODE_CMV_VCV||
                   ventModeManager.ventMode == VentModeManager.CIVL_VENTMODE_CMV_PCV)
                ({
                     tp: tpFSupp,
                     name: "FSupp",
                     unit: "???"
                })
                else if(ventModeManager.ventMode == VentModeManager.CIVL_VENTMODE_NIV)
                ({})
                else
                ({
                     tp: tpPSupp,
                     name: "PS",
                     unit: "cmH20"
                })
        }
        EditedParameter {
            tpScope:
                if(ventModeManager.ventMode == VentModeManager.CIVL_VENTMODE_SIMV_PC ||
                   ventModeManager.ventMode == VentModeManager.CIVL_VENTMODE_CMV_PCV)
                ({
                     tp: tpPInsp,
                     name: "PInsp",
                     unit: "cmH2O"
                })
                else if(ventModeManager.ventMode == VentModeManager.CIVL_VENTMODE_CMV_VCV ||
                        ventModeManager.ventMode == VentModeManager.CIVL_VENTMODE_SIMV_VC)
                ({
                    tp: tpVInsp
                })
                else
                ({
                     tp: tpPSupp,
                     name: "PS",
                     unit: "cmH20"
                })
            tp:  tpFormFlow;      name:"Форма потока" ; trueString: "треуг.";   falseString: "прямоуг."}
        spacing: 3
    }
}
