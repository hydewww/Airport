#ifndef _Global_
#define _Global_
#include<time.h>
//机场状态
#define OffWork 0    //下班
#define OnWork 1     //正在工作
#define ShutDown 2 
//窗口状态
#define CloseWin 0   //窗口关闭
#define OpenWin 1    //窗口开启
#define OnSerWin 2   //窗口正在服务
#define RestWin 3    //窗口正在休息
#define ReadyRestWin 4  //窗口准备休息
#define ReadyClosWin 5  //窗口准备关闭

//全局变量声明
extern int AirportState;//机场状态
extern int TotalOdinCus;//当前总的乘客人数
extern int OdinWatNum;//当前乘客等待人数

extern clock_t TimeStart;//开始时间
extern clock_t TimeFinish;//结束时间 
extern clock_t TimeNow;	//现在的时间

extern int MaxCustSingleLine;//单队列最大等待乘客数
extern int MaxLines;		// 蛇形缓冲区最多由MaxLines个直队组成
extern int MaxSeqLen;		// 最大允许等待长度
extern int EasySeqLen;		// 短期等待长度

extern int NumOfWin;	//安检口总数目
extern int WinNum;		//安检口工作数目
extern int MinRestSec;	//安检口口最小休息时长
extern int MaxRestSec;	//安检口最大休息时长
extern int MinCheck;	//最少开放安检口数量
extern int MaxCheck;	//最多开放安检口数量
extern int MaxCustCheck;//安检口队伍最大长度
extern int MaxSec;		//安检口最大安检时长 单位是秒
extern int MinSec;		//安检口最小安检时长 单位是秒
extern int PassengerArriveTask;//给到达的乘客安排窗口号码

struct entry {
	int no; //事件序号
	int sec;//事件发生时间间隔
	char type;//事件类型：C-乘客到达，X-安检口申请暂停，Q-下班；
	int mans; //事件属性1-到达人数
	int check; //事件属性2-申请暂停的安检口编号 
	int ev_valid; //判断事件是否读取
};

//函数声明
void MainInput();
void AirportOnServe();
void DistriNum(int);
void WinRun();
long SerTaskTime();
int  MainPara();
void CusOutput();
void NowTime();
void RegularOutput();
void ResultOutput();

#endif
