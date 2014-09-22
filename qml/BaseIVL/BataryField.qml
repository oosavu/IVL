import QtQuick 2.0
import "styleTypes"
StyleRectangle {
    Canvas{
        id: batCanvas
        anchors.fill: parent
        onPaint: {
            var ctx = getContext('2d');
            ctx.strokeStyle = "white";
            ctx.fillStyle = "#666666"
            ctx.lineWidth = 3;
            ctx.beginPath();
            ctx.moveTo(5,5)
            ctx.lineTo(5, batCanvas.height - 5)
            ctx.lineTo(batCanvas.width - 15, batCanvas.height - 5)
            ctx.lineTo(batCanvas.width - 15,  5)
            ctx.closePath()
            ctx.fill();
            ctx.stroke();

//            ctx.beginPath();
//            ctx.moveTo(batCanvas.width - 10, batCanvas.height - 10)
//            ctx.lineTo(batCanvas.width - 10, 10)
//            ctx.stroke()
//            ctx.beginPath();
//            ctx.moveTo(batCanvas.width - 10, batCanvas.height - 10)
//            ctx.lineTo(batCanvas.width - 10, 10)
//            ctx.stroke()
//            ctx.beginPath();
//            ctx.moveTo(batCanvas.width - 10, batCanvas.height - 10)
//            ctx.lineTo(batCanvas.width - 10, 10)
//            ctx.stroke()

            ctx.lineWidth = 3;
            ctx.beginPath();
            ctx.moveTo(batCanvas.width - 10, batCanvas.height - 10)
            ctx.lineTo(batCanvas.width - 10, 10)
            ctx.stroke()


        }
    }

}
