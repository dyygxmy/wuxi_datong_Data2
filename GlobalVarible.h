#ifndef GLOBALVARIBLE_H
#define GLOBALVARIBLE_H

#endif // GLOBALVARIBLE_H
extern bool isJS;
extern bool isRFID; //是否是RFID
extern bool isNormal;//是否正常
extern bool workmode;//工作模式
extern bool CsIsConnect; //CS351状态
extern bool RFIDISConnect;
extern bool RDYY;        //是否准备
extern bool ISmaintenance;
extern bool ISRESET;
extern bool ISWARNING;
extern bool Curve_Is_Null;
extern bool TaoTongState;
extern bool WIFI_STATE;
extern bool SerialGunMode;
extern bool DebugMode;
extern int Line_ID;
extern QString SYSS;     //状态
extern QString SaveWhat; //要保存什么
extern QString VIN_PIN_SQL;//VIN 码
extern QString SCREWID_SQL;//螺栓编号
extern QByteArray time_info;//实时信息包
extern QString proNum;      //当前程序号
extern QString lsNum;       //额定螺栓数量
extern QString CURVE_STR;
extern int QualifiedNum;  //合格数量
extern int TimeLeft;      //剩余时间
extern int BackTimeLeft;
extern int enablenumberLeft; //剩余螺栓数量
extern int TAOTONG;
extern QString Operator;
extern QString info[7];
extern QString status[20][5];
extern QString Version;
extern bool battery;





