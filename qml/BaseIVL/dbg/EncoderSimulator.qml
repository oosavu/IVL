import QtQuick 2.0
import "../styleTypes"
StyleRectangle{
    width: 196
    height: 96

    Row{
        anchors.fill: parent
        anchors.margins: 5
        spacing: 5
        StyleRectangle{
            width: parent.width/3 - 5
            height: parent.height
            Text{
                anchors.centerIn: parent
                text: "PRESS"
                color: "white"
            }
            color: if(areaPRESS.pressed) "red"
                   else "black"
            MouseArea{
                id: areaPRESS
                anchors.fill: parent
                onClicked: {
                    keySim.simulateKeyPressEvent(Qt.Key_Enter)
                }
            }
        }
        StyleRectangle{
            width: parent.width/3 - 5
            height: parent.height
            color: if(areaDOWN.pressed) "red"
                   else "black"
            Text{

                anchors.centerIn: parent
                text: "DOWN"
                color: "white"
            }
            MouseArea{
                id: areaDOWN
                anchors.fill: parent
                onClicked: {
                    keySim.simulateKeyPressEvent(Qt.Key_Down)
                }
            }
        }
        StyleRectangle{
            width: parent.width/3 - 5
            height: parent.height
            color: if(areaUP.pressed) "red"
                   else "black"
            Text{

                anchors.centerIn: parent
                text: "UP"
                color: "white"
            }
            MouseArea{
                 id: areaUP
                anchors.fill: parent
                onClicked: {
                    keySim.simulateKeyPressEvent(Qt.Key_Up)
                }
            }
        }
    }
}
