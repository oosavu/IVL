import QtQuick 2.0
import "../styleTypes"
NodeEmpty {
    id: nodeLineP
    titleText: qsTr("Paw (cmH2O)")

    property int nullPos:canvas.height*(graphP.maxPositiveVal)/(graphP.maxPositiveVal - graphP.maxNegativeVal)
    onNullPosChanged: canvas.requestPaint()
    onWidthChanged: canvas.requestPaint()

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

                drawLine(ctx,   0,          0,     0,  maxHeight    )
                drawLine(ctx,   0,          0, width,            0,  4)
                drawLine(ctx,   0,  maxHeight, width,  maxHeight  ,  4)
                drawLine(ctx,   0,    nullPos, width,  nullPos        )
            }
        },
        Item {
            id: valuesItem
            anchors.top: canvas.top
            anchors.right: canvas.left
            anchors.left: frameItem.left
            anchors.bottom: canvas.bottom
            anchors.rightMargin: 4
            Text {
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.left: parent.left
                height: 20
                id: maxText
                text:    if(graphP.maxPositiveVal == 200 ) "20"
                    else if(graphP.maxPositiveVal == 400 ) "40"
                    else if(graphP.maxPositiveVal == 600 ) "60"
                    else if(graphP.maxPositiveVal == 800 ) "80"
                    else if(graphP.maxPositiveVal == 1000) "100"
                    else if(graphP.maxPositiveVal == 1500) "150"
                    else if(graphP.maxPositiveVal == 2000) "200"
                    else  "1000"
                verticalAlignment: Text.AlignTop
                horizontalAlignment: Text.AlignRight
                font.pixelSize: 20
                color: "gray"
            }
            Text {
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.left: parent.left
                height: 20
                id: minText
                text: qsTr("-20")
                verticalAlignment: Text.AlignTop
                horizontalAlignment: Text.AlignRight
                font.pixelSize: 20
                color: "gray"
            }
            Text {
                anchors.right: parent.right
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.topMargin: canvas.height*(graphP.maxPositiveVal)/(graphP.maxPositiveVal - graphP.maxNegativeVal) - height/2
                height: 20
                id: zeroText
                text: qsTr("0")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignRight
                font.pixelSize: 20
                color: "gray"
            }
        }
    ]
}
