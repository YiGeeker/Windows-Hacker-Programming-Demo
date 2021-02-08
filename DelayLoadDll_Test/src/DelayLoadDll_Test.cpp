#include <windows.h>
#include <windowsx.h>
#include <string>
#include <stdio.h>
#include <tchar.h>
#include <commctrl.h>
#include "DelayLoadDll_Test.h"

using std::string;

void FreeRes_ShowError(char *pszText)
{
	char szErr[MAX_PATH] = { 0 };
	::wsprintf(szErr, "%s Error[%d]\n", pszText, ::GetLastError());
	::MessageBox(NULL, szErr, "ERROR", MB_OK);
}

// 释放资源
BOOL FreeMyResource(UINT uiResouceName, char *lpszResourceType, char *lpszSaveFileName)
{
	HRSRC hRsrc = ::FindResource(NULL, MAKEINTRESOURCE(uiResouceName), lpszResourceType);
	if (hRsrc == NULL)
	{
		FreeRes_ShowError("FindResource");
		return FALSE;
	}
	DWORD dwSize = ::SizeofResource(NULL, hRsrc);
	if (dwSize <= 0)
	{
		FreeRes_ShowError("SizeofResource");
		return FALSE;
	}
	HGLOBAL hGlobal = ::LoadResource(NULL, hRsrc);
	if (hGlobal == NULL)
	{
		FreeRes_ShowError("LoadResource");
		return FALSE;
	}
	LPVOID lpVoid = ::LockResource(hGlobal);
	if (lpVoid == NULL)
	{
		FreeRes_ShowError("LockResource");
		return FALSE;
	}

	FILE *fp = NULL;
	fopen_s(&fp, lpszSaveFileName, "wb+");
	if (fp == NULL)
	{
		FreeRes_ShowError("LockResource");
		return FALSE;
	}
	fwrite(lpVoid, sizeof(char), dwSize, fp);
	fclose(fp);

	return TRUE;
}

// 获取当前目录
void GetCurrentPath(char *lpszCurrentPath, DWORD dwSize)
{
	::GetModuleFileName(NULL, lpszCurrentPath, dwSize);
	CHAR *p = ::strrchr(lpszCurrentPath, '\\');
	p[0] = '\0';
}

// 加载界面皮肤
void LoadSkin()
{
	// 加载皮肤
	// 获取当前目录
	char szCurrentPath[MAX_PATH] = { 0 };
	GetCurrentPath(szCurrentPath, MAX_PATH);
	// 构造路径
	::lstrcat(szCurrentPath, "\\Skins\\");
	::lstrcat(szCurrentPath, "dogmax2.ssk");
	// 加载皮肤
	::skinppLoadSkin(szCurrentPath);
}

bool DlgOnInit(HWND hWnd, HWND hWndFocus, LPARAM lParam)
{
	// 释放DLL
	// 获取当前目录
	char szCurrentPath[MAX_PATH] = { 0 };
	GetCurrentPath(szCurrentPath, MAX_PATH);
	// 构造路径
	::lstrcat(szCurrentPath, "\\skinppwtl.dll");
	FreeMyResource(IDR_MY_BIN1, "MY_BIN", szCurrentPath);

	// 加载皮肤
	LoadSkin();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

bool DlgOnClose(HWND hWnd)
{
	::EndDialog(hWnd, NULL);
	return true;
}

INT_PTR CALLBACK DlgMainProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		HANDLE_MSG(hWnd, WM_INITDIALOG, DlgOnInit);
		HANDLE_MSG(hWnd, WM_CLOSE, DlgOnClose);
	}
	
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{
	::InitCommonControls();
	::DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DELAYLOADDLL_TEST_DIALOG), NULL, DlgMainProc, NULL);
	return 0;
}
