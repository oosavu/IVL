import QtQuick 2.0
import "../styleTypes"
StyleMenu {
    id: menuGraphics
    StyleText {
        id: titleText
        text: qsTr("Настройка вида центральной области")
        anchors.right: parent.right
        anchors.rightMargin: 1
        font.pixelSize: 25
        anchors.topMargin: 1
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.leftMargin: 1
    }

    StyleText {
        id: descriptionText
        width: 442
        height: 45
        text: qsTr("Выберите элементы, которые будут отображаться в центральной области экрана")
        wrapMode: Text.WordWrap
        font.pixelSize: 12
        anchors.topMargin: 3
        anchors.top: titleText.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }

    ListModel{
        id: nodeModel
        ListElement{str: "NodeP"       ; description: "график давления" ; displayed: false; prevDisplayed: false}
        ListElement{str: "NodeV"       ; description: "график объёма"   ; displayed: false; prevDisplayed: false}
        ListElement{str: "NodeF"       ; description: "график  потока"  ; displayed: false; prevDisplayed: false}
        ListElement{str: "NodeCO2"     ; description: "график CO2"      ; displayed: false; prevDisplayed: false}
        ListElement{str: "NodeFiO2"    ; description: "график FiO2"     ; displayed: false; prevDisplayed: false}
        ListElement{str: "NodeLoopPV"  ; description: "петля PV"        ; displayed: false; prevDisplayed: false}
        ListElement{str: "NodeLoopFV"  ; description: "петля VF"        ; displayed: false; prevDisplayed: false}
        ListElement{str: "NodeLoopFP"  ; description: "петля FP"        ; displayed: false; prevDisplayed: false}
        ListElement{str: "NodeISV"     ; description: "график ISV"      ; displayed: false; prevDisplayed: false}
        ListElement{str: "NodeColumns" ; description: "столбцы"         ; displayed: false; prevDisplayed: false}
        ListElement{str: "NodeDynLyng" ; description: "динамич. лёгкое" ; displayed: false; prevDisplayed: false}
        ListElement{str: "NodeAlarms"  ; description: "тревоги"         ; displayed: false; prevDisplayed: false}
        ListElement{str: "NodeMonit"   ; description: "мониторинг"      ; displayed: false; prevDisplayed: false}
    }
    GridView{
        id: nodeView
        anchors.top: descriptionText.bottom
        anchors.bottom: styleBut.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 40

        interactive: false
        model: nodeModel
        delegate: StyleRectangle{
            width: 95
            height: 90
            color:displayed? "green": "gray"

            StyleText{
                anchors.fill:parent
                anchors.margins: 3
                text: description
                wrapMode: Text.WordWrap
            }
            MouseArea{
                anchors.fill: parent
                onClicked:{
                    if (displayed == true) nodeModel.setProperty(index, "displayed", false)
                    else nodeModel.setProperty(index, "displayed", true)
                }
            }
        }
    }

    property int choiseCount: 0

    StyleOkCancelButtons {
        id: styleBut
        anchors.right: parent.right
        anchors.rightMargin: 3
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 3
        onOkClicked: {
            var listCentral = []
            for (var i = 0; i< nodeView.count; i++)
                if(nodeModel.get(i).displayed)listCentral.push(nodeModel.get(i).str)
            centralItem.setState(listCentral)
            menuGraphics.visible = false
        }
        onCancelClicked: {
            menuGraphics.visible = false
        }
    }

}
