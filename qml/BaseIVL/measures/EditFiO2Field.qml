import QtQuick 2.0
import "../styleTypes"
StyleRectangle {
    width: 94
    height: 196

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
        var curDotY = Math.round(70+persent)
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
            var fullHeight = 100

            var minpers = (dpFiO2.value - elFiO2.value)/100
            var maxpers = (dpFiO2.value + elFiO2.value)/100
            var currpers = currO2.value/100
            var setpers = dpFiO2.value/100

            ctx.strokeStyle = "#FF0000";
            ctx.fillStyle = "#550000"
            radiusRect(ctx, 5, 70, 15, (1 - maxpers)*fullHeight , 0, 0, 0, 0)
            drawCursor(ctx, 1-maxpers)

            ctx.strokeStyle = "#00FF00";
            ctx.fillStyle = "#005500"
            drawCursor(ctx, 1-setpers)
            radiusRect(ctx, 5, 70+(1 - maxpers)*fullHeight+1, 15, (maxpers - minpers)*fullHeight-2, 0, 0, 0, 0)
            ctx.strokeStyle = "#FF0000";
            ctx.fillStyle = "#550000"
            radiusRect(ctx, 5, 70+(1 - minpers)*fullHeight, 15, (minpers)*fullHeight, 0, 0, 0, 0)

            drawCursor(ctx, 1-minpers)

            ctx.strokeStyle = "#FFFF00";
            ctx.fillStyle = "#550000"
            drawCursor(ctx, 1-currpers)
        }
    }

    StyleTextM{
        text: "FiO2 | %"
        id: titleText
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
    }
    StyleToggleButton{
        x: 5
        y: 25
        width: parent.width - 10
        height: 40
        boolItem: onFiO2error
    }
    StyleTextL{
        x: 30
        y: 100
        text: dpFiO2.value
        width: parent.width - 30
        height: 25
    }
    ErrorLevelEditField{
        text: "+/-"
        param: elFiO2
        x: 30
        y: 145
    }
}
