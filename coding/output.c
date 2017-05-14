#include<stdio.h>
#include<stdlib.h>
#include"global.h"
#include"passenger.h"
#include"window.h"
#include<Windows.h>
#include<process.h>

void WinList(FILE*fp, int i) {
	Passenger* cur = Win[i].WinHead;
	do {
		cur = cur->next;
		fprintf(fp, " %d", cur->id);
	} while (cur != Win[i].WinTail);
}
void StatusOutput() {
	StartTimer(100);
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
		WinList(fp,i);
		fprintf(fp, ", WinListCustCount = \n", Win[i].WinTail - Win[i].WinHead);
	}		
	
	fprintf(fp, "ListLines = %d\n", Queuehead->next->id);		//�Ŷӻ��������׳˿ͱ�ţ���β�˿ͱ��
	fprintf(fp, "ListCustCount = %d\n", Queuetail->id);	//�Ŷӻ������ܳ˿���
	fclose(fp);
}

void EventOutput(char event,int id,int no) {	//id�˿� no�����
	FILE * fp;
	if (!(fp = fopen("output.txt", "a"))) {
		puts("Error: cannot open the file \"output.txt\".");
		exit(1);
	}
	switch (event) {
	case 'G':fprintf(fp, "%d�ų˿ͽ����Ŷӻ�����\n", id); break;
	case 'F':fprintf(fp, "�Ŷӻ���������\n"); break;
	case 'C':fprintf(fp, "%d�ų˿ͽ���%d�Ű����\n", id, no); break;
	case 'L':fprintf(fp, "%d�ų˿���ɰ����뿪\n", id); break;
	case 'O':fprintf(fp, "%d�Ű���ڿ���", no); break;
	case 'S':fprintf(fp, "%d�Ű���ڹر�", no); break;
	case 'X':fprintf(fp, "%d�Ű����������Ϣ", no); break;
	case 'K':fprintf(fp, "%d�Ű���ڿ�ʼ��Ϣ", no); break;
	case 'J':fprintf(fp, "%d�Ű���ڽ�����Ϣ", no); break;
	case 'Q':fprintf(fp, "���յ��°�ָ��\n"); break;
	default:fprintf(fp, "���յ�δ֪�¼�\n"); break;
	}
	fclose(fp);
}