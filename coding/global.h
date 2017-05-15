
#ifndef _Global_
#define _Global_
#include<time.h>
//机场状态
#define OffWork 0    //下班
#define OnWork 1     //正在工作
#define ShutDown 2	 //正在下班
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
extern int PassengerArriveTask;//给到达的乘客安排窗口号码
//extern int new_sigh;//同步锁
extern struct entry thisEvent;
extern Window *Win;
//排队缓冲区
extern int MaxCustSingleLine;// 单队列最大等待乘客数
extern int MaxLines;// 蛇形缓冲区最多由MaxLines个直队组成
extern int MaxSeqLen;// 最大允许等待长度
extern int EasySeqLen;// 短期等待长度
//安检口
extern int NumOfWin;//安检口总数目
extern int WinNum;//安检口工作数目
extern int MinCheck;// 最少开放安检口数量
extern int MaxCheck;// 最多开放安检口数量
extern int MaxCustCheck;// 安检口队伍最大长度
extern int MaxSec;// 安检口最大安检时长 单位是秒
extern int MinSec;// 安检口最小安检时长 单位是秒
extern int MinRestSec;//安检口口最小休息时长
extern int MaxRestSec;//安检口最大休息时长
//时间
extern time_t TimeStart;//开始时间
extern time_t TimeFinish;//结束时间 
extern time_t TimeNow;//现在的时间

typedef struct entry {
	int no; //事件序号
	int sec;//事件发生时间间隔
	char type;//事件类型：C-乘客到达，X-安检口申请暂停，Q-下班；
	int mans; //事件属性1-到达人数
	int check; //事件属性2-申请休息的安检口编号 
	int ev_valid; //事件是否被读取
}entry;


//函数声明
//maintain.c
int MainPara();//维护配置文件
//input.c
double random();//正态分布函数
void MainInput();//生成随机事件
void AirportOnServe();//读取事件
//Cmdinput.c
unsigned __stdcall CmdInput(void* pArguments);
//state.cpp
void DistriNum(entry *event);//为乘客分配号码并插入排队缓冲区
void WinRun();//安检口状态机
void PreWinRun();//缓冲区进安检口
int CheckWin();//判断安检口能否关闭 
void RestOrClosWin(entry event);//接收安检口事件完成安检口下班及休息功能
void StateTrans(entry * event);//总控制函数
//output.c
void StatusOutputCmd();//命令行输出
void EventOutputFile(char event, int id, int no);//事件发生文件输出
void StatusOutputFile();//周期性文件输出
#endif
