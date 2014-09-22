import QtQuick 2.0
import CppImport 1.0
import "../styleTypes"
StyleCentralDialog{
    x: 3
    y: 3
    width: 442
    height: 392
    onOkClicked:{ ventModeCentralItem.state = "stateParamsVM" }
    onCancelClicked:{ ventModeCentralItem.state = "stateParamsVM" }

}
