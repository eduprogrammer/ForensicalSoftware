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

#include "explorer.h"

using namespace EduardoProgramador;




Explorer::Explorer::Explorer(HWND hWnd)
{
	hInit = hWnd;
}

METHOD Explorer::Explorer::openBrowse()
{
	
	OPENFILENAMEA ofn;
	char szFile[252] = {0};

	ZeroMemory(&ofn, sizeof(OPENFILENAMEA));
	ofn.hwndOwner = hInit;
	ofn.lpstrFile = szFile;
	ofn.lpstrTitle = "Choose a File to Open";
	ofn.lStructSize = sizeof(OPENFILENAMEA);
	ofn.lpstrFilter = "All files\0*.*\0\0";
	ofn.nMaxFile = 252;

	
	if (GetOpenFileNameA(&ofn))
	{		

		OnOperationOpenStart(szFile, hInit);
		return YES;
	}
	else
	{		
		return NO;
	}
}

METHOD Explorer::Explorer::saveBrowse()
{
	OPENFILENAMEA ofn;
	char szFile[252] = {0};

	ZeroMemory(&ofn, sizeof(OPENFILENAMEA));
	ofn.hwndOwner = hInit;
	ofn.lpstrFile = szFile;
	ofn.lpstrTitle = "Choose a File to Save";
	ofn.lStructSize = sizeof(OPENFILENAMEA);
	ofn.lpstrFilter = "All files\0*.*\0\0";
	ofn.nMaxFile = 252;

	if (GetSaveFileNameA(&ofn))
	{
		OnOperationSaveStart(szFile, hInit);
		return YES;
	}
	else
	{
		return NO;
	}
}