
#include "stdafx.h"
#include <ostream>
#include <Windows.h>
#include <thread>
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


class ResizingArrayStack
{
public:
	ResizingArrayStack() // Ctor
	{
		// no elements yet
		this->totalElements = 0;
		
		// size of array
		this->size = 2;

		// create space for our array
		this->array = new int[this->size];

		// zero-set memory
		memset(this->array, 0x00, this->size);

		this->resizeMethodCalled = 0;
	}

	~ResizingArrayStack()
	{
		delete[] this->array;
	}

	void print()
	{
		for (int i=0; i < this->totalElements; i++) {
			std::cout << this->array[i];
		}
	}

	void resize()
	{
		this->resizeMethodCalled++;

		// keep old size
		int oldSize = this->size;

		// double our size
		this->size *= 2;

		// create new array
		int *newArray = new int[this->size];

		// zero-memory
		memset(newArray, 0x00, this->size);

		// copy old values to the new array
		for (int i = 0; i < oldSize; i++) {
			newArray[i] = this->array[i];
		}

		// set array as the new
		this->array = newArray;
	}

	void push(int item)
	{
		// 
		if (this->size <= this->totalElements) {
			this->resize();
		}

		this->array[this->totalElements++] = item;
	}

	int empty()
	{
		return this->totalElements == 0;
	}

	int getResizeMethodCalled() {
		return this->resizeMethodCalled;
	}

private:
	int size;
	int totalElements;
	int resizeMethodCalled;
	int *array;
};

int _tmain(int argc, _TCHAR* argv[])
{

	ResizingArrayStack stack;

	for (int i = 0; i < 1500000; i++) {
		stack.push(i);
	}

	std::cout << "resize method called: " << stack.getResizeMethodCalled() << " times.\n";

	//stack.print();

	
	/*
	HINSTANCE instance = NULL;
	hookHandle = SetWindowsHookEx(WH_KEYBOARD_LL, keyHandler, instance, 0);
	
	

	MSG message;
	while (GetMessage(&message, NULL, NULL, NULL) != NULL) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	
	UnhookWindowsHookEx(hookHandle);*/
	return 0;
}




