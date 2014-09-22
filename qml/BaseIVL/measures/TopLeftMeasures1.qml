import QtQuick 2.0
import "../styleTypes"
Item {

    Column{
        anchors.fill: parent

        MonitoringParameterItem{ param: currTi;         unitStr: "мсек";              nameStr: "T"          }
        MonitoringParameterItem{ param: currTiTtot;     unitStr: "ед.";               nameStr: "TiTtot"      }
        MonitoringParameterItem{ param: currMVspMV;     unitStr: "ед.";               nameStr: "MVspMV"      }
        MonitoringParameterItem{ param: currSI;         unitStr: "?";                 nameStr: "SI"          }
        MonitoringParameterItem{ param: currElastence;  unitStr: "?";                 nameStr: "Elastence"   }
        MonitoringParameterItem{ param: currRCirc;      unitStr: "0.1 cмH2O * c / л"; nameStr: "RCirc"       }
        MonitoringParameterItem{ param: currCCirc;      unitStr: "мл/см вод.ст.";     nameStr: "CCirc"       }
        MonitoringParameterItem{ param: currP01;        unitStr: "мм вод.ст.";        nameStr: "P01"         }
        MonitoringParameterItem{ param: currRSBI;       unitStr: "?";                 nameStr: "RSBI"        }
    }
}
