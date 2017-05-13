#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "passenger.h"
#include "window.h"

void SetAndBegin();

int main() {


}

void SetAndBegin() {

	Window *win;
	win = (Window*)malloc(sizeof(Window)*NumOfWin);

	memset(win, 0, sizeof(win[0]));
}