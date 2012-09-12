#include <Windows.h>
#include <Winbase.h>
#include <strsafe.h>
#include <wchar.h>
#include <cstring>

int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow
	) {
	
	wchar_t *command;
	int isDirectory = GetFileAttributes(lpCmdLine) & FILE_ATTRIBUTE_DIRECTORY;
	if (isDirectory) {

		int strlen;
		command = (wchar_t*)malloc(sizeof(wchar_t) * (strlen = (wcslen(lpCmdLine) * 2 + wcslen(L"cmd.exe /c mklink /d \"へのリンク\" \"\"") + 1)));
		swprintf(command, strlen, L"cmd.exe /c mklink /d \"%sへのリンク\" \"%s\"", lpCmdLine, lpCmdLine);
		
	} else {

		wchar_t *pos = wcsrchr(lpCmdLine, L'\\');
		wchar_t *name = (wchar_t*)malloc(sizeof(wchar_t) * wcslen(pos));
		wcscpy(name, pos+1);
		*pos = L'\0';
		wchar_t *path = lpCmdLine;
		pos = wcsrchr(name, L'.');

		//name.extという形式のファイル名かどうか
		int isNormalWinFilename = (pos != NULL) && (pos != name) && (wcslen(pos) != 1);
		
		if ( isNormalWinFilename ) {
			wchar_t *ext = (wchar_t*)malloc(sizeof(wchar_t)* (wcslen(pos)));
			wcscpy(ext, pos+1);
			*pos = L'\0';
			int strlen;
			wchar_t *linkName = (wchar_t*)malloc(sizeof(wchar_t)*(strlen = (wcslen(path) + wcslen(name) + wcslen(ext) + wcslen(L".\\へのリンク") + 1)));
			swprintf(linkName, strlen, L"%s\\%sへのリンク.%s", path, name, ext);
			wchar_t *targetName = (wchar_t*)malloc(sizeof(wchar_t) * (strlen = (wcslen(path) + wcslen(name) + wcslen(ext) + wcslen(L".\\") + 1)));
			swprintf(targetName, strlen, L"%s\\%s.%s", path, name, ext);
			command = (wchar_t*)malloc(sizeof(wchar_t) * (strlen = (wcslen(linkName) + wcslen(targetName) + wcslen(L"cmd.exe /c mklink \"\" \"\"") + 1)));
			swprintf(command, strlen, L"cmd.exe /c mklink \"%s\" \"%s\"", linkName, targetName);
			
			free(ext);
			free(linkName);
			free(targetName);
		} else {
			int strlen;
			wchar_t *linkName = (wchar_t*)malloc(sizeof(wchar_t)*(strlen = (wcslen(path) + wcslen(name) + wcslen(L"\\へのリンク") + 1)));
			swprintf(linkName, strlen, L"%s\\%sへのリンク", path, name);
			wchar_t *targetName = (wchar_t*)malloc(sizeof(wchar_t) * (strlen = (wcslen(path) + wcslen(name) + wcslen(L"\\") + 1)));
			swprintf(targetName, strlen, L"%s\\%s", path, name);
			command = (wchar_t*)malloc(sizeof(wchar_t) * (strlen = (wcslen(linkName) + wcslen(targetName) + wcslen(L"cmd.exe /c mklink \"\" \"\"") + 1)));
			swprintf(command, strlen, L"cmd.exe /c mklink \"%s\" \"%s\"", linkName, targetName);
			
			free(linkName);
			free(targetName);
		}

	
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		si.dwFlags = STARTF_USESHOWWINDOW;
		si.wShowWindow = SW_HIDE;
		ZeroMemory(&pi, sizeof(pi));

		CreateProcess(NULL, command, NULL, NULL, NULL, 0, NULL, NULL, &si, &pi);
	
		free(name);
		free(command);
	}
	return 0;
	
}