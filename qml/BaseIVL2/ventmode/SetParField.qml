import QtQuick 2.0
import CppImport 1.0
import "../styleTypes"

StyleRectangle {
    id: spField

    Row{
        id: foretherParams
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: 116
        anchors.margins: 3
        spacing: 3
        EditedParameter  {
             tpScope: ({
                 tp: tpFiO2,
                 name: "fio2",
                 unit: "%",
             })
             onClicked: {
                 if (setParField.state == "hidden") setParField.state = "simpleRedact"
                 focus = true
             }
             onAccepted: {
                 if (setParField.state == "simpleRedact")
                 {
                     ventModeManager.acceptModeVent()
                     setParField.state = "hidden"
                 }
                 focus = false
             }
             onCanceled: {
                 tp.restoreValue()
                 focus = false
             }
        }
        EditedParameter{
            tpScope: if(ventModeManager.ventMode == VentModeManager.CIVL_VENTMODE_BISTEP ||
                        ventModeManager.ventMode == VentModeManager.CIVL_VENTMODE_APRV      )
                         ({
                              tp: tpPLow,
                              name: "PLow",
                              unit: "cmH2O",
                          })
            else if(ventModeManager.ventMode == VentModeManager.CIVL_VENTMODE_NIV)
                         ({
                              tp: tpPTrig,
                              name: "PTrig",
                              unit: "cmH2O",
                          })
            else
                         ({
                              tp: tpPMax,
                              name: "PMax",
                              unit: "cmH2O",
                          })
            onClicked: {
                if (setParField.state == "hidden") setParField.state = "simpleRedact"
                focus = true
            }
            onAccepted: {
                if (setParField.state == "simpleRedact")
                {
                    ventModeManager.acceptModeVent()
                    setParField.state = "hidden"
                }
                focus = false
            }
            onCanceled: {
                tp.restoreValue()
                focus = false
            }
        }
        EditedParameter{
            tpScope: if(ventModeManager.ventMode == VentModeManager.CIVL_VENTMODE_BISTEP ||
                        ventModeManager.ventMode == VentModeManager.CIVL_VENTMODE_APRV      )
                         ({})
            else if(ventModeManager.ventMode == VentModeManager.CIVL_VENTMODE_NIV)
                         ({
                              tp: tpPSupp,
                              name: "PS",
                              unit: "cmH2O",
                         })
            else
                         ({
                              tp: tpPEEP,
                              name: "PEEP",
                              unit: "cmH2O",
                         })
            onClicked: {
                if (setParField.state == "hidden") setParField.state = "simpleRedact"
                focus = true
            }
            onAccepted: {
                if (setParField.state == "simpleRedact")
                {
                    ventModeManager.acceptModeVent()
                    setParField.state = "hidden"
                }
                focus = false
            }
            onCanceled: {
                tp.restoreValue()
                focus = false
            }
        }
        EditedParameter{            tpScope: if(ventModeManager.ventMode == VentModeManager.CIVL_VENTMODE_BISTEP ||
                        ventModeManager.ventMode == VentModeManager.CIVL_VENTMODE_APRV      )
                         ({
                              tp: tpTLow,
                              name: "TLow",
                              unit: "c",
                         })
            else if(ventModeManager.ventMode == VentModeManager.CIVL_VENTMODE_CPAP)
                         ({})
            else if(ventModeManager.ventMode == VentModeManager.CIVL_VENTMODE_NIV)
                         ({
                              tp: tpPEEP,
                              name: "PEEP",
                              unit: "cmH2O",
                         })
            else
                         ({
                              tp: tpRB,
                              name: "RB",
                              unit: "1/min",
                         })
            onClicked: {
                if (setParField.state == "hidden") setParField.state = "simpleRedact"
                focus = true
            }
            onAccepted: {
                if (setParField.state == "simpleRedact")
                {
                    ventModeManager.acceptModeVent()
                    setParField.state = "hidden"
                }
                focus = false
            }
            onCanceled: {
                tp.restoreValue()
                focus = false
            }
        }
    }
    state: "hidden"
    states: [
        State {
            name: "hidden"
            PropertyChanges {
                target: spField
                height: 122
                enabled: true
            }
        },
        State {
            name: "simpleRedact"
            PropertyChanges {
                target: spField
                height: 372
                enabled: true
            }
        },
        State {
            name: "fullRedact"
            PropertyChanges {
                target: spField
                height: 708
                enabled: true
            }
        }
    ]
    transitions:  Transition {
        id: trans1
        from: "*"
        to: "*"
        NumberAnimation { duration: 230; properties: "height"; easing.type: Easing.InOutQuad }
    }

    onStateChanged: {
        if(state == "hidden") focus = true
    }

    SetParFullItem{
        id: spFullItem
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: foretherParams.top
        visible: parent.state == "fullRedact" && trans1.running == false
    }

    function openRegimeEditDialog(){
        state = "fullRedact"
        spFullItem.state = "dialogRegime"
    }

    SetParSimpleItem{
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: foretherParams.top
        visible: parent.state == "simpleRedact" && trans1.running == false
    }
}
