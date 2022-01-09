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

#include <Windows.h>

extern HWND hWin; //defined in main.cpp
extern HWND hGlobalDlg; //defined in dialogs.cpp
extern LPVOID lpKey; //defined in routines.cpp
extern wchar_t wszFile[256]; //defined in routines.cpp