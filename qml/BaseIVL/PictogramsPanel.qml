import QtQuick 2.0
import "styleTypes"
Item {
    Row{

        Repeater{
            x:2
            model: 10
            Item{
                height: 50
                width:  50
                StyleRectangle{
                    height: 48
                    width:  48

                }
            }
        }
    }
}
