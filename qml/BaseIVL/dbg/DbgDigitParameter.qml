import QtQuick 2.0
import CppImport 1.0

Rectangle {
    id: dbgMp
    property alias text: nameText.text
    property var param
    width: itemrow.width + 20
    height: 20
    color: "gray"
    border.color: "black"
    //radius: 3
    Row{
        id: itemrow
        spacing: 2
        anchors.centerIn: parent
        Text{
            width: 100
            id: nameText
            text: "noname"
        }
        Text{
            width: 50
            text:"min: " + dbgMp.param.minValue
        }
        Text{
            width: 50
            text:"val: " + dbgMp.param.value
        }
        Text{
            width: 80
            text:"trueval: " + dbgMp.param.trueValue
        }
        Text{
            width: 80
            text:"max: " + dbgMp.param.maxValue
        }
        Rectangle{

            Text{
                text: "E"
                anchors.centerIn: parent
            }
            height: dbgMp.height -4
            width: 10
            //radius: 2
            color: if(param.errorLevel == Errored.ErrorNo) "green"
                    else if(param.errorLevel == Errored.Error1) "yello"
                    else if(param.errorLevel == Errored.Error2) "red"
        }
        Rectangle{
            height: dbgMp.height -4
            width: 10
           // radius: 2
            color: "red"
            Text{  text: "-"  }
            MouseArea{
                anchors.fill: parent
                onClicked: param.value -=1
            }
        }
        Rectangle{
            height: dbgMp.height -4
            width: 10
         //   radius: 2
            color: "red"
            Text{text: "+" }
            MouseArea{
                anchors.fill: parent
                onClicked: param.value +=1
            }
        }


    }
}
