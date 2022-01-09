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

#include "routines.h"

LPVOID lpKey;
wchar_t wszFile[256];
LPVOID bTest;
FORENSICAL_KEY sFk;

void startIconImg(HWND hWnd)
{
	HICON hIcon;
	hIcon = reinterpret_cast<HICON>(LoadImageW(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE));
	SendMessageW(hWnd, WM_SETICON, static_cast<WPARAM>(ICON_BIG), reinterpret_cast<LPARAM>(hIcon));
	DestroyIcon(hIcon);
				
}

void startBitmapImg(INT_PTR iBitmap, HWND hWnd, INT_PTR iWidth, INT_PTR iHeight)
{
	HBITMAP hBitmap;

	hBitmap = reinterpret_cast<HBITMAP>(LoadImageW(GetModuleHandle(nullptr), MAKEINTRESOURCE(iBitmap), IMAGE_BITMAP, iWidth, iHeight, LR_DEFAULTSIZE));


	SendMessageW(hWnd, STM_SETIMAGE, static_cast<WPARAM>(IMAGE_BITMAP), reinterpret_cast<LPARAM>(hBitmap));
}

void saveFile(HWND hWnd, LPWSTR sFile, LPCWSTR szFilter, LPCWSTR szTitle, void (*ok)(HWND, LPWSTR, UINT), void (*error)(), UINT iKey)
{	
	OPENFILENAMEW ofn;
	
	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.Flags = OFN_PATHMUSTEXIST;
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = sFile;
	ofn.lpstrFilter = szFilter;
	ofn.lpstrTitle = szTitle;
	ofn.lStructSize = sizeof(OPENFILENAMEW);
	ofn.nMaxFile = 252;
	
	if (GetSaveFileNameW(&ofn))
	{
		if (ok)
		{
			(*ok)(hWnd, sFile, iKey);
		}

	}
	else
	{
		if (error)
		{
			(*error)();
		}
	}


}

void saveKeyToFile(HWND hWnd, LPWSTR szFile, UINT iKey)
{	
	Forensical* forensical;		
	
	ZeroMemory(&sFk, sizeof(FORENSICAL_KEY));
	forensical = new Forensical();

	
	if (!forensical->ForensicalCreateKey(iKey, &sFk))
	{		
		MessageBoxW(hWnd, L"error", L"error", MB_OK);
	}
	else
	{		
		BYTE* pbKey = sFk.pbKey;
		DWORD dwRead = 0;

		HANDLE hFile;
		hFile = CreateFileW(szFile, GENERIC_WRITE, FILE_SHARE_WRITE, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (hFile == INVALID_HANDLE_VALUE)
		{			
			MessageBoxW(hWnd, L"error", L"error", MB_OK);

		}
		else
		{
			if (!WriteFile(hFile, pbKey, sFk.dwKeySize, &dwRead, nullptr))
			{				
				MessageBoxW(hWnd, L"error", L"error", MB_OK);

			}
			else
			{				
				lpKey = &sFk;
				CloseHandle(hFile);
				MessageBoxW(hWnd, L"done", L"done", MB_OK);

			}
		}


	}
}

DWORD WINAPI readKey(LPVOID lpParam)
{	
	HWND hBox;
	wchar_t szFile[256];
	char* szFile_c;
	OPENFILENAMEW ofn;
	Forensical* forensical;	
	
	hBox = GetDlgItem(hGlobalDlg, IDC_COMBO_READ_KEY);

	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.Flags = OFN_PATHMUSTEXIST;
	ofn.hwndOwner = hGlobalDlg;
	ofn.lpstrFile = szFile;
	ofn.lpstrFilter = L"All Files\0*.*\0\0";
	ofn.lpstrTitle = L"Choose a valid key";
	ofn.lStructSize = sizeof(OPENFILENAMEW);
	ofn.nMaxFile = 256;
	
	INT_PTR iChosen = SendMessageW(hBox, CB_GETCURSEL, 0, 0);

	UINT iKey;

	switch (iChosen)
	{

	case 0:
		iKey = KEY_2DES_112;
		break;

	case 1:
		iKey = KEY_3DES_168;
		break;

	case 2:
		iKey = KEY_DES_56;
		break;

	case 3:
		iKey = KEY_AES_128;
		break;

	case 4:
		iKey = KEY_AES_192;
		break;

	case 5:
		iKey = KEY_AES_256;
		break;

	case 6:
		iKey = KEY_RC2_40;
		break;

	case 7:
		iKey = KEY_RC4_40;
		break;

	default:
		iKey = KEY_2DES_112;
	}

	if (GetOpenFileNameW(&ofn))
	{

		forensical = new Forensical();
		ZeroMemory(&sFk, sizeof(FORENSICAL_KEY));

		szFile_c = new CHAR[256];
		wcstombs(szFile_c, szFile, 256);

		if (!forensical->ForensicalGetKeyFromFile(&sFk, szFile_c, iKey))
		{			
			MessageBoxW(hGlobalDlg, L"An error has ocurred while trying to read the specified key.", L"Error", MB_ICONERROR);
		}
		else
		{			
			lpKey = &sFk;
						
			MessageBoxW(hGlobalDlg, L"The key was exported successfully. You can start to encrypt or to decrypt something with the software", L"Successfully", MB_ICONINFORMATION);
		}
	}
	

	return static_cast<DWORD>(0);
}

DWORD WINAPI charEncrypt(LPVOID lpParam)
{	
	Forensical* forensical;

	FORENSICAL_DATA fd;
	FORENSICAL_KEY* fk;
	HWND hText, hArea;
	wchar_t* szSrcText, * szOut;
	char* c_src, * c_out;
	UINT uAns;
	
	forensical = new Forensical();

	fk = (FORENSICAL_KEY*) lpKey;
	ZeroMemory(&fd, sizeof(FORENSICAL_DATA));

	hText = GetDlgItem(hGlobalDlg, IDC_EDIT_CHAR_ENCRYPT);
	hArea = GetDlgItem(hGlobalDlg, IDC_AREA_CHAR_ENCRYPT);
	szSrcText = new WCHAR[512];
	c_src = new CHAR[512];
	
	SetWindowTextW(hArea, L"");
	GetWindowTextW(hGlobalDlg, szSrcText, 512);
	wcstombs(c_src, szSrcText, 512);

	if (lpKey)
	{
		MessageBoxW(hGlobalDlg, L"You have exported a valid key. It will be used in the encryption process.", L"Key Detected", MB_ICONINFORMATION);
		
		SetWindowTextW(hArea, L"[*] Wait...");				

		if (!forensical->ForensicalEncrypt(fk, c_src, &fd))
		{			
			MessageBoxW(hGlobalDlg, L"An error was ocurred while encrypting the string", L"Error", MB_ICONERROR);
		}
		else
		{			
			c_out = (char*)fd.pbData;
			szOut = new WCHAR[strlen(c_out)];
			mbstowcs(szOut, c_out, strlen(c_out));

			SetWindowTextW(hArea, szOut);
			MessageBoxW(hGlobalDlg, L"Message encrypted successfully", L"Success", MB_ICONINFORMATION);
		}


	}
	else
	{
		MessageBoxW(hGlobalDlg, L"To start the encryption routine, you must first generate a new key in Menu > Key > Generate New Key, or read one at Menu > Key > Read Key", L"Key Needed", MB_ICONINFORMATION);
	}

	return 0;
}

DWORD WINAPI fileEncryptBrowse(LPVOID lpParam)
{	
	OPENFILENAMEW ofn;
	
	ZeroMemory(&ofn, sizeof(OPENFILENAMEW));

	ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
	ofn.hwndOwner = hGlobalDlg;
	ofn.lpstrFile = wszFile;
	ofn.lpstrFilter = L"All Files \0*.*\0\0";
	ofn.lpstrTitle = L"File to Encrypt";
	ofn.nMaxFile = 256;
	ofn.lStructSize = sizeof(OPENFILENAMEW);

	HWND hBtnEnc = GetDlgItem(hGlobalDlg, IDC_BTN_FILE_ENC_START);
	
	if (GetOpenFileNameW(&ofn))
	{

		EnableWindow(hBtnEnc, TRUE);
		SetDlgItemTextW(hGlobalDlg, IDC_EDIT_FILE_ENCRYPT, wszFile);
	}
	else
	{
		EnableWindow(hBtnEnc, FALSE);
		SetDlgItemTextW(hGlobalDlg, IDC_EDIT_FILE_ENCRYPT, wszFile);
	}	


	return 0;
}

DWORD WINAPI fileEncryptStart(LPVOID lpParam)
{	
	OPENFILENAMEW ofn;
	wchar_t szFileOut[256];
	Forensical* forensical;
	char* c_fileInt, * c_fileOut;
	
	ZeroMemory(&ofn, sizeof(OPENFILENAMEW));

	ofn.Flags = OFN_PATHMUSTEXIST;
	ofn.hwndOwner = hGlobalDlg;
	ofn.lpstrFile = szFileOut;
	ofn.lpstrFilter = L"All Files \0*.*\0\0";
	ofn.lpstrTitle = L"Save File Encrypted";
	ofn.nMaxFile = 256;
	ofn.lStructSize = sizeof(OPENFILENAMEW);

	HWND hBtnEnc = GetDlgItem(hGlobalDlg, IDC_BTN_FILE_ENC_START);
	
	if (GetSaveFileNameW(&ofn))
	{
		forensical = new Forensical();

		if (lpKey)
		{
			
			c_fileInt = new CHAR[256];
			wcstombs(c_fileInt, wszFile, 256);
			c_fileOut = new CHAR[256];
			wcstombs(c_fileOut, szFileOut, 256);

			HWND hWait;
			hWait = GetDlgItem(hGlobalDlg, IDC_ST_FILE_ENC_WAIT);
			ShowWindow(hWait, TRUE);


			if (forensical->ForensicalEncrypt(reinterpret_cast<FORENSICAL_KEY*>(lpKey), c_fileInt, c_fileOut))
			{
				MessageBoxW(hGlobalDlg, L"The encryption has been processed successfully", L"Success", MB_ICONINFORMATION);
				ShowWindow(hWait, FALSE);
			}
			else
			{
				MessageBoxW(hGlobalDlg, L"The encrypting process has failured.", L"Error", MB_ICONERROR);
				ShowWindow(hWait, FALSE);
			}
		}
		else
		{
			MessageBoxW(hGlobalDlg, L"To start the encryption routine, you must first generate a new key in Menu > Key > Generate New Key, or read one at Menu > Key > Read Key", L"Key Needed", MB_ICONINFORMATION);
		}

	}
	else
	{
		MessageBoxW(hGlobalDlg, L"You must select a valid place to save the encrypted file.", L"Saving Needed", MB_ICONINFORMATION);
	}

	return 0;
}

DWORD WINAPI passEncrypt(LPVOID lpParam)
{	
	wchar_t szPass[512] = { 0 };
	char* cPass;
	wchar_t szTxt[512] = { 0 };
	char* cTxt;
	HWND hRbTxt;
	char* cRes;
	wchar_t* szRes, * szFinal;
	Forensical* forensical;
	FORENSICAL_KEY fk;
	FORENSICAL_DATA fd;
	OPENFILENAMEW ofnIn, ofnOut;
	wchar_t szFileIn[256], szFileOut[256];
	char* cIn, * cOut;
	
	GetDlgItemTextW(hGlobalDlg, IDC_EDIT_PASS_ENC_PASS, szPass, 512);
	
	if (!wcscmp(szPass, L""))
	{
		MessageBoxW(hGlobalDlg, L"Please, select a valid passowrd.", L"No Password", MB_ICONINFORMATION);

	}
	else
	{
		hRbTxt = GetDlgItem(hGlobalDlg, IDC_RB_PASS_ENC_TXT);

		LONG_PTR lMsg = SendMessageW(hRbTxt, BM_GETCHECK, 0, 0);
		if (lMsg == BST_CHECKED)
		{			
			GetDlgItemTextW(hGlobalDlg, IDC_EDIT_PASS_ENC_TEXT, szTxt, 512);
			if (!wcscmp(szTxt, L""))
			{
				MessageBoxW(hGlobalDlg, L"No text to encrypt. Input a valid text.", L"No Text", MB_ICONINFORMATION);
			}
			else
			{
				forensical = new Forensical();

				ZeroMemory(&fk, sizeof(FORENSICAL_KEY));
				cPass = new CHAR[512];
				wcstombs(cPass, szPass, 512);

				if (!forensical->ForensicalCreateKey(HASH_SHA256, cPass, KEY_AES_256, &fk))
				{					
					MessageBoxW(hGlobalDlg, L"Failed to encrypt text", L"Error", MB_ICONERROR);
				}
				else
				{					
					ZeroMemory(&fd, sizeof(FORENSICAL_DATA));
					cTxt = new CHAR[512];
					wcstombs(cTxt, szTxt, 512);

					if (!forensical->ForensicalEncrypt(&fk, cTxt, &fd))
					{
						MessageBoxW(hGlobalDlg, L"Failed to encrypt text", L"Error", MB_ICONERROR);
					}
					else
					{
						cRes = (char*)fd.pbData;
						szRes = new WCHAR[fd.dwOutputLen];
						mbstowcs(szRes, cRes, fd.dwOutputLen);

						szFinal = new WCHAR[fd.dwOutputLen + 50];
						wcscpy(szFinal, L"[*] Result: ");
						wcscat(szFinal, szRes);

						SetDlgItemTextW(hGlobalDlg, IDC_AREA_PASS_ENC, szFinal);

						MessageBoxW(hGlobalDlg, L"Encrypting process has been done successfully", L"Success", MB_ICONINFORMATION);
					}
				}
			}

		}
		else
		{			
			ZeroMemory(&ofnIn, sizeof(OPENFILENAMEW));
			ofnIn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
			ofnIn.hwndOwner = hGlobalDlg;
			ofnIn.lpstrFile = szFileIn;
			ofnIn.lpstrFilter = L"All files\0*.*\0\0";
			ofnIn.lpstrTitle = L"File to Encrypt";
			ofnIn.lStructSize = sizeof(OPENFILENAMEW);
			ofnIn.nMaxFile = 256;

			if (GetOpenFileNameW(&ofnIn))
			{
				ZeroMemory(&ofnOut, sizeof(OPENFILENAMEW));
				ofnOut.Flags = OFN_PATHMUSTEXIST;
				ofnOut.hwndOwner = hGlobalDlg;
				ofnOut.lpstrFile = szFileOut;
				ofnOut.lpstrTitle = L"Save the Encrypted file";
				ofnOut.lpstrFilter = L"All files\0*.*\0\0";
				ofnOut.nMaxFile = 256;
				ofnOut.lStructSize = sizeof(OPENFILENAMEW);
				
				SetDlgItemTextW(hGlobalDlg, IDC_EDIT_PASS_ENC_BROWSE, szFileIn);

				if (GetSaveFileNameW(&ofnOut))
				{
					
					forensical = new Forensical();
					ZeroMemory(&fk, sizeof(FORENSICAL_KEY));
					ZeroMemory(&fd, sizeof(FORENSICAL_DATA));

					cIn = new CHAR[256];
					cOut = new CHAR[256];
					wcstombs(cIn, szFileIn, 256);
					wcstombs(cOut, szFileOut, 256);

					GetDlgItemTextW(hGlobalDlg, IDC_EDIT_PASS_ENC_PASS, szPass, 512);
					cPass = new CHAR[512];
					wcstombs(cPass, szPass, 512);

					if (!forensical->ForensicalCreateKey(HASH_SHA256, cPass, KEY_AES_256, &fk))
					{						
						MessageBoxW(hGlobalDlg, L"Failed to encrypt file", L"Falied", MB_ICONERROR);
					}
					else
					{						

						SetDlgItemTextW(hGlobalDlg, IDC_AREA_PASS_ENC, L"[*] Wait...");

						if (!forensical->ForensicalEncrypt(&fk, cIn, cOut))
						{							
							MessageBoxW(hGlobalDlg, L"Failed to encrypt file", L"Falied", MB_ICONERROR);
						}
						else
						{							
							SetDlgItemTextW(hGlobalDlg, IDC_AREA_PASS_ENC, L"Encrypt process has been done successfully");
							MessageBoxW(hGlobalDlg, L"Encrypt process has been done successfully", L"Success", MB_ICONINFORMATION);
						}

					}

				}

			}
		}
	}
	

	return 0;
}

DWORD WINAPI fileDecryptBrowse(LPVOID lpParam)
{	
	OPENFILENAMEW ofn;
	
	ZeroMemory(wszFile, 256);
	ZeroMemory(&ofn, sizeof(OPENFILENAMEW));

	ofn.Flags = OFN_FILEMUSTEXIST;
	ofn.hwndOwner = hGlobalDlg;
	ofn.lpstrFile = wszFile;
	ofn.lpstrFilter = L"All Files \0*.*\0\0";
	ofn.lpstrTitle = L"File to Decrypt";
	ofn.nMaxFile = 256;
	ofn.lStructSize = sizeof(OPENFILENAMEW);

	HWND hBtnEnc = GetDlgItem(hGlobalDlg, IDC_BTN_FILE_DEC_START);
	
	if (GetOpenFileNameW(&ofn))
	{

		EnableWindow(hBtnEnc, TRUE);
		SetDlgItemTextW(hGlobalDlg, IDC_EDIT_FILE_DECRYPT, wszFile);
	}
	else
	{
		EnableWindow(hBtnEnc, FALSE);
		SetDlgItemTextW(hGlobalDlg, IDC_EDIT_FILE_DECRYPT, wszFile);
	}	


	return 0;
}

DWORD WINAPI fileDecryptStart(LPVOID lpParam)
{	
	OPENFILENAMEW ofn;
	wchar_t szFileOut[256];
	Forensical* forensical;
	char* c_fileInt, * c_fileOut;
	
	ZeroMemory(&ofn, sizeof(OPENFILENAMEW));

	ofn.Flags = OFN_PATHMUSTEXIST;
	ofn.hwndOwner = hGlobalDlg;
	ofn.lpstrFile = szFileOut;
	ofn.lpstrFilter = L"All Files \0*.*\0\0";
	ofn.lpstrTitle = L"Save File Decrypted";
	ofn.nMaxFile = 256;
	ofn.lStructSize = sizeof(OPENFILENAMEW);

	HWND hBtnEnc = GetDlgItem(hGlobalDlg, IDC_BTN_FILE_DEC_START);
	
	if (GetSaveFileNameW(&ofn))
	{
		forensical = new Forensical();

		if (lpKey)
		{

			c_fileInt = new CHAR[256];
			wcstombs(c_fileInt, wszFile, 256);
			c_fileOut = new CHAR[256];
			wcstombs(c_fileOut, szFileOut, 256);

			HWND hWait;
			hWait = GetDlgItem(hGlobalDlg, IDC_ST_FILE_DEC_WAIT);
			ShowWindow(hWait, TRUE);


			if (forensical->ForensicalDecrypt(reinterpret_cast<FORENSICAL_KEY*>(lpKey), c_fileInt, c_fileOut))
			{
				MessageBoxW(hGlobalDlg, L"The decryption has been processed successfully", L"Success", MB_ICONINFORMATION);
				ShowWindow(hWait, FALSE);
			}
			else
			{
				MessageBoxW(hGlobalDlg, L"The decrypting process has failured.", L"Error", MB_ICONERROR);
				ShowWindow(hWait, FALSE);
			}
		}
		else
		{
			MessageBoxW(hGlobalDlg, L"To start the encryption routine, you must first generate a new key in Menu > Key > Generate New Key, or read one at Menu > Key > Read Key", L"Key Needed", MB_ICONINFORMATION);
		}

	}
	else
	{
		MessageBoxW(hGlobalDlg, L"You must select a valid place to save the encrypted file.", L"Saving Needed", MB_ICONINFORMATION);
	}

	return 0;
}

DWORD WINAPI passDecrypt(LPVOID lpParam)
{	
	wchar_t szPass[512] = { 0 };
	char* cPass;		
	char* cRes;
	wchar_t* szRes, * szFinal;
	Forensical* forensical;
	FORENSICAL_KEY fk;
	FORENSICAL_DATA fd;
	OPENFILENAMEW ofnIn, ofnOut;
	wchar_t szFileIn[256], szFileOut[256];
	char* cIn, * cOut;
	
	GetDlgItemTextW(hGlobalDlg, IDC_EDIT_PASS_DEC_PASS, szPass, 512);
	
	if (!wcscmp(szPass, L""))
	{
		MessageBoxW(hGlobalDlg, L"Please, select a valid passowrd.", L"No Password", MB_ICONINFORMATION);

	}
	else
	{											
			ZeroMemory(&ofnIn, sizeof(OPENFILENAMEW));
			ofnIn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
			ofnIn.hwndOwner = hGlobalDlg;
			ofnIn.lpstrFile = szFileIn;
			ofnIn.lpstrFilter = L"All files\0*.*\0\0";
			ofnIn.lpstrTitle = L"File to Decrypt";
			ofnIn.lStructSize = sizeof(OPENFILENAMEW);
			ofnIn.nMaxFile = 256;

			if (GetOpenFileNameW(&ofnIn))
			{
				ZeroMemory(&ofnOut, sizeof(OPENFILENAMEW));
				ofnOut.Flags = OFN_PATHMUSTEXIST;
				ofnOut.hwndOwner = hGlobalDlg;
				ofnOut.lpstrFile = szFileOut;
				ofnOut.lpstrTitle = L"Save the Decrypted file";
				ofnOut.lpstrFilter = L"All files\0*.*\0\0";
				ofnOut.nMaxFile = 256;
				ofnOut.lStructSize = sizeof(OPENFILENAMEW);
				
				SetDlgItemTextW(hGlobalDlg, IDC_EDIT_PASS_DEC_BROWSE, szFileIn);

				if (GetSaveFileNameW(&ofnOut))
				{
					
					forensical = new Forensical();
					ZeroMemory(&fk, sizeof(FORENSICAL_KEY));
					ZeroMemory(&fd, sizeof(FORENSICAL_DATA));

					cIn = new CHAR[256];
					cOut = new CHAR[256];
					wcstombs(cIn, szFileIn, 256);
					wcstombs(cOut, szFileOut, 256);

					GetDlgItemTextW(hGlobalDlg, IDC_EDIT_PASS_DEC_PASS, szPass, 512);
					cPass = new CHAR[512];
					wcstombs(cPass, szPass, 512);

					if (!forensical->ForensicalCreateKey(HASH_SHA256, cPass, KEY_AES_256, &fk))
					{						
						MessageBoxW(hGlobalDlg, L"Failed to decrypt file", L"Falied", MB_ICONERROR);
					}
					else
					{						

						SetDlgItemTextW(hGlobalDlg, IDC_AREA_PASS_DEC, L"[*] Wait...");

						if (!forensical->ForensicalDecrypt(&fk, cIn, cOut))
						{
							
							MessageBoxW(hGlobalDlg, L"Failed to decrypt file", L"Falied", MB_ICONERROR);
						}
						else
						{							
							SetDlgItemTextW(hGlobalDlg, IDC_AREA_PASS_ENC, L"Decrypt process has been done successfully");
							MessageBoxW(hGlobalDlg, L"Decrypt process has been done successfully", L"Success", MB_ICONINFORMATION);
						}

					}

				}

			}
		
	}
	

	return 0;
}