#ifndef _WINDOW_H_
#define _WINDOW_H_
typedef struct Window
{
	int  WinState;/*����״̬��CloseWin���ڹر�  OpenWin����  OnSerWin���ڷ���
				 RestWin��Ϣ��  ReadyRestWin�ȴ���Ϣ  ReadyClosWin�ȴ��ر�*/
	int  SerNum;//����ĺ��� 		
	long SerTime;//���η������ʱ��		
	long RestTime;//������Ϣ����ʱ��
	long TotalSer;//�ܹ���������
	long TotalTime;//�ܹ�����ʱ��
	int  WaitNum;//��¼��ǰ������Ŷӳ˿�����
	char type;//��������:V-VIP���ڣ�O-��ͨ����
	Passenger *NowPas;//ָ�򱻰���˿�ָ��
	Passenger *WinHead;//���ڶ���ͷָ��
	Passenger *WinTail;//���ڶ���βָ��
}Window;//���ڽṹ

extern Window *Win;//���������
#endif