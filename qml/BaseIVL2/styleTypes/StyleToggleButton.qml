import QtQuick 2.0

import "../styleTypes"

StyleRectangle{

    property var boolItem
    property bool itemValue: boolItem.currValue

    onItemValueChanged: valSetSlider()

    function valSetSlider()
    {
      //  console.log("fio02error:" + itemValue)
        if(itemValue == true) slideItem.x = -5
        else slideItem.x = -container.width*3/4 + 5
    }

    width:96
    height: 46
    id:container
    clip: true

    Item {
        anchors.margins: 1
        id: slideItem
        width: parent.width*7/4
        height: parent.height
        Row{

            anchors.fill: parent
            Rectangle{
                width: parent.width*3/7
                height: parent.height
                color: "green"
                StyleText{
                    anchors.centerIn: parent
                    text:"Вкл"
                }
            }
            StyleRectangle{
                y:5
                height: parent.height - 10
                width: parent.width/7
                color: "blue"
            }


            Rectangle{
                height: parent.height
                width: parent.width*3/7
                color: "red"
                StyleText{
                    anchors.centerIn: parent
                    text:"Выкл"
                }
            }
        }

        MouseArea {
            id: area
            anchors.fill: parent
            drag.target: slideItem
            drag.axis: Drag.XAxis
            drag.minimumX: -container.width*3/4 + 5
            drag.maximumX: -5
            onReleased: {
                if (drag.active)
                {
                    if(slideItem.x<(-container.width*3/4+5+2) || slideItem.x > -7)
                        boolItem.currValue = !boolItem.currValue
                    else parent.parent.valSetSlider()
                }
            }
        }
    }


}
