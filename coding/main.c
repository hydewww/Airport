#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "passenger.h"
#include "window.h"

time_t TimeStart;
//time_t TimeNow;
time_t TimeFinish;
int AirportState;
int PassengerArriveTask;

void SetAndBegin() {

	Mainpara();
	Window *Win;
	Win = (Window*)malloc(sizeof(Window)*NumOfWin);
	//memset(Win, 0, sizeof(Win[0]));
	MainInput();
	time(&TimeStart);
	AirportState = OnWork;
}

int main() {
	SetAndBegin();
	while (AirportState!=OffWork) {
		AirportOnServe();
		StateTrans(&thisEvent);
	}
	time(&TimeFinish);
	StatusOutputFile();
}

