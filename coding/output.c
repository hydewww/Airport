#include"global.h"
#include"passenger.h"
#include"window.h"
#include"queue.h"
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<process.h>

void StatusOutputCmd();
void StatusOutputFile();
void StatusOutput() {
	StatusOutputCmd();
	StatusOutputFile();
}

void FinalOutputCmd();
void FinalOutputFile();
void FinalOutput() {
	FinalOutputCmd();
	FinalOutputFile();
}


/*StatusOutputCmd���ú���*/
void QueuePrint();//��ͼ�ν������λ�����
void WinPrint(Window win);//����״̬
/*over*/

//cmd״̬��� 1s
//time_t PreCmd; //��¼�ϴ����ʱ��---------------------------------------
clock_t PreCmd=0; //�޸���clock()����
clock_t NowCmd=0;
void StatusOutputCmd() {
	
	/*time(&TimeNow);
	//���ϴ��������1��  & �������ڹ���  => ����
	if (((difftime(TimeNow, PreCmd)) < 2) && (AirportState != OffWork))
		//return;
	PreCmd = TimeNow;	//��¼ʱ��*/

	NowCmd=clock(); //�޸���clock������
	if (((NowCmd - PreCmd) / CLOCKS_PER_SEC) < 1.5 && (AirportState != OffWork))
		return;
	PreCmd = NowCmd;


	system("CLS");
	//printf("��ǰ�¼���%d", thisEvent.no);/* test */
	printf("ʱ�� : %s", ctime(&TimeNow));
	//����״̬
	switch (AirportState) {
	case 0:printf("����״̬ = �°�\n"); break;
	case 1:printf("����״̬ = ���ڹ���\n"); break;
	case 2:printf("����״̬ = ׼���°�\n"); break;
	default: printf("����״̬�쳣"); exit(1);
	}
	//����״̬
	for (int i = 0; i < NumOfWin; i++) {
		//����n
		printf("WIN%02d  ", i+1);
		//����״̬
		WinPrint(Win[i]);
	}
	for (int i = 0; i < NumOfVIPWin; i++) {
		//����n
		printf("VIP%02d  ", i + 1);
		//����״̬
		WinPrint(VIPWin[i]);
	}

	//�Ŷӻ�����״̬
	if (OdinQueue->QueueHead->next != NULL) 
		QueuePrint(); //��ͼ�ν������λ�����
	else
		puts("\n�Ŷӻ���������");
}

//cmd�°����
void FinalOutputCmd() {
	system("cls");
	printf("�°�������������������������������������������\n\n");
	printf("�ϰ�ʱ�䣺%s", ctime(&TimeStart));
	printf("�°�ʱ��: %s", ctime(&TimeFinish));
	printf("���շ���������: %d  �ܹ�Ӫҵʱ��: %02d:%02d\n\n\n", OdinQueue->SumNum+VipQueue->SumNum, (TimeFinish - TimeStart) / 60, (TimeFinish - TimeStart) % 60);
	for (int i = 0; i < NumOfWin; i++) {
		//����n
		printf("WIN%02d  ", i + 1);
		//����״̬
		printf("�ܹ���������: %3d  �ܹ�����ʱ��: %02d:%02d\n", Win[i].TotalSer, Win[i].TotalTime/60,Win[i].TotalTime%60);
	}
	for (int i = 0; i < NumOfVIPWin; i++) {
		//����n
		printf("VIP%02d  ", i + 1);
		//����״̬
		printf("�ܹ���������: %3d  �ܹ�����ʱ��: %02d:%02d\n", VIPWin[i].TotalSer, VIPWin[i].TotalTime/60,VIPWin[i].TotalTime%60);
	}
}


//file�¼����
void EventOutputFile(char event, int PasID, int WinID) {	//PasID�˿� WinID�����
															//StatusOutputFile();
	FILE * fp;
	if (!(fp = fopen("output.txt", "a"))) {
		puts("Error: cannot open the file \"output.txt\".");
		exit(1);
	}
	switch (event) {
	case 'G':fprintf(fp, "%d�ų˿ͽ����Ŷӻ�����\n", PasID); printf("%d�ų˿ͽ����Ŷӻ�����\n", PasID); break;
	case 'F':fprintf(fp, "�Ŷӻ���������\n"); printf( "�Ŷӻ���������\n"); break;
	case 'C':fprintf(fp, "%d�ų˿ͽ���%d�Ű����\n", PasID, WinID); printf("%d�ų˿ͽ���%d�Ű����\n", PasID, WinID); break;
	case 'c':fprintf(fp, "%d��Vip����%d��Vip�����\n", PasID, WinID); printf("%d��Vip����%d��Vip�����\n", PasID, WinID); break;
	case 'L':fprintf(fp, "%d�ų˿���ɰ����뿪\n", PasID); printf("%d�ų˿���ɰ����뿪\n", PasID); break;
	case 'B':fprintf(fp, "[Warning] %d�ų˿Ͱ���ʧ��!\n", PasID);printf("[Warning] %d�ų˿Ͱ���ʧ��!\n", PasID); break;
	case 'O':fprintf(fp, "%d�Ű���ڿ���\n", WinID); printf("%d�Ű���ڿ���\n", WinID); break;
	case 'S':fprintf(fp, "%d�Ű���ڹر�\n", WinID);printf("%d�Ű���ڹر�\n", WinID); break;
	case 'X':fprintf(fp, "%d�Ű����������Ϣ\n", WinID);printf("%d�Ű����������Ϣ\n", WinID); break;
	case 'K':fprintf(fp, "%d�Ű���ڿ�ʼ��Ϣ\n", WinID);printf("%d�Ű���ڿ�ʼ��Ϣ\n", WinID); break;
	case 'J':fprintf(fp, "%d�Ű���ڽ�����Ϣ\n", WinID);printf("%d�Ű���ڽ�����Ϣ\n", WinID); break;
	case 'Q':fprintf(fp, "���յ��°�ָ��\n"); printf("���յ��°�ָ��\n"); break;
	default:fprintf(fp, "���յ�δ֪�¼�\n");printf("���յ�δ֪�¼�\n"); break;
	}
	fflush(fp);
	fclose(fp);
}

//file�°����  ����cmd
void FinalOutputFile() {
	FILE* fp;
	if (!(fp = fopen("output.txt", "a"))) {
		puts("Error: cannot open the file \"output.txt\".");
		exit(1);
	}
	fprintf(fp, "-------------------------------------------------------\n");

	fprintf(fp,"�°�������������������������������������������\n\n");
	fprintf(fp,"�ϰ�ʱ�䣺%s", ctime(&TimeStart));
	fprintf(fp,"�°�ʱ��: %s", ctime(&TimeFinish));
	fprintf(fp,"���շ���������: %d  �ܹ�Ӫҵʱ��: %02d:%02d\n\n\n", OdinQueue->SumNum + VipQueue->SumNum, (TimeFinish - TimeStart) / 60, (TimeFinish - TimeStart) % 60);
	for (int i = 0; i < NumOfWin; i++) {
		//����n
		fprintf(fp,"WIN%02d  ", i + 1);
		//����״̬
		fprintf(fp,"�ܹ���������: %3d  �ܹ�����ʱ��: %02d:%02d\n", Win[i].TotalSer, Win[i].TotalTime / 60, Win[i].TotalTime % 60);
	}
	for (int i = 0; i < NumOfVIPWin; i++) {
		//����n
		fprintf(fp,"VIP%02d  ", i + 1);
		//����״̬
		fprintf(fp,"�ܹ���������: %3d  �ܹ�����ʱ��: %02d:%02d\n", VIPWin[i].TotalSer, VIPWin[i].TotalTime / 60, VIPWin[i].TotalTime % 60);
	}
	
	fprintf(fp, "-------------------------------------------------------\n");
	fflush(fp);
	fclose(fp);
}

//file״̬��� 3s ����cmd
time_t PreFile;
void StatusOutputFile() {
	time(&TimeNow);
	if (difftime(TimeNow, PreFile)<3)
		return;
	PreFile = TimeNow;
	FILE* fp;
	if (!(fp = fopen("output.txt", "a"))) {
		puts("Error: cannot open the file \"output.txt\".");
		exit(1);
	}
	fprintf(fp, "-------------------------------------------------------\n");
	fprintf(fp, "ʱ�� : %s", ctime(&TimeNow));
	//����״̬
	switch (AirportState) {
	case 0:fprintf(fp, "����״̬ = �°�\n"); break;
	case 1:fprintf(fp, "����״̬ = ���ڹ���\n"); break;
	case 2:fprintf(fp, "����״̬ = ׼���°�\n"); break;
	default: fprintf(fp, "����״̬�쳣"); exit(1);
	}

	//����״̬
	for (int i = 0; i < NumOfWin; i++) {
		//����n
		fprintf(fp, "WIN%02d  ", i + 1);
		//����״̬
		switch (Win[i].WinState) {
		case 0:fprintf(fp, "    �ر�"); break;
		case 1:fprintf(fp, "  ������"); break;
		case 2:fprintf(fp, "  ������"); break;
		case 3:fprintf(fp, "  ��Ϣ��"); break;
		case 4:fprintf(fp, "׼����Ϣ"); break;
		case 5:fprintf(fp, "׼���ر�"); break;
		default:fprintf(fp, "\n����״̬�쳣��\n"); exit(1); break;
		}
		//���ڰ���
		if (Win[i].NowPas) {
			fprintf(fp, "\t���ڰ���: %3d ", Win[i].NowPas->id);
		}
		else {
			fprintf(fp, "\t���ڰ���:  �� ");
		}
		//���ڶ���
		if (Win[i].WinHead != Win[i].WinTail) {	//�п�
			fprintf(fp, " , ����:");
			Passenger* cur = Win[i].WinHead;
			do {
				cur = cur->next;
				fprintf(fp, " %3d", cur->id);
			} while (cur != Win[i].WinTail);
		}
		fprintf(fp, "\n");
	}
	//�Ŷӻ�����״̬
	if (OdinQueue->QueueHead->next != NULL) {
		fprintf(fp, "�Ŷӻ�����������: %d ,�׳˿�: %d , β�˿�: %d , ������: %d\n", OdinQueue->WaitNum, OdinQueue->QueueHead->next->id, OdinQueue->QueueTail->id, (OdinQueue->WaitNum + MaxCustSingleLine - 1) / MaxCustSingleLine);		//�Ŷӻ��������׳˿ͱ�ţ���β�˿ͱ��
	}//if
	else
		fprintf(fp, "�Ŷӻ�����������: 0\n");

	fprintf(fp, "-------------------------------------------------------\n");
	fflush(fp);
	fclose(fp);
}

/*StatusOutputCmd���ú���*/
  //��ͼ�ν������λ�����
void QueuePrint() {	
	int line = (OdinQueue->WaitNum + MaxCustSingleLine - 1) / MaxCustSingleLine;// ����
	printf("\n\t\t�Ŷӻ�����\n������: %d ,�׳˿�: %d , β�˿�: %d , ������: %d\n", OdinQueue->WaitNum, OdinQueue->QueueHead->next->id, OdinQueue->QueueTail->id, line);		//�Ŷӻ��������׳˿ͱ�ţ���β�˿ͱ��
	
	Passenger* CurPas = OdinQueue->QueueHead->next;

	//��һ��
	printf("|");
	for (int i = 0; i < MaxCustSingleLine; i++) {
		printf("----");
	}
	printf("|\n "); //���к�Ŀո��ǻ������Ŀ�ͷ
	/*��һ��over*/

	int flag = 1;	//��¼��ǰ����˳�������� 1=�� 0=��
	//��ӡǰline-1��
	for (int i = 0; i<line - 1; i++) {
		//����˿Ͷ���
		if (flag)
			for (int j = 0; j < MaxCustSingleLine; j++) {
				printf("%3d ", CurPas->id);
				CurPas = CurPas->next;
			}
		else
			for (int j = 0; j < MaxCustSingleLine; j++) {
				printf("\b\b\b\b%3d\b\b\b", CurPas->id);	//�������
				CurPas = CurPas->next;
			}
		//���Χ��
		if (flag) {//��������
			printf("|\n");
			//|---------    |
			printf("|");
			for (int j = 0; j < MaxCustSingleLine - 1; j++)
				printf("----");
			printf("    |\n");

			// \n |   .xxx.xxx.xxx.xxx|
			printf("|");//first
			for (int j = 0; j < MaxCustSingleLine; j++)
				printf("    ");
			printf(">\b");//last
		}
		else {//�����ǵ�
			printf("\n");
			//|    ---------|
			printf("|    ");
			for (int j = 0; j < MaxCustSingleLine - 1; j++)
				printf("----");
			printf("|\n");
			//\n |xxx  xxx  xxx  xxx      |
			printf("<");
		}
		flag = !flag;
	}//��ӡǰline-1��over

	 //�����ڶ�
	if (!flag) {//��������
		// xxx xxx xxx
		while (CurPas != NULL) {
			printf("\b\b\b\b%3d\b\b\b", CurPas->id);	//�������
			CurPas = CurPas->next;
		}
		printf("\n");
	}
	else {//�����ǵ�
		  //\n |xxx  xxx  xxx  xxx      |
		for (int j = 0; j < MaxCustSingleLine; j++) {
			if (CurPas != NULL) {
				printf("%3d ", CurPas->id);
				CurPas = CurPas->next;
			}
			else
				printf("    ");
		}
		printf("|\n");
	}
	/*�����ڶ���over*/

	//���һ��
	printf("|");
	for (int i = 0; i < MaxCustSingleLine; i++) {
		printf("----");
	}
	printf("|\n "); //���к�Ŀո��ǻ������Ŀ�ͷ
	/*���һ��over*/

	puts("");
}
  //����״̬
void WinPrint(Window win) {
	//״̬
	switch (win.WinState) {
	case 0:printf("    �ر�"); break;
	case 1:printf("  ������"); break;
	case 2:printf("  ������"); break;
	case 3:printf("  ��Ϣ��"); break;
	case 4:printf("׼����Ϣ"); break;
	case 5:printf("׼���ر�"); break;
	default:printf("\n����״̬�쳣��\n"); exit(1); break;
	}
	//���ڰ���˿�
	if (win.NowPas) {
		printf("\t���ڰ���: %3d ", win.NowPas->id);
	}
	else {
		printf("\t���ڰ���:  �� ");
	}
	//���ڶ���
	if (win.WinHead != win.WinTail) {	//�п�
		printf(" , ����:");
		Passenger* cur = win.WinHead;
		do {
			cur = cur->next;
			printf(" %3d", cur->id);
		} while (cur != win.WinTail);
	}
	puts("");
}


