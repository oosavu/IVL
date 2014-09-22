import QtQuick 2.0
import CppImport 1.0
import "../styleTypes"
Canvas {
    renderTarget : Canvas.Image


    anchors.fill: parent


    StyleTextS{
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 20
        text: "V (л)"
    }
    StyleTextS{
        x:0
        y:rendererVol.dataRect.y - 5
        text: if(rendererVol.maxV == GraphicRendererV.V_BOUND_01) "0.1"
         else if(rendererVol.maxV == GraphicRendererV.V_BOUND_02) "0.2"
         else if(rendererVol.maxV == GraphicRendererV.V_BOUND_05) "0.5"
         else if(rendererVol.maxV == GraphicRendererV.V_BOUND_1)  "1.0"
         else if(rendererVol.maxV == GraphicRendererV.V_BOUND_2)  "2.0"
         else if(rendererVol.maxV == GraphicRendererV.V_BOUND_5)  "5.0"
         else if(rendererVol.maxV == GraphicRendererV.V_BOUND_100)"100"
    }
    StyleTextS{
        x:0
        y:rendererVol.dataRect.y + rendererVol.dataRect.height/2 - 10
        text: if(rendererVol.maxV == GraphicRendererV.V_BOUND_01) "0.05"
         else if(rendererVol.maxV == GraphicRendererV.V_BOUND_02) "0.1"
         else if(rendererVol.maxV == GraphicRendererV.V_BOUND_05) "0.25"
         else if(rendererVol.maxV == GraphicRendererV.V_BOUND_1)  "0.5"
         else if(rendererVol.maxV == GraphicRendererV.V_BOUND_2)  "1.0"
         else if(rendererVol.maxV == GraphicRendererV.V_BOUND_5)  "2.5"
         else if(rendererVol.maxV == GraphicRendererV.V_BOUND_100)"50"
    }
    StyleTextS{
        x:0
        y:rendererVol.dataRect.y + rendererVol.dataRect.height - 15
        text: "0.0"
    }
    onPaint: {
        var ctx = getContext('2d');

        ctx.reset()
        ctx.fillStyle = "gray"
        ctx.clearRect(0,0,width,height)
        ctx.strokeStyle = "white";
        ctx.lineWidth = 1;
        ctx.beginPath();
            ctx.moveTo(rendererVol.dataRect.x,       rendererVol.dataRect.y  -10    )
            ctx.lineTo(rendererVol.dataRect.x ,
                       rendererVol.dataRect.y + rendererVol.dataRect.height     )
            ctx.lineTo(rendererVol.dataRect.x + rendererVol.dataRect.width,
                       rendererVol.dataRect.y + rendererVol.dataRect.height     )
        ctx.stroke();

        ctx.strokeStyle =  Qt.rgba(0.5, 0.5, 0.5, 1);
        ctx.beginPath();
            ctx.moveTo(rendererVol.dataRect.x+1,       rendererVol.dataRect.y + rendererVol.dataRect.height/2 )
            ctx.lineTo(rendererVol.dataRect.x + rendererVol.dataRect.width,
                       rendererVol.dataRect.y + rendererVol.dataRect.height/2      )
        ctx.stroke();

        ctx.beginPath();
            ctx.moveTo(rendererVol.dataRect.x+1,       rendererVol.dataRect.y   )

            ctx.lineTo(rendererVol.dataRect.x + rendererVol.dataRect.width,
                       rendererVol.dataRect.y )
        ctx.stroke();
    }
}
