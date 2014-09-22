import QtQuick 2.0
import "../styleTypes"
StyleRectangle {
    width: 98
    height: 123
    color: focus == true? "#444444": "black"

    property var param
    property var dp: param[0]
    onDpChanged: canvas.requestPaint()
    property string name: param[1]
    property string unit: param[2]
    property real fullAngle: Math.PI*1.5
    property real delta: (fullAngle - Math.PI)/2
    focus: false
    onFocusChanged: canvas.requestPaint()
    Connections{
        target: ventModeItem
        onAnyParamFocusedChanged: canvas.requestPaint()
    }

    Canvas{
        anchors.margins:2
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.width
        id: canvas
        renderTarget : Canvas.Image
        antialiasing:true
        onPaint: {
            //console.log("paint"+ focus)
            var ctx = getContext('2d');
            ctx.strokeStyle = "white";
            if(parent.focus == true) ctx.fillStyle = "#444444"
            else ctx.fillStyle = "black";
            ctx.lineWidth = 1;
            ctx.fillRect(0, 0, canvas.width, canvas.height);
            //ctx.fillStyle = "black";

            if(dp != 0 && ventModeItem.anyParamFocused == true)
            {
                var persent
               //ctx.moveTo(canvas.width/2,canvas.height/2);
                ctx.save();
                    ctx.translate(canvas.width/2, canvas.width/2)
                    //ctx.scale(1,(canvas.height-10)*2/(canvas.width))
                    ctx.beginPath();
                    ctx.arc(0,0, canvas.width/2,  Math.PI - delta, delta, false);
                    ctx.stroke();
                    ctx.beginPath();
                    ctx.arc(0,0, canvas.width/2-10,  Math.PI - delta, delta, false);
                    ctx.stroke();
                    drawCursor(ctx,getPersentParameter(param[0].trueValue,param[0].minValue,param[0].maxValue),"white",0.2)
                    drawCursor(ctx,getPersentParameter(param[0].value,param[0].minValue,param[0].maxValue),"green",0.2)
                ctx.restore()
            }
        }
    }

    MouseArea{
        anchors.fill: parent
        propagateComposedEvents: true
        onClicked: {
            if (parent.focus == false) parent.focus = true
            else parent.focus = false
            mouse.accepted = false
        }
    }

    Keys.onPressed: {
        if(event.key == Qt.Key_Enter)
        {
            focus = false
            //console.log("enter")
            //active = false
        }
        else if(event.key == Qt.Key_Up)
        {
            dp.value += 1
        }
        else if(event.key == Qt.Key_Down)
        {
            dp.value -= 1
        }
        canvas.requestPaint()
    }



    Text{
        anchors.margins:2
        id:valueText
        anchors.horizontalCenter: parent.horizontalCenter
        y: 25
        height: 32
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        color: "white"
        font.pointSize: 20
        text: dp.value
    }
    Text{
        anchors.margins:8
        id:unitText
        anchors.top: valueText.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: 25

        horizontalAlignment: Text.AlignHCenter
        color: "white"
        font.pointSize: 8
        text:  unit
    }
    Item{
        visible: ventModeItem.anyParamFocused == true
        anchors.margins:2
        id:limitsText
        anchors.bottom: titleText.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 15
        Text{
            id: minText
            anchors.bottom: parent.bottom
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.horizontalCenter
            color: "white"
            font.pointSize: 10
            text: dp.minValue
        }
        Text{
            anchors.bottom: parent.bottom
            anchors.top: parent.top
            anchors.left: parent.horizontalCenter
            anchors.right: parent.right
            horizontalAlignment: Text.AlignRight
            color: "white"
            font.pointSize: 10
            text: dp.maxValue
        }
    }
    Text{
        anchors.margins:3
        id:titleText
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: 25
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        color: "white"
        font.pointSize: 15
        text:if(dp != 0) parent.name
               else ""
    }

    function getPersentParameter(val,min,max)
    {
        return (val - min)/(max - min);
    }
    function drawCursor(ctx, persent, colour, depth)
    {
        ctx.save();
        ctx.strokeStyle = "red";
        ctx.fillStyle = colour;
        ctx.beginPath()
        ctx.arc(0,0, canvas.width/2-10, Math.PI - delta + fullAngle*persent-depth,  Math.PI - delta + fullAngle*persent+depth, false);
        ctx.lineTo(canvas.width/2*Math.cos(Math.PI - delta + fullAngle*persent),canvas.width/2*Math.sin(Math.PI - delta + fullAngle*persent))
        ctx.closePath()
        ctx.fill();
        ctx.stroke();
        ctx.restore();
    }


}
