import QtQuick 2.0
import CppImport 1.0
import "../styleTypes"
Item {
    Loader{
        id: graphLoader_1_1
        x:1
        y:1
        width: 273
        height: 148
    }
    Loader{
        id: graphLoader_2_1
        x:1
        y:151
        width: 273
        height: 148
    }
    Loader{
        id: graphLoader_3_1
        x:1
        y:301
        width: 273
        height: 148
    }
    Loader{
        id: graphLoader_1_2
        x:276
        y:1
        width: 273
        height: 148
    }
    Loader{
        id: graphLoader_2_2
        x:276
        y:151
        width: 273
        height: 148
    }
    Loader{
        id: graphLoader_3_2
        x:276
        y:301
        width: 273
        height: 148
    }
    Loader{
        id: graphLoaderBig_1_1
        x:1
        y:1
        width: 273
        height: 298
    }
    Loader{
        id: graphLoaderBig_1_2
        x:276
        y:1
        width: 273
        height: 298
    }
    Loader{
        id: graphLoaderBig_2_1
        x:1
        y:151
        width: 273
        height: 298
    }
    Loader{
        id: graphLoaderBig_2_2
        x:276
        y:151
        width: 273
        height: 298
    }
    Component.onCompleted: {
        graphLoaderBig_1_1.sourceComponent = nodeEmpty1
        graphLoader_1_2.sourceComponent = nodeEmpty2
        graphLoader_2_2.sourceComponent = nodeEmpty1
        graphLoader_3_1.sourceComponent = nodeEmpty2
        graphLoader_3_2.sourceComponent = nodeEmpty1
    }

    Component{
        id: nodeEmpty1
        NodeEmpty{
            color: "#550000"
        }
    }
    Component{
        id: nodeEmpty2
        NodeEmpty{
            color: "#005500"
        }
    }
    ModeGraphicDialog{
        id: mgd
        anchors.centerIn: parent
        visible: false
    }

    function expandNode(node)
    {
        if (node == graphLoader_1_2 || node == graphLoader_2_2)
        {
            graphLoader_1_2.sourceComponent = undefined
            graphLoader_2_2.sourceComponent = undefined
            graphLoaderBig_1_2.sourceComponent = nodeEmpty2
        }
        if (node == graphLoader_1_1 || node == graphLoader_2_1)
        {
            graphLoader_1_1.sourceComponent = undefined
            graphLoader_2_1.sourceComponent = undefined
            graphLoaderBig_1_1.sourceComponent = nodeEmpty2
        }
        if (node == graphLoader_3_1)
        {
            graphLoader_3_2.sourceComponent = undefined
            graphLoader_2_2.sourceComponent = undefined
            graphLoaderBig_1_2.sourceComponent = nodeEmpty2
        }
    }




//    property bool anyGraphicDialogOpened: false

//    visible: main.state == "graphics"

//    Component{
//        id: canvasV
//        CanvasV{  }
//    }
//    Component{
//        id: canvasP
//        CanvasP{  }
//    }
//    Component{
//        id: canvasF
//        CanvasF{  }
//    }
//    property var nodeIndexes:{
//        0: node_11_1    ,
//        1: node_211_1   ,
//        2: node_211_2   ,
//        3: node_212_1   ,
//        4: node_212_2   ,
//        5: node_212_3   ,
//        6: node_221_1   ,
//        7: node_221_2   ,
//        8: node_221_3   ,
//        9: node_222_1   ,
//        11: node_222_2  ,
//        12: node_222_3  ,
//        13: node_222_4  ,
//        14: node_3111_1 ,
//        15: node_3111_2 ,
//        16: node_3111_3
//    }
//    Item{ anchors.fill: parent
//        visible: graphicManager.layout == GraphicEnums.GRAPH_LAYOUT_11
//        GraphicsNodeItem{
//            id: node_11_1
//            position: GraphicEnums.GRAPH_POSITION_11_1
//            anchors.top: parent.top
//            anchors.bottom: parent.bottom
//            anchors.left: parent.left
//            anchors.right: parent.right
//        }
//    }
//    Item{ anchors.fill: parent
//        visible: graphicManager.layout == GraphicEnums.GRAPH_LAYOUT_211
//        GraphicsNodeItem{
//            id: node_211_1
//            position: GraphicEnums.GRAPH_POSITION_211_1
//            anchors.top: parent.top
//            anchors.bottom: parent.verticalCenter
//            anchors.left: parent.left
//            anchors.right: parent.right
//        }
//        GraphicsNodeItem{
//            id: node_211_2
//            position: GraphicEnums.GRAPH_POSITION_211_2
//            anchors.top: parent.verticalCenter
//            anchors.bottom: parent.bottom
//            anchors.left: parent.left
//            anchors.right: parent.right
//        }
//    }
//    Item{ anchors.fill: parent
//        visible: graphicManager.layout == GraphicEnums.GRAPH_LAYOUT_221
//        GraphicsNodeItem{
//            id: node_221_1
//            position: GraphicEnums.GRAPH_POSITION_221_1
//            anchors.top: parent.top
//            anchors.bottom: parent.verticalCenter
//            anchors.left: parent.left
//            anchors.right: parent.horizontalCenter
//        }
//        GraphicsNodeItem{
//            id: node_221_2
//            position: GraphicEnums.GRAPH_POSITION_221_2
//            anchors.top: parent.top
//            anchors.bottom: parent.verticalCenter
//            anchors.left: parent.horizontalCenter
//            anchors.right: parent.right
//        }
//        GraphicsNodeItem{
//            id: node_221_3
//            position: GraphicEnums.GRAPH_POSITION_221_3
//            anchors.top: parent.verticalCenter
//            anchors.bottom: parent.bottom
//            anchors.left: parent.left
//            anchors.right: parent.right
//        }
//    }
//    Item{ anchors.fill: parent
//        visible: graphicManager.layout == GraphicEnums.GRAPH_LAYOUT_212
//        GraphicsNodeItem{
//            id: node_212_1
//            position: GraphicEnums.GRAPH_POSITION_212_1
//            anchors.top: parent.top
//            anchors.bottom: parent.verticalCenter
//            anchors.left: parent.left
//            anchors.right: parent.right
//        }
//        GraphicsNodeItem{
//            id: node_212_2
//            position: GraphicEnums.GRAPH_POSITION_212_2
//            anchors.top: parent.verticalCenter
//            anchors.bottom: parent.bottom
//            anchors.left: parent.left
//            anchors.right: parent.horizontalCenter
//        }
//        GraphicsNodeItem{
//            id: node_212_3
//            position: GraphicEnums.GRAPH_POSITION_212_3
//            anchors.top: parent.verticalCenter
//            anchors.bottom: parent.bottom
//            anchors.left: parent.horizontalCenter
//            anchors.right: parent.right
//        }
//    }
//    Item{ anchors.fill: parent
//        visible: graphicManager.layout == GraphicEnums.GRAPH_LAYOUT_222
//        GraphicsNodeItem{
//            id: node_222_1
//            position: GraphicEnums.GRAPH_POSITION_222_1
//            anchors.top: parent.top
//            anchors.bottom: parent.verticalCenter
//            anchors.left: parent.left
//            anchors.right: parent.horizontalCenter
//        }
//        GraphicsNodeItem{
//            id: node_222_2
//            position: GraphicEnums.GRAPH_POSITION_222_2
//            anchors.top: parent.top
//            anchors.bottom: parent.verticalCenter
//            anchors.left: parent.horizontalCenter
//            anchors.right: parent.right
//        }
//        GraphicsNodeItem{
//            id: node_222_3
//            position: GraphicEnums.GRAPH_POSITION_222_3
//            anchors.top: parent.verticalCenter
//            anchors.bottom: parent.bottom
//            anchors.left: parent.left
//            anchors.right: parent.horizontalCenter
//        }
//        GraphicsNodeItem{
//            id: node_222_4
//            position: GraphicEnums.GRAPH_POSITION_222_4
//            anchors.top: parent.verticalCenter
//            anchors.bottom: parent.bottom
//            anchors.left: parent.horizontalCenter
//            anchors.right: parent.right
//        }
//    }
//    Item{ anchors.fill: parent
//        visible: graphicManager.layout == GraphicEnums.GRAPH_LAYOUT_3111
//        GraphicsNodeItem{
//            id: node_3111_1
//            position: GraphicEnums.GRAPH_POSITION_3111_1
//            x:0
//            y:0
//            width: parent.width
//            height: parent.height/3
//        }
//        GraphicsNodeItem{
//            id: node_3111_2
//            position: GraphicEnums.GRAPH_POSITION_3111_2
//            x:0
//            y:parent.height/3
//            width: parent.width
//            height: parent.height/3
//        }
//        GraphicsNodeItem{
//            id: node_3111_3
//            position: GraphicEnums.GRAPH_POSITION_3111_3
//            x:0
//            y:parent.height*2/3
//            width: parent.width
//            height: parent.height/3
//        }
//    }
}
