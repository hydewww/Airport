#ifndef _Window_
#define _Window_
typedef struct Window
{
	int WinState;/*����״̬��CloseWin���ڹر�  OpenWin����  OnSerWin���ڷ���
				 RestWin��Ϣ��  ReadyRestWin�ȴ���Ϣ  ReadyClosWin�ȴ��ر�*/
	int SerNum;//����ĺ��� 		
	long SerTime;//���η������ʱ��		
	/*
	
	*/
	long RestTime;//������Ϣ����ʱ��
	long TotalSer;//�ܹ���������
	long TotalTime;//�ܹ�����ʱ��
	int  WaitNum;//��¼��ǰ������Ŷӳ˿�����
	Passenger *NowPas;//ָ�򱻰���˿�ָ��
	Passenger *WinHead;//���ڶ���ͷָ��
	Passenger *WinTail;//���ڶ���βָ��
}Window;//���ڽṹ

extern Window *Win;//���������
#endif