import QtQuick 2.0
import "../styleTypes"
StyleRectangle {
    width: 273
    height: 148
    MouseArea{
        anchors.fill: parent
        onClicked: {
            if(!mgd.visible)
            {
                mgd.parent = parent
                mgd.currLoader = parent.parent

    //            mgd.x = parent.parent.x
    //            mgd.y = parent.parent.y
                mgd.width = 273
                mgd.height = 148
                mgd.visible = !mgd.visible
            }
        }
    }
}
