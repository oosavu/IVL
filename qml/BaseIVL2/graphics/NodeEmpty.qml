import QtQuick 2.0
import "../styleTypes"

Item{
    width: 20
    height: 20
    property alias titleText: title.text
    property alias frameItem: frame

    StyleRectangle {
        id: re

        anchors.fill: parent
        anchors.bottomMargin: 3
        anchors.rightMargin:  3
        color: "transparent"

        StyleText
        {
            id: title
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            text: "пустой текст"
            font.pixelSize: 20
            color: "#ffffff"
            height: 25
        }

        Item{
            id: frame

            anchors.top: title.bottom
            anchors.left: re.left
            anchors.right: re.right
            anchors.bottom: re.bottom
        }
    }



    function drawLine(_ctx, x1, y1, x2, y2, dashLen) //для канвасов
    {
        if (dashLen == undefined)
        {
            _ctx.beginPath();
            _ctx.moveTo(x1,y1)
            _ctx.lineTo(x2,y2)
            _ctx.stroke();
            return
        }

        _ctx.beginPath();
        _ctx.moveTo(x1, y1);

        var dX = x2 - x1;
        var dY = y2 - y1;
        var dashes = Math.floor(Math.sqrt(dX * dX + dY * dY) / dashLen);
        var dashX = dX / dashes;
        var dashY = dY / dashes;

        var q = 0;
        while (q++ < dashes)
        {
            x1 += dashX;
            y1 += dashY;
            _ctx[q % 2 == 0 ? 'moveTo' : 'lineTo'](x1, y1);
        }
        _ctx[q % 2 == 0 ? 'moveTo' : 'lineTo'](x2, y2);

        _ctx.stroke();
        _ctx.closePath();
    }

}
