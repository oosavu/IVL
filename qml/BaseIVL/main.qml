import QtQuick 2.0
import CppImport 1.0
import "ventmode"
import "graphics"
import "alarms"
import "dbg"
import "measures"
import "styleTypes"

Item {
    id: main
    //color:"black"
    width:1024
    height:768

    Dictionary{id:dict}


    TimeField{          x:1;    y:1;    width: 98;      height: 23;    id: timeField        }
    BataryField{        x:101;  y:1;    width: 48;      height: 23;    id: bataryField      }
    MainAlarmField{     x:151;  y:1;    width: 498;     height: 48;    id: mainAlarmField   }
    VentModeField{      x:651;  y:1;    width: 148;     height: 98;    id: ventModeField    }
    RightPanel{         x:700;  y:100;  width: 100;     height: 500;   id: ventModeItem     }
    BottomPanel{        x:150;  y:550;  width: 550;     height: 50;    id: bottomPanel      }
    PictogramsPanel{    x:151;  y:51;   width: 498;     height: 48;    id: pictogramsPanel  }
    MeasuresItem{       x:0;    y:25;   width: 150;     height: 375;   id: measureItem      }
    BottomLeftPanel{    x:1;    y:401;  width: 148;     height: 198;   id: bottomLeftPanel  }
    GraphicsCentralItem{x:150;  y:100;  width: 550;     height: 450;   id: graphicCentralItem;  visible: false }


    GraphicsLayoutDialog{id: graphicsLayoutDialog; visible: false}
    VentModeCentralItem{ id: ventModeCentralItem; visible: false}
    ErrorLevelsDialog{ id: errorLevelsDialog; visible: false}


    state: "graphics"
    states:[
        State {
            name: "graphics"
            PropertyChanges {
                target: graphicCentralItem
                explicit: true;
                visible: true
            }
        },
        State {
            name: "ventDialog"
            PropertyChanges {
                explicit: true;
                target: ventModeCentralItem
                visible: true
            }
        },
        State {
            name: "layoutDialog"
            PropertyChanges {
                explicit: true;
                target: graphicsLayoutDialog
                visible: true
            }
        },
        State {
            name: "errorLevelsDialog"
            PropertyChanges {
                explicit: true;
                target: errorLevelsDialog
                visible: true
            }
        }
    ]
}
