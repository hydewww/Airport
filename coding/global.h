#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include<time.h>
#include"passenger.h"
#include"queue.h"
#include"window.h"

#define WINDOWS_X 1500 
#define WINDOWS_Y 600

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

extern int EventNum;
extern int OdinPas;//当前普通乘客总人数
extern int OdinWaitNum;//当前总乘客等待人数

extern int lock; //同步锁
extern struct entry thisEvent;

typedef struct entry
{
	int  no; //事件序号
	int  sec;//事件发生时间间隔
	char type;//事件类型：C-乘客到达，V-VIP乘客到达，X-安检口申请暂停，Q-下班；
	int  mans; //事件属性1-到达人数
	int  check; //事件属性2-申请休息的安检口编号 
	int  ev_valid; //事件是否被读取
}entry;

//排队缓冲区
extern int MaxCustSingleLine;// 单队列最大等待乘客数
extern int MaxLines;// 蛇形缓冲区最多由MaxLines个直队组成
extern int MaxSeqLen;// 最大允许等待长度
extern int EasySeqLen;// 短期等待长度
extern Queue* OdinQueue;
extern Queue* VipQueue;
//安检口
extern int NumOfWin;//安检口总数目
extern int WinNum;//普通安检口工作数目
extern int VipWinNum;//Vip安检口工作数目
extern int MinCheck;// 最少开放安检口数量
extern int MaxCheck;// 最多开放安检口数量
extern int MaxCustCheck;// 安检口队伍最大长度
extern int MaxSec;// 安检口最大安检时长 单位是秒
extern int MinSec;// 安检口最小安检时长 单位是秒
extern int MinRestSec;//安检口口最小休息时长
extern int MaxRestSec;//安检口最大休息时长
extern int NumOfVIPWin;//VIP安检口数目
extern struct Window *Win;
extern struct Window *VIPWin;
//时间
extern time_t TimeStart;//开始时间
extern time_t TimeFinish;//结束时间 
extern time_t TimeNow;//现在的时间
//GUI
extern int Xlong;	//窗口大小
extern int Ylong;
extern int CXlong;	//安检口
extern int CYlong;
extern int RXlong;	//乘客大小
extern int RYlong;
extern int EnLineCache;	//未进入动画的缓冲区乘客
const int CacheNum = 50; //缓存数

typedef struct Cache {
	int no[CacheNum];
	int head;
	int tail;
}Cache;
extern Cache  EnCheckCache, DeCheckCache;//进安检口缓存 出安检口缓存
extern int SingleLinePos;//每列的格子数
typedef struct Pos //安检口坐标
{
	int x;
	int y;
}Pos;
extern Pos *OdiWin;
extern Pos *VipWin;


//函数声明
//maintain.c
//int MainPara();//维护配置文件
//input.c
unsigned _stdcall KeyEvent(void * p);//-------------------------KEYBOARD
int InputInt(int* num);
double random(int ,int);//正态分布函数
void MainInput();//生成随机事件
void AirportOnServe();//读取事件
//state.cpp
void DistriNum(entry *event);//为乘客分配号码并插入排队缓冲区
void WinRun();//安检口状态机
void PreWinRun(int);//缓冲区进安检口
int CheckWin();//判断安检口能否关闭 
void RestOrClosWin(entry *event);//接收安检口事件完成安检口下班及休息功能
void StateTrans(entry * event);//总控制函数
//output.c
void EventOutputFile(char event, int id, int no);//事件发生文件输出
void StatusOutput();//状态输出（cmd、file）
void FinalOutput();//下班输出（cmd、file）
void InitInterface();
//toy.cpp
void InitDraw();
void ResetCheckCache();
void toy();
int BeginOK(int);//判断乘客是否到位，到位开始设置安检时间
//Draw.cpp
void SetWin();//初始化安检口图像
void SetButton(); //初始化按键
unsigned _stdcall MouseEvent(void* p); //鼠标事件
void InitState();//安检口状态初始化
void UpdateState(); //安检口状态变化
//welcome.cpp
void InitInter();
bool judgeButton(int x, int y, int bx, int by,int width,int height);
void drawButton(int x, int y, int width, int height, char *str);
//configure.cpp
int ParaData();
void MainPara();
//main.cpp
int InitInterCheck();
void BeginServe();
//StarClock.cpp
void InitStar();
void StarClock();
#endif
