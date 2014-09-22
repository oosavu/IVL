import QtQuick 2.0
import "../styleTypes"
NodeEmpty {
    id: nodeLineF
    titleText: qsTr("Flow (l/min)")

    frameItem.children: [
        Canvas{
            id: canvas
            anchors.leftMargin:   50
            anchors.bottomMargin: 3
            anchors.rightMargin:  3
            renderTarget : Canvas.Image
            renderStrategy:Canvas.Immediate
            anchors.fill: frameItem
            onPaint: {
                var maxHeight = height - 1
                var ctx = getContext('2d');
                ctx.reset()
                ctx.fillStyle = "gray"
                ctx.clearRect(0,0,width,height)
                ctx.strokeStyle = "gray";
                ctx.lineWidth = 1;

                drawLine(ctx,   0,         0,     0,  maxHeight    )
                drawLine(ctx,   0,         0, width,          0,  4)
                drawLine(ctx,   0, maxHeight, width,  maxHeight,  4)
                drawLine(ctx,   0,  height/2, width,    height/2   )


            }
        },

        Item {
            id: valuesItem
            anchors.top: canvas.top
            anchors.right: canvas.left
            anchors.left: frameItem.left
            anchors.bottom: canvas.bottom
            anchors.rightMargin: 4
            StyleText {
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.left: parent.left
                height: 20
                id: maxText
                text:    if(graphF.maxPositiveVal == 100  ) "0.1"
                    else if(graphF.maxPositiveVal == 250  ) "0.25"
                    else if(graphF.maxPositiveVal == 500  ) "0.5"
                    else if(graphF.maxPositiveVal == 1000 ) "1.0"
                    else if(graphF.maxPositiveVal == 2000 ) "2.0"
                    else if(graphF.maxPositiveVal == 4000 ) "4.0"
                    else if(graphF.maxPositiveVal == 10000) "10.0"
                    else  "err"
                font.pixelSize: 20
                color: "gray"
            }
            StyleText {
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.left: parent.left
                height: 20
                id: minText
                text:    if(graphF.maxPositiveVal == 100  ) "-0.1"
                    else if(graphF.maxPositiveVal == 250  ) "-0.25"
                    else if(graphF.maxPositiveVal == 500  ) "-0.5"
                    else if(graphF.maxPositiveVal == 1000 ) "-1.0"
                    else if(graphF.maxPositiveVal == 2000 ) "-2.0"
                    else if(graphF.maxPositiveVal == 4000 ) "-4.0"
                    else if(graphF.maxPositiveVal == 10000) "-10.0"
                    else  "err"
                font.pixelSize: 20
                color: "gray"
            }
            StyleText {
                anchors.right: parent.right
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.topMargin: canvas.height/2 - height/2
                height: 20
                id: zeroText
                text: qsTr("0")
                font.pixelSize: 20
                color: "gray"
            }
        }
    ]
}
