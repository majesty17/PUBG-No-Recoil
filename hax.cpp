#include "stdafx.h"
#include "windows.h"
#include <iostream>

bool LeftMouseDown = true;
int leftMouseVKCode = 1;
int RecoilState = 3;

void __stdcall RemoveRecoil()
{
	HWND foregroundWin;

	leftMouseVKCode = 1;
	while (1)
	{
		foregroundWin = GetForegroundWindow();
		if (foregroundWin == FindWindowA("UnrealWindow", 0) && RecoilState == 3)
		{
			if (LeftMouseDown)
			{
				Sleep(30u);
				mouse_event(1u, 0, 2u, 0, 3u);
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

void main() {

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)RemoveRecoil, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)KeyHandlerThread, 0, 0, 0);

	std::cin.get();

}
