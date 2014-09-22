import QtQuick 2.0
import "../styleTypes"
StyleRectangle {
    id: styleRectangle1

    MouseArea{
        anchors.fill: parent
        onClicked: {
            setParField.openRegimeEditDialog()
        }
    }

    StyleText {
        id: text1
        height: 34
        text: dict.ventModesStrs[ventModeManager.trueVentMode]
        style: Text.Normal
        font.strikeout: false
        font.underline: false
        font.bold: true
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 5
        font.pixelSize: 34
    }

    StyleText {
        id: text2
        x: 1
        y: 38
        width: 78
        height: 30
        text: if(tpPatientAge.trueValue == 0) qsTr("ADULT")
                else qsTr("CHILD")
        font.pixelSize: 19
    }

    StyleText {
        id: text3
        x: 82
        y: 38
        width: 61
        height: 30
        text: qsTr(tpPatientHeight.trueValue + " кг")
        font.pixelSize: 18
    }

    StyleText {
        id: text4
        x: 146
        y: 38
        width: 59
        height: 30
        text: if(tpPatientGender.trueValue == 0) qsTr("жен")
              else qsTr("муж")
        font.pixelSize: 19
    }

    StyleText {
        id: text5
        x: 1
        y: 71
        width: 204
        height: 47
        text: qsTr("еще  индикаторы")
        anchors.right: parent.right
        anchors.rightMargin: 1
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 1
        anchors.leftMargin: 1
        anchors.left: parent.left
        font.pixelSize: 12
    }
}
