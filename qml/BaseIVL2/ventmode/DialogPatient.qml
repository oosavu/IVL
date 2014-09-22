import QtQuick 2.0

import QtQuick 2.0
import "../styleTypes"

StyleRectangle {
    StyleText{
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 61
        text: "Настройка параметров Пациента"
        font.pixelSize: 25
        id: titlePatient
    }

    Item{
        anchors.top: titlePatient.bottom
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
                    tp:  tpPatientAge,
                    name: "Возраст",
                    falseString: "Детский",
                    trueString: "Взрослый"
                })
                onClicked:  focus = true
                onAccepted: focus = false
            }
            EditedParameter {
                tpScope: ({
                    tp:  tpPatientGender,
                    name: "Пол",
                    falseString: "мужской",
                    trueString: "женский"
                })
                onClicked:  focus = true
                onAccepted: focus = false
            }
            EditedParameter {
                tpScope: ({
                    tp: tpPatientHeight,
                    name: "Вес",
                    unit: "кг",
                })
                onClicked:  focus = true
                onAccepted: focus = false
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
            //ventModeManager.acceptModeApnea()
            fullItem.state = "dialogParamRegime"
        }
        onCancelClicked: {
            //ventModeManager.cancelModeApnea()
            fullItem.state = "dialogParamRegime"
        }
    }



}
