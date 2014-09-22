import QtQuick 2.0
import CppImport 1.0
import "../styleTypes"
StyleRectangle {
    id: elRedactor

    anchors.fill: parent

    property string name: "MV"
    property var currVal: currVE
    property var elMin:   elMVmin
    property var elMax:   elMVmax
    property string unit: "L/min"

    Text{
        anchors.margins: 3
        id: titleTextRedactor
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height: 40
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 18
        color: "white"
        text: "Редактирование " + name
    }
    EditedParameter{
        id: epdMax
        anchors.margins: 3
        anchors.left: parent.left
        anchors.top: titleTextRedactor.bottom
        tp: elMax
        name: "max"
        unit: unit
        onAccepted: {
            dp.acceptValue()
            focus = false
        }
        onClicked: focus = true
    }
    EditedParameter{
        anchors.margins: 3
        id: epdMin
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        tp: elMin
        name: "min"
        unit: unit
        onAccepted: {
            dp.acceptValue()
            focus = false
        }
        onClicked: focus = true
    }
    Item{
        anchors.left: parent.left
        anchors.right: canvasRedact.left
        anchors.top: epdMax.bottom
        anchors.bottom: epdMin.top
        Text{
            anchors.centerIn: parent
            text: if(currVal.avilability) currVal.value
              else "---"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 30
            color: "white"
        }
    }
    Connections
    {
        target: currVal
        onValueChanged: canvasRedact.requestPaint()
        onAvilabilityChanged: canvasRedact.requestPaint()
    }
    Connections
    {
        target: elMin
        onCurrValueChanged: canvasRedact.requestPaint()
    }
    Connections
    {
        target: elMax
        onCurrValueChanged: canvasRedact.requestPaint()
    }

    Canvas{
        anchors.margins: 3
        anchors.left: epdMin.right
        anchors.right: parent.right
        anchors.top:  titleTextRedactor.bottom
        anchors.bottom: parent.bottom
        id: canvasRedact
        onPaint: {
            //console.log("me painted!!!!!!!!!11111111!!!!!!!!!!!")
            var ctx = getContext('2d');
            ctx.clearRect(0, 0, canvasRedact.width, canvasRedact.height);

            var columnXMin = width/3
            var columnXMax = 2*width/3
            var columnYMin = 20
            var columnYMax = height - 20
            var fullheight = columnYMax - columnYMin

            var persentMaxPix = fullheight*(elMax.currValue   - elMin.minValue) / (elMax.maxValue - elMin.minValue)
            var persentMinPix = fullheight*(elMin.currValue   - elMin.minValue) / (elMax.maxValue - elMin.minValue)
            var persentValPix = fullheight*(currVal.value - elMin.minValue) / (elMax.maxValue - elMin.minValue)

            ctx.color = "black"

            ctx.fillStyle = "red"
            ctx.beginPath()
            ctx.moveTo( columnXMin , columnYMin               )
            ctx.lineTo( columnXMax , columnYMin               )
            ctx.lineTo( columnXMax , columnYMax-persentMaxPix )
            ctx.lineTo( columnXMin , columnYMax-persentMaxPix )
            ctx.closePath()
            ctx.stroke()
            ctx.fill()

            ctx.fillStyle = "green"
            ctx.beginPath()
            ctx.moveTo( columnXMin , columnYMax-persentMaxPix )
            ctx.lineTo( columnXMax , columnYMax-persentMaxPix )
            ctx.lineTo( columnXMax , columnYMax-persentMinPix )
            ctx.lineTo( columnXMin , columnYMax-persentMinPix )
            ctx.closePath()
            ctx.stroke()
            ctx.fill()

            ctx.fillStyle = "red"
            ctx.beginPath()
            ctx.moveTo( columnXMin , columnYMax-persentMinPix )
            ctx.lineTo( columnXMax , columnYMax-persentMinPix )
            ctx.lineTo( columnXMax , columnYMax               )
            ctx.lineTo( columnXMin , columnYMax               )
            ctx.closePath()
            ctx.stroke()
            ctx.fill()

            ctx.fillStyle = "blue"
            ctx.beginPath()
            ctx.moveTo( columnXMin , columnYMax-persentValPix - 5 )
            ctx.lineTo( columnXMax , columnYMax-persentValPix - 5 )
            ctx.lineTo( columnXMax , columnYMax-persentValPix + 5 )
            ctx.lineTo( columnXMin , columnYMax-persentValPix + 5 )
            ctx.closePath()
            ctx.stroke()
            ctx.fill()

        }
    }
}
