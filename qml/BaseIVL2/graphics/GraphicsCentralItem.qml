import QtQuick 2.0
import CppImport 1.0
import "../styleTypes"

Item {
    id: item1

    property int halfHeight: leftItem.height/2
    property int thirdHeigt: leftItem.height/3
    property int halfWidth: leftItem.width/2

    onWidthChanged: {
        //refreshLoadersSizes()
        syncGraphic()
    }

    state: "rightColumnOn"
    states:[
        State{
            name: "rightColumnOn"
            PropertyChanges {
                target: rightItem
                width: 150
            }
        },
        State{
            name: "rightColumnOff"
            PropertyChanges {
                target: rightItem
                width: 0
            }
        }
    ]

    function refreshLoadersSizes()
    {
        loader_11_1_1.x=0                 ; loader_11_1_1.y=0                       ; loader_11_1_1.width = leftItem.width     ; loader_11_1_1.height = leftItem.height       ;
        loader_12_1_1.x=0                 ; loader_12_1_1.y=0                       ; loader_12_1_1.width = leftItem.width     ; loader_12_1_1.height = halfHeight            ;
        loader_12_2_1.x=0                 ; loader_12_2_1.y= halfHeight             ; loader_12_2_1.width = leftItem.width     ; loader_12_2_1.height = halfHeight            ;
        loader_13_1_1.x=0                 ; loader_13_1_1.y=0                       ; loader_13_1_1.width = leftItem.width     ; loader_13_1_1.height = thirdHeigt            ;
        loader_13_2_1.x=0                 ; loader_13_2_1.y= thirdHeigt             ; loader_13_2_1.width = leftItem.width     ; loader_13_2_1.height = thirdHeigt            ;
        loader_13_3_1.x=0                 ; loader_13_3_1.y= thirdHeigt*2           ; loader_13_3_1.width = leftItem.width     ; loader_13_3_1.height = thirdHeigt            ;
        loader_22_1_1.x=0                 ; loader_22_1_1.y=0                       ; loader_22_1_1.width = leftItem.width/2   ; loader_22_1_1.height = halfHeight            ;
        loader_22_2_1.x=0                 ; loader_22_2_1.y= halfHeight             ; loader_22_2_1.width = leftItem.width/2   ; loader_22_2_1.height = halfHeight            ;
        loader_22_1_2.x= leftItem.width/2 ; loader_22_1_2.y=0                       ; loader_22_1_2.width = leftItem.width/2   ; loader_22_1_2.height = halfHeight            ;
        loader_22_2_2.x= leftItem.width/2 ; loader_22_2_2.y= halfHeight             ; loader_22_2_2.width = leftItem.width/2   ; loader_22_2_2.height = halfHeight            ;
        loader_23_1_1.x=0                 ; loader_23_1_1.y=0                       ; loader_23_1_1.width = leftItem.width/2   ; loader_23_1_1.height = thirdHeigt            ;
        loader_23_2_1.x=0                 ; loader_23_2_1.y= thirdHeigt             ; loader_23_2_1.width = leftItem.width/2   ; loader_23_2_1.height = thirdHeigt            ;
        loader_23_3_1.x=0                 ; loader_23_3_1.y= thirdHeigt*2           ; loader_23_3_1.width = leftItem.width/2   ; loader_23_3_1.height = thirdHeigt            ;
        loader_23_1_2.x= leftItem.width/2 ; loader_23_1_2.y=0                       ; loader_23_1_2.width = leftItem.width/2   ; loader_23_1_2.height = thirdHeigt            ;
        loader_23_2_2.x= leftItem.width/2 ; loader_23_2_2.y= thirdHeigt             ; loader_23_2_2.width = leftItem.width/2   ; loader_23_2_2.height = thirdHeigt            ;
        loader_23_3_2.x= leftItem.width/2 ; loader_23_3_2.y= thirdHeigt*2           ; loader_23_3_2.width = leftItem.width/2   ; loader_23_3_2.height = thirdHeigt            ;
        loader_23___1.x= leftItem.width/2 ; loader_23___1.y=0                       ; loader_23___1.width = leftItem.width/2   ; loader_23___1.height = thirdHeigt*2          ;
        loader_23___2.x= leftItem.width/2 ; loader_23___2.y= thirdHeigt             ; loader_23___2.width = leftItem.width/2   ; loader_23___2.height = thirdHeigt*2          ;
        loader_23___3.x= leftItem.width/2 ; loader_23___3.y=0                       ; loader_23___3.width = leftItem.width/2   ; loader_23___3.height = thirdHeigt*2          ;
        loader_23___4.x= leftItem.width/2 ; loader_23___4.y= thirdHeigt             ; loader_23___4.width = leftItem.width/2   ; loader_23___4.height = thirdHeigt*2          ;
        loader_right_full.x= 0            ; loader_right_full.y= 0                  ; loader_right_full.width= rightItem.width ; loader_right_full.height= rightItem.height   ;
        loader_right_top.x = 0            ; loader_right_top.y = 0                  ; loader_right_top.width = rightItem.width ; loader_right_top.height = rightItem.height/2 ;
        loader_right_bot.x = 0            ; loader_right_bot.y = rightItem.height/2 ; loader_right_bot.width = rightItem.width ; loader_right_bot.height = rightItem.height/2 ;
    }

    Item{
        id: leftItem
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right:rightItem.left

        Loader{ id: loader_11_1_1 }
        Loader{ id: loader_12_1_1 }
        Loader{ id: loader_12_2_1 }
        Loader{ id: loader_13_1_1 }
        Loader{ id: loader_13_2_1 }
        Loader{ id: loader_13_3_1 }
        Loader{ id: loader_22_1_1 }
        Loader{ id: loader_22_2_1 }
        Loader{ id: loader_22_1_2 }
        Loader{ id: loader_22_2_2 }
        Loader{ id: loader_23_1_1 }
        Loader{ id: loader_23_2_1 }
        Loader{ id: loader_23_3_1 }
        Loader{ id: loader_23_1_2 }
        Loader{ id: loader_23_2_2 }
        Loader{ id: loader_23_3_2 }
        Loader{ id: loader_23___1 }
        Loader{ id: loader_23___2 }
        Loader{ id: loader_23___3 }
        Loader{ id: loader_23___4 }

    }
    Item{
        id: rightItem
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        width: 150
        Loader{ id: loader_right_full  }
        Loader{ id: loader_right_top   }
        Loader{ id: loader_right_bot   }
    }

    function resetGraphicsState(){
        loader_11_1_1.sourceComponent = undefined
        loader_12_1_1.sourceComponent = undefined
        loader_12_2_1.sourceComponent = undefined
        loader_13_1_1.sourceComponent = undefined
        loader_13_2_1.sourceComponent = undefined
        loader_13_3_1.sourceComponent = undefined
        loader_22_1_1.sourceComponent = undefined
        loader_22_2_1.sourceComponent = undefined
        loader_22_1_2.sourceComponent = undefined
        loader_22_2_2.sourceComponent = undefined
        loader_23_1_1.sourceComponent = undefined
        loader_23_2_1.sourceComponent = undefined
        loader_23_3_1.sourceComponent = undefined
        loader_23_1_2.sourceComponent = undefined
        loader_23_2_2.sourceComponent = undefined
        loader_23_3_2.sourceComponent = undefined
        loader_23___1.sourceComponent = undefined
        loader_23___2.sourceComponent = undefined
        loader_23___3.sourceComponent = undefined
        loader_23___4.sourceComponent = undefined
        loader_right_full.sourceComponent = undefined
        loader_right_top.sourceComponent = undefined
        loader_right_bot.sourceComponent = undefined
    }
    function syncLoader(loader)
    {

        if(loader.sourceComponent == nodeGraphP) graphP.setState(true,loader.x+x+50,loader.y+y+25,loader.width-56,loader.height-31)
        if(loader.sourceComponent == nodeGraphV) graphV.setState(true,loader.x+x+50,loader.y+y+25,loader.width-56,loader.height-31)
        if(loader.sourceComponent == nodeGraphF) graphF.setState(true,loader.x+x+50,loader.y+y+25,loader.width-56,loader.height-31)

        if(loader.sourceComponent == nodeGraphFiCO2mm)     graphFiCO2mm.setState(true,loader.x+x+50,loader.y+y+25,loader.width-56,loader.height-31)
        if(loader.sourceComponent == nodeGraphFiCO2pers) graphFiCO2pers.setState(true,loader.x+x+50,loader.y+y+25,loader.width-56,loader.height-31)

        if(loader.sourceComponent == nodeLoopPV) loopPV.setState(true,loader.x+x+ 3,loader.y+y+25,loader.width- 9,loader.height-31)
        if(loader.sourceComponent == nodeLoopFV) loopFV.setState(true,loader.x+x+ 3,loader.y+y+25,loader.width- 9,loader.height-31)
        if(loader.sourceComponent == nodeLoopFP) loopFP.setState(true,loader.x+x+ 3,loader.y+y+25,loader.width- 9,loader.height-31)
    }
    function syncGraphic()
    {
        refreshLoadersSizes()
        graphicManager.stopAll()
        syncLoader(loader_11_1_1)
        syncLoader(loader_12_1_1)
        syncLoader(loader_12_2_1)
        syncLoader(loader_13_1_1)
        syncLoader(loader_13_2_1)
        syncLoader(loader_13_3_1)
        syncLoader(loader_22_1_1)
        syncLoader(loader_22_2_1)
        syncLoader(loader_22_1_2)
        syncLoader(loader_22_2_2)
        syncLoader(loader_23_1_1)
        syncLoader(loader_23_2_1)
        syncLoader(loader_23_3_1)
        syncLoader(loader_23_1_2)
        syncLoader(loader_23_2_2)
        syncLoader(loader_23_3_2)
        syncLoader(loader_23___1)
        syncLoader(loader_23___2)
        syncLoader(loader_23___3)
        syncLoader(loader_23___4)
       // console.log(graphP.isOn + " " +graphV.isOn + " " +graphF.isOn)
        graphicManager.startAll()
    }

    function setNodeToLoader(nodeStr, loader)
    {
        if      ( nodeStr  == "NodeP"           ) loader.sourceComponent = nodeGraphP
        else if ( nodeStr  == "NodeV"           ) loader.sourceComponent = nodeGraphV
        else if ( nodeStr  == "NodeF"           ) loader.sourceComponent = nodeGraphF
        else if ( nodeStr  == "NodeCO2pers"     ) loader.sourceComponent = nodeGraphFiCO2pers
        else if ( nodeStr  == "NodeCO2mm"       ) loader.sourceComponent = nodeGraphFiCO2mm
        else if ( nodeStr  == "NodeLoopPV"      ) loader.sourceComponent = nodeLoopPV
        else if ( nodeStr  == "NodeLoopFV"      ) loader.sourceComponent = nodeLoopFV
        else if ( nodeStr  == "NodeLoopFP"      ) loader.sourceComponent = nodeLoopFP
        else if ( nodeStr  == "NodeISV"         ) loader.sourceComponent = nodeISV
        else if ( nodeStr  == "NodeColumns"     ) loader.sourceComponent = nodeColumns
        else if ( nodeStr  == "NodeDynLyng"     ) loader.sourceComponent = nodeDynLyng
        else if ( nodeStr  == "NodeAlarms"      ) loader.sourceComponent = nodeAlarms
        else if ( nodeStr  == "NodeMonit"       ) loader.sourceComponent = nodeMonit
        else loader.sourceComponent = nodeEmpty

    }

    Component.onCompleted: {
        refreshLoadersSizes()
       setState(["NodeP", "NodeV", "NodeF","NodeCO2pers","NodeCO2mm","NodeLoopPV"])

    }

    function setState(gList)
    {
        var listLeft  = []
        var listMid   = []
        var listRight = []

        for(var i = 0; i< gList.length; i++)
        {
            if(gList[i] == "NodeP" || gList[i] == "NodeV" || gList[i] == "NodeF" || gList[i] == "NodeCO2mm" || gList[i] == "NodeCO2pers")
            {
                listLeft.push(gList[i])
            }
            else if(gList[i] == "NodeLoopPV" || gList[i] == "NodeLoopFV" || gList[i] == "NodeLoopFP"
                    || gList[i] == "NodeCO2" || gList[i] == "NodeISV"|| gList[i] == "NodeColumns" || gList[i] == "NodeDynLyng")
            {
                listMid.push(gList[i])
            }
            else if(gList[i] == "NodeAlarms" || gList[i] == "NodeMonit")
            {
                listRight.push(gList[i])
            }
        }
        var listLeftMid = listLeft.concat(listMid)


        resetGraphicsState()

        if(listRight.length != 0)
        {
            item1.state = "rightColumnOn"
            if(listRight.length == 1)
            {
                setNodeToLoader(listRight[0], loader_right_full)
            }
            else if(listRight.length == 2)
            {
                setNodeToLoader(listRight[0], loader_right_top)
                setNodeToLoader(listRight[1], loader_right_bot)
            }
        }
        else item1.state = "rightColumnOff"

        if(listLeftMid.length == 1) setNodeToLoader(listLeftMid[0], loader_11_1_1)
        else if (listLeftMid.length == 2)
        {
                setNodeToLoader(listLeftMid[0], loader_12_1_1)
                setNodeToLoader(listLeftMid[1], loader_12_2_1)
        }
        else if (listLeftMid.length == 3)
        {
            if(listLeft.length == 0 || listLeft.length == 3)
            {
                setNodeToLoader(listLeftMid[0], loader_13_1_1)
                setNodeToLoader(listLeftMid[1], loader_13_2_1)
                setNodeToLoader(listLeftMid[2], loader_13_3_1)
            }
            else if(listLeft.length == 1)
            {
                setNodeToLoader(listLeftMid[0], loader_13_1_1)
                setNodeToLoader(listLeftMid[1], loader_23___3)
                setNodeToLoader(listLeftMid[2], loader_23___4)
            }
            else if(listLeft.length == 2)
            {
                setNodeToLoader(listLeftMid[0], loader_22_1_1)
                setNodeToLoader(listLeftMid[1], loader_22_2_1)
                setNodeToLoader(listLeftMid[2], loader_22_1_2)
                setNodeToLoader("empty"       , loader_22_2_2)
            }
        }
        else if (listLeftMid.length == 4)
        {
            setNodeToLoader(listLeftMid[0], loader_22_1_1)
            setNodeToLoader(listLeftMid[1], loader_22_2_1)
            setNodeToLoader(listLeftMid[2], loader_22_1_2)
            setNodeToLoader(listLeftMid[3], loader_22_2_2)
        }
        else if (listLeftMid.length == 5)
        {
            if(listLeft.length == 0)
            {
                setNodeToLoader(listLeftMid[0], loader_23_1_1)
                setNodeToLoader(listLeftMid[1], loader_23_2_1)
                setNodeToLoader(listLeftMid[2], loader_23_3_1)
                setNodeToLoader(listLeftMid[3], loader_22_2_1)
                setNodeToLoader(listLeftMid[4], loader_22_2_2)
            }
            else if(listLeft.length == 1)
            {
                setNodeToLoader(listLeftMid[0], loader_13_1_1)
                setNodeToLoader(listLeftMid[1], loader_23_2_1)
                setNodeToLoader(listLeftMid[2], loader_23_3_1)
                setNodeToLoader(listLeftMid[3], loader_23_2_2)
                setNodeToLoader(listLeftMid[4], loader_23_3_2)
            }
            else if(listLeft.length == 2)
            {
                setNodeToLoader(listLeftMid[0], loader_22_1_1)
                setNodeToLoader(listLeftMid[1], loader_22_2_1)
                setNodeToLoader(listLeftMid[2], loader_23_1_2)
                setNodeToLoader(listLeftMid[3], loader_23_2_2)
                setNodeToLoader(listLeftMid[4], loader_23_3_2)
            }
            else if(listLeft.length == 3)
            {
                setNodeToLoader(listLeftMid[0], loader_23_1_1)
                setNodeToLoader(listLeftMid[1], loader_23_2_1)
                setNodeToLoader(listLeftMid[2], loader_23_3_1)
                setNodeToLoader(listLeftMid[3], loader_22_1_2)
                setNodeToLoader(listLeftMid[4], loader_22_2_2)
            }
            else if(listLeft.length == 4)
            {
                setNodeToLoader(listLeftMid[0], loader_23_1_1)
                setNodeToLoader(listLeftMid[1], loader_23_2_1)
                setNodeToLoader(listLeftMid[2], loader_23_3_1)
                setNodeToLoader(listLeftMid[3], loader_23_1_2)
                setNodeToLoader(listLeftMid[4], loader_23___4)
            }
            else if(listLeft.length == 5)
            {
                setNodeToLoader(listLeftMid[0], loader_23_1_1)
                setNodeToLoader(listLeftMid[1], loader_23_2_1)
                setNodeToLoader(listLeftMid[2], loader_23_3_1)
                setNodeToLoader(listLeftMid[3], loader_23_1_2)
                setNodeToLoader(listLeftMid[4], loader_23_2_2)
            }
        }
        else if (listLeftMid.length == 6)
        {
            setNodeToLoader(listLeftMid[0], loader_23_1_1)
            setNodeToLoader(listLeftMid[1], loader_23_2_1)
            setNodeToLoader(listLeftMid[2], loader_23_3_1)
            setNodeToLoader(listLeftMid[3], loader_23_1_2)
            setNodeToLoader(listLeftMid[4], loader_23_2_2)
            setNodeToLoader(listLeftMid[5], loader_23_3_2)
        }
        syncGraphic()

    }

    Component{
        id: nodeGraphP
        NodeLineP{
        }
    }
    Component{
        id: nodeGraphV
        NodeLineV{
        }
    }
    Component{
        id: nodeGraphF
        NodeLineF{
        }
    }
    Component{
        id: nodeGraphFiCO2pers
        NodeLineCO2pers{
        }
    }
    Component{
        id: nodeGraphFiCO2mm
        NodeLineCO2mm{
        }
    }
    Component{
        id: nodeLoopPV
        NodeLoopPV{
        }
    }
    Component{
        id: nodeLoopFV
        NodeLoopFV{
        }
    }
    Component{
        id: nodeLoopFP
        NodeLoopFP{
        }
    }
    Component{
        id: nodeISV
        NodeEmpty{
            titleText: "iSV граф"
        }
    }
    Component{
        id: nodeColumns
        NodeEmpty{
            titleText: "колонки"
        }
    }
    Component{
        id: nodeDynLyng
        NodeEmpty{
            titleText: "динамическое лёгкое"
        }
    }
    Component{
        id: nodeAlarms
        NodeAlarms{
        }
    }
    Component{
        id: nodeMonit
        NodeMonit{
        }
    }
    Component{
        id: nodeEmpty
        NodeEmpty{

            titleText: "пустота"
        }
    }

//    ModeGraphicDialog{
//        id: mgd
//        anchors.centerIn: parent
//        visible: false
//    }
}

