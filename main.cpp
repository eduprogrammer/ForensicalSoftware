/*
	Copyright 2021. Eduardo Programador

	Forensical Software.

	This software contains several functions
	to cryptography, including:

	1 - Symmetric Cryptography (AES, DES, etc.);
	2 - Encryption and Decryption routines;
	3 - MAC Calculations (HMAC with MD5, SHA-256, etc.)

	www.eduardoprogramador.com
	consultoria@eduardoprogramador.com

	All rights reserved.
*/


#include "dialogs.h"
#pragma comment(lib, "forensical.lib")

HWND hWin;


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPWSTR wsCmdLine, INT_PTR iCmdShow)
{	
	HWND hWnd;	
	MSG msg;
	
	LPCWSTR wsClsName = L"Forensical";
	hWnd = CreateWindowW(wsClsName, wsClsName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, hInstance, nullptr);
	hWin = hWnd;
	
	DialogBoxW(hInstance, MAKEINTRESOURCE(IDD_DIALOG_INIT), hWnd, dlgProc);

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	return msg.wParam;

	
}

