import QtQuick 2.0
import CppImport 1.0

Rectangle {
    id: dbgMp
    property alias text: nameText.text
    property var param
    width: 160
    height: 20
    color: "gray"
    border.color: "black"
   // radius: 3
    Row{
        anchors.centerIn: parent
        Text{
            width: 100
            id: nameText
            text: "noname"
        }
        Text{
            width: 30
            text: dbgMp.param.value
        }

        Rectangle{
            Text{
                text: "A"
                anchors.centerIn: parent
            }
           // radius: 2
            height: dbgMp.height - 4
            width: 10
            y:3
            color: if(param.avilability == true) "green"
                   else "red"
        }
        Item{width:2}
        Rectangle{
            Text{
                text: "E"
                anchors.centerIn: parent
            }
         //   radius: 2
            height: dbgMp.height -4
            width: 10
            y:3
            color: if(param.errorLevel == Errored.ErrorNo) "green"
                    else if(param.errorLevel == Errored.Error1) "yello"
                    else if(param.errorLevel == Errored.Error2) "red"
        }
    }
}
