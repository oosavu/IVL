import QtQuick 2.0
import CppImport 1.0
import "dbg"
import "styleTypes"
import "measures"

StyleRectangle {
    id: botleft
    clip: true
    Item{
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 25
        StyleTextM{
            anchors.centerIn: parent
            text: if(botleft.state == "monit1") "Мониторинг 1"
            else if(botleft.state == "monit2") "Мониторинг 2"
            else if(botleft.state == "alarms") "Тревоги"
            else if(botleft.state == "encoder") "Энкодер"
        }
        MouseArea{
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.top: parent.top
            width: parent.width/2
            onClicked:{
                if(botleft.state == "monit1") botleft.state = "encoder"
                else if(botleft.state == "monit2") botleft.state = "monit1"
                else if(botleft.state == "alarms") botleft.state = "monit2"
                else if(botleft.state == "encoder") botleft.state = "alarms"
            }
        }
        MouseArea{
            anchors.bottom: parent.bottom
            anchors.top: parent.top
            anchors.right: parent.right
            width: parent.width/2

            onClicked:{
                if(botleft.state == "monit1") botleft.state = "monit2"
                else if(botleft.state == "monit2") botleft.state = "alarms"
                else if(botleft.state == "alarms") botleft.state = "encoder"
                else if(botleft.state == "encoder") botleft.state = "monit1"
            }
        }
    }


    TopLeftMeasures1 {
        visible: false
        id: monit1
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height - 25
    }
    TopLeftMeasures2 {
        visible: false
        id: monit2
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height - 25
    }
    Rectangle {
        visible: false
        id: alarms
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height - 25
        color: "blue"
    }
    EncoderSimulator{
        visible: false
        id: encoder
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height - 25
        color: "blue"
    }
    state: "monit1"
    states:[
        State {
            name: "monit1"
            PropertyChanges {
                target: monit1
                explicit: true;
                visible: true
            }
        },
        State {
            name: "monit2"
            PropertyChanges {
                explicit: true;
                target: monit2
                visible: true
            }
        },
        State {
            name: "alarms"
            PropertyChanges {
                explicit: true;
                target: alarms
                visible: true
            }
        },
        State {
            name: "encoder"
            PropertyChanges {
                explicit: true;
                target: encoder
                visible: true
            }
        }
    ]

//    property var titles:{
//    0: "Мониторинг 1",
//    1: "Мониторинг 2",
//    2: "журнал"
//    }
//    VisualItemModel {
//        id: itemModel
//        TopLeftMeasures1{ }
//        TopLeftMeasures2{}
//        //Rectangle { height: 196; width:  196; }
//        //Rectangle { height: 196; width:  196; }
//        Rectangle { height: 196; width:  196; }
//    }

//    ListView {
//        id: view
//        anchors.bottom: parent.bottom
//        anchors.left: parent.left
//        anchors.right: parent.right
//        height: parent.height - 25
//        snapMode: ListView.SnapOneItem
//        orientation: ListView.Horizontal
//        model: itemModel
//        highlightRangeMode: ListView.StrictlyEnforceRange
//    }

}
