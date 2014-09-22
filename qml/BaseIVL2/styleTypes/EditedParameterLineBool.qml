import QtQuick 2.0
import CppImport 1.0

StyleRectangle{

    signal  clicked
    signal accepted
    signal canceled
    property var tp
    property string nameStr: "noname"

    border.color: mainItem.panelElementColor
    border.width: 2
    radius: 5
    color: mainItem.panelColor;

//    if (dp.errorLevel == TunningParameter.TPErrorNo) mainItem.panelColor;
//    else if(dp.errorLevel == TunningParameter.TPError1) mainItem.warningColor;
//    else mainItem.errorColorFon;
//    width: parent.width

    height: 50
    id: editedParameterLine

    StyleText{
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: 5
        text: nameStr
        font.pixelSize: 25
    }

    StyleRectangle{
        id: toggleButton
        border.color: mainItem.panelElementColor
        border.width: 2
        radius: 8
        clip: true
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: 3
        width: 100

        state: if(tp.currValue == true) "onState"
             else "offState"
        states:[
            State{
                name: "onState"
                PropertyChanges {
                    target: slideItem
                    x: 0
                }
                PropertyChanges {
                    target: toggleButton
                    color: mainItem.okColorFon
                }
            },
            State{
                name: "offState"
                PropertyChanges {
                    target: slideItem
                    x: -toggleButton.width*3/4
                }
                PropertyChanges {
                    target: toggleButton
                    color: mainItem.errorColorFon
                }
            }
        ]
        Item{
            id: slideItem
            height: parent.height
            width:  toggleButton.width*7/4

            Item{
                width: toggleButton.width*3/4
                height: parent.height
                x:0
                y:0
                StyleText{
                    anchors.centerIn: parent
                    text:"Вкл"
                }
            }
            StyleRectangle{
                x:toggleButton.width*3/4
                y:1
                height: parent.height - 2
                width: toggleButton.width/4
                color: "blue"
                border.color: mainItem.panelElementColor
                border.width: 2
                radius: 8
            }
            Item{
                height: parent.height
                width: toggleButton.width*3/4
                x:toggleButton.width
                y:0
                StyleText{
                    anchors.centerIn: parent
                    text:"Выкл"
                }
            }
        }
        transitions:  Transition {
            id: trans1
            from: "*"
            to: "*"
            NumberAnimation {
                duration: 100;
                target: slideItem
                properties: "x";
                easing.type: Easing.InOutQuad
            }
        }
    }
    MouseArea{
        anchors.fill: parent
        onClicked:{
            tp.currValue = !tp.currValue
        }
    }
}
