import QtQuick 2.0

Loader {
    width: 148
    height: 73
    property int position
    MouseArea{
        onClicked:
        {
            map[position] = map[position]<16? map[position]+1 : 0
            synchronizeMap()
        }
        anchors.fill: parent
    }
}
