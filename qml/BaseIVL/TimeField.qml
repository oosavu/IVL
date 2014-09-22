import QtQuick 2.0
import "styleTypes"
StyleRectangle {

    StyleTextS{
        anchors.centerIn: parent
        text: Qt.formatDateTime(canManager.systemDateTime,"hh:mm:ss")
    }
}
