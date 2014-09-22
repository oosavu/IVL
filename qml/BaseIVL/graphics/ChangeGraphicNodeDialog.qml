import QtQuick 2.0
import CppImport 1.0
import "../styleTypes"

StyleRectangle {
    id: changeGraphicsNodeDialog
    visible: false
    onVisibleChanged: {
        if(visible == true) graphicCentralItem.anyGraphicDialogOpened = true
        else graphicCentralItem.anyGraphicDialogOpened = false
    }

    property bool isFull: true
    property int position
    width: 196
    height: view.model.count*35+10

    ListView{
        property int currentNodeId: model.get(currentIndex).nodeId
        id: view
        interactive: false
        anchors.fill: parent
        anchors.margins: 5
        model: isFull? graphicNodesModelFull : graphicNodesModelTrimmed
        spacing: 5
        delegate: Component{
            Item{
                width: view.width
                height: (view.height - 5*(view.model.count - 1))/view.model.count
                StyleRectangle{
                    color: if(graphicManager.listGraphics[position] == nodeId) "#444444"
                            else "black"
                    anchors.fill: parent
                    StyleTextM{
                        text: description
                        anchors.centerIn: parent
                    }
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked:{
                        graphicManager.setGraphicType(position,nodeId)
                        changeGraphicsNodeDialog.visible = false
                    }
                }
            }
        }
    }

    ListModel {
        id: graphicNodesModelFull
        ListElement {
            nodeId: 0
            description: "GRAPH_TYPE_P"
        }
        ListElement {
            nodeId: 1
            description: "GRAPH_TYPE_V"
        }
        ListElement {
            nodeId: 2
            description: "GRAPH_TYPE_F"
        }
        ListElement {
            nodeId: 3
            description: "GRAPH_TYPE_CO2"
        }
        ListElement {
            nodeId: 4
            description: "GRAPH_TYPE_LOOP"
        }
    }
    ListModel {
        id: graphicNodesModelTrimmed
        ListElement {
            nodeId: 0
            description: "GRAPH_TYPE_P"
        }
        ListElement {
            nodeId: 1
            description: "GRAPH_TYPE_V"
        }
        ListElement {
            nodeId: 2
            description: "GRAPH_TYPE_F"
        }
        ListElement {
            nodeId: 3
            description: "GRAPH_TYPE_CO2"
        }
    }


}
