import QtQuick 2.0
import "styleTypes"
StyleRectangle {
    id: styleRectangle1
    Column {
        id: columnMenuItems
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.margins:3
        spacing: 3
        StyleButton{
            width: parent.width - 2
            color: miRightPanelDialog.visible? mainItem.okColor: mainItem.buttonColor
            height: 40
            text: "вид"
            onClicked: {
                miRightPanelDialog.visible = !miRightPanelDialog.visible
            }
        }
        StyleButton{
            width: parent.width - 2
            height: 40
            text: "журнал событий"
            color: miRightPanelDialog.visible? mainItem.okColor: mainItem.buttonColor
            onClicked: {
                miAlarms.visible = !miAlarms.visible
            }
        }
        StyleButton{
            width: parent.width - 2
            height: 40
            color: miModeGraphics.visible? mainItem.okColor: mainItem.buttonColor
            text: "графика"
            onClicked: {
                miModeGraphics.visible = !miModeGraphics.visible
            }
        }
        StyleButton{

            width: parent.width - 2
            height: 40
            text: "тренды"
        }
        StyleButton{
            width: parent.width - 2
            height: 40
            text: "пороги тревог"
            color: miErrorLevels.visible? mainItem.okColor: mainItem.buttonColor
            onClicked: {
                miErrorLevels.visible = !miErrorLevels.visible
            }
        }
        StyleButton{
            width: parent.width - 2
            height: 40
            text: "сервис"
            color: miService.visible? mainItem.okColor: mainItem.buttonColor
            onClicked: {
                miService.visible = !miService.visible
            }
        }
    }

    Grid {
        id: pictogramsGreed
        anchors.right: parent.right
        anchors.bottom: columnMenuItems.top
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins:3
        rows: 6
        spacing: 3
        property int pictogramSize: 53
        StyleButton{
            text: "П"
            height: parent.pictogramSize
            width: parent.pictogramSize
        }
        StyleButton{
            text: "И"
            height: parent.pictogramSize
            width: parent.pictogramSize
        }
        StyleButton{
            text: "К"
            height: parent.pictogramSize
            width: parent.pictogramSize
        }
        StyleButton{
            text: "Т"
            height: parent.pictogramSize
            width: parent.pictogramSize
        }
        StyleButton{
            text: "О"
            height: parent.pictogramSize
            width: parent.pictogramSize
        }
        StyleButton{
            text: "Г"
            height: parent.pictogramSize
            width: parent.pictogramSize
        }
        StyleButton{
            text: "Р"
            height: parent.pictogramSize
            width: parent.pictogramSize
        }
        StyleButton{
            text: "А"
            height: parent.pictogramSize
            width: parent.pictogramSize
        }
        StyleButton{
            text: "М"
            height: parent.pictogramSize
            width: parent.pictogramSize
        }

        StyleButton{
            text: "Ы"
            height: parent.pictogramSize
            width: parent.pictogramSize
        }


    }
}
