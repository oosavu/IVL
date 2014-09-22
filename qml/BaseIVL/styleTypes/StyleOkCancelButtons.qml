import QtQuick 2.0

Item{
    property alias okActive: okButton.active
    property alias cancelActive: cancelButton.active
    signal okClicked
    signal cancelClicked
    width: 200
    height: 50
    StyleButton{
        id: okButton
        text:"OK"
        onClicked: parent.okClicked()

    }
    StyleButton{
        id: cancelButton
        x: 101
        text: "CANCEL"
        onClicked: parent.cancelClicked()
    }
}
