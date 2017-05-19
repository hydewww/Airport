#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<process.h>
#include "global.h"
#include "passenger.h"
#include "window.h"

void StatusOutputFile() {
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

void StatusOutputCmd() {
	system("cls");
	printf("T=<%l>\n", TimeNow);								//T=<��ǰʱ�䣨3λ��>
	printf("OFFDUTY = %c\n", AirportState == 0 ? "N" : "Y");	//�Ƿ��°�
																	//WIN1 : State = ״̬(11λ)��WinList = �����г˿ͱ���б�WinListCustCount = ����ڶ�������
	for (int i = 0; i < NumOfWin; i++) {
		printf("WIN%d : State = %11d, ", i, Win[i].WinState);
		Passenger* cur = Win[i].WinHead;
		do {
			cur = cur->next;
			printf(" %d", cur->id);
		} while (cur != Win[i].WinTail);
		printf(", WinListCustCount = \n", Win[i].WinTail - Win[i].WinHead);
	}
	printf("ListLines = %d\n", Queuehead->next->id);		//�Ŷӻ��������׳˿ͱ�ţ���β�˿ͱ��
	printf("ListCustCount = %d\n", Queuetail->id);	//�Ŷӻ������ܳ˿���
}