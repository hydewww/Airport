#include<stdio.h>
#include"global.h"

 int NumOfWin;//安检口总数目
 int MinRestSec;//安检口口最小休息时长
 int MaxRestSec;//安检口最大休息时长
 int MaxCustSingleLine;// 单队列最大等待乘客数
 int MaxLines;// 蛇形缓冲区最多由MaxLines个直队组成
 int MaxSeqLen;// 最大允许等待长度
 int EasySeqLen;// 短期等待长度
 int MinCheck;// 最少开放安检口数量
 int MaxCheck;// 最多开放安检口数量
 int MaxCustCheck;// 安检口队伍最大长度
 int MaxSec;// 安检口最大安检时长 单位是秒
 int MinSec;// 安检口最小安检时长 单位是秒

int MainPara()
{
	char c; //储存修改与否指示
	int num;//储存要修改信息的编号
	FILE * fp; //文件指针
	if ((fp = fopen("para.dat", "rb")) == NULL) //以只读方式打开配置文件para.dat
	{
		printf("error! Can not open para.dat!\n");  //若无法打开，则报错
	}
	fseek(fp, 0, SEEK_SET); //置文件指针于文件头部
	printf("当前配置文件信息:\n");
	//从配置文件读取数据
	fread(&NumOfWin, sizeof(int), 1, fp);
	printf("1.安检口总数目:               %3d\n", NumOfWin);
	fread(&MinRestSec, sizeof(int), 1, fp);
	printf("2.安检口口最小休息时长:       %3d\n", MinRestSec);
	fread(&MaxRestSec, sizeof(int), 1, fp);
	printf("3.安检口最大休息时长:         %3d\n", MaxRestSec);
	fread(&MaxCustSingleLine, sizeof(int), 1, fp);
	printf("4.单队列最大等待乘客数:       %3d\n", MaxCustSingleLine);
	fread(&MaxLines, sizeof(int), 1, fp);
	printf("5.蛇形缓冲区最大直队个数:     %3d\n", MaxLines);
	fread(&MaxSeqLen, sizeof(int), 1, fp);
	printf("6.最大允许等待长度:           %3d\n", MaxSeqLen);
	fread(&EasySeqLen, sizeof(int), 1, fp);
	printf("7.短期等待长度:               %3d\n", EasySeqLen);
	fread(&MinCheck, sizeof(int), 1, fp);
	printf("8.最少开放安检口数量:         %3d\n", MinCheck);
	fread(&MaxCheck, sizeof(int), 1, fp);
	printf("9.最多开放安检口数量:         %3d\n", MaxCheck);
	fread(&MaxCustCheck, sizeof(int), 1, fp);
	printf("10.安检口队伍最大长度:        %3d\n", MaxCustCheck);
	fread(&MaxSec, sizeof(int), 1, fp);
	printf("11.安检口最大安检时长:        %3d\n", MaxSec);
	fread(&MinSec, sizeof(int), 1, fp);
	printf("12.安检口最小安检时长:        %3d\n", MinSec);
	fclose(fp);//关闭文件指针

	while (1) //判断是否需要修改
	{
		printf("是否需要修改:\tY\tN\n");
		c = getchar();
		if (c == 'n' || c == 'N' || c == 'y' || c == 'Y') //输入正确
		{
			break;
		}
		printf("非法输入，请重新输入！\n"); //输入非法
	}
		if (c == 'n' || c == 'N') //不需要修改
		{
			return 0;
		}
		else  //需要修改
		{
			fp = fopen("para.dat", "rb+");
			while (1)
			{
				printf("输入要修改的信息编号,0代表完成修改:\n");
				scanf("%d", &num);
				if (num == 0) //完成修改
				{
					break;
				}
				switch (num)
				{
				case 1:
					printf("1.安检口总数目:               %3d\n", NumOfWin);
					printf("请输入要修改的值:              ");
					scanf("%d", &NumOfWin);
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&NumOfWin, sizeof(int), 1, fp);
					printf("修改完成\n");
					break;
				case 2:
					printf("2.安检口口最小休息时长:       %3d\n", MinRestSec);
					printf("请输入要修改的值:              ");
					scanf("%d", &MinRestSec);
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&MinRestSec, sizeof(int), 1, fp);
					printf("修改完成\n");
					break;
				case 3:
					printf("3.安检口最大休息时长:         %3d\n", MaxRestSec);
					printf("请输入要修改的值:              ");
					scanf("%d", &MaxRestSec);
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&MaxRestSec, sizeof(int), 1, fp);
					printf("修改完成\n");
					break;
				case 4:
					printf("4.单队列最大等待乘客数:       %3d\n", MaxCustSingleLine);
					printf("请输入要修改的值:              ");
					scanf("%d", &MaxCustSingleLine);
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&MaxCustSingleLine, sizeof(int), 1, fp);
					printf("修改完成\n");
					break;
				case 5:
					printf("5.蛇形缓冲区最大直队个数:     %3d\n", MaxLines);
					printf("请输入要修改的值:              ");
					scanf("%d", &MaxLines);
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&MaxLines, sizeof(int), 1, fp);
					printf("修改完成\n");
					break;
				case 6:
					printf("6.最大允许等待长度:           %3d\n", MaxSeqLen);
					printf("请输入要修改的值:              ");
					scanf("%d", &MaxSeqLen);
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&MaxSeqLen, sizeof(int), 1, fp);
					printf("修改完成\n");
					break;
				case 7:
					printf("7.短期等待长度:               %3d\n", EasySeqLen);
					printf("请输入要修改的值:              ");
					scanf("%d", &EasySeqLen);
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&EasySeqLen, sizeof(int), 1, fp);
					printf("修改完成\n");
					break;
				case 8:
					printf("8.最少开放安检口数量:         %3d\n", MinCheck);
					printf("请输入要修改的值:              ");
					scanf("%d", &MinCheck);
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&MinCheck, sizeof(int), 1, fp);
					printf("修改完成\n");
					break;
				case 9:
					printf("9.最多开放安检口数量:         %3d\n", MaxCheck);
					printf("请输入要修改的值:              ");
					scanf("%d", &MaxCheck);
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&MaxCheck, sizeof(int), 1, fp);
					printf("修改完成\n");
					break;
				case 10:
					printf("10.安检口队伍最大长度:        %3d\n", MaxCustCheck);
					printf("请输入要修改的值:              ");
					scanf("%d", MaxCustCheck);
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&MaxCustCheck, sizeof(int), 1, fp);
					printf("修改完成\n");
					break;
				case 11:
					printf("11.安检口最大安检时长:        %3d\n", MaxSec);
					printf("请输入要修改的值:              ");
					scanf("%d", &MaxSec);
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&MaxSec, sizeof(int), 1, fp);
					printf("修改完成\n");
					break;
				case 12:
					printf("12.安检口最小安检时长:        %3d\n", MinSec);
					printf("请输入要修改的值:              ");
					scanf("%d", &MinSec);
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&MinSec, sizeof(int), 1, fp);
					printf("修改完成\n");
					break;
				default:
					printf("非法输入，请重新输入！\n");
				}//switch

			} //while
			fclose(fp);
		}//else
		return 0;
}