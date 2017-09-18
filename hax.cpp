#include "windows.h"
#include <iostream>

//with different weapons, there are different fire rate and recoil.
DWORD recoilStep=2u;
DWORD fireRate=30u;
/*
weapon   fireRate   recoilUp
-----------------------------
AKM      0.100s     8
SCAR-L   0.096s     7
M16A4    0.075s     7
M416     0.086s     7
UMP9     0.092s     5
SKS      0.090s     8
UZI      0.048s     5
*/

bool LeftMouseDown = true;
int leftMouseVKCode = 1;
int RecoilState = 4;       //default state is turned off;

//to be changed into real game window name
LPCTSTR windowsName="notepad";

void __stdcall RemoveRecoil()
{
	HWND foregroundWin;

	leftMouseVKCode = 1;
	while (1)
	{
		foregroundWin = GetForegroundWindow();
		if (foregroundWin == FindWindowA(windowsName, 0) && RecoilState == 3)
		{
			if (LeftMouseDown)
			{
				Sleep(fireRate);
				mouse_event(1u, 0, recoilStep, 0, 3u);
			}
		}
		Sleep(1u);
	}
}

void __stdcall KeyHandlerThread()
{
	while (1)
	{
		if (GetAsyncKeyState(0x78) < 0)           // F9 turns recoil reducer on.
		{
			RecoilState = 3;
			Beep(0x320u, 0xC8u);
		}
		if (GetAsyncKeyState(0x79) < 0)           // F10 turns recoil reducer off.
		{
			RecoilState = 4;
			Beep(0x64u, 0xC8u);
		}
		LeftMouseDown = GetAsyncKeyState(leftMouseVKCode) < 0;
		Sleep(1u);
	}
}

int main() {

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)RemoveRecoil, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)KeyHandlerThread, 0, 0, 0);

	std::cin.get();

}
