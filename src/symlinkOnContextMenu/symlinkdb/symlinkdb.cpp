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

	wchar_t *dpos = wcsrchr(lpCmdLine, L'\\');
	wchar_t *dname = (wchar_t*)malloc(sizeof(wchar_t) * wcslen(dpos));
	wcscpy(dname, dpos+1);
	int strlen;
	wchar_t *newpath = (wchar_t*)malloc(sizeof(wchar_t) * (strlen = (wcslen(dname) + wcslen(L"%HOMEPATH%\\Dropbox\\")) + 1));
	swprintf(newpath, strlen, L"%%HOMEPATH%%\\Dropbox\\%s", dname);
	strlen = ExpandEnvironmentStrings(newpath, NULL, 0);
	wchar_t *path = (wchar_t*)malloc(sizeof(wchar_t) * (strlen + 1));
	ExpandEnvironmentStrings(newpath, path, 1000);
	MoveFile(lpCmdLine, path);

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE;
	ZeroMemory(&pi, sizeof(pi));
	
	wchar_t *command = (wchar_t*)malloc(sizeof(wchar_t) * (strlen = (wcslen(path) + wcslen(lpCmdLine) + wcslen(L"cmd.exe /c mv mklink /d \"\" \"\"") + 1)));
	
	int isDirectory = GetFileAttributes(path) & FILE_ATTRIBUTE_DIRECTORY;
	if (isDirectory) {
		swprintf(command, strlen, L"cmd.exe /c mklink /d \"%s\" \"%s\"", lpCmdLine, path);
	} else {
		swprintf(command, strlen, L"cmd.exe /c mklink \"%s\" \"%s\"", lpCmdLine, path);
	}
	CreateProcess(NULL, command, NULL, NULL, NULL, 0, NULL, NULL, &si, &pi);

	free(command);
	free(dname);
	free(newpath);
	free(path);
	
	return 0;
	
}