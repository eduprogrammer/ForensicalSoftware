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

typedef void ONCE;
typedef BYTE METHOD;


namespace EduardoProgramador
{
	namespace Explorer
	{				
		class Explorer
		{
		private:					
			HWND hInit;

		public:		

			const static BYTE NO = 0;
			const static BYTE YES = 1;			

			Explorer(HWND hWnd);

			METHOD openBrowse();

			METHOD saveBrowse();

			virtual ONCE OnOperationOpenStart(LPSTR szFile, HWND hWnd); 

			virtual ONCE OnOperationSaveStart(LPSTR szFile, HWND hWnd);

		};
	}
}