import QtQuick 2.0
import CppImport 1.0
import "../styleTypes"
Canvas {
    renderTarget : Canvas.Image

    anchors.fill: parent

    property int pixIn20cm: if     (rendererP.maxP == GraphicRendererP.P_BOUND_20 )rendererP.dataRect.height/2
                            else if(rendererP.maxP == GraphicRendererP.P_BOUND_40 )rendererP.dataRect.height/3
                            else if(rendererP.maxP == GraphicRendererP.P_BOUND_60 )rendererP.dataRect.height/4
                            else if(rendererP.maxP == GraphicRendererP.P_BOUND_80 )rendererP.dataRect.height/5
                            else if(rendererP.maxP == GraphicRendererP.P_BOUND_100)rendererP.dataRect.height/6
                            else if(rendererP.maxP == GraphicRendererP.P_BOUND_140)rendererP.dataRect.height/8
                            else if(rendererP.maxP == GraphicRendererP.P_BOUND_200)rendererP.dataRect.height/11

    onPixIn20cmChanged: requestPaint()
    StyleTextS{
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 20
        text: "P (mm H2O)"
    }
    StyleTextS{
        x:0
        y:rendererP.dataRect.y - height/2
        text: if(rendererP.maxP == GraphicRendererP.P_BOUND_20 ) "20"
         else if(rendererP.maxP == GraphicRendererP.P_BOUND_40 ) "40"
         else if(rendererP.maxP == GraphicRendererP.P_BOUND_60 ) "60"
         else if(rendererP.maxP == GraphicRendererP.P_BOUND_80 ) "80"
         else if(rendererP.maxP == GraphicRendererP.P_BOUND_100) "100"
         else if(rendererP.maxP == GraphicRendererP.P_BOUND_140) "140"
         else if(rendererP.maxP == GraphicRendererP.P_BOUND_200) "200"
    }
    StyleTextS{
        x:0
        y:if(rendererP.maxP == GraphicRendererP.P_BOUND_20 )      rendererP.dataRect.y + rendererP.dataRect.height - pixIn20cm - height/2
          else if(rendererP.maxP == GraphicRendererP.P_BOUND_40 ) rendererP.dataRect.y + rendererP.dataRect.height - pixIn20cm - height/2
          else if(rendererP.maxP == GraphicRendererP.P_BOUND_60 ) rendererP.dataRect.y + rendererP.dataRect.height - pixIn20cm - height/2
          else if(rendererP.maxP == GraphicRendererP.P_BOUND_80 ) rendererP.dataRect.y + rendererP.dataRect.height - pixIn20cm- height/2
          else if(rendererP.maxP == GraphicRendererP.P_BOUND_100) rendererP.dataRect.y + rendererP.dataRect.height - pixIn20cm- height/2
          else if(rendererP.maxP == GraphicRendererP.P_BOUND_140) rendererP.dataRect.y + rendererP.dataRect.height - pixIn20cm- height/2
          else if(rendererP.maxP == GraphicRendererP.P_BOUND_200) rendererP.dataRect.y + rendererP.dataRect.height - pixIn20cm - height/2
        text: "0.0"
    }
    StyleTextS{
        x:0
        y:rendererP.dataRect.y + rendererP.dataRect.height - height/2
        text: "-20"
    }
    onPaint: {


        var ctx = getContext('2d');

        ctx.reset()
        ctx.fillStyle = "gray"
        ctx.clearRect(0,0,width,height)
        ctx.strokeStyle = "white";
        ctx.lineWidth = 1;

        ctx.beginPath();
            ctx.moveTo(rendererP.dataRect.x, rendererP.dataRect.y  -5    )
            ctx.lineTo(rendererP.dataRect.x, rendererP.dataRect.y + rendererP.dataRect.height + 5    )
        ctx.stroke();
        ctx.beginPath();
            ctx.moveTo(rendererP.dataRect.x, rendererP.dataRect.y + rendererP.dataRect.height - pixIn20cm)
            ctx.lineTo(rendererP.dataRect.x + rendererP.dataRect.width,rendererP.dataRect.y + rendererP.dataRect.height - pixIn20cm)
        ctx.stroke();

        ctx.strokeStyle =  Qt.rgba(0.5, 0.5, 0.5, 1);
        ctx.beginPath();
            ctx.moveTo(rendererP.dataRect.x+1, rendererP.dataRect.y + rendererP.dataRect.height   )
            ctx.lineTo(rendererP.dataRect.x + rendererP.dataRect.width,rendererP.dataRect.y + rendererP.dataRect.height)
        ctx.stroke();
        ctx.beginPath();
            ctx.moveTo(rendererP.dataRect.x+1, rendererP.dataRect.y  )
            ctx.lineTo(rendererP.dataRect.x + rendererP.dataRect.width,rendererP.dataRect.y )
        ctx.stroke();
    }
}
