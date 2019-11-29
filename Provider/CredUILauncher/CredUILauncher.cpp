// CredUILauncher.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <WinCred.h>

int _tmain(int argc, _TCHAR* argv[])
{
	BOOL save = false;
	DWORD authPackage = 0;
	LPVOID authBuffer;
	ULONG authBufferSize = 0;
	CREDUI_INFO credUiInfo;

	credUiInfo.pszCaptionText = TEXT("WinCred UI Demo");
	credUiInfo.pszMessageText = TEXT("Example of RFID!");
	credUiInfo.cbSize = sizeof(credUiInfo);
	credUiInfo.hbmBanner = nullptr;
	credUiInfo.hwndParent = nullptr;
	
	CredUIPromptForWindowsCredentials(&credUiInfo, 0, &authPackage, nullptr, 0, &authBuffer, &authBufferSize, &save, 0);

	return 0;
}

