import QtQuick 2.0
import "../styleTypes"
StyleRectangle {

    width: parent.width
    height: parent.childrenHeight

    property string name: "NoName"
    property var currVal: currVE
    property var elMin:   elVExpMin
    property var elMax:   elVExpMax
    property string unit: "popugais"

    Connections
    {
        target: currVal
        onValueChanged: canvas.requestPaint()
        onAvilabilityChanged: canvas.requestPaint()
    }
    Connections
    {
        target: elMin
        onValueChanged: canvas.requestPaint()
    }
    Connections
    {
        target: elMax
        onCurrValueChanged: canvas.requestPaint()
    }

    Text{
        id: nameText
        text: name
        color: "white"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 20
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        width: parent.width/4
    }

    Canvas{
        id: canvas
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: nameText.right
        onPaint:{
            console.log("awsedasfasfsd" + elMin.currValue + " " + currVal.value + " " + elMax.currValue )
            var ctx = getContext('2d');
           // ctx.reset()
            ctx.fillStyle = "#00FF00";
            ctx.lineCap = 'round'
            ctx.clearRect(0, 0, canvas.width, canvas.height);

            var fullInterval = elMax.maxValue - elMin.minValue
            var persentMin = (elMin.currValue - elMin.minValue)/fullInterval
            var persentVal = (currVal.value - elMin.minValue)/fullInterval
            var persentMax = (elMax.currValue - elMin.minValue)/fullInterval
            var pixMin = persentMin*(width-14) + 14
            var pixVal = persentVal*(width-14) + 14
            var pixMax = persentMax*(width-14) + 14

            //ctx.lineTo(width - ctx.lineWidth , height/2)
            ctx.lineWidth = 8;
            ctx.strokeStyle = "#DD2222"
            ctx.beginPath()
            ctx.moveTo(14 , height/2)
            ctx.lineTo(pixMin , height/2)
            ctx.stroke()

            ctx.lineWidth = 8;
            ctx.strokeStyle = "#22DD22"
            ctx.beginPath()
            ctx.moveTo(pixMin , height/2)
            ctx.lineTo(pixMax , height/2)
            ctx.stroke()

            ctx.lineWidth = 8;
            ctx.strokeStyle = "#DD2222"
            ctx.beginPath()
            ctx.moveTo(pixMax , height/2)
            ctx.lineTo(width - 14 , height/2)
            ctx.stroke()

            ctx.lineWidth = 14
            ctx.strokeStyle = "#FF0000";
            ctx.beginPath()
            ctx.moveTo(pixMin , height/2)
            ctx.lineTo(pixMin+ 0.01 , height/2)
            ctx.stroke()

            ctx.lineWidth = 14
            ctx.strokeStyle = "#FF0000";
            ctx.beginPath()
            ctx.moveTo(pixMax , height/2)
            ctx.lineTo(pixMax+ 0.01 , height/2)
            ctx.stroke()

            ctx.lineWidth = 12
            ctx.strokeStyle = "#FF9E00";
            ctx.beginPath()
            ctx.moveTo(pixVal , height/2)
            ctx.lineTo(pixVal+ 0.01 , height/2)
            ctx.stroke()
        }
    }
}

