import QtQuick 2.0

Item{
    id: item1
    property alias okActive: okButton.active
    property alias cancelActive: cancelButton.active
    signal okClicked
    signal cancelClicked
    width: 200
    height: 50
    StyleButton{
        id: okButton
        x: 1
        y: 1
        text:"OK"
        anchors.right: parent.horizontalCenter
        anchors.rightMargin: 2
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.left: parent.left
        onClicked: parent.okClicked()
    }
    StyleButton{
        id: cancelButton
        text: "CANCEL"
        anchors.left: parent.horizontalCenter
        anchors.leftMargin: 2
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        onClicked: parent.cancelClicked()
    }
}
