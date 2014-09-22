import QtQuick 2.0
import "../styleTypes"
Item {


    Column{
        anchors.fill: parent
        MonitoringParameterItem{ param: currPEEPtot;    unitStr: "?";                   nameStr: "PEEPtot"      }
        MonitoringParameterItem{ param: currExpEndFlow; unitStr: "0.1 л/мин";           nameStr: "ExpEndFlow"   }
        MonitoringParameterItem{ param: currRCExp;      unitStr: "мс";                  nameStr: "RCExp"        }
        MonitoringParameterItem{ param: currRCInsp;     unitStr: "мс";                  nameStr: "RCInsp"       }
        MonitoringParameterItem{ param: currRExp;       unitStr: "мм вод.ст";           nameStr: "RExp"         }
        MonitoringParameterItem{ param: currCDyn;       unitStr: "мл/см вод.ст.";       nameStr: "CDyn"         }
        MonitoringParameterItem{ param: currWVent;      unitStr: "0.01 Дж/л";           nameStr: "WVent"        }
        MonitoringParameterItem{ param: currWSpont;     unitStr: "0.01 Дж/л";           nameStr: "WSpont"       }
    }
}
