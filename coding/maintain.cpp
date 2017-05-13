#include<stdio.h>
#include"global.h"

 int NumOfWin;//���������Ŀ
 int MinRestSec;//����ڿ���С��Ϣʱ��
 int MaxRestSec;//����������Ϣʱ��
 int MaxCustSingleLine;// ���������ȴ��˿���
 int MaxLines;// ���λ����������MaxLines��ֱ�����
 int MaxSeqLen;// �������ȴ�����
 int EasySeqLen;// ���ڵȴ�����
 int MinCheck;// ���ٿ��Ű��������
 int MaxCheck;// ��࿪�Ű��������
 int MaxCustCheck;// ����ڶ�����󳤶�
 int MaxSec;// �������󰲼�ʱ�� ��λ����
 int MinSec;// �������С����ʱ�� ��λ����

int MainPara()
{
	char c; //�����޸����ָʾ
	int num;//����Ҫ�޸���Ϣ�ı��
	FILE * fp; //�ļ�ָ��
	if ((fp = fopen("para.dat", "rb")) == NULL) //��ֻ����ʽ�������ļ�para.dat
	{
		printf("error! Can not open para.dat!\n");  //���޷��򿪣��򱨴�
	}
	fseek(fp, 0, SEEK_SET); //���ļ�ָ�����ļ�ͷ��
	printf("��ǰ�����ļ���Ϣ:\n");
	//�������ļ���ȡ����
	fread(&NumOfWin, sizeof(int), 1, fp);
	printf("1.���������Ŀ:               %3d\n", NumOfWin);
	fread(&MinRestSec, sizeof(int), 1, fp);
	printf("2.����ڿ���С��Ϣʱ��:       %3d\n", MinRestSec);
	fread(&MaxRestSec, sizeof(int), 1, fp);
	printf("3.����������Ϣʱ��:         %3d\n", MaxRestSec);
	fread(&MaxCustSingleLine, sizeof(int), 1, fp);
	printf("4.���������ȴ��˿���:       %3d\n", MaxCustSingleLine);
	fread(&MaxLines, sizeof(int), 1, fp);
	printf("5.���λ��������ֱ�Ӹ���:     %3d\n", MaxLines);
	fread(&MaxSeqLen, sizeof(int), 1, fp);
	printf("6.�������ȴ�����:           %3d\n", MaxSeqLen);
	fread(&EasySeqLen, sizeof(int), 1, fp);
	printf("7.���ڵȴ�����:               %3d\n", EasySeqLen);
	fread(&MinCheck, sizeof(int), 1, fp);
	printf("8.���ٿ��Ű��������:         %3d\n", MinCheck);
	fread(&MaxCheck, sizeof(int), 1, fp);
	printf("9.��࿪�Ű��������:         %3d\n", MaxCheck);
	fread(&MaxCustCheck, sizeof(int), 1, fp);
	printf("10.����ڶ�����󳤶�:        %3d\n", MaxCustCheck);
	fread(&MaxSec, sizeof(int), 1, fp);
	printf("11.�������󰲼�ʱ��:        %3d\n", MaxSec);
	fread(&MinSec, sizeof(int), 1, fp);
	printf("12.�������С����ʱ��:        %3d\n", MinSec);
	fclose(fp);//�ر��ļ�ָ��

	while (1) //�ж��Ƿ���Ҫ�޸�
	{
		printf("�Ƿ���Ҫ�޸�:\tY\tN\n");
		c = getchar();
		if (c == 'n' || c == 'N' || c == 'y' || c == 'Y') //������ȷ
		{
			break;
		}
		printf("�Ƿ����룬���������룡\n"); //����Ƿ�
	}
		if (c == 'n' || c == 'N') //����Ҫ�޸�
		{
			return 0;
		}
		else  //��Ҫ�޸�
		{
			fp = fopen("para.dat", "rb+");
			while (1)
			{
				printf("����Ҫ�޸ĵ���Ϣ���,0��������޸�:\n");
				scanf("%d", &num);
				if (num == 0) //����޸�
				{
					break;
				}
				switch (num)
				{
				case 1:
					printf("1.���������Ŀ:               %3d\n", NumOfWin);
					printf("������Ҫ�޸ĵ�ֵ:              ");
					scanf("%d", &NumOfWin);
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&NumOfWin, sizeof(int), 1, fp);
					printf("�޸����\n");
					break;
				case 2:
					printf("2.����ڿ���С��Ϣʱ��:       %3d\n", MinRestSec);
					printf("������Ҫ�޸ĵ�ֵ:              ");
					scanf("%d", &MinRestSec);
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&MinRestSec, sizeof(int), 1, fp);
					printf("�޸����\n");
					break;
				case 3:
					printf("3.����������Ϣʱ��:         %3d\n", MaxRestSec);
					printf("������Ҫ�޸ĵ�ֵ:              ");
					scanf("%d", &MaxRestSec);
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&MaxRestSec, sizeof(int), 1, fp);
					printf("�޸����\n");
					break;
				case 4:
					printf("4.���������ȴ��˿���:       %3d\n", MaxCustSingleLine);
					printf("������Ҫ�޸ĵ�ֵ:              ");
					scanf("%d", &MaxCustSingleLine);
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&MaxCustSingleLine, sizeof(int), 1, fp);
					printf("�޸����\n");
					break;
				case 5:
					printf("5.���λ��������ֱ�Ӹ���:     %3d\n", MaxLines);
					printf("������Ҫ�޸ĵ�ֵ:              ");
					scanf("%d", &MaxLines);
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&MaxLines, sizeof(int), 1, fp);
					printf("�޸����\n");
					break;
				case 6:
					printf("6.�������ȴ�����:           %3d\n", MaxSeqLen);
					printf("������Ҫ�޸ĵ�ֵ:              ");
					scanf("%d", &MaxSeqLen);
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&MaxSeqLen, sizeof(int), 1, fp);
					printf("�޸����\n");
					break;
				case 7:
					printf("7.���ڵȴ�����:               %3d\n", EasySeqLen);
					printf("������Ҫ�޸ĵ�ֵ:              ");
					scanf("%d", &EasySeqLen);
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&EasySeqLen, sizeof(int), 1, fp);
					printf("�޸����\n");
					break;
				case 8:
					printf("8.���ٿ��Ű��������:         %3d\n", MinCheck);
					printf("������Ҫ�޸ĵ�ֵ:              ");
					scanf("%d", &MinCheck);
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&MinCheck, sizeof(int), 1, fp);
					printf("�޸����\n");
					break;
				case 9:
					printf("9.��࿪�Ű��������:         %3d\n", MaxCheck);
					printf("������Ҫ�޸ĵ�ֵ:              ");
					scanf("%d", &MaxCheck);
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&MaxCheck, sizeof(int), 1, fp);
					printf("�޸����\n");
					break;
				case 10:
					printf("10.����ڶ�����󳤶�:        %3d\n", MaxCustCheck);
					printf("������Ҫ�޸ĵ�ֵ:              ");
					scanf("%d", MaxCustCheck);
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&MaxCustCheck, sizeof(int), 1, fp);
					printf("�޸����\n");
					break;
				case 11:
					printf("11.�������󰲼�ʱ��:        %3d\n", MaxSec);
					printf("������Ҫ�޸ĵ�ֵ:              ");
					scanf("%d", &MaxSec);
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&MaxSec, sizeof(int), 1, fp);
					printf("�޸����\n");
					break;
				case 12:
					printf("12.�������С����ʱ��:        %3d\n", MinSec);
					printf("������Ҫ�޸ĵ�ֵ:              ");
					scanf("%d", &MinSec);
					fseek(fp, sizeof(int)*(num - 1), SEEK_SET);
					fwrite(&MinSec, sizeof(int), 1, fp);
					printf("�޸����\n");
					break;
				default:
					printf("�Ƿ����룬���������룡\n");
				}//switch

			} //while
			fclose(fp);
		}//else
		return 0;
}