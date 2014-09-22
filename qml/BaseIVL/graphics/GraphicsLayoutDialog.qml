import QtQuick 2.0
import "../styleTypes"

StyleCentralDialog{

    ListModel {
        id: layoutsModel
        ListElement {
            enumValue: 0//graphicsManager.GRAPH_LAYOUT_11
            description: "LAY_11"
        }
        ListElement {
            enumValue: 1//graphicsManager.GRAPH_LAYOUT_211
            description: "LAY_211"
        }
        ListElement {
            enumValue: 2//graphicsManager.GRAPH_LAYOUT_222
            description: "LAY_212"
        }
        ListElement {
            enumValue: 3//graphicsManager.GRAPH_LAYOUT_212
            description: "LAY_221"
        }
        ListElement {
            enumValue: 4//graphicsManager.GRAPH_LAYOUT_221
            description: "LAY_222"
        }
        ListElement {
            enumValue: 5//graphicsManager.GRAPH_LAYOUT_3111
            description: "LAY_3111"
        }
    }
    GridView{
        interactive: false
        property string currentLayout: model.get(currentIndex).description


        id: layoutChoiseView
        cellWidth: width/4; cellHeight: height/3

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height - 50
        focus: true //TODO зачем эта строка?


        delegate: Component{
            Item{
                width: layoutChoiseView.width/4
                height: layoutChoiseView.height/3
                StyleRectangle{
                    color: if(layoutChoiseView.currentIndex == index) "#444444"
                            else "black"
                    anchors.centerIn: parent
                    width: layoutChoiseView.width/4 - 10
                    height: layoutChoiseView.height/3 - 10
                    Text{
                        text: description
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        font.pointSize: 12
                        color: "white"
                        anchors.centerIn: parent
                    }
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked:{
                        layoutChoiseView.currentIndex = index
                    }
                }
            }
        }
        model: layoutsModel
    }

    onCancelClicked: main.state = "graphics"
    okActive: layoutChoiseView.model.get(layoutChoiseView.currentIndex).enumValue != graphicManager.layout
    onOkClicked: {
        graphicManager.layout = layoutChoiseView.model.get(layoutChoiseView.currentIndex).enumValue
        console.log("from QML set layout: " + graphicManager.layout)
        main.state = "graphics"
    }
}
