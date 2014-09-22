import QtQuick 2.0
import "../styleTypes"

StyleRectangle {
    StyleText{
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 61
        text: "Настройка параметров АПНОЭ"
        font.pixelSize: 25
        id: titleAPNEA
    }
    Item{
        anchors.top: titleAPNEA.bottom
        anchors.bottom: dialogKeysOKCansel.top
        anchors.left: parent.left
        anchors.right: parent.right

        Grid {
            anchors.centerIn: parent
            id: addiditionalParams
            rows:2
            columns: 2
            EditedParameter {
                tpScope: ({
                    tp: tpApneaRegime,
                    name: "Управление:",
                    unit: "%",
                    falseString: "По далению",
                    trueString: "По потоку"
                })
            }
            EditedParameter {
                tpScope:
                    if(tpApneaRegime.currValue == 0)
                    ({
                        tp: tpApneaPi,
                        name: "Papnea:",
                        unit: "cmH2O"
                    })
                    else
                    ({
                        tp: tpApneaV,
                        name: "Vapnea:",
                        unit: "мл"
                    })
            }
            EditedParameter {
                tpScope: ({
                    tp: tpApneaRB,
                    name: "RBapnea:",
                    unit: "1/сек"
                })
            }
            EditedParameter {
                tpScope: ({
                    tp: tpApneaT,
                    name: "Tapnea:",
                    unit: "сек"
                })
            }
            spacing: 3
        }
    }
    StyleOkCancelButtons {
        id: dialogKeysOKCansel
        width: 304
        height: 70

        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: 3
        onOkClicked: {
            ventModeManager.acceptModeApnea()
            fullItem.state = "dialogParamRegime"
        }
        onCancelClicked: {
            ventModeManager.cancelModeApnea()
            fullItem.state = "dialogParamRegime"
        }
    }
    onVisibleChanged: {
        if(visible == false) ventModeManager.cancelModeApnea()
    }
}
