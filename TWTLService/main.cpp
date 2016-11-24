// main.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <cstdio>
#include <cstdlib>
#include <cerrno>

static int get_full_path(_In_ LPCTSTR lpszArgv0, _Outptr_opt_ LPTSTR *lpszResult);

int __cdecl _tmain(int argc, LPTSTR *argv) {
	if (argc == 1) {
		SERVICE_TABLE_ENTRY DispatchTable[] = {
			{ SVCNAME, (LPSERVICE_MAIN_FUNCTION) SvcMain },
			{ NULL, NULL }
		};
		if (!StartServiceCtrlDispatcher(DispatchTable)) {
			SvcReportEvent(_T("StartServiceCtrlDispatcher"), EVENTLOG_ERROR_TYPE);
			puts("Failed to start service");
			return -1;
		}
	} else if (argc == 2) {
		LPTSTR path = NULL;
		if (get_full_path(argv[0], &path)) {
			puts("Failed to get full path of this executable.");
			return -1;
		}
		_tprintf(_T("Full path is: %s\n"), path);
		int ret = RunCommand(argv[1], path);
		free(path);
		if (ret == -1) {
			RunCommand(_T("Usage"), _T(""));
		} else if (ret == -2) {
			puts("Command failed.");
			return -2;
		}
	} else {
		RunCommand(_T("Usage"), _T(""));
	}
    
	return 0;
}

int get_full_path(_In_ LPCTSTR lpszArgv0, _Outptr_opt_ LPTSTR *lpszResult) {
	if (wcslen(lpszArgv0) == 0)
		return -1;
	constexpr size_t len = 261 * sizeof(TCHAR);
	LPTSTR pBuf = new TCHAR[len];
	int bytes = GetModuleFileName(NULL, pBuf, len);
	if (bytes == 0) {
		return -1;
	} else {
		*lpszResult = pBuf;
	}
	return 0;
}
