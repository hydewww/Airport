#include<stdio.h>
#include"global.h"
#include"passenger.h"
#include"window.h"

 int NumOfWin;			//1.普通安检口数目
 int NumOfVIPWin;		//2.VIP安检口数目
 int MinCheck;			//3.最少开放安检口数量
 int MaxCustCheck;		//4.安检口队伍最大长度
 int MinRestSec;		//5.安检口最小休息时长
 int MaxRestSec;		//6.安检口最大休息时长
 int MaxSec;			//7.安检口最大安检时长 单位是秒
 int MinSec;			//8.安检口最小安检时长 单位是秒
 int MaxCustSingleLine;	//9.缓冲区单队列最大乘客数
 int MaxLines;			//10.蛇形缓冲区最多由MaxLines个直队组成
 int MaxSeqLen;			//11.最大允许等待长度
 int EasySeqLen;		//12.短期等待长度

int MainPara()
{
	char c; //储存修改与否指示
	int num;//储存要修改信息的编号
	FILE * fp; //文件指针
	if ((fp = fopen("para.dat", "rb")) == NULL) //以只读方式打开配置文件para.dat
	{
		printf("Error! Can not open para.dat!\n");  //若无法打开，则报错
		exit(1);
	}
	fseek(fp, 0, SEEK_SET); //置文件指针于文件头部
	printf("当前配置文件信息:\n");
	//从配置文件读取数据
	fread(&NumOfWin, sizeof(int), 1, fp);
	printf("1. 普通安检口总数目:          %3d\n", NumOfWin);
	fread(&NumOfVIPWin, sizeof(int), 1, fp);
	printf("2. VIP安检口数目:             %3d\n", NumOfVIPWin);
	fread(&MinCheck, sizeof(int), 1, fp);
	printf("3. 最少开放安检口数量:        %3d\n", MinCheck);
	fread(&MaxCustCheck, sizeof(int), 1, fp);
	printf("4. 安检口队伍最大长度:        %3d\n", MaxCustCheck);
	fread(&MaxRestSec, sizeof(int), 1, fp);
	printf("5. 安检口最大休息时长:        %3d\n", MaxRestSec);
	fread(&MinRestSec, sizeof(int), 1, fp);
	printf("6. 安检口最小休息时长:        %3d\n", MinRestSec);
	fread(&MaxSec, sizeof(int), 1, fp);
	printf("7. 安检口最大安检时长:        %3d\n", MaxSec);
	fread(&MinSec, sizeof(int), 1, fp);
	printf("8. 安检口最小安检时长:        %3d\n", MinSec);
	fread(&MaxCustSingleLine, sizeof(int), 1, fp);
	printf("9. 单队列最大等待乘客数:      %3d\n", MaxCustSingleLine);
	fread(&MaxLines, sizeof(int), 1, fp);
	printf("10.蛇形缓冲区最大直队个数:    %3d\n", MaxLines);
	fread(&MaxSeqLen, sizeof(int), 1, fp);
	printf("11.最大允许等待长度:          %3d\n", MaxSeqLen);
	fread(&EasySeqLen, sizeof(int), 1, fp);
	printf("12.短期等待长度:              %3d\n", EasySeqLen);
	puts("");
	fclose(fp);//关闭文件指针

	while (1) //判断是否需要修改
	{
		printf("是否需要修改(Y/N): ");
		c = getchar();
		if (c == 'n' || c == 'N' || c == 'y' || c == 'Y') //输入正确
		{
			while (getchar() != '\n'); //清空缓冲区
			break;
		}
		printf("\t非法输入，请重新输入！\n"); //输入非法
		while (getchar() != '\n'); //清空缓冲区
	}
	puts("");
		if (c == 'n' || c == 'N') //不需要修改
		{
			return 0;
		}
		else  //需要修改
		{
			fp = fopen("para.dat", "rb+");
			int ret = 0;
			while (1)
			{
				do //检测输入的是否是数字
				{
					printf("输入要修改的信息编号,0代表完成修改,-1显示当前配置: ");
				} while (InputInt(&num));

				if (num == 0) //完成修改
				{
					printf("退出修改\n\n");
					break;
				}
				switch (num)
				{
				case -1:
					printf("1.普通安检口总数目:           %3d\n", NumOfWin);
					printf("2.VIP安检口总数目:            %3d\n", NumOfVIPWin);
					printf("3.最少开放安检口数量:         %3d\n", MinCheck);
					printf("4.安检口队伍最大长度:         %3d\n", MaxCustCheck);
					printf("5.安检口最大休息时长:         %3d\n", MaxRestSec);
					printf("6.安检口最小休息时长:         %3d\n", MinRestSec);
					printf("7.安检口最大安检时长:         %3d\n", MaxSec);
					printf("8.安检口最小安检时长:         %3d\n", MinSec);
					printf("9.单队列最大等待乘客数:       %3d\n", MaxCustSingleLine);
					printf("10.蛇形缓冲区最大直队个数:    %3d\n", MaxLines);
					printf("11.最大允许等待长度:          %3d\n", MaxSeqLen);
					printf("12.短期等待长度:              %3d\n", EasySeqLen);
					break;
				case 1:
					do {
						printf("1.普通安检口总数目:           %3d\n", NumOfWin);
						printf("请输入要修改的值:              ");
					} while (InputInt(&NumOfWin));
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&NumOfWin, sizeof(int), 1, fp);
					printf("修改完成\n");
					break;
				case 2:
					do {
						printf("2.VIP安检口总数目:            %3d\n", NumOfVIPWin);
						printf("请输入要修改的值:              ");
					} while (InputInt(&NumOfVIPWin));	
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&NumOfVIPWin, sizeof(int), 1, fp);
					printf("修改完成\n");
					break;
				case 3:
					do {
						printf("3.最少开放安检口数量:         %3d\n", MinCheck);
						printf("请输入要修改的值:              ");
					} while (InputInt(&MinCheck));
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&MinCheck, sizeof(int), 1, fp);
					printf("修改完成\n");
					break;
				case 4:
					do{
						printf("4.安检口队伍最大长度:         %3d\n", MaxCustCheck);
						printf("请输入要修改的值:              ");
					} while (InputInt(&MaxCustCheck));
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&MaxCustCheck, sizeof(int), 1, fp);
					printf("修改完成\n");
					break;
				case 5:
					do{
					printf("5.安检口最大休息时长:         %3d\n", MaxRestSec);
					printf("请输入要修改的值:              ");
					} while (InputInt(&MaxRestSec));
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&MaxRestSec, sizeof(int), 1, fp);
					printf("修改完成\n");
					break;
				case 6:
					do{
					printf("6.安检口口最小休息时长:       %3d\n", MinRestSec);
					printf("请输入要修改的值:              ");
					} while (InputInt(&MinRestSec));
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&MinRestSec, sizeof(int), 1, fp);
					printf("修改完成\n");
					break;
				case 7:
					do{
					printf("7.安检口最大安检时长:         %3d\n", MaxSec);
					printf("请输入要修改的值:              ");
					} while (InputInt(&MaxSec));
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&MaxSec, sizeof(int), 1, fp);
					printf("修改完成\n");
					break;
				case 8:
					do{
					printf("8.安检口最小安检时长:         %3d\n", MinSec);
					printf("请输入要修改的值:              ");
					} while (InputInt(&MinSec));
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&MinSec, sizeof(int), 1, fp);
					printf("修改完成\n");
					break;
				case 9:
					do{
					printf("9.单队列最大等待乘客数:       %3d\n", MaxCustSingleLine);
					printf("请输入要修改的值:              ");
					} while (InputInt(&MaxCustSingleLine));
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&MaxCustSingleLine, sizeof(int), 1, fp);
					printf("修改完成\n");
					break;
				case 10:
					do{
					printf("10.蛇形缓冲区最大直队个数:     %3d\n", MaxLines);
					printf("请输入要修改的值:              ");
					} while (InputInt(&MaxLines));
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&MaxLines, sizeof(int), 1, fp);
					printf("修改完成\n");
					break;
				case 11:
					do{
					printf("11.最大允许等待长度:          %3d\n", MaxSeqLen);
					printf("请输入要修改的值:               ");
					} while (InputInt(&MaxSeqLen));
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&MaxSeqLen, sizeof(int), 1, fp);
					printf("修改完成\n");
					break;
				case 12:
					do{
					printf("12.短期等待长度:              %3d\n", EasySeqLen);
					printf("请输入要修改的值:              ");
					} while (InputInt(&EasySeqLen));
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&EasySeqLen, sizeof(int), 1, fp);
					printf("修改完成\n");
					break;
				default:
					printf("非法输入，请重新输入！\n");
				}//switch
				puts("");
			} //while
			fclose(fp);
		}//else
		return 0;
}