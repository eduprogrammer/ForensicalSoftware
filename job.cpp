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
#include"explorer.h"
#include <cstdio>

using namespace EduardoProgramador;

METHOD RES;
HANDLE hThreadTxt;
wchar_t* res;
char* k_res;

DWORD WINAPI threadTxt(LPVOID lpParam);
DWORD WINAPI threadFile(LPVOID lpParam);

Jobs::Jobs(HWND hWnd)
{
	this->hWndG = hWnd;		
	hRbTxt = GetDlgItem(hWnd, IDC_RB_HMAC_TEXT);
	mRes = 0;
	
}

Jobs::~Jobs()
{

}

METHOD Jobs::isTextHmac()
{	

	LRESULT lMsg = SendMessageW(this->hRbTxt, BM_GETCHECK, 0, 0);
	
	if (lMsg == BST_CHECKED)
	{		
		return YES;
		
	}
	else
	{		
		return NO;
	}
	
}

ONCE Jobs::macFromText()
{	

	TXTPARAMS txtP;
	wchar_t* szPass;
	ZeroMemory(&txtP, sizeof(TXTPARAMS));

	HWND hTxt = GetDlgItem(this->hWndG, IDC_EDIT_HMAC_TEXT);
	HWND hRes = GetDlgItem(this->hWndG, IDC_EDIT_HMAC_RESULT);	
	
	LPWSTR szIntxt = new WCHAR[512];
	szPass = new WCHAR[512];
	GetWindowTextW(hTxt, szIntxt, 512);
	GetDlgItemTextW(this->hWndG, IDC_EDIT_HMAC_PASS, szPass,512);				
				
		txtP.hWnd = this->hWndG;
		txtP.lpJobs = this;				

		hThreadTxt = CreateThread(nullptr, 0, threadTxt, &txtP, 0, 0);																	
}

ONCE Jobs::macFromFile()
{		
	FILEPARAMS fp;
	
	ZeroMemory(&fp, sizeof(FILEPARAMS));
	fp.hWnd = this->hWndG;
	fp.lpJobs = this;
	
	CreateThread(nullptr, 0, &threadFile, &fp, 0, nullptr);
	
	
}

DWORD WINAPI threadTxt(LPVOID lpParam)
{	
	FORENSICAL_KEY fk;
	Jobs* jobs;
	TXTPARAMS* _txtP;	
	HWND hWnd;
	HWND hWait, hCombo;
	wchar_t* szTxt, * szPass;
	char* cTxt, * cPass;
	FORENSICAL_HMAC fHmac;	
	char iHash, iKey, iHmac;
	unsigned short usSelected;
	
	ZeroMemory(&fk, sizeof(FORENSICAL_KEY));
	ZeroMemory(&fHmac, sizeof(FORENSICAL_HMAC));
	_txtP = (TXTPARAMS*)lpParam;
	jobs = (Jobs *) _txtP->lpJobs;
	hWnd = (HWND)_txtP->hWnd;
	hWait = GetDlgItem(hWnd, IDC_STATIC_HMAC_WAIT);
	hCombo = GetDlgItem(hWnd, IDC_COMBO_HMAC_HASH);

	szTxt = new WCHAR[512];
	cTxt = new CHAR[512];
	szPass = new WCHAR[512];
	cPass = new CHAR[512];

	GetDlgItemTextW(hWnd, IDC_EDIT_HMAC_PASS, szPass, 512);
	GetDlgItemTextW(hWnd, IDC_EDIT_HMAC_TEXT, szTxt, 512);
	
	usSelected = SendMessageW(hCombo, CB_GETCURSEL, 0, 0);	

	wcstombs(cPass, szPass, 512);
	wcstombs(cTxt, szTxt, 512);	

	switch (usSelected)
	{

	case 0:
		iHash = HASH_MD5;
		iHmac = HMAC_MD5;
		iKey = KEY_2DES_112;
		break;

	case 1:
		iHash = HASH_SHA;
		iHmac = HMAC_SHA;
		iKey = KEY_3DES_168;
		break;

	case 2:
		iHash = HASH_SHA256;
		iHmac = HMAC_SHA256;
		iKey = KEY_AES_256;
		break;

	case 3:
		iHash = HASH_SHA512;
		iHmac = HMAC_SHA512;
		iKey = KEY_AES_256;
		break;
		

	default:
		iHash = HASH_MD5;
		iHmac = HMAC_MD5;
		iKey = KEY_2DES_112;
		break;
	}
		
	ShowWindow(hWait, SW_SHOW);		
	

	if (!jobs->ForensicalCreateKey(iHash, cPass, iKey, &fk))
	{
		MessageBoxW(hWnd, L"It was not possible to calculate the HMAC Result", L"error", MB_ICONERROR);
		ShowWindow(hWait, SW_HIDE);
	}
	else
	{
		if (!jobs->ForensicalGetMac(iHmac, &fk, cTxt, &fHmac))
		{
			MessageBoxW(hWnd, L"It was not possible to calculate the HMAC Result", L"error", MB_ICONERROR);
			ShowWindow(hWait, SW_HIDE);
		}
		else
		{			
			SetDlgItemTextA(hWnd, IDC_EDIT_HMAC_RESULT, fHmac.szHashData);
			ShowWindow(hWait, SW_HIDE);

			MessageBoxW(hWnd, L"Yeah! The MAC (Message Authentication Code) was calculated successfully!", L"Success", MB_ICONINFORMATION);

		}
	}		

	return 0;
}

DWORD WINAPI threadFile(LPVOID lpParam)
{	
	HWND hWnd, hCombo, hWait;
	Jobs* jobs;
	char szFile[252];
	char* szPass;
	BYTE iHash, iMac, iKey;
	BYTE iChosen;
	FORENSICAL_KEY fk;
	FORENSICAL_HMAC fHmac;
	OPENFILENAMEA ofn;
	
	hWnd = (HWND) ((LPFILEPARAMS)lpParam)->hWnd;
	hCombo = GetDlgItem(hWnd, IDC_COMBO_HMAC_HASH);
	hWait = GetDlgItem(hWnd, IDC_STATIC_HMAC_WAIT);
	jobs = (Jobs*)((LPFILEPARAMS)lpParam)->lpJobs;
	szPass = new CHAR[252];
	
	ShowWindow(hWait, SW_SHOW);	

	iChosen = SendMessageW(hCombo, CB_GETCURSEL, 0, 0);
	
	switch (iChosen)
	{
	case 0:
		iHash = HASH_MD5;		
		iMac = HMAC_MD5;
		iKey = KEY_2DES_112;
		break;

	case 1:
		iHash = HASH_SHA;
		iMac = HMAC_SHA;
		iKey = KEY_3DES_168;
		break;

	case 2:
		iHash = HASH_SHA256;
		iMac = HMAC_SHA256;
		iKey = KEY_AES_256;
		break;

	case 3:
		iHash = HASH_SHA512;
		iMac = HMAC_SHA512;
		iKey = KEY_AES_256;
		break;					

	default:
		iHash = HASH_MD5;
		iMac = HMAC_MD5;
		iKey = KEY_2DES_112;
		break;
	}


	szPass = new CHAR[252];
	GetDlgItemTextA(hWnd, IDC_EDIT_HMAC_PASS, szPass, 512);

	if (!strcmp(szPass, "")) 
	{
		MessageBoxW(hWnd, L"You must enter a valid password", L"Empty Password", MB_ICONINFORMATION);
		ShowWindow(hWait, SW_HIDE);
	}
	else
	{
		ZeroMemory(&fk, sizeof(FORENSICAL_KEY));
		ZeroMemory(&fHmac, sizeof(FORENSICAL_HMAC));
		
		ZeroMemory(&ofn, sizeof(OPENFILENAMEA));
		ofn.hwndOwner = hWnd;
		ofn.lpstrFile = szFile;
		ofn.lpstrTitle = "Open a File to get the MAC";
		ofn.lStructSize = sizeof(OPENFILENAMEA);
		ofn.lpstrFilter = "All files\0*.*\0\0";
		ofn.nMaxFile = 252;

		if (GetOpenFileNameA(&ofn))
		{

			SetDlgItemTextA(hWnd, IDC_EDIT_HMAC_FILE, szFile);

			if (!jobs->ForensicalCreateKey(iHash, szPass,iKey,&fk))
			{
				MessageBoxW(hWnd, L"It was not possible to calculate the Hmac result", L"Error", MB_ICONERROR);
				ShowWindow(hWait, SW_HIDE);
			}
			else
			{
				if (!jobs->ForensicalGetMacF(iMac, &fk, szFile, &fHmac))
				{
					MessageBoxW(hWnd, L"It was not possible to calculate the Hmac result", L"Error", MB_ICONERROR);
					ShowWindow(hWait, SW_HIDE);
				}
				else
				{
					SetDlgItemTextA(hWnd, IDC_EDIT_HMAC_RESULT, fHmac.szHashData);
					MessageBoxA(hWnd, "The Hmac result has been successfully calculated", "Success", MB_ICONINFORMATION);
					ShowWindow(hWait, SW_HIDE);					

				}
			}
		}		

	}
	

	return 0;
	
}

METHOD Jobs::getMacResult()
{
	return mRes;
}

void Jobs::setNo()
{
	mRes = NO;
}

void Jobs::setYes()
{
	mRes = YES;
}

METHOD Jobs::enc(LPWSTR szFile)
{
	return EncryptFileW(szFile);
}

METHOD Jobs::dec(LPWSTR szFile)
{
	return DecryptFileW(szFile, 0);
}

ONCE Explorer::Explorer::OnOperationOpenStart(LPSTR szFile, HWND hWnd)
{
	Jobs jobs = hWnd;
	wchar_t *wszFile;
	wszFile = new WCHAR[252];
	mbstowcs(wszFile, szFile, 252);

	if (!jobs.enc(wszFile))
	{		
		MessageBoxW(hWnd, L"The file has not been encrypted", L"Error", MB_ICONERROR);
	}
	else
	{
		MessageBoxW(hWnd, L"The file was encrypted successfully", L"Succesfully", MB_ICONINFORMATION);
	}

	delete[]wszFile;



}

ONCE Explorer::Explorer::OnOperationSaveStart(LPSTR szFile, HWND hWnd)
{
	Jobs jobs = hWnd;
	wchar_t* wszFile;
	wszFile = new WCHAR[252];
	mbstowcs(wszFile, szFile, 252);

	if (!jobs.dec(wszFile))
	{
		MessageBoxW(hWnd, L"The file has not been decrypted", L"Error", MB_ICONERROR);
	}
	else
	{
		MessageBoxW(hWnd, L"The file was decrypted successfully", L"Succesfully", MB_ICONINFORMATION);
	}

	delete[]wszFile;
}



