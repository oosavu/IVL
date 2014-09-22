import QtQuick 2.0

StyleRectangle {
    property bool active: true
    property alias text: butText.text;
    width: 98
    height: 48
    x:1
    y:1
    color: area.pressed? mainItem.okColor : active? mainItem.buttonColor: mainItem.errorColor
    signal clicked


    StyleText{
        wrapMode: Text.WordWrap
        anchors.centerIn: parent
        id: butText
    }

    MouseArea{
        visible: parent.active
        id: area
        anchors.fill: parent
        onClicked: parent.clicked()
    }
}
