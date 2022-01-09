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


#define IDD_DIALOG_INIT                 101
#define IDR_MENU1                       103
#define IDB_BITMAP1                     104
#define IDI_ICON1                       105
#define IDB_BITMAP2                     106
#define IDD_GENERATE_KEY                107
#define IDD_READ_KEY                    108
#define IDB_BITMAP3                     109
#define IDB_BITMAP4                     111
#define IDD_DLG_CHAR_ENCRYPT            112
#define IDB_BITMAP5                     113
#define IDD_DLG_FILE_ENCRYPT            115
#define IDB_BITMAP6                     117
#define IDD_DLG_PASS_ENC                118
#define IDB_BITMAP7                     120
#define IDD_DLG_FILE_DECRYPT            120
#define IDD_DLG_PASS_DEC                121
#define IDD_DLG_HMAC                    122
#define IDB_BITMAP8                     124
#define IDD_DLG_EASY_ENC                125
#define IDD_DLG_EASY_DEC                126
#define IDB_BITMAP9                     127
#define IDC_IMAGE_LOGO                  1001
#define IDC_IMAGE_FENIX1                1002
#define IDC_IMAGE_FENIX2                1003
#define IDC_COMBO_GEN_KEY               1006
#define IDC_BTN_KEY_GENERATE            1007
#define IDC_IMG_KEY_GEN_BACK            1008
#define IDC_IMG_KEY_READ_BACK           1009
#define IDC_COMBO_READ_KEY              1010
#define IDC_BTN_KEY_READ                1011
#define IDC_EDIT_CHAR_ENCRYPT           1012
#define IDC_BTN_CHAR_ENCRYPT            1013
#define IDC_BMP_CHAR_ENCRYPT            1014
#define IDC_AREA_CHAR_ENCRYPT           1015
#define IDC_EDIT_FILE_ENCRYPT           1016
#define IDC_BTN_FILE_ENC_BROWSE         1017
#define IDC_COMBO_FILE_ENCRYPT          1018
#define IDC_BTN_FILE_ENC_START          1019
#define IDC_BMP_FILE_ENCRYPT            1020
#define IDC_EDIT_PASS_ENC_PASS          1021
#define IDC_EDIT_PASS_ENC_TEXT          1022
#define IDC_EDIT_PASS_ENC_BROWSE        1024
#define IDC_BTN_PASS_ENC_START          1025
#define IDC_RB_PASS_ENC_TXT             1027
#define IDC_RB_PASS_ENC_FILE            1028
#define IDC_AREA_PASS_ENC               1029
#define IDC_IMG_PASS_ENC                1030
#define IDC_ST_FILE_ENC_WAIT            1031
#define IDC_EDIT_FILE_DECRYPT           1036
#define IDC_COMBO_FILE_DECRYPT          1037
#define IDC_BMP_FILE_DECRYPT            1038
#define IDC_BTN_FILE_DEC_START          1039
#define IDC_ST_FILE_DEC_WAIT            1040
#define IDC_EDIT_PASS_DEC_PASS          1041
#define IDC_EDIT_PASS_DEC_BROWSE        1043
#define IDC_BTN_PASS_DEC_START          1044
#define IDC_AREA_PASS_DEC               1047
#define IDC_IMG_PASS_DEC                1048
#define IDC_BTN_FILE_DEC_BROWSE         1049
#define IDC_RB_HMAC_TEXT                1050
#define IDC_RB_HMAC_FILE                1051
#define IDC_EDIT_HMAC_TEXT              1052
#define IDC_EDIT_HMAC_FILE              1053
#define IDC_BTN_HMAC_CALCULATE          1055
#define IDC_BMP_HMAC_BACK               1056
#define IDC_EDIT_HMAC_PASS              1057
#define IDC_EDIT_HMAC_RESULT            1058
#define IDC_STATIC_HMAC_WAIT            1059
#define IDC_COMBO_HMAC_HASH             1060
#define IDC_BTN_EASY_ENC                1061
#define IDC_BMP_EASY_ENC                1062
#define IDC_BMP_EASY_DEC                1063
#define IDC_BTN_EASY_DEC                1064
#define IDC_STATIC_EASY_DEC             1065
#define IDC_STATIC_EASY_ENC             1066
#define ID__GENERATEKEY                 40001
#define ID_KEYS_READFROMKEY             40002
#define ID_ENCRYPTION_CHARACTERENCRYPTION 40003
#define ID_ENCRYPTION_FILEENCRYPTION    40004
#define ID_DECRYPTION_CHARACTERDECRYPTION 40005
#define ID_DECRYPTION_FILEDECRYPTION    40006
#define ID_HMAC_HMACMODULE              40007
#define ID_HMACMODULE_CHARACTERHMAC     40008
#define ID_HMACMODULE_FILEHMAC          40009
#define ID_ABOUT_ABOUTFORENSICAL        40010
#define ID_ABOUT_USAGETUTORIAL          40011
#define ID_ABOUT_DEVELOPERPAGE          40012
#define ID_FILE_EXIT                    40013
#define ID_FILE_EASYENCRYPTION          40014
#define ID_FILE_EASYDECRYPTION          40015
#define ID_ENCRYPTION_PASSWORDENCRYPTION 40016
#define ID_DECRYPTION_PASS              40017
#define ID_HMACMODULE_GETMAC            40018


#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE        128
#define _APS_NEXT_COMMAND_VALUE         40019
#define _APS_NEXT_CONTROL_VALUE         1067
#define _APS_NEXT_SYMED_VALUE           101
#endif
#endif
