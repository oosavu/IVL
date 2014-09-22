import QtQuick 2.0

Rectangle {
    color: "lightgray"
//    border.color: "black"
//    border.width: 2
//    radius: 5
    width: fieldColumn.width+10
    height: fieldColumn.height+25
    property alias fields: fieldColumn.children
    property alias text: titleText.text
    Column{
        y:20
        id: fieldColumn
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Text{
        anchors.horizontalCenter: parent.horizontalCenter
        y: 0
        id: titleText
        text: "nototle"
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        //font.pointSize: 15
    }
}
