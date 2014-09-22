import QtQuick 2.0
import "../styleTypes"

Item {
    id: item1
    StyleRectangle {
        color: "lightgreen"
        id: text1
        height: 60
        anchors.right: parent.right
        anchors.rightMargin: 40
        anchors.top: parent.top
        anchors.topMargin: 3
        anchors.left: parent.left
        anchors.leftMargin: 40
        Text{
            anchors.fill: parent
            text: qsTr("ПЕРЕЙТИ В РАСШИРЕННЫЙ РЕЖИМ")
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 20
        }
        MouseArea{
            anchors.fill: parent
            onClicked: spField.state = "fullRedact"
        }
    }

    Item{
        anchors.top: text1.bottom
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        width: parent.width/4
        Item{
            anchors.fill: parent
            anchors.margins: 10
            StyleButton{
                anchors.margins: 10
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.verticalCenter
                text: "принять"
                active: ventModeManager.avilableChangeMode
                onClicked:{
                    ventModeManager.acceptModeVent()
                    setParField.state = "hidden"
                }
            }
            StyleButton{
                anchors.margins: 10
                anchors.top: parent.verticalCenter
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                text: "отмена"
                onClicked:{
                    ventModeManager.cancelModeVent()
                    setParField.state = "hidden"
                }
            }
        }
    }


}
