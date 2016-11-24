#pragma once

#include "targetver.h"

#include <Windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <cstdio>

#define SVCNAME TEXT("TWTLService")

int RunCommand(_In_ LPCTSTR szCommand, _In_ LPCTSTR lpszPath); // RunCommand.cpp
VOID SvcReportEvent(_In_ LPCTSTR szFunction, _In_ WORD wEventType); // SvcReportEvent.cpp
VOID WINAPI SvcMain(_In_ DWORD dwArgc, _In_ LPCTSTR *lpszArgv); // SvcMain.cpp
