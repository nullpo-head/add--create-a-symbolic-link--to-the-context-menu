#include <shlwapi.h>
#include <string>


void error(LPCWSTR mes) {
	MessageBox(NULL, mes, TEXT("エラー"), MB_OK | MB_ICONWARNING);
}

bool BoolRegDeleteKey(HKEY key, LPCWSTR path) {
	return ERROR_SUCCESS == RegDeleteKey(key, path);
}

int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow
	) {
		int result = MessageBox(NULL, TEXT("シンボリックリンク作成メニューを本当に削除しますか？"), TEXT("アンインストール"), MB_YESNO | MB_ICONQUESTION);
		result;
		if ( result == IDYES ) {
			bool result = BoolRegDeleteKey(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CommandStore\\shell\\newsymlink\\command"))
					&& BoolRegDeleteKey(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CommandStore\\shell\\newsymlink"))
				    && BoolRegDeleteKey(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CommandStore\\shell\\symlinktodb\\command"))
				    && BoolRegDeleteKey(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CommandStore\\shell\\symlinktodb"))
					&& BoolRegDeleteKey(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CommandStore\\shell\\symuninstall\\command"))
					&& BoolRegDeleteKey(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CommandStore\\shell\\symuninstall"))
					&& BoolRegDeleteKey(HKEY_CLASSES_ROOT, TEXT("*\\shell\\symlink"))
					&& BoolRegDeleteKey(HKEY_CLASSES_ROOT, TEXT("Folder\\shell\\newsymlink"));
			
			if (!result) {
				error(TEXT("何らかの原因でレジストリの削除の途中でレジストリの削除が失敗しました。Readme.txtを参考に手動でソフトウェアを全削除してください。"));
				return 0;
			}
			

			//lpCmdLineにはインストールパスが格納されている
			using namespace std;
			
			wchar_t *command;
			wstring installPath(lpCmdLine);
			wstring directory = installPath + L"\\directory_created";
			//ファイルdirectory_createdが存在していたら、フォルダもプログラムによって作成されたからフォルダごと削除
			if (PathFileExists((wchar_t*)directory.c_str())) {

				int length = directory.length() + wcslen(L"cmd.exe /c timeout /t 5 && rd /s /q \"\"");
				command = (wchar_t*)malloc(sizeof(wchar_t) * (length + 1));
				swprintf(command, length, L"cmd.exe /c timeout /t 5 && rd /s /q \"%s\"", lpCmdLine);				
			
			} else {


				wstring symlink = installPath + L"symlink.exe";
				wstring symlinkdb = installPath + L"symlinkdb.exe";
				wstring uninstall = installPath + L"uninstall.exe";

				int length = symlink.length() + symlinkdb.length() + uninstall.length() + wcslen(L"cmd.exe /c timeout /t 5 && del/q \"\" \"\" \"\"");
				command = (wchar_t*)malloc(sizeof(wchar_t) * (length + 1));
				swprintf(command, length, L"cmd.exe /c timeout /t 5 && del /q \"%s\" \"%s\" \"%s\"", (wchar_t*)symlink.c_str(), (wchar_t*)symlinkdb.c_str(), (wchar_t*)uninstall.c_str());
			}

			STARTUPINFO si;
			PROCESS_INFORMATION pi;
			ZeroMemory(&si, sizeof(si));
			si.cb = sizeof(si);
			ZeroMemory(&pi, sizeof(pi));
			si.dwFlags = STARTF_USESHOWWINDOW;
			si.wShowWindow = SW_HIDE;
	
			CreateProcess(NULL, command, NULL, NULL, NULL, 0, NULL, NULL, &si, &pi);

			return 0;

			
		} else {
			//アンインストールがキャンセルされた
			return 0;
		}

}