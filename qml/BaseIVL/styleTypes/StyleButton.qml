import QtQuick 2.0

StyleRectangle {
    property bool active: true
    property alias text: butText.text;
    width: 98
    height: 48
    x:1
    y:1
    color: area.pressed? "lightgreen" : active? "gray": "lightred"
    signal clicked


    StyleTextS{
        wrapMode: Text.WordWrap
        id: butText
        anchors.fill: parent
        text: parent.text

    }

    MouseArea{
        visible: parent.active
        id: area
        anchors.fill: parent
        onClicked: parent.clicked()
    }
}
