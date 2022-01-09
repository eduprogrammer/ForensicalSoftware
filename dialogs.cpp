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
#include "explorer.h"



HWND hGlobalDlg;
wchar_t szFile[252] = { 0 };

INT_PTR CALLBACK dlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{

	case WM_INITDIALOG:
		startIconImg(hWnd);

		startBitmapImg(IDB_BITMAP1, GetDlgItem(hWnd, IDC_IMAGE_LOGO), 140, 120);
		startBitmapImg(IDB_BITMAP2, GetDlgItem(hWnd, IDC_IMAGE_FENIX1), 50, 50);
		startBitmapImg(IDB_BITMAP2, GetDlgItem(hWnd, IDC_IMAGE_FENIX2), 50, 50);		

		return (INT_PTR)TRUE;


	case WM_CLOSE:
		EndDialog(hWnd, 0);
		PostQuitMessage(0);
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_FILE_EXIT:
			EndDialog(hWnd, 0);
			PostQuitMessage(0);
			return (INT_PTR)TRUE;

		case ID__GENERATEKEY:
			EndDialog(hWnd, 0);
			DialogBoxW(GetModuleHandleW(nullptr), MAKEINTRESOURCEW(IDD_GENERATE_KEY), hWin, dlgKeyGen);
			return (INT_PTR)TRUE;

		case ID_KEYS_READFROMKEY:
			EndDialog(hWnd, 0);
			DialogBoxW(GetModuleHandleW(nullptr), MAKEINTRESOURCEW(IDD_READ_KEY), hWin, dlgKeyRead);
			return (INT_PTR)TRUE;

		case ID_ENCRYPTION_CHARACTERENCRYPTION:			
			EndDialog(hWnd, 0);
			DialogBoxW(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_CHAR_ENCRYPT), hWnd, dlgCharEncrypt);
			return TRUE;

		case ID_ENCRYPTION_FILEENCRYPTION:			
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_FILE_ENCRYPT), hWnd, dlgFileEncrypt);
			return TRUE;

		case ID_ENCRYPTION_PASSWORDENCRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_PASS_ENC), hWnd, dlgPassEncrypt);
			return TRUE;		

		case ID_DECRYPTION_FILEDECRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_FILE_DECRYPT), hWnd, dlgFileDecrypt);
			return TRUE;

		case ID_DECRYPTION_PASS:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_PASS_DEC), hWnd, dlgPassDecrypt);
			return TRUE;

		case ID_HMACMODULE_GETMAC:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_HMAC), hWnd, dlgHmac);
			return TRUE;

		case ID_FILE_EASYENCRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_EASY_ENC), hWnd, dlgEasyEnc);
			break;

		case ID_FILE_EASYDECRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_EASY_DEC), hWnd, dlgEasyDec);
			break;

		default:
			return (INT_PTR)FALSE;
		}


	default:
		return (INT_PTR)FALSE;
	}
} 

INT_PTR CALLBACK dlgKeyGen(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch (uMsg)
	{
	case WM_INITDIALOG:

		startIconImg(hWnd);
		startBitmapImg(IDB_BITMAP3, GetDlgItem(hWnd, IDC_IMG_KEY_GEN_BACK), 100, 200);

		HWND hBox;
		hBox = GetDlgItem(hWnd, IDC_COMBO_GEN_KEY);

		SendMessageW(hBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"RC2_40"));
		SendMessageW(hBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"RC4_40"));
		SendMessageW(hBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"DES_56"));
		SendMessageW(hBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"2DES_112"));
		SendMessageW(hBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"3DES_168"));
		SendMessageW(hBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"KEY_AES_128"));
		SendMessageW(hBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"KEY_AES_192"));
		SendMessageW(hBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"KEY_AES_256"));

		SendMessageW(hBox, CB_SETCURSEL, static_cast<WPARAM>(0), 0);

		return (INT_PTR)TRUE;

	case WM_CLOSE:
		EndDialog(hWin, 0);
		PostQuitMessage(0);
		return (INT_PTR)TRUE;

	case WM_COMMAND:

		switch (LOWORD(wParam))
		{

		case IDC_BTN_KEY_GENERATE:

			INT_PTR iChosen;
			HWND hBox;
			hBox = GetDlgItem(hWnd, IDC_COMBO_GEN_KEY);

			iChosen = SendMessageW(hBox, CB_GETCURSEL, 0, 0);
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
			

			saveFile(hWnd, szFile, L"All Files\0*.*\0\0", L"Save Key", &saveKeyToFile, nullptr, iKey);

			return static_cast<INT_PTR>(TRUE);

		case ID_FILE_EXIT:
			EndDialog(hWnd, 0);
			PostQuitMessage(0);
			return (INT_PTR)TRUE;

		case ID_KEYS_READFROMKEY:
			EndDialog(hWnd, 0);
			DialogBoxW(GetModuleHandleW(nullptr), MAKEINTRESOURCEW(IDD_READ_KEY), hWin, dlgKeyRead);
			return (INT_PTR)TRUE;

		case ID_ENCRYPTION_CHARACTERENCRYPTION:			
			EndDialog(hWnd, 0);
			DialogBoxW(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_CHAR_ENCRYPT), hWnd, dlgCharEncrypt);
			return TRUE;

		case ID_ENCRYPTION_FILEENCRYPTION:			
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_FILE_ENCRYPT), hWnd, dlgFileEncrypt);
			return TRUE;

		case ID_ENCRYPTION_PASSWORDENCRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_PASS_ENC), hWnd, dlgPassEncrypt);
			return TRUE;		

		case ID_DECRYPTION_FILEDECRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_FILE_DECRYPT), hWnd, dlgFileDecrypt);
			return TRUE;

		case ID_DECRYPTION_PASS:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_PASS_DEC), hWnd, dlgPassDecrypt);
			return TRUE;

		case ID_HMACMODULE_GETMAC:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_HMAC), hWnd, dlgHmac);
			return TRUE;

		case ID_FILE_EASYENCRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_EASY_ENC), hWnd, dlgEasyEnc);
			break;

		case ID_FILE_EASYDECRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_EASY_DEC), hWnd, dlgEasyDec);
			break;

		default:
			return static_cast<INT_PTR>(FALSE);
		}



	default:
		return static_cast<INT_PTR>(FALSE);
	}
}

INT_PTR CALLBACK dlgKeyRead(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{

	case WM_INITDIALOG:
		startIconImg(hWnd);
		startBitmapImg(IDB_BITMAP4, GetDlgItem(hWnd, IDC_IMG_KEY_READ_BACK), 100, 200);

		HWND hBox;
		hBox = GetDlgItem(hWnd, IDC_COMBO_READ_KEY);

		SendMessageW(hBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"RC2_40"));
		SendMessageW(hBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"RC4_40"));
		SendMessageW(hBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"DES_56"));
		SendMessageW(hBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"2DES_112"));
		SendMessageW(hBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"3DES_168"));
		SendMessageW(hBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"KEY_AES_128"));
		SendMessageW(hBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"KEY_AES_192"));
		SendMessageW(hBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"KEY_AES_256"));

		SendMessageW(hBox, CB_SETCURSEL, static_cast<WPARAM>(0), 0);

		hGlobalDlg = hWnd;

		return TRUE;

	case WM_CLOSE:
		EndDialog(hWnd, 0);
		PostQuitMessage(0);
		return TRUE;

	case WM_COMMAND:

		switch (LOWORD(wParam))
		{


		case IDC_BTN_KEY_READ:
			CreateThread(nullptr, 0, &readKey, nullptr, 0, nullptr);
			return TRUE;

		case ID_FILE_EXIT:
			EndDialog(hWnd, 0);
			PostQuitMessage(0);
			return (INT_PTR)TRUE;

		case ID__GENERATEKEY:
			EndDialog(hWnd, 0);
			DialogBoxW(GetModuleHandleW(nullptr), MAKEINTRESOURCEW(IDD_GENERATE_KEY), hWin, dlgKeyGen);
			return (INT_PTR)TRUE;

		case ID_ENCRYPTION_CHARACTERENCRYPTION:			
			EndDialog(hWnd, 0);
			DialogBoxW(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_CHAR_ENCRYPT), hWnd, dlgCharEncrypt);
			return TRUE;

		case ID_ENCRYPTION_FILEENCRYPTION:			
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_FILE_ENCRYPT), hWnd, dlgFileEncrypt);
			return TRUE;

		case ID_ENCRYPTION_PASSWORDENCRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_PASS_ENC), hWnd, dlgPassEncrypt);
			return TRUE;
		

		case ID_DECRYPTION_FILEDECRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_FILE_DECRYPT), hWnd, dlgFileDecrypt);
			return TRUE;

		case ID_DECRYPTION_PASS:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_PASS_DEC), hWnd, dlgPassDecrypt);
			return TRUE;

		case ID_HMACMODULE_GETMAC:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_HMAC), hWnd, dlgHmac);
			return TRUE;

		case ID_FILE_EASYENCRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_EASY_ENC), hWnd, dlgEasyEnc);
			break;

		case ID_FILE_EASYDECRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_EASY_DEC), hWnd, dlgEasyDec);
			break;


		default:
			return FALSE;
		}

	default:
		return FALSE;
	}
}

INT_PTR CALLBACK dlgCharEncrypt(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{

	case WM_INITDIALOG:
		startIconImg(hWnd);
		startBitmapImg(IDB_BITMAP5, GetDlgItem(hWnd, IDC_BMP_CHAR_ENCRYPT), 100, 70);

		hGlobalDlg = hWnd;

		return TRUE;

	case WM_CLOSE:
		EndDialog(hWnd, 0);
		PostQuitMessage(0);
		return TRUE;

	case WM_COMMAND:

		switch (LOWORD(wParam))
		{

		case IDC_BTN_CHAR_ENCRYPT:
			CreateThread(nullptr, 0, &charEncrypt, nullptr, 0, 0);
			return TRUE;

		case ID_FILE_EXIT:
			EndDialog(hWnd, 0);
			PostQuitMessage(0);
			return (INT_PTR)TRUE;

		case ID__GENERATEKEY:
			EndDialog(hWnd, 0);
			DialogBoxW(GetModuleHandleW(nullptr), MAKEINTRESOURCEW(IDD_GENERATE_KEY), hWin, dlgKeyGen);
			return (INT_PTR)TRUE;

		case ID_KEYS_READFROMKEY:
			EndDialog(hWnd, 0);
			DialogBoxW(GetModuleHandleW(nullptr), MAKEINTRESOURCEW(IDD_READ_KEY), hWin, dlgKeyRead);
			return (INT_PTR)TRUE;

		case ID_ENCRYPTION_FILEENCRYPTION:			
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_FILE_ENCRYPT), hWnd, dlgFileEncrypt);
			return TRUE;

		case ID_ENCRYPTION_PASSWORDENCRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_PASS_ENC), hWnd, dlgPassEncrypt);
			return TRUE;		

		case ID_DECRYPTION_FILEDECRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_FILE_DECRYPT), hWnd, dlgFileDecrypt);
			return TRUE;

		case ID_DECRYPTION_PASS:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_PASS_DEC), hWnd, dlgPassDecrypt);
			return TRUE;

		case ID_HMACMODULE_GETMAC:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_HMAC), hWnd, dlgHmac);
			return TRUE;

		case ID_FILE_EASYENCRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_EASY_ENC), hWnd, dlgEasyEnc);
			break;

		case ID_FILE_EASYDECRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_EASY_DEC), hWnd, dlgEasyDec);
			break;

		default:
			return FALSE;
		}

	default:
		return FALSE;
	}
}

INT_PTR CALLBACK dlgFileEncrypt(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{

	case WM_INITDIALOG:
		startIconImg(hWnd);
		startBitmapImg(IDB_BITMAP6, GetDlgItem(hWnd, IDC_BMP_FILE_ENCRYPT), 100, 170);

		HWND hBox;
		hBox = GetDlgItem(hWnd, IDC_COMBO_FILE_ENCRYPT);

		SendMessageW(hBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"RC2_40"));
		SendMessageW(hBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"RC4_40"));
		SendMessageW(hBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"DES_56"));
		SendMessageW(hBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"2DES_112"));
		SendMessageW(hBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"3DES_168"));
		SendMessageW(hBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"KEY_AES_128"));
		SendMessageW(hBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"KEY_AES_192"));
		SendMessageW(hBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"KEY_AES_256"));

		SendMessageW(hBox, CB_SETCURSEL, static_cast<WPARAM>(0), 0);

		HWND hStart;
		hStart = GetDlgItem(hWnd, IDC_BTN_FILE_ENC_START);

		EnableWindow(hStart, FALSE);

		hGlobalDlg = hWnd;

		return TRUE;

	case WM_CLOSE:
		EndDialog(hWnd, 0);
		PostQuitMessage(0);
		return TRUE;

	case WM_COMMAND:

		switch (LOWORD(wParam))
		{

		case IDC_BTN_FILE_ENC_BROWSE:
			CreateThread(nullptr, 0, &fileEncryptBrowse, nullptr, 0, 0);
			return TRUE;

		case IDC_BTN_FILE_ENC_START:
			CreateThread(nullptr, 0, &fileEncryptStart, nullptr, 0, 0);
			return TRUE;

		case ID_FILE_EXIT:
			EndDialog(hWnd, 0);
			PostQuitMessage(0);
			return (INT_PTR)TRUE;

		case ID__GENERATEKEY:
			EndDialog(hWnd, 0);
			DialogBoxW(GetModuleHandleW(nullptr), MAKEINTRESOURCEW(IDD_GENERATE_KEY), hWin, dlgKeyGen);
			return (INT_PTR)TRUE;

		case ID_KEYS_READFROMKEY:
			EndDialog(hWnd, 0);
			DialogBoxW(GetModuleHandleW(nullptr), MAKEINTRESOURCEW(IDD_READ_KEY), hWin, dlgKeyRead);
			return (INT_PTR)TRUE;

		case IDD_DLG_CHAR_ENCRYPT:
			EndDialog(hWnd, 0);
			DialogBoxW(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDD_DLG_CHAR_ENCRYPT), hWin, dlgCharEncrypt);
			return TRUE;

		case ID_ENCRYPTION_PASSWORDENCRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_PASS_ENC), hWnd, dlgPassEncrypt);
			return TRUE;		

		case ID_DECRYPTION_FILEDECRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_FILE_DECRYPT), hWnd, dlgFileDecrypt);
			return TRUE;

		case ID_DECRYPTION_PASS:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_PASS_DEC), hWnd, dlgPassDecrypt);
			return TRUE;

		case ID_HMACMODULE_GETMAC:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_HMAC), hWnd, dlgHmac);
			return TRUE;

		case ID_FILE_EASYENCRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_EASY_ENC), hWnd, dlgEasyEnc);
			break;

		case ID_FILE_EASYDECRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_EASY_DEC), hWnd, dlgEasyDec);
			break;

		default:
			return FALSE;
		}


	default:
		return FALSE;
	}
}

INT_PTR CALLBACK dlgPassEncrypt(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{

	case WM_INITDIALOG:
		startIconImg(hWnd);
		startBitmapImg(IDB_BITMAP7, GetDlgItem(hWnd, IDC_IMG_PASS_ENC), 150, 40);

		HWND hStart, hRbText, hRbFile, hPass;
		hStart = GetDlgItem(hWnd, IDC_BTN_PASS_ENC_START);
		hRbText = GetDlgItem(hWnd, IDC_RB_PASS_ENC_TXT);
		hRbFile = GetDlgItem(hWnd, IDC_RB_PASS_ENC_FILE);
		hPass = GetDlgItem(hWnd, IDC_EDIT_PASS_ENC_PASS);

		SendMessageW(hRbFile, BM_SETCHECK, BST_CHECKED, 0);
		SendMessageW(hPass, EM_SETPASSWORDCHAR, (WPARAM)L'*', 0);

		hGlobalDlg = hWnd;


		return TRUE;

	case WM_CLOSE:
		EndDialog(hWnd, 0);
		PostQuitMessage(0);
		return TRUE;

	case WM_COMMAND:

		switch (LOWORD(wParam))
		{

		case ID_FILE_EXIT:
			EndDialog(hWnd, 0);
			PostQuitMessage(0);
			return (INT_PTR)TRUE;

		case ID__GENERATEKEY:
			EndDialog(hWnd, 0);
			DialogBoxW(GetModuleHandleW(nullptr), MAKEINTRESOURCEW(IDD_GENERATE_KEY), hWin, dlgKeyGen);
			return (INT_PTR)TRUE;

		case ID_KEYS_READFROMKEY:
			EndDialog(hWnd, 0);
			DialogBoxW(GetModuleHandleW(nullptr), MAKEINTRESOURCEW(IDD_READ_KEY), hWin, dlgKeyRead);
			return (INT_PTR)TRUE;

		case ID_ENCRYPTION_CHARACTERENCRYPTION:			
			EndDialog(hWnd, 0);
			DialogBoxW(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_CHAR_ENCRYPT), hWnd, dlgCharEncrypt);
			return TRUE;

		case ID_ENCRYPTION_FILEENCRYPTION:			
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_FILE_ENCRYPT), hWnd, dlgFileEncrypt);
			return TRUE;		

		case ID_DECRYPTION_FILEDECRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_FILE_DECRYPT), hWnd, dlgFileDecrypt);
			return TRUE;

		case ID_DECRYPTION_PASS:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_PASS_DEC), hWnd, dlgPassDecrypt);
			return TRUE;	

		case ID_HMACMODULE_GETMAC:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_HMAC), hWnd, dlgHmac);
			return TRUE;

		case ID_FILE_EASYENCRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_EASY_ENC), hWnd, dlgEasyEnc);
			break;

		case ID_FILE_EASYDECRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_EASY_DEC), hWnd, dlgEasyDec);
			break;

		case IDC_BTN_PASS_ENC_START:
			CreateThread(nullptr, 0, passEncrypt, nullptr, 0, 0);
			return TRUE;



		default:
			return FALSE;
		}

	default:
		return FALSE;
	}
}

INT_PTR CALLBACK dlgFileDecrypt(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{

	case WM_INITDIALOG:
		startIconImg(hWnd);
		startBitmapImg(IDB_BITMAP6, GetDlgItem(hWnd, IDC_BMP_FILE_DECRYPT), 100, 170);

		HWND hBox;
		hBox = GetDlgItem(hWnd, IDC_COMBO_FILE_DECRYPT);

		SendMessageW(hBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"RC2_40"));
		SendMessageW(hBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"RC4_40"));
		SendMessageW(hBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"DES_56"));
		SendMessageW(hBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"2DES_112"));
		SendMessageW(hBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"3DES_168"));
		SendMessageW(hBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"KEY_AES_128"));
		SendMessageW(hBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"KEY_AES_192"));
		SendMessageW(hBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"KEY_AES_256"));

		SendMessageW(hBox, CB_SETCURSEL, static_cast<WPARAM>(0), 0);

		HWND hStart;
		hStart = GetDlgItem(hWnd, IDC_BTN_FILE_DEC_START);

		EnableWindow(hStart, FALSE);

		hGlobalDlg = hWnd;

		return TRUE;

	case WM_CLOSE:
		EndDialog(hWnd, 0);
		PostQuitMessage(0);
		return TRUE;

	case WM_COMMAND:

		switch (LOWORD(wParam))
		{

		case IDC_BTN_FILE_DEC_BROWSE:
			CreateThread(nullptr, 0, &fileDecryptBrowse, nullptr, 0, 0);
			return TRUE;

		case IDC_BTN_FILE_DEC_START:
			CreateThread(nullptr, 0, &fileDecryptStart, nullptr, 0, 0);
			return TRUE;

		case ID_FILE_EXIT:
			EndDialog(hWnd, 0);
			PostQuitMessage(0);
			return (INT_PTR)TRUE;

		case ID__GENERATEKEY:
			EndDialog(hWnd, 0);
			DialogBoxW(GetModuleHandleW(nullptr), MAKEINTRESOURCEW(IDD_GENERATE_KEY), hWin, dlgKeyGen);
			return (INT_PTR)TRUE;


		case ID_KEYS_READFROMKEY:
			EndDialog(hWnd, 0);
			DialogBoxW(GetModuleHandleW(nullptr), MAKEINTRESOURCEW(IDD_READ_KEY), hWin, dlgKeyRead);
			return (INT_PTR)TRUE;

		case ID_ENCRYPTION_CHARACTERENCRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_CHAR_ENCRYPT), hWnd, dlgCharEncrypt);
			return TRUE;

		case ID_ENCRYPTION_FILEENCRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_FILE_ENCRYPT), hWnd, dlgFileEncrypt);
			return TRUE;

		case ID_ENCRYPTION_PASSWORDENCRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_PASS_ENC), hWnd, dlgPassEncrypt);
			return TRUE;		

		case ID_DECRYPTION_PASS:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_PASS_DEC), hWnd, dlgPassDecrypt);
			return TRUE;

		case ID_HMACMODULE_GETMAC:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_HMAC), hWnd, dlgHmac);
			return TRUE;

		case ID_FILE_EASYENCRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_EASY_ENC), hWnd, dlgEasyEnc);
			break;

		case ID_FILE_EASYDECRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_EASY_DEC), hWnd, dlgEasyDec);
			break;

		default:
			return FALSE;
		}


	default:
		return FALSE;
	}
}

INT_PTR CALLBACK dlgPassDecrypt(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{

	case WM_INITDIALOG:
		startIconImg(hWnd);
		startBitmapImg(IDB_BITMAP7, GetDlgItem(hWnd, IDC_IMG_PASS_DEC), 150, 40);

		HWND hStart, hPass;
		hStart = GetDlgItem(hWnd, IDC_BTN_PASS_DEC_START);		
		hPass = GetDlgItem(hWnd, IDC_EDIT_PASS_DEC_PASS);
		
		SendMessageW(hPass, EM_SETPASSWORDCHAR, (WPARAM)L'*', 0);

		hGlobalDlg = hWnd;

		return TRUE;

	case WM_CLOSE:
		EndDialog(hWnd, 0);
		PostQuitMessage(0);
		return TRUE;

	case WM_COMMAND:

		switch (LOWORD(wParam))
		{

		case ID_FILE_EXIT:
			EndDialog(hWnd, 0);
			PostQuitMessage(0);
			return (INT_PTR)TRUE;

		case ID__GENERATEKEY:
			EndDialog(hWnd, 0);
			DialogBoxW(GetModuleHandleW(nullptr), MAKEINTRESOURCEW(IDD_GENERATE_KEY), hWin, dlgKeyGen);
			return (INT_PTR)TRUE;

		case ID_KEYS_READFROMKEY:
			EndDialog(hWnd, 0);
			DialogBoxW(GetModuleHandleW(nullptr), MAKEINTRESOURCEW(IDD_READ_KEY), hWin, dlgKeyRead);
			return (INT_PTR)TRUE;

		case ID_ENCRYPTION_CHARACTERENCRYPTION:			
			EndDialog(hWnd, 0);
			DialogBoxW(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_CHAR_ENCRYPT), hWnd, dlgCharEncrypt);
			return TRUE;

		case ID_ENCRYPTION_FILEENCRYPTION:			
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_FILE_ENCRYPT), hWnd, dlgFileEncrypt);
			return TRUE;

		case ID_ENCRYPTION_PASSWORDENCRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_PASS_ENC), hWnd, dlgPassEncrypt);
			return TRUE;		

		case ID_DECRYPTION_FILEDECRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_FILE_DECRYPT), hWnd, dlgFileDecrypt);
			return TRUE;

		case ID_HMACMODULE_GETMAC:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_HMAC), hWnd, dlgHmac);
			return TRUE;

		case ID_FILE_EASYENCRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_EASY_ENC), hWnd, dlgEasyEnc);
			break;

		case ID_FILE_EASYDECRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_EASY_DEC), hWnd, dlgEasyDec);
			break;

		case IDC_BTN_PASS_DEC_START:
			CreateThread(nullptr, 0, passDecrypt, nullptr, 0, 0);
			return TRUE;

		default:
			return FALSE;
		}

	default:
		return FALSE;
	}
}

INT_PTR CALLBACK dlgHmac(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	
	

	switch (uMsg)
	{

		

	case WM_INITDIALOG:		
						
		HWND hBmp;
		hBmp = GetDlgItem(hWnd, IDC_BMP_HMAC_BACK);
		startBitmapImg(IDB_BITMAP8, hBmp, 50, 50);
		startIconImg(hWnd);

		HWND hRbTxt;
		hRbTxt = GetDlgItem(hWnd, IDC_RB_HMAC_TEXT);
		SendMessageW(hRbTxt, BM_SETCHECK, BST_CHECKED, 0);

		HWND hPass;
		hPass = GetDlgItem(hWnd, IDC_EDIT_HMAC_PASS);
		SendMessageW(hPass, EM_SETPASSWORDCHAR, static_cast<WPARAM>(L'*'), 0);

		HWND hWait, hCombo;
		hWait = GetDlgItem(hWnd, IDC_STATIC_HMAC_WAIT);
		hCombo = GetDlgItem(hWnd, IDC_COMBO_HMAC_HASH);

		ShowWindow(hWait, SW_HIDE);

		SendMessageW(hCombo, CB_ADDSTRING, 0, (LPARAM)L"MD5");
		SendMessageW(hCombo, CB_ADDSTRING, 0, (LPARAM)L"SHA-1");
		SendMessageW(hCombo, CB_ADDSTRING, 0, (LPARAM)L"SHA-256");
		SendMessageW(hCombo, CB_ADDSTRING, 0, (LPARAM)L"SHA-512");

		SendMessageW(hCombo, CB_SETCURSEL, 0, 0);		

		
		return TRUE;

	case WM_CLOSE:
		EndDialog(hWnd, 0);
		PostQuitMessage(0);
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{

		case ID_FILE_EXIT:
			EndDialog(hWnd, 0);
			PostQuitMessage(0);
			return (INT_PTR)TRUE;

		case ID__GENERATEKEY:
			EndDialog(hWnd, 0);
			DialogBoxW(GetModuleHandleW(nullptr), MAKEINTRESOURCEW(IDD_GENERATE_KEY), hWin, dlgKeyGen);
			return (INT_PTR)TRUE;

		case ID_KEYS_READFROMKEY:
			EndDialog(hWnd, 0);
			DialogBoxW(GetModuleHandleW(nullptr), MAKEINTRESOURCEW(IDD_READ_KEY), hWin, dlgKeyRead);
			return (INT_PTR)TRUE;

		case ID_ENCRYPTION_CHARACTERENCRYPTION:			
			EndDialog(hWnd, 0);
			DialogBoxW(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_CHAR_ENCRYPT), hWnd, dlgCharEncrypt);
			return TRUE;

		case ID_ENCRYPTION_FILEENCRYPTION:			
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_FILE_ENCRYPT), hWnd, dlgFileEncrypt);
			return TRUE;

		case ID_ENCRYPTION_PASSWORDENCRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_PASS_ENC), hWnd, dlgPassEncrypt);
			return TRUE;

		case ID_DECRYPTION_FILEDECRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_FILE_DECRYPT), hWnd, dlgFileDecrypt);
			return TRUE;	

		case ID_FILE_EASYENCRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_EASY_ENC), hWnd, dlgEasyEnc);
			break;

		case ID_FILE_EASYDECRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_EASY_DEC), hWnd, dlgEasyDec);
			break;

		case IDC_BTN_HMAC_CALCULATE:

			Jobs* jobs;
			jobs = new Jobs(hWnd);

			if (jobs)
			{
				if (jobs->isTextHmac())
				{

					wchar_t* szText; 
					szText = new WCHAR[512];
					GetDlgItemTextW(hWnd, IDC_EDIT_HMAC_TEXT, szText, 512);
					if (!wcscmp(szText, L""))
					{
						MessageBoxW(hWnd, L"Enter a valid text to calculate the MAC", L"No Text", MB_ICONINFORMATION);
					}
					else
					{
						wchar_t* szPass;
						szPass = new WCHAR[512];
						GetDlgItemTextW(hWnd, IDC_EDIT_HMAC_PASS, szPass, 512);

						if (!wcscmp(szPass, L""))
						{
							MessageBoxW(hWnd, L"You must inform a valid password", L"No Password", MB_ICONINFORMATION);
						}
						else
						{
							wchar_t *szTxt;
							szTxt = new WCHAR[512];

							jobs->macFromText();
							
						}
					}

					
				}
				else
				{

					jobs->macFromFile();

					
				}
			}

			
			return TRUE;

		default:
			return FALSE;
		}
		return TRUE;

	default:
		return FALSE;
	}
}

INT_PTR CALLBACK dlgEasyEnc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{

	case WM_INITDIALOG:

		HWND hBitmap, hWait;
		hBitmap = GetDlgItem(hWnd, IDC_BMP_EASY_ENC);
		hWait = GetDlgItem(hWnd, IDC_STATIC_EASY_ENC);

		startBitmapImg(IDB_BITMAP9, hBitmap, 50, 50);
		ShowWindow(hWait, SW_HIDE);

		return TRUE;

	case WM_CLOSE:
		EndDialog(hWnd, 0);
		PostQuitMessage(0);
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{

		case ID_FILE_EXIT:
			EndDialog(hWnd, 0);
			PostQuitMessage(0);
			return (INT_PTR)TRUE;

		case ID__GENERATEKEY:
			EndDialog(hWnd, 0);
			DialogBoxW(GetModuleHandleW(nullptr), MAKEINTRESOURCEW(IDD_GENERATE_KEY), hWin, dlgKeyGen);
			return (INT_PTR)TRUE;

		case ID_KEYS_READFROMKEY:
			EndDialog(hWnd, 0);
			DialogBoxW(GetModuleHandleW(nullptr), MAKEINTRESOURCEW(IDD_READ_KEY), hWin, dlgKeyRead);
			return (INT_PTR)TRUE;

		case ID_ENCRYPTION_CHARACTERENCRYPTION:			
			EndDialog(hWnd, 0);
			DialogBoxW(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_CHAR_ENCRYPT), hWnd, dlgCharEncrypt);
			return TRUE;

		case ID_ENCRYPTION_FILEENCRYPTION:			
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_FILE_ENCRYPT), hWnd, dlgFileEncrypt);
			return TRUE;

		case ID_ENCRYPTION_PASSWORDENCRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_PASS_ENC), hWnd, dlgPassEncrypt);
			return TRUE;

		case ID_DECRYPTION_FILEDECRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_FILE_DECRYPT), hWnd, dlgFileDecrypt);
			return TRUE;

		case ID_FILE_EASYDECRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_EASY_DEC), hWnd, dlgEasyDec);
			break;
		

		case IDC_BTN_EASY_ENC:			

			Explorer::Explorer* exp;
			exp = new Explorer::Explorer(hWnd);
			exp->openBrowse();

			return TRUE;

		default:
			return FALSE;
		}		

		return TRUE;

	default:
		return FALSE;
	}
}

INT_PTR CALLBACK dlgEasyDec(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{

	case WM_INITDIALOG:

		HWND hBitmap, hWait;
		hBitmap = GetDlgItem(hWnd, IDC_BMP_EASY_DEC);
		hWait = GetDlgItem(hWnd, IDC_STATIC_EASY_DEC);

		startBitmapImg(IDB_BITMAP9, hBitmap, 50, 50);
		ShowWindow(hWait, SW_HIDE);

		return TRUE;

	case WM_CLOSE:
		EndDialog(hWnd, 0);
		PostQuitMessage(0);
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{

		case ID_FILE_EXIT:
			EndDialog(hWnd, 0);
			PostQuitMessage(0);
			return (INT_PTR)TRUE;

		case ID__GENERATEKEY:
			EndDialog(hWnd, 0);
			DialogBoxW(GetModuleHandleW(nullptr), MAKEINTRESOURCEW(IDD_GENERATE_KEY), hWin, dlgKeyGen);
			return (INT_PTR)TRUE;

		case ID_KEYS_READFROMKEY:
			EndDialog(hWnd, 0);
			DialogBoxW(GetModuleHandleW(nullptr), MAKEINTRESOURCEW(IDD_READ_KEY), hWin, dlgKeyRead);
			return (INT_PTR)TRUE;

		case ID_ENCRYPTION_CHARACTERENCRYPTION:			
			EndDialog(hWnd, 0);
			DialogBoxW(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_CHAR_ENCRYPT), hWnd, dlgCharEncrypt);
			return TRUE;

		case ID_ENCRYPTION_FILEENCRYPTION:			
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_FILE_ENCRYPT), hWnd, dlgFileEncrypt);
			return TRUE;

		case ID_ENCRYPTION_PASSWORDENCRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_PASS_ENC), hWnd, dlgPassEncrypt);
			return TRUE;

		case ID_DECRYPTION_FILEDECRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_FILE_DECRYPT), hWnd, dlgFileDecrypt);
			return TRUE;

		case ID_FILE_EASYENCRYPTION:
			EndDialog(hWnd, 0);
			DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCEW(IDD_DLG_EASY_ENC), hWnd, dlgEasyEnc);
			break;


		case IDC_BTN_EASY_DEC:

			Explorer::Explorer* exp;
			exp = new Explorer::Explorer(hWnd);
			exp->saveBrowse();

			return TRUE;

		default:
			return FALSE;
		}

		return TRUE;

	default:
		return FALSE;
	}
}
