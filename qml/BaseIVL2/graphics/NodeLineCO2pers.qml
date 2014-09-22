import QtQuick 2.0
import "../styleTypes"

NodeEmpty {
    id: nodeLineF
    titleText: qsTr("EtCO2(%)")

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
                drawLine(ctx,   0, maxHeight, width,  maxHeight  )
                drawLine(ctx,   0,  height/2, width,    height/2,  4)
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
                text: "10"
                font.pixelSize: 20
                color: "gray"
            }
            StyleText {
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.left: parent.left
                height: 20
                id: minText
                text:   "0"
                font.pixelSize: 20
                color: "gray"
            }

        }
    ]
}
