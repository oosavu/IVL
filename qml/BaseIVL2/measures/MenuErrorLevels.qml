import QtQuick 2.0
import CppImport 1.0
import "../styleTypes"
StyleMenu {
    id: menuErrorLevels

    Text {
        id: titleText
        height: 31
        color: "#ffffff"
        text: qsTr("Пороги тревог")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 23
        anchors.topMargin: 3
        anchors.top: parent.top
    }

    ListModel{
        id: elModel
        Component.onCompleted: {
            append({name: "MV"      , unit: "L/min" , currVal: currVE       , elMin: elMVmin      , elMax: elMVmax      })
            append({name: "Vexp"    , unit: "ml"    , currVal: currVolExp   , elMin: elVExpMin    , elMax: elVExpMax    })
            append({name: "RB"      , unit: "1/min" , currVal: currRB       , elMin: elRBmin      , elMax: elRBmax      })
            append({name: "EtCO2%"  , unit: "%"     , currVal: currEtCO2_pr , elMin: elEtCO2prMin , elMax: elEtCO2prMax })
            append({name: "EtCO2mm" , unit: "mm Hg" , currVal: currEtCO2_mm , elMin: elEtCO2mmMin , elMax: elEtCO2mmMax })
            append({name: "!!SpO2"  , unit: "mm Hg" , currVal: currEtCO2_mm , elMin: elRBmin      , elMax: elRBmax      })
            append({name: "!!PR"    , unit: "mm Hg" , currVal: currEtCO2_mm , elMin: elRBmin      , elMax: elRBmax      })
            append({name: "!!O2"    , unit: "mm Hg" , currVal: currEtCO2_mm , elMin: elRBmin      , elMax: elRBmax      })
            append({name: "P_O2"    , unit: "mm Hg" , currVal: currEtCO2_mm , elMin: elRBmin      , elMax: elRBmax      })
            append({name: "!!P"     , unit: "mm Hg" , currVal: currEtCO2_mm , elMin: elRBmin      , elMax: elRBmax      })
        }
    }

    Item{
        id: paramDialogContainer
        anchors.margins: 3
        anchors.top: titleText.bottom
        anchors.left: paramsMenu.right
        anchors.bottom: styleBut.top
        anchors.right: parent.right

//        ErrorLevelRedactor{name: "MV"      ; unit: "L/min" ; currVal: currVE       ; elMin: elMVmin      ; elMax: elMVmax      ; visible: elView.currentIndex == 0}
//        ErrorLevelRedactor{name: "Vexp"    ; unit: "ml"    ; currVal: currVolExp   ; elMin: elVExpMin    ; elMax: elVExpMax    ; visible: elView.currentIndex == 1}
//        ErrorLevelRedactor{name: "RB"      ; unit: "1/min" ; currVal: currRB       ; elMin: elRBmin      ; elMax: elRBmax      ; visible: elView.currentIndex == 2}
//        ErrorLevelRedactor{name: "EtCO2%"  ; unit: "%"     ; currVal: currEtCO2_pr ; elMin: elEtCO2prMin ; elMax: elEtCO2prMax ; visible: elView.currentIndex == 3}
//        ErrorLevelRedactor{name: "EtCO2mm" ; unit: "mm Hg" ; currVal: currEtCO2_mm ; elMin: elEtCO2mmMin ; elMax: elEtCO2mmMax ; visible: elView.currentIndex == 4}
//        ErrorLevelRedactor{name: "!!SpO2"  ; unit: "mm Hg" ; currVal: currEtCO2_mm ; elMin: elRBmin      ; elMax: elRBmax      ; visible: elView.currentIndex == 5}
//        ErrorLevelRedactor{name: "!!PR"    ; unit: "mm Hg" ; currVal: currEtCO2_mm ; elMin: elRBmin      ; elMax: elRBmax      ; visible: elView.currentIndex == 6}
//        ErrorLevelRedactor{name: "!!O2"    ; unit: "mm Hg" ; currVal: currEtCO2_mm ; elMin: elRBmin      ; elMax: elRBmax      ; visible: elView.currentIndex == 7}
//        ErrorLevelRedactor{name: "P_O2"    ; unit: "mm Hg" ; currVal: currEtCO2_mm ; elMin: elRBmin      ; elMax: elRBmax      ; visible: elView.currentIndex == 8}
//        ErrorLevelRedactor{name: "!!P"     ; unit: "mm Hg" ; currVal: currEtCO2_mm ; elMin: elRBmin      ; elMax: elRBmax      ; visible: elView.currentIndex == 9}
    }

    Item{
        anchors.margins: 3
        id: paramsMenu
        anchors.top: titleText.bottom
        anchors.left: parent.left
        anchors.bottom: styleBut.top
        width: parent.width/2

        ListView{
            id: elView
            interactive: false
            model: elModel
            currentIndex:0
            anchors.fill: parent
            spacing: 3
            delegate: Component{
                StyleRectangle {
                    height: elView.height/10 - 3
                    width: parent.width
                    //property var elStruct
                    color: if(elView.currentIndex == index) mainItem.panelElementColor
                      else  mainItem.panelColor


                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            elView.currentIndex = index
                        }
                    }
                    Connections
                    {
                        target: currVal
                        onValueChanged: canvas.requestPaint()
                        onAvilabilityChanged: canvas.requestPaint()
                    }
                    Connections
                    {
                        target: elMin
                        onCurrValueChanged: canvas.requestPaint()
                    }
                    Connections
                    {
                        target: elMax
                        onCurrValueChanged: canvas.requestPaint()
                    }
                    Text{
                        id: nameText
                        text: name
                        color: if (currVal.errorLevel == MeasureParameter.MErrorNo)"white"
                        else "red"
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        font.pixelSize: 20
                        anchors.top: parent.top
                        anchors.left: parent.left
                        anchors.bottom: parent.bottom
                        width: parent.width/4
                    }
                    Canvas{

                        id: canvas
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.right: parent.right
                        anchors.left: nameText.right
                        onPaint:{
                            var ctx = getContext('2d');
                            // ctx.reset()
                            ctx.fillStyle = mainItem.panelColor;
                            ctx.lineCap = 'round'
                            ctx.clearRect(0, 0, canvas.width, canvas.height);

                            var fullInterval = elMax.maxValue - elMin.minValue
                            var persentMin = (elMin.currValue - elMin.minValue)/fullInterval
                            var persentVal = (currVal.value - elMin.minValue)/fullInterval
                            var persentMax = (elMax.currValue - elMin.minValue)/fullInterval
                            var pixMin = persentMin*(width-14) + 14
                            var pixVal = persentVal*(width-14) + 14
                            var pixMax = persentMax*(width-14) + 14

                            //ctx.lineTo(width - ctx.lineWidth , height/2)
                            ctx.lineWidth = 8;
                            ctx.strokeStyle = mainItem.errorColorFon
                            ctx.beginPath()
                            ctx.moveTo(14 , height/2)
                            ctx.lineTo(pixMin , height/2)
                            ctx.stroke()

                            ctx.lineWidth = 8;
                            ctx.strokeStyle = mainItem.okColorFon
                            ctx.beginPath()
                            ctx.moveTo(pixMin , height/2)
                            ctx.lineTo(pixMax , height/2)
                            ctx.stroke()

                            ctx.lineWidth = 8;
                            ctx.strokeStyle = mainItem.errorColorFon
                            ctx.beginPath()
                            ctx.moveTo(pixMax , height/2)
                            ctx.lineTo(width - 14 , height/2)
                            ctx.stroke()

                            ctx.lineWidth = 14
                            ctx.strokeStyle = mainItem.errorColor
                            ctx.beginPath()
                            ctx.moveTo(pixMin , height/2)
                            ctx.lineTo(pixMin+ 0.01 , height/2)
                            ctx.stroke()

                            ctx.lineWidth = 14
                            ctx.strokeStyle = mainItem.errorColor
                            ctx.beginPath()
                            ctx.moveTo(pixMax , height/2)
                            ctx.lineTo(pixMax+ 0.01 , height/2)
                            ctx.stroke()

                            ctx.lineWidth = 12
                            ctx.strokeStyle = mainItem.buttonColor
                            ctx.beginPath()
                            ctx.moveTo(pixVal , height/2)
                            ctx.lineTo(pixVal+ 0.01 , height/2)
                            ctx.stroke()
                        }
                    }
                }
            }
        }
    }


    StyleOkCancelButtons {
        id: styleBut
        anchors.right: parent.right
        anchors.rightMargin: 3
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 3
        onOkClicked: {
            menuErrorLevels.visible = false
        }
        onCancelClicked: {
            menuErrorLevels.visible = false
        }
    }


}

