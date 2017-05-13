#include<stdio.h>
#include<stdlib.h>
#include"global.h"
#include"passenger.h"
#include"window.h"

void WinList(FILE*fp, int i) {
	//test
	Window* Win = (Window*)malloc(sizeof(Window)*NumOfWin);
	//
	Passenger* cur = Win[i].WinHead;
	fprintf(fp, "WinList = %d", cur->id);
	do {
		fprintf(fp, " %d", cur->id);
		cur = cur->next;
	} while (cur != Win[i].WinTail);
}
void StatusOutput() {
	//test
	Window* Win = (Window*)malloc(sizeof(Window)*NumOfWin);
	//
	FILE* fp;
	if (!  (fp=fopen("output.txt", "a"))  ) {
		puts("Error: cannot open the file \"output.txt\".");
		exit(1);
	}
	//fprintf(fp, "-----------------------------------------------\n");
	fprintf(fp,"T=<%l>\n", TimeNow);								//T=<��ǰʱ�䣨3λ��>
	fprintf(fp, "OFFDUTY = %c\n", AirportState == 0 ? "N" : "Y");	//�Ƿ��°�
	//WIN1 : State = ״̬(11λ)��WinList = �����г˿ͱ���б�WinListCustCount = ����ڶ�������
	for (int i = 0; i < NumOfWin; i++) {
		fprintf(fp,"WIN%d : State = %11d, ", i, Win[i].WinState);
		WinList(fp,i);
		fprintf(fp, ", WinListCustCount = \n", Win[i].WinTail - Win[i].WinHead + 1);
	}		
	
	fprintf(fp, "ListLines = %d\n", );		//�Ŷӻ��������׳˿ͱ�ţ���β�˿ͱ��
	fprintf(fp, "ListCustCount = %d\n", );	//�Ŷӻ������ܳ˿���
	fclose(fp);
}

void EventOutput(char ch,int no) {	//???
	FILE * fp;
	if (!(fp = fopen("output.txt", "a"))) {
		puts("Error: cannot open the file \"output.txt\".");
		exit(1);
	}
	if (ch == 'Q') {
		fprintf(fp,"���յ��°�ָ��");
		return;
	}
	else if (ch == 'G') {				//??????
		if (OdinWatNum == MaxSeqLen)
			fprintf(fp,"�Ŷӻ���������\n");
		else
			fprintf(fp, "%d�˿ͽ����Ŷӻ�����\n", no);
	}
	else if (ch == 'L') {
		fprintf(fp, "%d�˿���ɰ����뿪\n", no);
	}
}