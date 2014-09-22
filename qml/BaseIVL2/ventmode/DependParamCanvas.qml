import QtQuick 2.0
import CppImport 1.0
import "../styleTypes"

StyleRectangle {
    id: styleRectangle1
    width: 100
    height: 130 //parent.height
    property string name: "paramname"
    property int el:  param.errorLevel
    property int val: param.value
    property int min: param.minValue
    property int max: param.maxValue
    property var param

    color:   if(el == AssociatedParameter.APErrorNo) mainItem.panelColor
        else if(el == AssociatedParameter.APError1)  mainItem.warningColor
        else mainItem.errorColorFon


    border.width: 2
    radius: 5
    border.color: mainItem.panelElementColor

    StyleText {
        id: titleText
        text: name
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        font.pixelSize: 18
        height: 25
        color: param.avilability? mainItem.textColor : mainItem.panelElementColor
    }

    Item {
        visible: param.avilability

        id: itemData
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: titleText.bottom
        width: parent.width/2


        StyleText {
            id: valueText
            text: val
            anchors.centerIn: parent
            font.pixelSize: 17
            color: el == AssociatedParameter.APErrorNo? mainItem.okColor: el == AssociatedParameter.APError1? mainItem.warningColor: mainItem.errorColor
        }

        StyleText {
            id: maxText
            text: max
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.margins: 6
            font.pixelSize: 16
        }

        StyleText {
            id: minText
            text: min
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.margins: 6
            font.pixelSize: 17
        }
    }

    onVisibleChanged: dpCanvas.requestPaint()
    Connections{
        target: param
        onValueChanged: dpCanvas.requestPaint()
        onMinValueChanged: dpCanvas.requestPaint()
        onMaxValueChanged: dpCanvas.requestPaint()
        onErrorLevelChanged: dpCanvas.requestPaint()
    }

    Canvas {        
        visible: param.avilability
        id: dpCanvas
        anchors.right: itemData.left
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.top: titleText.bottom

        renderTarget: Canvas.Image
        antialiasing: true

        onPaint: {
            //console.log(width + " " + height)
            var ctx = getContext('2d');
            ctx.reset()
            ctx.fillStyle = mainItem.panelColor;
            ctx.lineCap = 'round'
            ctx.clearRect(0, 0, dpCanvas.width, dpCanvas.height);

            ctx.lineWidth = 15;
            var pixOffset = 20

            ctx.lineWidth = 20;
            ctx.strokeStyle = mainItem.panelElementColor
            ctx.beginPath()
            ctx.moveTo( width/2 , pixOffset )
            ctx.lineTo( width/2 , height - pixOffset )
            ctx.stroke()

            if(val >= min && val <= max)
            {
                var pixPersent = (height - 2*pixOffset)*(val-min)/(max-min)

                ctx.lineWidth = 16;
                ctx.strokeStyle = mainItem.errorColorFon
                ctx.beginPath()
                ctx.moveTo( width/2 , pixOffset )
                ctx.lineTo( width/2 , pixOffset + 0.1 )
                ctx.stroke()
                ctx.beginPath()
                ctx.moveTo( width/2 , height - pixOffset )
                ctx.lineTo( width/2 , height - pixOffset +0.1 )
                ctx.stroke()

                ctx.lineWidth = 12;
                ctx.strokeStyle = mainItem.okColorFon
                ctx.beginPath()
                ctx.moveTo( width/2 , height - pixOffset - pixPersent)
                ctx.lineTo( width/2 , height - pixOffset - pixPersent +0.1 )
                ctx.stroke()
            }
            else if(val < min)
            {
                var pixPersentMin = (height - 2*pixOffset)*(min - val)/(max-val)

                ctx.lineWidth = 16;
                ctx.strokeStyle = mainItem.errorColorFon
                ctx.beginPath()
                ctx.moveTo( width/2 , pixOffset )
                ctx.lineTo( width/2 , pixOffset + 0.1 )
                ctx.stroke()
                ctx.strokeStyle = mainItem.errorColor
                ctx.beginPath()
                ctx.moveTo( width/2 , height - pixOffset  - pixPersentMin)
                ctx.lineTo( width/2 , height - pixOffset  - pixPersentMin +0.1 )
                ctx.stroke()

                ctx.lineWidth = 12;
                ctx.strokeStyle = mainItem.okColorFon
                ctx.beginPath()
                ctx.moveTo( width/2 , height - pixOffset )
                ctx.lineTo( width/2 , height - pixOffset +0.1)
                ctx.stroke()
            }
            else if(val > max)
            {
                var pixPersentMax = (height - 2*pixOffset)*(max - min)/(val - min)

                ctx.lineWidth = 16;
                ctx.strokeStyle = mainItem.errorColorFon
                ctx.beginPath()
                ctx.moveTo( width/2 , height -  pixOffset )
                ctx.lineTo( width/2 , height -  pixOffset + 0.1 )
                ctx.stroke()
                ctx.strokeStyle = mainItem.errorColor
                ctx.beginPath()
                ctx.moveTo( width/2 , height - pixOffset  - pixPersentMax)
                ctx.lineTo( width/2 , height - pixOffset  - pixPersentMax +0.1 )
                ctx.stroke()

                ctx.lineWidth = 12;
                ctx.strokeStyle = mainItem.okColorFon
                ctx.beginPath()
                ctx.moveTo( width/2 ,  pixOffset )
                ctx.lineTo( width/2 ,  pixOffset +0.1)
                ctx.stroke()
            }
        }
    }
}
