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
        text: "F (л/мин)"
    }
    StyleTextS{
        x:0
        y:rendererFlow.dataRect.y - 5
        text: if(rendererFlow.maxF == GraphicRendererF.F_BOUND_10  ) "10"
         else if(rendererFlow.maxF == GraphicRendererF.F_BOUND_25  ) "25"
         else if(rendererFlow.maxF == GraphicRendererF.F_BOUND_50  ) "50"
         else if(rendererFlow.maxF == GraphicRendererF.F_BOUND_100 ) "100"
         else if(rendererFlow.maxF == GraphicRendererF.F_BOUND_200 ) "200"
         else if(rendererFlow.maxF == GraphicRendererF.F_BOUND_400 ) "400"
         else if(rendererFlow.maxF == GraphicRendererF.F_BOUND_1000) "1000"
    }
    StyleTextS{
        x:0
        y:rendererFlow.dataRect.y + rendererFlow.dataRect.height/2 -height/2
        text: "0.0"
    }
    StyleTextS{
        x:0
        y:rendererFlow.dataRect.y + rendererFlow.dataRect.height - height/2
        text: if(rendererFlow.maxF == GraphicRendererF.F_BOUND_10  ) "-10"
         else if(rendererFlow.maxF == GraphicRendererF.F_BOUND_25  ) "-25"
         else if(rendererFlow.maxF == GraphicRendererF.F_BOUND_50  ) "-50"
         else if(rendererFlow.maxF == GraphicRendererF.F_BOUND_100 ) "-100"
         else if(rendererFlow.maxF == GraphicRendererF.F_BOUND_200 ) "-200"
         else if(rendererFlow.maxF == GraphicRendererF.F_BOUND_400 ) "-400"
         else if(rendererFlow.maxF == GraphicRendererF.F_BOUND_1000) "-1000"
    }
    onPaint: {
        var ctx = getContext('2d');

        ctx.reset()
        ctx.fillStyle = "gray"
        ctx.clearRect(0,0,width,height)
        ctx.strokeStyle = "white";
        ctx.lineWidth = 1;

        ctx.beginPath();
            ctx.moveTo(rendererFlow.dataRect.x, rendererFlow.dataRect.y  -5    )
            ctx.lineTo(rendererFlow.dataRect.x, rendererFlow.dataRect.y + rendererFlow.dataRect.height + 5    )
        ctx.stroke();
        ctx.beginPath();
            ctx.moveTo(rendererFlow.dataRect.x, rendererFlow.dataRect.y + rendererFlow.dataRect.height/2 )
            ctx.lineTo(rendererFlow.dataRect.x + rendererFlow.dataRect.width,rendererFlow.dataRect.y + rendererFlow.dataRect.height/2)
        ctx.stroke();

        ctx.strokeStyle =  Qt.rgba(0.5, 0.5, 0.5, 1);
        ctx.beginPath();
            ctx.moveTo(rendererFlow.dataRect.x+1, rendererFlow.dataRect.y + rendererFlow.dataRect.height   )
            ctx.lineTo(rendererFlow.dataRect.x + rendererFlow.dataRect.width,rendererFlow.dataRect.y + rendererFlow.dataRect.height)
        ctx.stroke();
        ctx.beginPath();
            ctx.moveTo(rendererFlow.dataRect.x+1, rendererFlow.dataRect.y  )
            ctx.lineTo(rendererFlow.dataRect.x + rendererFlow.dataRect.width,rendererFlow.dataRect.y )
        ctx.stroke();
    }
}
