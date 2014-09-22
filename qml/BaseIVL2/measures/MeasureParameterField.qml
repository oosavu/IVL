import QtQuick 2.0
import CppImport 1.0
//import "../styleTypes"

Rectangle {
    id: rectangle1
    color: "#666666"
    border.color: "#FFFFFF"

    property var measParam
    property var unitStr
    property var nameStr
    width: 123
    height: 123

    states:[
        State{
            name: "full"
            when: height>70
        },
        State{
            name: "simple"
            when: height<=70
        }
    ]

    Item{
        anchors.fill: parent
        visible: parent.state == "simple"

        Text {
            id: titleTextSimple

            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: parent.width/3
            color: "white"
            font.pixelSize:  height*2/4
            text: nameStr+":"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight
        }

        Text {
            id: valueTextSimple
            anchors.left:   titleTextSimple.right
            anchors.right:  unitTextSimple.left
            anchors.top:    parent.top
            anchors.bottom: parent.bottom
            color: if(measParam.errorLevel == MeasureParameter.MErrorNo)"white"
                else "red"
            font.pixelSize:  height*3/4
            text: if(measParam.avilability) measParam.value
                else "--.-"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        Text {
            id: unitTextSimple
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            width: parent.width/4
            color: "white"
            font.pixelSize:  height*2/5
            text: unitStr
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight
        }

    }

    Item{
        anchors.fill: parent
        visible: parent.state == "full"


        Text {
            id: titleText
            anchors.top: parent.top
            anchors.left: parent.left
            width: parent.width*3/5
            height: parent.height/3
            color: "white"
            font.pixelSize:  height*3/4
            text: nameStr
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight
        }

        Text {
            id: unitText
            anchors.top: parent.top
            anchors.left: titleText.right
            anchors.right: parent.right
            anchors.bottom: titleText.bottom
            color: "white"
            font.pixelSize:  height/2
            text: "(" + unitStr + ")"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
        }

        Text {
            id: valueText
            anchors.top: titleText.bottom
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            width: parent.width*2/3
            color: if(measParam.errorLevel == MeasureParameter.MErrorNo)"white"
                   else "red"
            font.pixelSize:  height*4/5
            text: if(measParam.avilability) measParam.value
                  else "--.-"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight
        }

        ListModel{
            id: miniTrendModel
            ListElement{val: 323; isErrored: false; isAvilable: true}
            ListElement{val:  23; isErrored: true; isAvilable: true}
            ListElement{val: 423; isErrored: false; isAvilable: true}
            ListElement{val: 123; isErrored: true; isAvilable: true}
            ListElement{val: 623; isErrored: false; isAvilable: true}
            ListElement{val: 310; isErrored: false; isAvilable: true}
            ListElement{val: 233; isErrored: true; isAvilable: true}

        }

//        Canvas{
//            id: miniTrendCanvas
//            anchors.top: titleText.bottom
//            anchors.right: valueText.left
//            anchors.bottom: parent.bottom
//            anchors.left: parent.left
//            anchors.margins: 2
//            renderTarget : Canvas.Image
//            antialiasing:true
//            onPaint:
//            {
//                var ctx = getContext('2d');
//                var cloumnWidth = width/miniTrendModel.count

//                ctx.reset()
//                ctx.fillStyle = "#666666";
//                ctx.lineCap = 'round'
//                ctx.clearRect(0, 0, width, height);
//                ctx.lineCap = "round"
//                ctx.lineWidth = cloumnWidth

//                var maxTrendValue = 0
//                for(var i = 0;i < miniTrendModel.count; i++)
//                {
//                    if(maxTrendValue < miniTrendModel.get(i).val) maxTrendValue = miniTrendModel.get(i).val
//                }

//                for(var i = 0; i < miniTrendModel.count; i++)
//                {
//                    if(miniTrendModel.get(i).isErrored)ctx.strokeStyle = "#FF0000"
//                    else ctx.strokeStyle = "#00FF00"
//                    ctx.beginPath()
//                    ctx.moveTo(width/(miniTrendModel.count*2) + i*width/miniTrendModel.count +2, height - cloumnWidth/2 )
//                    ctx.lineTo(width/(miniTrendModel.count*2) + i*width/miniTrendModel.count +2, height - cloumnWidth/2 - ( height - cloumnWidth)* miniTrendModel.get(i).val/maxTrendValue )
//                    ctx.stroke()
//                }
//            }
//        }
    }
}
