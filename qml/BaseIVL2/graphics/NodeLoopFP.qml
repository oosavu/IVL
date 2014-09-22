import QtQuick 2.0
import "../styleTypes"

NodeEmpty {
    onWidthChanged: canvas.requestPaint()
    titleText: qsTr("Петля F:P")

    frameItem.children: [
        Canvas{

            id: canvas
            anchors.leftMargin: 3
            anchors.rightMargin: 3
            anchors.bottomMargin: 3
            anchors.fill: frameItem

            renderTarget  : Canvas.Image
            renderStrategy: Canvas.Immediate
            onPaint: {
                var ctx = getContext('2d');
                ctx.reset()
                ctx.fillStyle = "gray"
                ctx.clearRect(0,0,width,height)
                ctx.strokeStyle = "gray";
                ctx.lineWidth = 1;

                drawLine(ctx,   0,         height*10/11,     width,  height*10/11  )
                drawLine(ctx,   width/2,  0, width/2,    height   )
            }
        },

        Text {
            anchors.left: canvas.left
            anchors.bottom: canvas.bottom
            anchors.bottomMargin: canvas.height/11
            height: 20
            width: 50
            id: minFText
            text:    if(loopFP.maxPositiveValX == 100  ) "-0.1"
                else if(loopFP.maxPositiveValX == 250  ) "-0.25"
                else if(loopFP.maxPositiveValX == 500  ) "-0.5"
                else if(loopFP.maxPositiveValX == 1000 ) "-1.0"
                else if(loopFP.maxPositiveValX == 2000 ) "-2.0"
                else if(loopFP.maxPositiveValX == 4000 ) "-4.0"
                else if(loopFP.maxPositiveValX == 10000) "-10.0"
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
            id: maxFText
            text:    if(loopFP.maxPositiveValX == 100  ) "0.1"
                else if(loopFP.maxPositiveValX == 250  ) "0.25"
                else if(loopFP.maxPositiveValX == 500  ) "0.5"
                else if(loopFP.maxPositiveValX == 1000 ) "1.0"
                else if(loopFP.maxPositiveValX == 2000 ) "2.0"
                else if(loopFP.maxPositiveValX == 4000 ) "4.0"
                else if(loopFP.maxPositiveValX == 10000) "10.0"
                else  "err"
            verticalAlignment: Text.AlignBottom
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 20
            color: "gray"
        },

        Text {
            anchors.top: canvas.top
            anchors.left: canvas.horizontalCenter
            anchors.leftMargin: 3
            height: 20
            width: 50
            id: maxPText
            text:    if(loopFP.maxPositiveValY == 200 ) "20"
                else if(loopFP.maxPositiveValY == 400 ) "40"
                else if(loopFP.maxPositiveValY == 600 ) "60"
                else if(loopFP.maxPositiveValY == 800 ) "80"
                else if(loopFP.maxPositiveValY == 1000) "100"
                else if(loopFP.maxPositiveValY == 1500) "150"
                else if(loopFP.maxPositiveValY == 2000) "200"
                else  "err"
            verticalAlignment: Text.AlignBottom
            horizontalAlignment: Text.AlignLeft
            font.pixelSize: 20
            color: "gray"
        }
    ]



}
