#include<stdio.h>
#include"global.h"
#include"passenger.h"
#include"window.h"

 int NumOfWin;			//1.��ͨ�������Ŀ
 int NumOfVIPWin;		//2.VIP�������Ŀ
 int MinCheck;			//3.���ٿ��Ű��������
 int MaxCustCheck;		//4.����ڶ�����󳤶�
 int MinRestSec;		//5.�������С��Ϣʱ��
 int MaxRestSec;		//6.����������Ϣʱ��
 int MaxSec;			//7.�������󰲼�ʱ�� ��λ����
 int MinSec;			//8.�������С����ʱ�� ��λ����
 int MaxCustSingleLine;	//9.���������������˿���
 int MaxLines;			//10.���λ����������MaxLines��ֱ�����
 int MaxSeqLen;			//11.�������ȴ�����
 int EasySeqLen;		//12.���ڵȴ�����

int MainPara()
{
	char c; //�����޸����ָʾ
	int num;//����Ҫ�޸���Ϣ�ı��
	FILE * fp; //�ļ�ָ��
	if ((fp = fopen("para.dat", "rb")) == NULL) //��ֻ����ʽ�������ļ�para.dat
	{
		printf("Error! Can not open para.dat!\n");  //���޷��򿪣��򱨴�
		exit(1);
	}
	fseek(fp, 0, SEEK_SET); //���ļ�ָ�����ļ�ͷ��
	printf("��ǰ�����ļ���Ϣ:\n");
	//�������ļ���ȡ����
	fread(&NumOfWin, sizeof(int), 1, fp);
	printf("1. ��ͨ���������Ŀ:          %3d\n", NumOfWin);
	fread(&NumOfVIPWin, sizeof(int), 1, fp);
	printf("2. VIP�������Ŀ:             %3d\n", NumOfVIPWin);
	fread(&MinCheck, sizeof(int), 1, fp);
	printf("3. ���ٿ��Ű��������:        %3d\n", MinCheck);
	fread(&MaxCustCheck, sizeof(int), 1, fp);
	printf("4. ����ڶ�����󳤶�:        %3d\n", MaxCustCheck);
	fread(&MaxRestSec, sizeof(int), 1, fp);
	printf("5. ����������Ϣʱ��:        %3d\n", MaxRestSec);
	fread(&MinRestSec, sizeof(int), 1, fp);
	printf("6. �������С��Ϣʱ��:        %3d\n", MinRestSec);
	fread(&MaxSec, sizeof(int), 1, fp);
	printf("7. �������󰲼�ʱ��:        %3d\n", MaxSec);
	fread(&MinSec, sizeof(int), 1, fp);
	printf("8. �������С����ʱ��:        %3d\n", MinSec);
	fread(&MaxCustSingleLine, sizeof(int), 1, fp);
	printf("9. ���������ȴ��˿���:      %3d\n", MaxCustSingleLine);
	fread(&MaxLines, sizeof(int), 1, fp);
	printf("10.���λ��������ֱ�Ӹ���:    %3d\n", MaxLines);
	fread(&MaxSeqLen, sizeof(int), 1, fp);
	printf("11.�������ȴ�����:          %3d\n", MaxSeqLen);
	fread(&EasySeqLen, sizeof(int), 1, fp);
	printf("12.���ڵȴ�����:              %3d\n", EasySeqLen);
	puts("");
	fclose(fp);//�ر��ļ�ָ��

	while (1) //�ж��Ƿ���Ҫ�޸�
	{
		printf("�Ƿ���Ҫ�޸�(Y/N): ");
		c = getchar();
		if (c == 'n' || c == 'N' || c == 'y' || c == 'Y') //������ȷ
		{
			while (getchar() != '\n'); //��ջ�����
			break;
		}
		printf("\t�Ƿ����룬���������룡\n"); //����Ƿ�
		while (getchar() != '\n'); //��ջ�����
	}
	puts("");
		if (c == 'n' || c == 'N') //����Ҫ�޸�
		{
			return 0;
		}
		else  //��Ҫ�޸�
		{
			fp = fopen("para.dat", "rb+");
			int ret = 0;
			while (1)
			{
				do //���������Ƿ�������
				{
					printf("����Ҫ�޸ĵ���Ϣ���,0��������޸�,-1��ʾ��ǰ����: ");
				} while (InputInt(&num));

				if (num == 0) //����޸�
				{
					printf("�˳��޸�\n\n");
					break;
				}
				switch (num)
				{
				case -1:
					printf("1.��ͨ���������Ŀ:           %3d\n", NumOfWin);
					printf("2.VIP���������Ŀ:            %3d\n", NumOfVIPWin);
					printf("3.���ٿ��Ű��������:         %3d\n", MinCheck);
					printf("4.����ڶ�����󳤶�:         %3d\n", MaxCustCheck);
					printf("5.����������Ϣʱ��:         %3d\n", MaxRestSec);
					printf("6.�������С��Ϣʱ��:         %3d\n", MinRestSec);
					printf("7.�������󰲼�ʱ��:         %3d\n", MaxSec);
					printf("8.�������С����ʱ��:         %3d\n", MinSec);
					printf("9.���������ȴ��˿���:       %3d\n", MaxCustSingleLine);
					printf("10.���λ��������ֱ�Ӹ���:    %3d\n", MaxLines);
					printf("11.�������ȴ�����:          %3d\n", MaxSeqLen);
					printf("12.���ڵȴ�����:              %3d\n", EasySeqLen);
					break;
				case 1:
					do {
						printf("1.��ͨ���������Ŀ:           %3d\n", NumOfWin);
						printf("������Ҫ�޸ĵ�ֵ:              ");
					} while (InputInt(&NumOfWin));
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&NumOfWin, sizeof(int), 1, fp);
					printf("�޸����\n");
					break;
				case 2:
					do {
						printf("2.VIP���������Ŀ:            %3d\n", NumOfVIPWin);
						printf("������Ҫ�޸ĵ�ֵ:              ");
					} while (InputInt(&NumOfVIPWin));	
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&NumOfVIPWin, sizeof(int), 1, fp);
					printf("�޸����\n");
					break;
				case 3:
					do {
						printf("3.���ٿ��Ű��������:         %3d\n", MinCheck);
						printf("������Ҫ�޸ĵ�ֵ:              ");
					} while (InputInt(&MinCheck));
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&MinCheck, sizeof(int), 1, fp);
					printf("�޸����\n");
					break;
				case 4:
					do{
						printf("4.����ڶ�����󳤶�:         %3d\n", MaxCustCheck);
						printf("������Ҫ�޸ĵ�ֵ:              ");
					} while (InputInt(&MaxCustCheck));
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&MaxCustCheck, sizeof(int), 1, fp);
					printf("�޸����\n");
					break;
				case 5:
					do{
					printf("5.����������Ϣʱ��:         %3d\n", MaxRestSec);
					printf("������Ҫ�޸ĵ�ֵ:              ");
					} while (InputInt(&MaxRestSec));
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&MaxRestSec, sizeof(int), 1, fp);
					printf("�޸����\n");
					break;
				case 6:
					do{
					printf("6.����ڿ���С��Ϣʱ��:       %3d\n", MinRestSec);
					printf("������Ҫ�޸ĵ�ֵ:              ");
					} while (InputInt(&MinRestSec));
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&MinRestSec, sizeof(int), 1, fp);
					printf("�޸����\n");
					break;
				case 7:
					do{
					printf("7.�������󰲼�ʱ��:         %3d\n", MaxSec);
					printf("������Ҫ�޸ĵ�ֵ:              ");
					} while (InputInt(&MaxSec));
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&MaxSec, sizeof(int), 1, fp);
					printf("�޸����\n");
					break;
				case 8:
					do{
					printf("8.�������С����ʱ��:         %3d\n", MinSec);
					printf("������Ҫ�޸ĵ�ֵ:              ");
					} while (InputInt(&MinSec));
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&MinSec, sizeof(int), 1, fp);
					printf("�޸����\n");
					break;
				case 9:
					do{
					printf("9.���������ȴ��˿���:       %3d\n", MaxCustSingleLine);
					printf("������Ҫ�޸ĵ�ֵ:              ");
					} while (InputInt(&MaxCustSingleLine));
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&MaxCustSingleLine, sizeof(int), 1, fp);
					printf("�޸����\n");
					break;
				case 10:
					do{
					printf("10.���λ��������ֱ�Ӹ���:     %3d\n", MaxLines);
					printf("������Ҫ�޸ĵ�ֵ:              ");
					} while (InputInt(&MaxLines));
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&MaxLines, sizeof(int), 1, fp);
					printf("�޸����\n");
					break;
				case 11:
					do{
					printf("11.�������ȴ�����:          %3d\n", MaxSeqLen);
					printf("������Ҫ�޸ĵ�ֵ:               ");
					} while (InputInt(&MaxSeqLen));
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&MaxSeqLen, sizeof(int), 1, fp);
					printf("�޸����\n");
					break;
				case 12:
					do{
					printf("12.���ڵȴ�����:              %3d\n", EasySeqLen);
					printf("������Ҫ�޸ĵ�ֵ:              ");
					} while (InputInt(&EasySeqLen));
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&EasySeqLen, sizeof(int), 1, fp);
					printf("�޸����\n");
					break;
				default:
					printf("�Ƿ����룬���������룡\n");
				}//switch
				puts("");
			} //while
			fclose(fp);
		}//else
		return 0;
}