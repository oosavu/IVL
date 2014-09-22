#ifndef LIMITDEFINES_H
#define LIMITDEFINES_H

#include <QObject>

const qint32  MIN_FLOW[2]     = {   30,   30}; //   30 Flow_min минимальный основной поток  -  3 l/min
const qint32  MAX_FLOW[2]     = { 1000,  400}; // 1000 Flow_max максимальный основной поток - 100 l/min
const qint32  MIN_PRESRAMP[2] = {   50,   50}; //   50 Flow_min минимальный основной поток  -  3 l/min
const qint32  MAX_PRESRAMP[2] = { 2000, 2000}; // 1000 Flow_max максимальный основной поток - 100 l/min
const qint32  MIN_VT[2]       = {  200,   50}; //   50 V_min  минимальный объем вдоха  -   50ml
const qint32  MAX_VT[2]       = { 2000,  400}; // 2000 V_max  максимальный объем вдоха - 2000ml
const qint32  MIN_VAPN[2]     = {  200,   50};
const qint32  MAX_VAPN[2]     = { 2000,  400};
const qint32  MIN_VE[2]       = {   30,    7}; //   10 Vm_min минимальная минутная вентиляция  -  3 l/min
const qint32  MAX_VE[2]       = {  300,  100}; //  250 Vm_max максимальная минутная вентиляция - 25 l/min
const qint32  MIN_VE_PS[2]    = {    2,    1}; //   10 Vm_min минимальная минутная вентиляция  -  3 l/min
const qint32  MIN_RB[2]       = {    8,   15}; //    8 f_min  минимальная частота вентиляции  -  8 1/min
const qint32  MAX_RB[2]       = {   60,   80}; //   60 f_max  максимальная частота вентиляции - 60 1/min
const qint32  MIN_RB_NIV[2]   = {   15,   15}; //   15 f_min  минимальная частота вентиляции  -  8 1/min
const qint32  MAX_RB_NIV[2]   = {   25,   25}; //   25 f_max  максимальная частота вентиляции - 60 1/min
const qint32  MIN_RB_SIMV[2]  = {    1,    1}; /* f_min для SIMV */
const qint32  MAX_RB_SIMV[2]  = {   30,   30}; /* f_max для SIMV */
const qint32  MIN_TAPN[2]     = {   10,   10}; // Время апноэ  сек
const qint32  MAX_TAPN[2]     = {   60,   20}; // Время апноэ  сек
const qint32  MAX_PIP_VCV[2]  = {   80,   60}; // Pmax_max_VCV макс.  уровень ограничения Pвдоха (VCV)- 80 см H2O
const qint32  MAX_PIP_PCV[2]  = {   80,   60}; // Pmax_max_PCV максимальное значение Pвдоха (PCV)- 40 см H2O
const qint32  MIN_WEIGHT_APN[2] = {   150,    50};
const qint32  MAX_WEIGHT_APN[2] = {  2000,   350};
const qint32  MIN_T_HIGH[2]  = {   10,   10};
const qint32  MAX_T_HIGH[2]  = {  300,  300};
const qint32  MIN_T_LOW[2]   = {   20,   20};
const qint32  MAX_T_LOW[2]   = {  300,  300};
const qint32  MIN_P_HIGH[2]  = {    0,    0};
const qint32  MAX_P_HIGH[2]  = {   70,   70};
const qint32  MIN_P_LOW[2]   = {    0,    0};
const qint32  MAX_P_LOW[2]   = {   30,   30};
const qint32  MIN_TI[2]      = {    2,    2};
const qint32  MAX_TI[2]      = {   30,   30};
const qint32  MAX_PT[2]      = {   80,   25};
const qint32  MAX_PT_100[2]  = {  100,   25};
const qint32  MIN_PT[2]      = {   10,   10};
const qint32  MAX_PT_NIV[2]  = {   20,   20};
const qint32  MIN_PT_NIV[2]  = {   10,   10};
const qint32  MAX_TEXP[2]    = { 7000, 5000};
const qint32  MIN_TEXP[2]    = {  300,  200};
const qint32  MAX_TSENSE[2]  = {  100,  100};
const qint32  MIN_TSENSE[2]  = {    0,    0};
const qint32  MAX_PSENSE[2]  = { 7000, 5000};
const qint32  MIN_PSENSE[2]  = {    5,    5};
const qint32  MAX_FSENSE[2]  = { 7000, 5000};
const qint32  MIN_FSENSE[2]  = {    5,    5};
const qint32  MAX_TPLATO     =    40;
const qint32  MIN_TPLATO     =     0;
const qint32  MAX_MV[2]      = { 7000, 5000};
const qint32  MIN_MV[2]      = {    5,    5};
const qint32  MAX_OXY        =   100;
const qint32  MIN_OXY        =     0;




#define  MIN_RB_AS                1 //минимальная частота вентиляции (вспом.) -  1 1/min
#define  MAX_RB_AS               30 //20 //максимальная частота вентиляции (вспом.)- 20 1/min
#define  MIN_TI_TC_SIMV           1 // Ti_Tc_min минимальное отношение вдох/цикл  - 1%
#define  MIN_TI_TC               20 // Ti_Tc_min минимальное отношение вдох/цикл  - 20%
#define  MAX_TI_TC               80 // Ti_Tc_max максимальное отношение вдох/цикл - 80%
#define  MIN_PIP_VCV             10 // Pmax_min_VCV миним. уровень ограничения Pвдоха (VCV)- 20 см H2O
#define  MIN_PIP_PCV             10 // Pmax_min_PCV минимальное  значение Pвдоха (PCV)- 10 см H2O
#define  MAX_PEEP                25 // PEEP_max     максимальное значение PEEP - 25 см H2O
#define  MIN_PEEP                 0
#define  MAX_TPL                 40 // Tpl_max   максимальная длительность плато - 40%
#define  MAX_FTRIG               20 // Ftrig_max максимальное значение порога триггера по потоку - 20 l/min
#define  MIN_FTRIG                0 // Ftrig_min минимальное значение порога триггера по потоку - 0 l/min
#define  MAX_PTRIG              200 // Ptrig_max максимальное значение порога триггера по давлению - 10 см Н2О
#define  MIN_PTRIG                0 //
#define  STEP_PTRIG              10 //
#define  MIN_PS                   0 // Давление поддержки см Н2О
#define  MAX_PS                  80 //40 // Давление поддержки см Н2О
#define  MIN_TRIGWND              0 //1 // %
#define  MAX_TRIGWND            100 // %
#define  MIN_FACC                10 //
#define  MAX_FACC               100 //
#define  MIN_FEND                 5 //
#define  MAX_FEND                50 //
#define  MIN_FEND_NIV            10 //
#define  MAX_FEND_NIV            50 //
#define  MIN_O2                  21 //
#define  MAX_O2                 100 //

#define  MIN_PRESRAMP_CHILD      50  /* скорость нарастания давления, минимальная величина для детского пациента*/
#define  MIN_PRESRAMP_ADULT      50  /* скорость нарастания давления, минимальная величина для взрослого пациента*/
#define  MAX_PRESRAMP_CHILD    2000  /* скорость нарастания давления, максимальная величина для детского пациента*/
#define  MAX_PRESRAMP_ADULT    2000  /* скорость нарастания давления, максимальная величина для взрослого пациента*/

#define  MIN_PERCMV                  25
#define  MAX_PERCMV                 300

#define  MIN_ETC                      0
#define  MAX_ETC                    100

#define  MIN_OXY_CHILD           MIN_O2
#define  MIN_OXY_ADULT           MIN_O2
#define  MAX_OXY_CHILD           MAX_O2
#define  MAX_OXY_ADULT           MAX_O2
#define  MIN_OXY_CHILD_NIV           21
#define  MIN_OXY_ADULT_NIV           21
#define  MAX_OXY_CHILD_NIV           70
#define  MAX_OXY_ADULT_NIV           70
#define  MIN_PMAX_CHILD     MIN_PIP_VCV
#define  MIN_PMAX_ADULT     MIN_PIP_VCV
#define  MAX_PMAX_CHILD              65
#define  MAX_PMAX_ADULT              87
#define  MAX_PMAX_ADULT_105         105
#define  MIN_PSENSE_CHILD            10
#define  MIN_PSENSE_ADULT            10
#define  MAX_PSENSE_CHILD     MAX_PTRIG
#define  MAX_PSENSE_ADULT     MAX_PTRIG
#define  MIN_PSENSE_CHILD_NIV        10
#define  MIN_PSENSE_ADULT_NIV        10
#define  MAX_PSENSE_CHILD_NIV       100
#define  MAX_PSENSE_ADULT_NIV       100
#define  MIN_PSENSE_CHILD_CMV MIN_PTRIG
#define  MIN_PSENSE_ADULT_CMV MIN_PTRIG
#define  MAX_PSENSE_CHILD_CMV MAX_PTRIG
#define  MAX_PSENSE_ADULT_CMV MAX_PTRIG
#define  MIN_FSENSE_CHILD             1
#define  MIN_FSENSE_ADULT             1
#define  MAX_FSENSE_CHILD            10
#define  MAX_FSENSE_ADULT            20
#define  MIN_FSENSE_CHILD_CMV MIN_FTRIG
#define  MIN_FSENSE_ADULT_CMV MIN_FTRIG
#define  MAX_FSENSE_CHILD_CMV MAX_FTRIG
#define  MAX_FSENSE_ADULT_CMV MAX_FTRIG
#define  MIN_RB_CHILD_CMV            15
#define  MIN_RB_ADULT_CMV_PCV         4
#define  MIN_RB_ADULT_CMV_VCV         3
#define  MAX_RB_CHILD_CMV            80
#define  MAX_RB_ADULT_CMV            60
#define  MIN_RB_CHILD_NIV            15
#define  MIN_RB_ADULT_NIV            15
#define  MAX_RB_CHILD_NIV            25
#define  MAX_RB_ADULT_NIV            25
#define  MIN_RB_CHILD_SIMV            1
#define  MIN_RB_ADULT_SIMV            1
#define  MAX_RB_CHILD_SIMV           30
#define  MAX_RB_ADULT_SIMV           30
#define  MIN_RB_CHILD_PCV_VG         15
#define  MIN_RB_ADULT_PCV_VG          4
#define  MAX_RB_CHILD_PCV_VG         80
#define  MAX_RB_ADULT_PCV_VG         60
#define  MAX_PEEP_ADULT_PCV_VG       35
#define  MAX_PEEP_ADULT_CMV          35
#define  MIN_PEEP_CHILD        MIN_PEEP
#define  MIN_PEEP_ADULT        MIN_PEEP
#define  MAX_PEEP_CHILD        MAX_PEEP
#define  MAX_PEEP_ADULT        MAX_PEEP
#define  MIN_VINSP_CHILD             20
#define  MIN_VINSP_ADULT            200
#define  MAX_VINSP_CHILD            400
#define  MAX_VINSP_ADULT           2000
#define  MIN_TINSP_CHILD            200
#define  MIN_TINSP_ADULT            200
#define  MAX_TINSP_CHILD           3000
#define  MAX_TINSP_ADULT           3000
#define  MAX_TINSP_ADULT_SIMV     10000
#define  MAX_TINSP_CHILD_CPAP      4000
#define  MAX_TINSP_ADULT_CPAP      4000
#define  MIN_PINSP_CHILD              0
#define  MIN_PINSP_ADULT              0
#define  MAX_PINSP_CHILD             60
#define  MAX_PINSP_ADULT             75
#define  MAX_PINSP_ADULT_100        100
#define  MIN_PSUPP_CHILD_BISTEP       0
#define  MAX_PSUPP_CHILD_BISTEP      35
#define  MIN_PSUPP_CHILD         MIN_PS
#define  MIN_PSUPP_ADULT         MIN_PS
#define  MAX_PSUPP_CHILD         MAX_PS
#define  MAX_PSUPP_ADULT         MAX_PS
#define  MIN_TAPNEA_CHILD            10
#define  MIN_TAPNEA_ADULT            10
#define  MAX_TAPNEA_CHILD            20
#define  MAX_TAPNEA_ADULT            60
#define  MIN_VAPNEA_CHILD            50
#define  MIN_VAPNEA_ADULT           200
#define  MAX_VAPNEA_CHILD           400
#define  MAX_VAPNEA_ADULT          2000
#define  MIN_PHIGH_CHILD              0
#define  MIN_PHIGH_ADULT              0
#define  MAX_PHIGH_CHILD             45
#define  MAX_PHIGH_ADULT             70
#define  MIN_PHIGH_CHILD_APRV         5
#define  MIN_PHIGH_ADULT_APRV         5
#define  MAX_PHIGH_CHILD_APRV        50
#define  MAX_PHIGH_ADULT_APRV        50
#define  MIN_PLOW_CHILD               0
#define  MIN_PLOW_ADULT               0
#define  MAX_PLOW_CHILD              20
#define  MAX_PLOW_ADULT              30
#define  MIN_THIGH_CHILD           1000
#define  MIN_THIGH_ADULT           1000
#define  MAX_THIGH_CHILD          30000
#define  MAX_THIGH_ADULT          30000
#define  MIN_THIGH_CHILD_APRV      2000
#define  MIN_THIGH_ADULT_APRV      2000
#define  MAX_THIGH_CHILD_APRV     30000
#define  MAX_THIGH_ADULT_APRV     30000
#define  MIN_TLOW_CHILD            2000
#define  MIN_TLOW_ADULT            2000
#define  MAX_TLOW_CHILD           30000
#define  MAX_TLOW_ADULT           30000
#define  MIN_TLOW_CHILD_APRV        500
#define  MIN_TLOW_ADULT_APRV        500
#define  MAX_TLOW_CHILD_APRV       3000
#define  MAX_TLOW_ADULT_APRV       3000
#define  MIN_PLATO_CHILD              0
#define  MIN_PLATO_ADULT              0
#define  MAX_PLATO_CHILD             40
#define  MAX_PLATO_ADULT             40
#define  MIN_TRIGWND_CHILD  MIN_TRIGWND
#define  MIN_TRIGWND_ADULT  MIN_TRIGWND
#define  MAX_TRIGWND_CHILD  MAX_TRIGWND
#define  MAX_TRIGWND_ADULT  MAX_TRIGWND
#define  MIN_FSUPP_CHILD             10
#define  MIN_FSUPP_ADULT             10
#define  MAX_FSUPP_CHILD             10
#define  MAX_FSUPP_ADULT             10
#define  MIN_FSUPP_CHILD_CMV          0
#define  MIN_FSUPP_ADULT_CMV          0
#define  MAX_FSUPP_CHILD_CMV         30
#define  MAX_FSUPP_ADULT_CMV         30
#define  MIN_PEEP_CHILD_NIV           0
#define  MIN_PEEP_ADULT_NIV           0
#define  MAX_PEEP_CHILD_NIV          10
#define  MAX_PEEP_ADULT_NIV          10
#define  MIN_PEEP_CPAP                2
#define  MIN_PSUPP_CHILD_NIV          5
#define  MIN_PSUPP_ADULT_NIV          5
#define  MAX_PSUPP_CHILD_NIV         25
#define  MAX_PSUPP_ADULT_NIV         25
#define  MIN_PTAPNEA_CHILD           10
#define  MIN_PTAPNEA_ADULT           10
#define  MAX_PTAPNEA_CHILD           20
#define  MAX_PTAPNEA_ADULT           20
#define  MIN_FMAX_CHILD               3
#define  MIN_FMAX_ADULT               3
#define  MAX_FMAX_CHILD              40
#define  MAX_FMAX_ADULT             100
#define  MIN_FMAX_CHILD_NIV          25
#define  MIN_FMAX_ADULT_NIV          25
#define  MAX_FMAX_CHILD_NIV         100
#define  MAX_FMAX_ADULT_NIV         100
#define  MIN_DELTA_PEEP               3
#define  MAX_DELTA_PEEP              25

/*************************************************************************************************/

/* задаваемые величины для CMV/VCV */
#define  O2_ADULT_INI            21
#define  PMAX_ADULT_INI          40
#define  RB_ADULT_INI             8
#define  PEEP_ADULT_INI           0
#define  VINSP_ADULT_INI       1000
#define  TINSP_ADULT_INI       2500
#define  PTRIG_ADULT_INI        100
#define  TPL_PERC_ADULT_INI       0
#define  TPL_SEC_ADULT_INI        0

#define  O2_CHILD_INI            21
#define  PMAX_CHILD_INI          30
#define  RB_CHILD_INI            15
#define  PEEP_CHILD_INI           5
#define  VINSP_CHILD_INI        100
#define  TINSP_CHILD_INI        800 /* 700 !!! Самостоятельно заменил, т.к. выходил за допуск параметр Ti:Tc */
#define  PTRIG_CHILD_INI         50
#define  TPL_PERC_CHILD_INI       0
#define  TPL_SEC_CHILD_INI        0

/* задаваемые величины для других режимов */
#define  T_HIGH_ADULT_INI      2500
#define  T_LOW_ADULT_INI       5000
#define  P_HIGH_ADULT_INI        15
#define  P_LOW_ADULT_INI          2
#define  PT_ADULT_INI            10
#define  PSUP_ADULT_INI           5
#define  FEND_ADULT_INI_NOT_NIV  25 /* [%] */
#define  FEND_ADULT_INI_NIV      15 /* [л/мин] */
#define  FSUP_ADULT_INI          10
#define  PRAMP_ADULT_INI        500 /* скорость нарастания давления (Pramp) [mmH2O/s] */
#define  FACC_ADULT_INI          50

#define  T_HIGH_CHILD_INI      1500
#define  T_LOW_CHILD_INI       2500
#define  P_HIGH_CHILD_INI        10
#define  P_LOW_CHILD_INI          5
#define  PT_CHILD_INI            20
#define  PSUP_CHILD_INI           5
#define  FEND_CHILD_INI_NOT_NIV  25 /* [%] */
#define  FEND_CHILD_INI_NIV      15 /* [л/мин] */
#define  FSUP_CHILD_INI          10
#define  PRAMP_CHILD_INI        500 /* скорость нарастания давления (Pramp) [mmH2O/s] */
#define  FACC_CHILD_INI          50

#define  MAX_INSP_PAUSE          10
#define  MIN_INSP_PAUSE           1

#define  BIF_INI                  0 //
#define  BIF_INI_CPAP           100 // При переходе в режим СРАР BiF = 10,0 L/min
#define  TRIGWND_ADULT_INI      100
#define  FTRIG_ADULT_INI          5 // Чувствительность триггера по потоку (L/min)
#define  INSP_PAUSE_INI          10 // Инспираторная пауза
#define  TAPN_ADULT_INI          20 // Время апноэ

#define  TRIGWND_CHILD_INI      100
#define  FTRIG_CHILD_INI          3 // Чувствительность триггера по потоку (L/min)
#define  TAPN_CHILD_INI          10 // Время апноэ

#define  SPO2_WAVERATE_INI      470 /* частота отсчетов ФПГ [0.1 Гц]. 94Гц соответствует скорости развертки 25мм/сек на экране 12" (размер пикселя = 0.266 мм.) */
#define  SPO2_AVERTIME_INI       16

#define  DISCON_SENSE_INI        50
#define  DELTA_PEEP_INI           3

// Настройки
// Границы веса пациента для режима апноэ
#define  WEIGTH_APNEA_MAX       200
#define  WEIGTH_APNEA_MIN         5
#define  WEIGTH_APNEA_ADULT_INI 700
#define  VT_APNEA_ADULT_INI    1000
#define  RB_APNEA_ADULT_INI       8
#define  PT_APNEA_ADULT_INI      10

#define  WEIGTH_APNEA_CHILD_INI 100
#define  VT_APNEA_CHILD_INI     100
#define  RB_APNEA_CHILD_INI      30
#define  PT_APNEA_CHILD_INI      10

#define  PEEP_APNEA               5  /* Уровень ПДКВ при АПНОЭ */

#define  _HZ                      0

#endif // LIMITDEFINES_H
