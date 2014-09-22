import QtQuick 2.0

StyleRectangle {
    x:151
    color:"#444444"
    y:101
    width: 548
    height: 448
    signal okClicked
    signal cancelClicked
    property alias okActive: dialogOkCancel.okActive
    property alias cancelActive: dialogOkCancel.cancelActive
    property alias visibleOkCancel: dialogOkCancel.visible
    StyleOkCancelButtons{
        id:dialogOkCancel
        x: parent.width - 202
        y: parent.height - 52

        onCancelClicked: parent.cancelClicked()
        onOkClicked: parent.okClicked()
    }
}
