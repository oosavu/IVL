import QtQuick 2.0
import "../styleTypes"
StyleRectangle {
    width: 94
    height: 196
    property var minEL
    property var maxEL
    property var param
    property alias unit: unitText.text
    property alias titletext: titleText.text

    function radiusRect(ctx, x, y, w, h, tl, tr, br, bl){
        var r = x + w,
            b = y + h;

        ctx.beginPath();
        ctx.moveTo(x+tl, y);
        ctx.lineTo(r-(tr), y);
        ctx.quadraticCurveTo(r, y, r, y+tr);
        ctx.lineTo(r, b-br);
        ctx.quadraticCurveTo(r, b, r-br, b);
        ctx.lineTo(x+bl, b);
        ctx.quadraticCurveTo(x, b, x, b-bl);
        ctx.lineTo(x, y+tl);
        ctx.quadraticCurveTo(x, y, x+tl, y);
        ctx.fill()
        ctx.stroke();

    }
    function drawCursor(ctx, persent){
        ctx.beginPath();
        var curDotY = Math.round(25+(height - 30)*persent)
        ctx.moveTo(20, curDotY)
        ctx.lineTo(27, curDotY-4);
        ctx.lineTo(27, curDotY+4);
        ctx.closePath()
        ctx.fill()
        ctx.stroke();

    }
    Canvas{
        //antialiasing: true
        anchors.fill: parent
        onPaint: {
            var ctx = getContext('2d');
            ctx.strokeStyle = "white";
            ctx.fillStyle = "#660000"
            ctx.lineWidth = 1;
            var fullHeight = height - 30
            var minmax = maxEL.maxValue - minEL.minValue
            var minpers = (minEL.value - minEL.minValue)/minmax
            var maxpers = (maxEL.value - minEL.minValue)/minmax
            var currpers = (param.value - minEL.minValue)/minmax

            ctx.strokeStyle = "#FF0000";
            ctx.fillStyle = "#550000"
            radiusRect(ctx, 5, 25, 15, (1 - maxpers)*fullHeight , 0, 0, 0, 0)
            ctx.strokeStyle = "#00FF00";
            ctx.fillStyle = "#005500"
            drawCursor(ctx, 1-currpers)
            radiusRect(ctx, 5, 25+(1 - maxpers)*fullHeight+1, 15, (maxpers - minpers)*fullHeight-2, 0, 0, 0, 0)
            ctx.strokeStyle = "#FF0000";
            ctx.fillStyle = "#550000"
            radiusRect(ctx, 5, 25+(1 - minpers)*fullHeight, 15, (minpers)*fullHeight, 0, 0, 0, 0)

            drawCursor(ctx, 1-minpers)
            drawCursor(ctx, 1-maxpers)
        }
    }

    StyleTextM{
        id: titleText
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
    }
    StyleTextS{
        id: unitText
        x: 30
        y: 25
        width: parent.width - 30
        height: 15
    }
    ErrorLevelEditField{
        text: "max"
        param: maxEL
        x: 30
        y: 40
    }
    StyleTextL{
        x: 30
        y: 100
        text: param.value
        width: parent.width - 30
        height: 25
    }

    ErrorLevelEditField{
        text: "min"
        param: minEL
        x: 30
        y: 145
    }


}
