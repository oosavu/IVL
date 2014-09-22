import QtQuick 2.0
import CppImport 1.0
import "../styleTypes"
StyleRectangle {

    ListModel
    {
        id: optionsModel
        Component.onCompleted: {
            append({dp: optCapnoBO     , name: "Капнограф БО"                         })
            append({dp: optCapnoPT     , name: "Капнограф ПТ"                         })
            append({dp: optFastOxy     , name: "датчик потребления кислорода "        })
            append({dp: optBiSTEP      , name: "режим BiSTEP"                         })
            append({dp: optNIV         , name: "режим NIV"                            })
            append({dp: optAPRV        , name: "режим APRV"                           })
            append({dp: optNebul       , name: "небулайзер"                           })
            append({dp: optSpO2        , name: "пульсоксиметр"                        })
            append({dp: optLungMassage , name: "массаж лёгких"                        })
            append({dp: optCombinedIVL , name: "сочетанная ИВЛ"                       })
            append({dp: optISV         , name: "режим ISV"                            })
            append({dp: optIPPV        , name: "режим IPPV"                           })
            append({dp: optPreOxy      , name: "процедура преоксигенации"             })
            append({dp: optFickSens    , name: "измерение сердечного выброса по Фику" })
            append({dp: optVolCapno    , name: "объемная капнометрия"                 })
            append({dp: optNeonat      , name: "неонатальный режим"                   })
            append({dp: optWireless    , name: "беспроводной интерфейс"               })
            append({dp: optSCM         , name: "работа в СЦМ"                         })
            append({dp: optPCV_VG      , name: "режим PCV_VG"                         })
            append({dp: optSanat       , name: "процедура поддержки санации"          })
            append({dp: optAlvRecrMan  , name: "маневр раскрытия альвеол"             })
            append({dp: optSIMV_DC     , name: "режим SIMV/DC"                        })
        }
    }
    ListView{
        model: optionsModel
        spacing: 3
        clip: true
        anchors.fill: parent
        anchors.margins: 23
        delegate:
            EditedParameterLineBool{
                tp: dp
                width: parent.width
                nameStr: name
        }
    }

    function acceptChanges()
    {
        optCapnoBO.acceptValue()
        optCapnoPT.acceptValue()
        optFastOxy.acceptValue()
        optBiSTEP.acceptValue()
        optNIV.acceptValue()
        optAPRV.acceptValue()
        optNebul.acceptValue()
        optSpO2.acceptValue()
        optLungMassage.acceptValue()
        optCombinedIVL.acceptValue()
        optISV.acceptValue()
        optIPPV.acceptValue()
        optPreOxy.acceptValue()
        optFickSens.acceptValue()
        optVolCapno.acceptValue()
        optNeonat.acceptValue()
        optWireless.acceptValue()
        optSCM.acceptValue()
        optPCV_VG.acceptValue()
        optSanat.acceptValue()
        optAlvRecrMan.acceptValue()
        optSIMV_DC.acceptValue()
    }
    function restoreChanges()
    {
        optCapnoBO.restoreValue()
        optCapnoPT.restoreValue()
        optFastOxy.restoreValue()
        optBiSTEP.restoreValue()
        optNIV.restoreValue()
        optAPRV.restoreValue()
        optNebul.restoreValue()
        optSpO2.restoreValue()
        optLungMassage.restoreValue()
        optCombinedIVL.restoreValue()
        optISV.restoreValue()
        optIPPV.restoreValue()
        optPreOxy.restoreValue()
        optFickSens.restoreValue()
        optVolCapno.restoreValue()
        optNeonat.restoreValue()
        optWireless.restoreValue()
        optSCM.restoreValue()
        optPCV_VG.restoreValue()
        optSanat.restoreValue()
        optAlvRecrMan.restoreValue()
        optSIMV_DC.restoreValue()
    }

//    EditedParameterView{
//        anchors.fill: parent
//        anchors.margins: 3
//        spacing: 3
//        model: optionsListModel
//    }

}
