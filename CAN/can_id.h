#ifndef CAN_ID_H
#define CAN_ID_H


/** Пространство имён, соержащее в себе идентификаторы всех сообщений в аппарате ИВЛ-18
* Принято решение весь диапазон 11-бит идентификаторов разбить на несколько поддиапазонов
* Каждому блоку будет выделяться одинаковое число идентификаторов из уникального диапазона.
* Драйвер CAN будет вызывать одну и ту же функцию обработки для каждого блока, если ему будут
* принадлежать принятые ID. Функция обработки должна сама разгребать конкретные ID.
* Сообщения с ID < 0x3FF в системе не используются
* Принято решение выделять 32 идентификатора на каждый блок.
* См. также "CAN protocol description.txt"
*/
namespace canId{

    /**
    * блок 1: ID 992..1023 (0x3E0..0x3FF)
    * Сообщение от блока питания о пропадании питания примерно через 0.5 с
    * Блок необходим, т.к. сообщение с ID=1023 сделано самым высокоприоритетным. Все остальные
    * используемые в аппарате сообщения имеют бОльшие ID (менее приоритетны)
    */
    namespace power1{
        enum{
            ID_OFF_PWR = 1023
        };
    }

    /**
    * блок 2: ID 1024..1055 (0x400..0x41F)
    * Блок питания
    */
    namespace power2{
         enum{
            ID_MODE_PWR       =  1024,
            ID_STATUS_PWR     =  1025,
            ID_VERSION_PWR    =  1026,
            ID_BEEP_SND_PWR   =  1027,
            ID_VOLUME_SND_PWR =  1028
         };
    }

    /**
    * блок 4: ID 1088..1119 (0x440..0x45F)
    * Смеситель газов
    */
    namespace mix{
         enum{
            ID_MODE_MIX       =  1088,
            ID_OPT_MIX        =  1089,
            ID_STATUS_MIX     =  1090,
            ID_VERSION_MIX    =  1091,
            ID_TASKOXY_MIX    =  1092
         };
    }


    /**
    * блок 5: ID 1120..1151 (0x460..0x47F)
    * Блок управления
    * Т.к. все входящие/исходящие сообщения заложены в каждом блоке, и
    * БУ является управляющим блоком, то для него не надо выделять идентификаторы,
    * кроме двух системных, для синхронизации остальных блоков
    */
    namespace bu{
         enum{
            ID_SYNHRO         =  1120,
            ID_SYNHRO_GRAPH1  =  1121,
            ID_SETOPT_BU      =  1122,
            ID_OXY            =  1123
         };
    }

    /**
    * блок 6: ID 1152..1183 (0x480..0x49F)
    * Капнограф БО
    */
    namespace capno1{
         enum{
            ID_MODE_CAPNO1         = 1152,
            ID_OPT_CAPNO1          = 1153,
            ID_STATUS_CAPNO1       = 1154,
            ID_VERSION_CAPNO1      = 1155,
            ID_WAVE_CAPNO1         = 1156,

            ID_CO2_DATA_CAPNO1     = 1157,
            ID_O2_DATA_CAPNO1      = 1158,
            ID_N2O_DATA_CAPNO1     = 1159,

            ID_CALOXY_CAPNO1       = 1160,
            ID_CALOXY_DEBUG_CAPNO1 = 1161,
            ID_CALIBR_MSG_CAPNO1   = 1162,
            ID_CALCO2_CAPNO1       = 1166
         };
    }

    /**
    * блок 7: ID 1184..1215 (0x4A0..0x4BF)
    * Контроллер ИВЛ
    */
    namespace kivl{
         enum{
            ID_MODE_CIVL       = 1184,
            ID_PARAPNEA_CIVL   = 1185,
            ID_INSP_CIVL       = 1186,
            ID_PAR1_CIVL       = 1187,
            ID_PAR2_CIVL       = 1188,
            ID_PAR3_CIVL       = 1189,
            ID_WAVE_CIVL       = 1190,
            ID_CLBR_STEP_CIVL  = 1191,
            ID_STATUS_CIVL     = 1192,
            ID_CLBR_ERR_CIVL   = 1193,
            ID_VERSION_CIVL    = 1194,
            ID_OPT_CIVL        = 1195,
            ID_M_VINSP_CIVL    = 1196,
            ID_M_VEXP_CIVL     = 1197,
            ID_M_PEEP_CIVL	   = 1198,
            ID_M_RB_CIVL	   = 1199,
            ID_M_PIP_CIVL	   = 1200,
            ID_M_MV_CIVL	   = 1201,
            ID_M_TEXP_CIVL	   = 1202,
            ID_M_TINSP_CIVL    = 1203,
            ID_M_COMPL_CIVL    = 1204,
            ID_M_LEAK_CIVL     = 1205,
            ID_DBG_AR_CIVL     = 1206,
            ID_WORKTIME_CIVL   = 1207,
            ID_OXYVOLTAGE_CIVL = 1208,
            ID_M_PPLATO_CIVL   = 1209,
            ID_M_FLOWPEAK_CIVL = 1210,
            ID_M_AIRWAY_CIVL   = 1211,
            ID_DBG_CIVL        = 1212,
            ID_ISV_PAR1_CIVL   = 1213,
            ID_ISV_PAR2_CIVL   = 1214
         };
    }

    /**
    * блок 8: ID 1216..1247 (0x4C0..0x4DF)
    * Капнограф прямого потока (capnostat5)
    */

    namespace capno2{
         enum{
            ID_MODE_CAPNO2       =  1216,  /* 0x4C0 */
            ID_OPT0_CAPNO2       =  1217,  /* 0x4C1 */
            ID_OPT1_CAPNO2       =  1218,  /* 0x4C2 */
            ID_STATUS_CAPNO2     =  1219,  /* 0x4C3 */
            ID_WAVE_CAPNO2       =  1220,  /* 0x4C4 */
            ID_DATA_CAPNO2       =  1221,  /* 0x4C5 */
            ID_VERSION_CAPNO2    =  1222  /* 0x4C6 */
         };
    }
    /**
    * блок 9: ID 1248..1251 (0x4E0..0x4E3)
    * Пульсоксиметр
    */
    namespace spo{
         enum{
            ID_MODE_SPO         =    1248,
            ID_STATUS_SPO       =    1249,
            ID_VERSION_SPO      =    1250,
            ID_WAVE_SPO         =    1251,
            ID_OPT_SPO          =    1252
         };
    }

    /**
    * блок 10: ID 1280..1311 (0x500..0x51F)
    * Контроллер ИВЛ (второй блок)
    */
    namespace kivl2{
         enum{
            ID_ISV_INFO1_CIVL2   = 1280,
            ID_ISV_INFO2_CIVL2   = 1281,
            ID_LSF_COMPL_CIVL2   = 1282,
            ID_DEBUG_LINE_CIVL2  = 1283
         };
    }

}



#endif // CAN_ID_H


































