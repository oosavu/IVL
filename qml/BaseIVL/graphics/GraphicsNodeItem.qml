import QtQuick 2.0
import CppImport 1.0

Item {
    id: gni    

    property alias position: cgnd.position

    property int graphicType: graphicManager.listGraphics[position]

    MouseArea{
        onClicked:
        {
            if(!graphicCentralItem.anyGraphicDialogOpened) cgnd.visible = true
        }
        anchors.fill: parent
    }
    Loader{
        anchors.fill: parent
        id: axisCanvasLoader
        sourceComponent: if (graphicType == GraphicEnums.GRAPH_TYPE_V) canvasV
        else if (graphicType == GraphicEnums.GRAPH_TYPE_P) canvasP
        else if (graphicType == GraphicEnums.GRAPH_TYPE_F) canvasF
    }
    ChangeGraphicNodeDialog{
        id: cgnd
        position: 0
        x: parent.width/2 - width/2
        y: parent.height/2 - height/2
    }
}

