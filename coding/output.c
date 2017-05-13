#include<stdio.h>
extern int NumOfWin;		//安检口总数目
extern int MinRestSec;		//安检口口最小休息时长
extern int MaxRestSec;		//安检口最大休息时长
extern int MaxCustSingleLine;//单队列最大等待乘客数
extern int MaxLines;		//蛇形缓冲区最多由MaxLines个直队组成
extern int MaxSeqLen;		//最大允许等待长度
extern int EasySeqLen;		// 短期等待长度
extern int MinCheck;		//最少开放安检口数量
extern int MaxCheck;		//最多开放安检口数量
extern int MaxCustCheck;	//安检口队伍最大长度
extern int MaxSec;			//安检口最大安检时长单位是秒
extern int MinSec;			//检口最小安检时长
	
void CusOutput() {

}