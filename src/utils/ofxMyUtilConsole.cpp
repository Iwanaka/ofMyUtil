#include "ofxMyUtilConsole.h"
#include <WinSock2.h>

//--------------------------------------------------------------
// ofxMyUtil Console
//--------------------------------------------------------------

//--------------------------------------------------------------
//7:normal 8:gray 9:blue 10:green 11:aqua 12:red 13:purple 14:yellow 15:white
void ofxMyUtil::Console::chengeConsollColor(unsigned short colorID) {

	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, colorID);

}

//--------------------------------------------------------------
void ofxMyUtil::Console::hideConsole() {

	HWND handle;
	AllocConsole();
	handle = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(handle, 0);
}