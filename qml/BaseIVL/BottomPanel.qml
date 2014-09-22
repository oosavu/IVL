import QtQuick 2.0
import CppImport 1.0
import "graphics"
import "styleTypes"

Item {
    visible: main.state == "graphics"

    StyleButton{
        x:1
        y:1
        width:  88
        height: 48
        text: "пороги тревог"
        onClicked: {
            if (main.state == "graphics"){
                main.state = "errorLevelsDialog"
            }
        }
    }
    StyleButton{
        x:92
        y:1
        width:  89
        height: 48
        text: "вид"
        onClicked:{
            if (main.state == "graphics"){
                main.state =  "layoutDialog"
            }
        }
    }
    StyleButton{
        x:184
        y:1
        width:  90
        height: 48
        text: "журнал тревог"

    }
    StyleButton{
        x:276
        y:1
        width:  89
        height: 48
        text: "тренды"

    }
    StyleButton{
        x:368
        y:1
        width:  89
        height: 48
        text: "мони торинг"
    }
    StyleButton{
        x:460
        y:1
        width:  89
        height: 48
        text: "наст ройки"
    }



}
