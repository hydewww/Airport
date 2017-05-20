#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<process.h>
#include "global.h"
#include "passenger.h"
#include "window.h"

void StatusOutputFile() {
	time(&TimeNow);
	if ( ((int)difftime(TimeStart,TimeNow)) %3!=0)
		return;
	FILE* fp;
	if (!  (fp=fopen("output.txt", "a"))  ) {
		puts("Error: cannot open the file \"output.txt\".");
		exit(1);
	}
	fprintf(fp,"T=<%l>\n", TimeNow);								//T=<��ǰʱ�䣨3λ��>
	fprintf(fp, "OFFDUTY = %c\n", AirportState == 0 ? "N" : "Y");	//�Ƿ��°�
	//WIN1 : State = ״̬(11λ)��WinList = �����г˿ͱ���б�WinListCustCount = ����ڶ�������
	for (int i = 0; i < NumOfWin; i++) {
		fprintf(fp,"WIN%d : State = %11d, ", i, Win[i].WinState);
		Passenger* cur = Win[i].WinHead;
		do {
			cur = cur->next;
			fprintf(fp, " %d", cur->id);
		} while (cur != Win[i].WinTail);
		fprintf(fp, ", WinListCustCount = \n", Win[i].WinTail - Win[i].WinHead);
	}		
	
	fprintf(fp, "ListLines = %d\n", Queuehead->next->id);		//�Ŷӻ��������׳˿ͱ�ţ���β�˿ͱ��
	fprintf(fp, "ListCustCount = %d\n", Queuetail->id);	//�Ŷӻ������ܳ˿���
	fclose(fp);
}

void EventOutputFile(char event,int PasID,int WinID) {	//PasID�˿� WinID�����
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
time_t t1;
time_t t2;

void StatusOutputCmd() {
	t1 = t2;
	time(&t2);
	if (((int)difftime(t2,t1 )) !=1 )
		return;
	puts("--------------------------------------");
	printf("ʱ�� : %s", ctime(&TimeNow));	
	//����״̬
	switch (AirportState) {
	case 0:printf("����״̬ = �°�\n"); break;
	case 1:printf("����״̬ = ������  \n"); break;
	case 2:printf("����״̬ = ׼���°�\n"); break;
	default: printf("����״̬�쳣"); exit(1);
	}
	//�Ŷӻ�����״̬
	if (Queuehead->next != NULL)
		printf("�Ŷӻ�����������: %d ,�׳˿�: %d , β�˿�: %d\n", OdinLineWaitNum, Queuehead->next->id, Queuetail->id);		//�Ŷӻ��������׳˿ͱ�ţ���β�˿ͱ��
	else
		puts("�Ŷӻ�����������: 0");
	puts("");
	//����״̬
	for (int i = 0; i < NumOfWin; i++) {
		//����id
		printf("WIN%d  ", i);
		//״̬
		switch (Win[i].WinState) {
		case 0:printf("    �ر�"); break;
		case 1:printf("    ����"); break;
		case 2:printf("  ������"); break;
		case 3:printf("    ��Ϣ"); break;
		case 4:printf("׼����Ϣ"); break;
		case 5:printf("׼���ر�"); break;
		default:printf("״̬�쳣"); exit(1); break;
		}
		//���ڰ���˿�
		if (Win[i].NowPas) {
			printf("\t���ڰ���: %2d ", Win[i].NowPas->id);
		}
		else {
			printf("\t���ڰ���: �� ");
		}
		//���ڶ���
		if (Win[i].WinHead != Win[i].WinTail) {	//�п�
			printf(" , ����:");
			Passenger* cur = Win[i].WinHead;	
			do {
				cur = cur->next;
				printf(" %d", cur->id);
			} while (cur != Win[i].WinTail);	
		}
		printf("\n");
	}

	printf("���ڷ����¼�:%d\n", thisEvent.no);
}