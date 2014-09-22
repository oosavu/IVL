import QtQuick 2.0
import "../styleTypes"
import CppImport 1.0

StyleRectangle {

    property var mp1
    property var mp2
    property string name1: " "
    property string name2: " "
    property string unit1: " "
    property string unit2: " "
    property var el1min
    property var el1max
    width: 123
    height: 123

    Text{
        id: titleText
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height/6
        text: name1 + " / " + name2
        color: "white"
        font.pixelSize: height - 2
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }
    Item{
        id:mp1Item
        anchors.top: titleText.bottom
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.right: parent.horizontalCenter
        Text{
            id: val1Text
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: parent.height/2
            text: if(mp1 == undefined) "none"
               else  if(mp1.avilability)mp1.value
              else "--.-"
            font.pixelSize: height - 2
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            color: if(mp1 == undefined) "white"
                else if(mp1.errorLevel == MeasureParameter.MErrorNo)"white"
                else "red"
        }
        Text{
            id: el1Text
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height: parent.height/4
            font.pixelSize: height - 2
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text: if(el1min == undefined || el1max == undefined) " "
            else el1min.trueValue + "/" + el1max.trueValue
            color: "white"
        }
        Text{
            id: unit1Text
            anchors.top: val1Text.bottom
            anchors.bottom: el1Text.top
            anchors.left: parent.left
            anchors.right: parent.right
            font.pixelSize: height - 2
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text: unit1
            color: "white"
        }
    }

    Item{
        id:mp2Item
        anchors.top: titleText.bottom
        anchors.left: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        Text{
            id: val2Text
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: parent.height/2
            text: if(mp2 == undefined) ""
                  else  if(mp2.avilability)mp2.value
                 else "--.-"
            font.pixelSize: height - 2
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            color:if(mp2 == undefined) "black"
                else if(mp2.errorLevel == MeasureParameter.MErrorNo)"white"
                else "red"
        }
        Text{
            id: el2Text
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height: parent.height/4
            font.pixelSize: height - 2
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            //text: //el2min.trueValue + "/" + el2max.trueValue
            color: "white"
        }
        Text{
            id: unit2Text
            anchors.top: val2Text.bottom
            anchors.bottom: el2Text.top
            anchors.left: parent.left
            anchors.right: parent.right
            font.pixelSize: height - 2
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text: unit2
            color: "white"
        }
    }

}
