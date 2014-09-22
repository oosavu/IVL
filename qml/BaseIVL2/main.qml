import QtQuick 2.0
import CppImport 1.0
import "ventmode"
import "graphics"
import "alarms"
import "dbg"
import "menues"
import "measures"
import "styleTypes"

Item {
    //visible: false
    id: mainItem
    width: 1024
    height: 768
    Dictionary{id:dict}
    property bool displayMenu: true
    onDisplayMenuChanged: {
        if (displayMenu == true)
        {
            menuField.visible = true
            centralItem.x = 119
            centralItem.y = 59
            centralItem.width = 698
            centralItem.height = 586
        }
        else{
            menuField.visible = false
            centralItem.x = 1
            centralItem.y = 59
            centralItem.width = 816
            centralItem.height = 586
        }
    }

    GraphicsCentralItem {
        id: centralItem
        x: 119
        y: 59
        width: 698
        height: 586
    }

    LeftBotField {
        id: leftBotField
        x: 1
        y: 645
        width: 115
        height: 122
    }

    MeasuresItem {
        id: measParField
        x: 817
        y: 134
        width: 206
        height: 633
    }

    RegimeField {
        id: regimeField
        x: 817
        y: 1
        width: 206
        height: 130
    }

    MainAlarmField {
        id: mainAlarmField
        x: 119
        y: 1
        width: 695
        height: 55
    }

    StyleButton {

        text: if(displayMenu)"скрыть меню"
            else "показать меню"
        id: openMenuButton
        x: 1
        y: 1
        width: 115
        height: 55
        onClicked: {
            if (displayMenu == false) displayMenu = true
            else displayMenu = false
        }
    }

    MenuField {
        id: menuField
        x: 1
        y: 59
        width: 115
        height: 583
    }
    SetParField {
        id: setParField
        height: 122
        anchors.right: mainAlarmField.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 1
        anchors.left: mainAlarmField.left
    }

    MenuItemModeGraphics {id: miModeGraphics; visible: false}
    MenuRightPanelDialog {id: miRightPanelDialog; visible: false}
    MenuItemAlarms{id: miAlarms; visible: false}
    MenuErrorLevels{id: miErrorLevels; visible: false}
    MenuItemService{id: miService; visible: false}


    property string panelColor:         "#00A0A0"
    property string panelBorderColor:   "white"
    property string panelElementColor:  "#555555"
    property string buttonColor:        "orange"

    property string textColor:          "white"
    property string offTextColor:       "#AAAAAA"

    property string okColor:            "green"
    property string okColorFon:         "#90EE90"
    property string warningColor:       "#FFBE00"
    property string errorColor:         "red"
    property string errorColorFon:      "#EE9090"



    ListModel
    {
        id: model_CMV_VCV
        ListElement{ paramNum: 0; }
        ListElement{ paramNum: 1; }
        ListElement{ paramNum: 2; }
        ListElement{ paramNum: 3; }
        ListElement{ paramNum: 4; }
        ListElement{ paramNum: 5; }
        ListElement{ paramNum: 6; }
        ListElement{ paramNum: 7; }
    }
    ListModel
    {
        id: model_maximum
        ListElement{ paramNum: 0; }
        ListElement{ paramNum: 1; }
        ListElement{ paramNum: 2; }
        ListElement{ paramNum: 3; }
        ListElement{ paramNum: 4; }
        ListElement{ paramNum: 5; }
        ListElement{ paramNum: 6; }
        ListElement{ paramNum: 7; }
        ListElement{ paramNum: 8; }
        ListElement{ paramNum: 9; }
        ListElement{ paramNum: 10; }
        ListElement{ paramNum: 11; }
        ListElement{ paramNum: 12; }
        ListElement{ paramNum: 13; }
        ListElement{ paramNum: 14; }
        ListElement{ paramNum: 15; }
    }
    ListModel
    {
        id: model_user1
        ListElement{ paramNum: 4; }
        ListElement{ paramNum: 5; }
        ListElement{ paramNum: 6; }
        ListElement{ paramNum: 7; }
        ListElement{ paramNum: 8; }
        ListElement{ paramNum: 9; }
        ListElement{ paramNum: 10; }
        ListElement{ paramNum: 11; }
    }
    ListModel
    {
        id: model_user2
        ListElement{ paramNum: 8;  }
        ListElement{ paramNum: 9;  }
        ListElement{ paramNum: 10; }
        ListElement{ paramNum: 11; }
        ListElement{ paramNum: 12; }
        ListElement{ paramNum: 13; }
        ListElement{ paramNum: 14; }
        ListElement{ paramNum: 15; }
    }


}
