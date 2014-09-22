import QtQuick 2.0
import "../styleTypes"
NodeEmpty {

    titleText: qsTr("Петля P:V")

    frameItem.children: [
        Canvas{

            id: canvas
            renderTarget : Canvas.Image
            renderStrategy:Canvas.Immediate

            anchors.leftMargin: 3
            anchors.rightMargin: 3
            anchors.bottomMargin: 3
            anchors.fill: frameItem

            onPaint: {
                var ctx = getContext('2d');
                ctx.reset()
                ctx.fillStyle = "gray"
                ctx.clearRect(0,0,width,height)
                ctx.strokeStyle = "gray";
                ctx.lineWidth = 1;

                drawLine(ctx,   0,         height*10/11,     width,  height*10/11  )
                drawLine(ctx,   width/11,  0, width/11,    height   )


            }
        },

        Text {
            anchors.top: canvas.top
            anchors.left: canvas.left
            anchors.leftMargin: canvas.width/11
            height: 20
            width: 50
            id: maxVText
            text:    if(loopPV.maxPositiveValY == 100  ) "0.1"
                else if(loopPV.maxPositiveValY == 200  ) "0.2"
                else if(loopPV.maxPositiveValY == 500  ) "0.5"
                else if(loopPV.maxPositiveValY == 1000 ) "1.0"
                else if(loopPV.maxPositiveValY == 2000 ) "2.0"
                else if(loopPV.maxPositiveValY == 5000 ) "5.0"
                else if(loopPV.maxPositiveValY == 10000) "10.0"
                else  "err"
            verticalAlignment: Text.AlignBottom
            horizontalAlignment: Text.AlignLeft
            font.pixelSize: 20
            color: "gray"
        },

        Text {
            anchors.right: canvas.right
            anchors.bottom: canvas.bottom
            anchors.bottomMargin: canvas.height/11
            height: 20
            width: 50
            id: maxPText
            text:    if(loopPV.maxPositiveValX == 200 ) "20"
                else if(loopPV.maxPositiveValX == 400 ) "40"
                else if(loopPV.maxPositiveValX == 600 ) "60"
                else if(loopPV.maxPositiveValX == 800 ) "80"
                else if(loopPV.maxPositiveValX == 1000) "100"
                else if(loopPV.maxPositiveValX == 1500) "150"
                else if(loopPV.maxPositiveValX == 2000) "200"
                else  "err"
            verticalAlignment: Text.AlignBottom
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 20
            color: "gray"
        }
    ]


}
