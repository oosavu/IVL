import QtQuick 2.0
import CppImport 1.0

StyleRectangle{

    id: editParameter

    property var tpScope:({}) //: ({tp: undefined, name: "noName", unit: "popugais", trueString: "Вкл", falseString: "Выкл", changeInterval: function() { return 1; }})

    property var tp: tpScope.tp != undefined? tpScope.tp: undefined
    property string name: tpScope.name != undefined? tpScope.name: "noname"
    property string unit: tpScope.unit != undefined? tpScope.unit: "noUnit"
    property string trueString: tpScope.trueString != undefined? tpScope.trueString: ""
    property string falseString: tpScope.falseString != undefined? tpScope.falseString: ""
    property int changeInterval: if(tpScope.changeIntervalFunc  != undefined) tpScope.changeIntervalFunc()
                                 else if(tp != undefined){
                                                                       if(tp.maxValue - tp.minValue < 10)  1
                                                                       else if(tp.maxValue - tp.minValue < 100)  10
                                                                       else if(tp.maxValue - tp.minValue < 500)  50
                                                                       else  100
                                 } else 1

//    property string valTextStr: tpScope.valTextFunc != undefined? tpScope.valTextFunc(): tp.currValue
//    property string minTextStr: tp.minValue
//    property string maxTextStr: tp.maxValue

    property bool isBoolParameter: if(tp != undefined) tp.minValue == 0 && tp.maxValue == 1;
                                else false

    signal clicked
    signal accepted
    signal canceled

    onClicked: {
       // if (setParField.state == "hidden") setParField.state = "simpleRedact"
        focus = true
    }
    onAccepted: {
//        if (setParField.state == "simpleRedact")
//        {
//            ventModeManager.acceptModeVent()
//            setParField.state = "hidden"
//        }
        focus = false
    }
    onCanceled: {
        tp.restoreValue()
        focus = false
    }

    border.width: 2
    radius: 5
    border.color: mainItem.panelElementColor
    color: if(tp == undefined) mainItem.panelColor;
      else if (tp.errorLevel == TunningParameter.TPErrorNo) mainItem.panelColor;
      else if(tp.errorLevel == TunningParameter.TPError1) mainItem.warningColor;
      else mainItem.errorColorFon;
    width: 170
    height: 116
    opacity: tpScope == undefined? 0: 1

    onTpScopeChanged: canvas.requestPaint()
    Connections{
        ignoreUnknownSignals: true
        target: if(tp!= undefined) tp
                else parent //лишь бы что то
        onCurrValueChanged:   canvas.requestPaint()
        onTrueValueChanged:  canvas.requestPaint()
        onErrorLevelChanged:  canvas.requestPaint()
    }
    focus: false
    onFocusChanged:    canvas.requestPaint()
    onVisibleChanged:   canvas.requestPaint()

    Canvas{
        anchors.fill: parent
        id: canvas
        renderTarget : Canvas.Image
        antialiasing:true
        onPaint: {
            var ctx = getContext('2d');
            ctx.reset()
            ctx.fillStyle = mainItem.panelColor
            ctx.lineCap = 'round'
            ctx.clearRect(0, 0, canvas.width, canvas.height);

            if(isBoolParameter && tp != undefined)
            {
                if(parent.focus == true)
                {
                    drawSmothRect(ctx,x,y,width,height,5,mainItem.panelElementColor)
                    drawSmothRect(ctx,x+10,y+35,width-20,height-45,5,mainItem.panelColor)
                }
                ctx.strokeStyle = mainItem.panelElementColor;
                ctx.lineWidth = 8;
                ctx.beginPath()
                ctx.arc(0,itemTexts.y+itemTexts.height/2,itemTexts.x - 10,-Math.PI/5,Math.PI/5, false)
                ctx.stroke()
                ctx.strokeStyle = mainItem.buttonColor;
                ctx.lineWidth = 12;
                ctx.beginPath()
                if(tp.currValue == 0)  ctx.arc(0,itemTexts.y+itemTexts.height/2,itemTexts.x - 10,-Math.PI/5,-Math.PI/5+0.01, false)
                else if(tp.currValue == 1)  ctx.arc(0,itemTexts.y+itemTexts.height/2,itemTexts.x - 10,Math.PI/5-0.01,Math.PI/5, false)
                ctx.stroke()
            }
            else if (!isBoolParameter && tp != undefined){

                ctx.fillStyle = mainItem.panelColor;
                ctx.clearRect(0, 0, canvas.width, canvas.height);
                var outRad  = height/2+5
                var rad = outRad - 10
                var persentValue = getPersentParameter(tp.currValue,tp.minValue,tp.maxValue)
                var persentTrueValue = getPersentParameter(tp.trueValue,tp.minValue,tp.maxValue)
                var bottomOffset = 5
                var offsetAngle  = Math.asin(bottomOffset/rad)
                var startAngle   = Math.PI - offsetAngle
                var fullAngle    = Math.PI + 2 * offsetAngle
                ctx.translate(canvas.width/2, outRad+20)
                if(parent.focus == true)
                {
                    drawSmothRect(ctx,x - width/2,y-outRad - 20,width,height,5, mainItem.panelElementColor)
                    ctx.lineWidth = 1;
                    if(tp.errorLevel == TunningParameter.TPErrorNo) ctx.fillStyle = mainItem.panelColor;
                    else if(tp.errorLevel == TunningParameter.TPError1) ctx.fillStyle = "#FF00FF";
                    else ctx.fillStyle = mainItem.errorColorFon;
                    ctx.beginPath()
                    ctx.arc(0,0, outRad, startAngle - 0.12 ,  startAngle + fullAngle + 0.12 , false);
                    ctx.closePath()
                    ctx.fill()
                }
                ctx.strokeStyle = mainItem.panelElementColor;
                ctx.lineWidth = 8;
                ctx.beginPath()
                ctx.arc(0,0, rad, startAngle,  startAngle + fullAngle, false);
                ctx.stroke()
                if(tp.errorLevel == TunningParameter.TPErrorNo)  ctx.strokeStyle = mainItem.buttonColor;
                else ctx.strokeStyle = mainItem.errorColor
                ctx.lineWidth = 8 ;
                ctx.beginPath()
                ctx.arc(0,0, rad, startAngle, startAngle + fullAngle* persentValue, false);
                ctx.stroke()
                ctx.strokeStyle = mainItem.okColor;
                ctx.lineWidth = 12 ;
                ctx.beginPath()
                ctx.arc(0,0, rad, startAngle + fullAngle* persentTrueValue - 0.01,  startAngle + fullAngle* persentTrueValue, false);
                ctx.stroke()
                if(tp.errorLevel == TunningParameter.TPErrorNo)  ctx.strokeStyle = mainItem.buttonColor;
                else ctx.strokeStyle = mainItem.errorColor
                ctx.lineWidth = 12 ;
                ctx.beginPath()
                ctx.arc(0,0, rad, startAngle + fullAngle* persentValue - 0.01,  startAngle + fullAngle* persentValue, false);
                ctx.stroke()
            }
        }
    }
    MouseArea{
        visible: parent.focus != true
        anchors.fill: parent
        onClicked:  parent.clicked()
    }
    StyleText {
        visible: tp != undefined
        id: titleText
        width: parent.width
        height: 26
        text: name
        font.pixelSize: 22
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Item {
        visible: !isBoolParameter && tp != undefined
        id: item1
        height: 22
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        StyleText {
            visible: editParameter.focus == true
            id: minText
            text: tp == undefined? "error": tpScope.minTextFunc != undefined? tpScope.minTextFunc(): tp.minValue
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.top: parent.top
            horizontalAlignment: Text.AlignLeft
            font.pixelSize: 18
        }
        StyleText {
            visible: editParameter.focus == true
            id: maxText
            text: tp == undefined? "error": tpScope.maxTextFunc != undefined? tpScope.maxTextFunc(): tp.maxValue
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.top: parent.top
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 18
        }
        StyleText {
            id: unitText
            text: unit
            anchors.centerIn: parent
            font.pixelSize: 18
        }
    }

    StyleText {
        visible: !isBoolParameter && tp != undefined
        id: valueText
        text: tp == undefined? "error!!!": tpScope.valTextFunc != undefined? tpScope.valTextFunc(): tp.currValue
        font.bold: true
        font.pixelSize: 38
        anchors.horizontalCenter: parent.horizontalCenter
        y: parent.height/2
    }

    Item{
        visible: parent.focus == true  && !isBoolParameter && tp != undefined
        id: editValueItem
        anchors.fill: parent
        MouseArea{
            id: acceptArea
            anchors.top: parent.verticalCenter
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            onClicked: {
                editParameter.accepted()
            }
        }
        MouseArea{
            id: minusArea
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.horizontalCenter
            anchors.bottom: parent.verticalCenter
            onClicked: {
                tp.currValue -= changeInterval
            }
        }
        MouseArea{
            id: plusArea
            anchors.top: parent.top
            anchors.left: parent.horizontalCenter
            anchors.right: parent.right
            anchors.bottom: parent.verticalCenter
            onClicked: {
                tp.currValue += changeInterval
            }
        }
    }

    StyleText{
        visible: parent.focus && !isBoolParameter && tp != undefined
        width: 30
        height: 30
        text: "-"
        anchors.left: parent.left
        anchors.top: parent.top
        font.pixelSize: 30
        font.bold: true
    }
    StyleText{
        visible: parent.focus && !isBoolParameter && tp != undefined
        width: 30
        height: 30
        text: "+"
        anchors.right: parent.right
        anchors.top: parent.top
        font.pixelSize: 30
        font.bold: true
    }

    Item {
        visible: isBoolParameter
        id: itemTexts
        y: 10
        height: parent.height - 45
        anchors.left: parent.left
        anchors.leftMargin: 45
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        StyleText{
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.verticalCenter
            text: falseString
            font.pixelSize:
                if(tp == undefined) 23
                else if(tp.currValue == false)22
                else 18

            color:
                if(tp == undefined) mainItem.textColor
                else if(tp.currValue == false) mainItem.textColor
                   else mainItem.offTextColor

            MouseArea{
                visible: editParameter.focus == true
                anchors.fill: parent
                onClicked: {
                    tp.currValue = 0
                }
            }
        }
        StyleText{
            anchors.top: parent.verticalCenter
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            text: trueString
            font.pixelSize: if(tp == undefined) 23
                            else if(tp.currValue == true) 22
                            else 18

            color: if(tp == undefined) mainItem.textColor
                   else if(tp.currValue == true) mainItem.textColor
                   else mainItem.offTextColor

            MouseArea{
                visible: editParameter.focus == true
                anchors.fill: parent
                onClicked: {
                    tp.currValue = 1
                }
            }
        }
        MouseArea{
            visible: editParameter.focus == true
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.right: itemTexts.left
            onClicked: {
                parent.focus = false
            }
        }
    }


    function drawSmothRect(_ctx,x,y,w,h,rad,color)
    {
        _ctx.fillStyle = color
        _ctx.beginPath()
        _ctx.moveTo(x+w-rad , y)
        _ctx.quadraticCurveTo(x+w,y,x+w,y+rad)
        _ctx.lineTo(x+w , y+h-rad)
        _ctx.quadraticCurveTo(x+w,y+h,x+w-rad,y+h)
        _ctx.lineTo(x+rad , y+h )
        _ctx.quadraticCurveTo(x,y+h,x,y+h-rad)
        _ctx.lineTo(x , y+rad )
        _ctx.quadraticCurveTo(x,y,x+rad,y)
        _ctx.closePath()
        _ctx.fill()
    }

    function getPersentParameter(val,min,max)
    {
        return (val - min)/(max - min);
    }

}
