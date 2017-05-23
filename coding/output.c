#include"global.h"
#include"passenger.h"
#include"window.h"
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<process.h>

void WinPrint(Window* win) {
	switch (win->WinState) {
	case 0:printf("    �ر�"); break;
	case 1:printf("  ������"); break;
	case 2:printf("  ������"); break;
	case 3:printf("  ��Ϣ��"); break;
	case 4:printf("׼����Ϣ"); break;
	case 5:printf("׼���ر�"); break;
	default:printf("\n����״̬�쳣��\n"); exit(1); break;
	}
	//���ڰ���
	if (win->NowPas) {
		printf("\t���ڰ���: %3d ", win->NowPas->id);
	}
	else {
		printf("\t���ڰ���:  �� ");
	}
	//���ڶ���
	if (win->WinHead != win->WinTail) {	//�п�
		printf(" , ����:");
		Passenger* cur = win->WinHead;
		do {
			cur = cur->next;
			printf(" %3d", cur->id);
		} while (cur != win->WinTail);
	}

}


extern int ii;
time_t PreFile;
void StatusOutputFile() {
	time(&TimeNow);
	double wtf;
	wtf = difftime(TimeNow, PreFile);
	if (wtf <3)
		return;
	PreFile = TimeNow;
	FILE* fp;
	if (!(fp = fopen("output.txt", "a"))) {
		puts("Error: cannot open the file \"output.txt\".");
		exit(1);
	}
	fprintf(fp, "-----------------------------------------------\n");
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
		fprintf(fp,"WIN%d  ", i + 1);
		//����״̬
		switch (Win[i].WinState) {
		case 0:fprintf(fp,"    �ر�"); break;
		case 1:fprintf(fp,"  ������"); break;
		case 2:fprintf(fp,"  ������"); break;
		case 3:fprintf(fp,"  ��Ϣ��"); break;
		case 4:fprintf(fp,"׼����Ϣ"); break;
		case 5:fprintf(fp,"׼���ر�"); break;
		default:fprintf(fp,"\n����״̬�쳣��\n"); exit(1); break;
		}
		//���ڰ���
		if (Win[i].NowPas) {
			fprintf(fp,"\t���ڰ���: %3d ", Win[i].NowPas->id);
		}
		else {
			fprintf(fp,"\t���ڰ���:  �� ");
		}
		//���ڶ���
		if (Win[i].WinHead != Win[i].WinTail) {	//�п�
			fprintf(fp," , ����:");
			Passenger* cur = Win[i].WinHead;
			do {
				cur = cur->next;
				fprintf(fp," %3d", cur->id);
			} while (cur != Win[i].WinTail);
		}
		fprintf(fp,"\n");
	}

	//�Ŷӻ�����״̬
	if (Queuehead->next != NULL) 
		fprintf(fp,"\n\t\t�Ŷӻ�����\n������: %d ,�׳˿�: %d , β�˿�: %d , ������: %d\n", OdinLineWaitNum, Queuehead->next->id, Queuetail->id, (OdinLineWaitNum + MaxCustSingleLine - 1) / MaxCustSingleLine);		//�Ŷӻ��������׳˿ͱ�ţ���β�˿ͱ��
	else
		fprintf(fp,"\n�Ŷӻ�����������: 0\n");

	fprintf(fp, "-----------------------------------------------\n");
}

void EventOutputFile(char event, int PasID, int WinID) {	//PasID�˿� WinID�����
	//StatusOutputFile();
	FILE * fp;
	if (!(fp = fopen("output.txt", "a"))) {
		puts("Error: cannot open the file \"output.txt\".");
		exit(1);
	}
	switch (event) {
	case 'G':fprintf(fp, "%d�ų˿ͽ����Ŷӻ�����\n", PasID); break;
	case 'F':fprintf(fp, "�Ŷӻ���������\n"); break;
	case 'C':fprintf(fp, "%d�ų˿ͽ���%d�Ű����\n", PasID, WinID); break;
	case 'L':fprintf(fp, "%d�ų˿���ɰ����뿪\n", PasID); break;
	case 'O':fprintf(fp, "%d�Ű���ڿ���\n", WinID); break;
	case 'S':fprintf(fp, "%d�Ű���ڹر�\n", WinID); break;
	case 'X':fprintf(fp, "%d�Ű����������Ϣ\n", WinID); break;
	case 'K':fprintf(fp, "%d�Ű���ڿ�ʼ��Ϣ\n", WinID); break;
	case 'J':fprintf(fp, "%d�Ű���ڽ�����Ϣ\n", WinID); break;
	case 'Q':fprintf(fp, "���յ��°�ָ��\n"); break;
	default:fprintf(fp, "���յ�δ֪�¼�\n"); break;
	}
	fclose(fp);
}

time_t PreCmd; //��¼�ϴ����ʱ��
extern int ii;
extern int OdinLineWaitNum;

//ÿ����cmd��ӡ��ǰ״̬
void StatusOutputCmd() {
	StatusOutputFile();
	time(&TimeNow);
	//���ϴ��������1��  & �������ڹ���  => ����
	if (((difftime(TimeNow, PreCmd)) < 1) && (AirportState != OffWork))
		return;
	PreCmd = TimeNow;	//��¼ʱ��
	//puts("--------------------------------------");
	system("CLS");
	printf("�������ڷ�����%d���¼�\n", ii);//
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
		printf("WIN%d  ", i+1);
		////����״̬
		//switch (Win[i].WinState) {
		//case 0:printf("    �ر�"); break;
		//case 1:printf("  ������"); break;
		//case 2:printf("  ������"); break;
		//case 3:printf("  ��Ϣ��"); break;
		//case 4:printf("׼����Ϣ"); break;
		//case 5:printf("׼���ر�"); break;
		//default:printf("\n����״̬�쳣��\n"); exit(1); break;
		//}
		////���ڰ���
		//if (Win[i].NowPas) {
		//	printf("\t���ڰ���: %3d ", Win[i].NowPas->id);
		//}
		//else {
		//	printf("\t���ڰ���:  �� ");
		//}
		////���ڶ���
		//if (Win[i].WinHead != Win[i].WinTail) {	//�п�
		//	printf(" , ����:");
		//	Passenger* cur = Win[i].WinHead;
		//	do {
		//		cur = cur->next;
		//		printf(" %3d", cur->id);
		//	} while (cur != Win[i].WinTail);
		//}
		WinPrint(&Win[i]);
		printf("\n");
	}

	//�Ŷӻ�����״̬
	if (Queuehead->next != NULL) {
		printf("\n\t\t�Ŷӻ�����\n������: %d ,�׳˿�: %d , β�˿�: %d , ������: %d\n", OdinLineWaitNum, Queuehead->next->id, Queuetail->id, (OdinLineWaitNum+MaxCustSingleLine-1) / MaxCustSingleLine);		//�Ŷӻ��������׳˿ͱ�ţ���β�˿ͱ��
		Passenger* CurPas = Queuehead->next;
		int flag = 1;
		for (int i = 0; i<OdinLineWaitNum; i++) {
			if (flag)
				printf("%3d ", CurPas->id);
			else 
				printf("\b\b\b\b%3d\b\b\b", CurPas->id);
			if ((i + 1) % MaxCustSingleLine == 0) {
				flag = !flag;
				printf("\n");
				if (!flag) 
					for (int j = 0; j < MaxCustSingleLine; j++) 
						printf("    ");
			}//if
			CurPas = CurPas->next;
		}//for
		printf("\n");
	}//if
	else
		puts("\n�Ŷӻ�����������: 0");
	//puts("--------------------------------------");
}
