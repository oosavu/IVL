import QtQuick 2.0
import "../styleTypes"
StyleRectangle {
    width: 273
    height: 148
    color: "gray"

    property var currNode: parent
    property var currLoader
    //onCurrLoaderChanged: console.log(currLoader)

    MouseArea{
        anchors.fill: parent
        onClicked: {
            graphicCentralItem.expandNode(currLoader)
            parent.visible = false
        }
    }


    Grid{
        anchors.fill: parent
        anchors.margins: 3
        columns: 2
        spacing: 3
        StyleRectangle{
            height: 26
            width:132
            StyleTextS{
                anchors.centerIn: parent
                text: "график P"
            }
        }
        StyleRectangle{
            height: 26
            width:132
            StyleTextS{
                anchors.centerIn: parent
                text: "график V"
            }
        }
        StyleRectangle{
            height: 26
            width:132
            StyleTextS{
                anchors.centerIn: parent
                text: "график F"
            }
        }
        StyleRectangle{
            height: 26
            width:132
            StyleTextS{
                anchors.centerIn: parent
                text: "график FiO2"
            }
        }
        StyleRectangle{
            height: 26
            width:132
            StyleTextS{
                anchors.centerIn: parent
                text: "петля"
            }
        }
        StyleRectangle{
            height: 26
            width:132
            StyleTextS{
                anchors.centerIn: parent
                text: "дин. лёгкое"
            }
        }

        StyleRectangle{
            height: 26
            width:132
            StyleTextS{
                anchors.centerIn: parent
                text: "мониторинг"
            }
        }
        StyleRectangle{
            height: 26
            width:132
            StyleTextS{
                anchors.centerIn: parent
                text: "набл. парам "
            }
        }
        StyleRectangle{
            height: 26
            width:132
            StyleTextS{
                anchors.centerIn: parent
                text: "оставить текущее"
            }
        }
        StyleRectangle{
            height: 26
            width:132
            StyleTextS{
                anchors.centerIn: parent
                text: "объед. ячейки  "
            }
        }






    }
}
