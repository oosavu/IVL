import QtQuick 2.0

MeasureParameterField {
    property var minVal
    property var maxVal

    Canvas{
        opacity: 0.3
        id: canvas
        anchors.fill: parent
        anchors.margins: 3
        onPaint: {
            var ctx = getContext('2d');
            ctx.strokeStyle = "white";
            ctx.fillStyle = "#660000"
            ctx.lineWidth = 1;
            var pers = (measParam.value - minVal.value)/(maxVal.value - minVal.value)

            ctx.fillRect(0, 0, width*pers, height);
        }
    }

    Item {
        Text{
            anchors.centerIn: parent
            text: "min: " + minVal.value
            font.pointSize: 12
            color: "white"
        }
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        width: 80
        height: parent.height/2
    }
    Item {
        Text{
            anchors.centerIn: parent
            text: "max: " + maxVal.value
            font.pointSize: 12
            color: "white"
        }
        anchors.top: parent.top
        anchors.right: parent.right
        width: 80
        height: parent.height/2
    }
}
