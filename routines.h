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
#include "resource.h"
#include "forensical.h"
#include "globals.h"

typedef unsigned char METHOD;

typedef void ONCE;

typedef struct _TXTPARAMS {
	HWND hWnd;
	LPVOID lpJobs;	
} TXTPARAMS, * LPTXTPARAMS;

typedef struct _FILEPARAMS {
	HWND hWnd;
	LPVOID lpJobs;
} FILEPARAMS, *LPFILEPARAMS;

#pragma warning(disable: 4996)

using namespace EduardoProgramador;

void startIconImg(HWND hWnd);
void startBitmapImg(INT_PTR iBitmap, HWND hWnd, INT_PTR iWidth, INT_PTR iHeight);
void saveFile(HWND hWnd, LPWSTR sFile, LPCWSTR szFilter, LPCWSTR szTitle, void (*ok)(HWND, LPWSTR, UINT), void (*error)(), UINT iKey);
void saveKeyToFile(HWND hWnd, LPWSTR szFile, UINT iKey);
DWORD WINAPI readKey(LPVOID lpParam);
DWORD WINAPI charEncrypt(LPVOID lpParam);
DWORD WINAPI fileEncryptBrowse(LPVOID lpParam);
DWORD WINAPI fileEncryptStart(LPVOID lpParam);
DWORD WINAPI passEncrypt(LPVOID lpParam);
DWORD WINAPI fileDecryptBrowse(LPVOID lpParam);
DWORD WINAPI fileDecryptStart(LPVOID lpParam);
DWORD WINAPI passDecrypt(LPVOID lpParam);

namespace EduardoProgramador
{
	class Jobs : public Forensical
	{
	private:	
		HWND hWndG;
		HWND hRbTxt;
		METHOD mRes;		
		void setYes();
		void setNo();		

	public:		
		
		const static METHOD YES = 1;
		const static METHOD NO = 0;

		Jobs(HWND hwnd);
		~Jobs();

		METHOD isTextHmac();
		ONCE macFromText();
		ONCE macFromFile();
		METHOD getMacResult();	
		METHOD enc(LPWSTR szFile);
		METHOD dec(LPWSTR szFile);

		
	};
}
