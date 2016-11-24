
#include "stdafx.h"
#include "Sample.h"

//
// Purpose: 
//   Logs messages to the event log
//
// Parameters:
//   szFunction - name of function
//   wEventType - type of event
//
// Return value:
//   None
//
// Remarks:
//   The service must have an entry in the Application event log.
//
//   wEventType is one of:
//     EVENTLOG_ERROR_TYPE
//     EVENTLOG_WARNING_TYPE
//     EVENTLOG_INFORMATION_TYPE
//     EVENTLOG_AUDIT_SUCCESS
//     EVENTLOG_AUDIT_FAILURE
VOID SvcReportEvent(_In_ LPCTSTR szFunction, _In_ WORD wEventType) {
	HANDLE hEventSource;
	LPCTSTR lpszStrings[2];
	TCHAR Buffer[80];

	hEventSource = RegisterEventSource(NULL, SVCNAME);

	if (NULL != hEventSource)
	{
		StringCchPrintf(Buffer, 80, TEXT("%s failed with %d"), szFunction, GetLastError());

		lpszStrings[0] = SVCNAME;
		lpszStrings[1] = Buffer;

		ReportEvent(hEventSource,        // event log handle
			wEventType, // event type
			0,                   // event category
			SVC_ERROR,           // event identifier
			NULL,                // no security identifier
			2,                   // size of lpszStrings array
			0,                   // no binary data
			lpszStrings,         // array of strings
			NULL);               // no binary data

		DeregisterEventSource(hEventSource);
	}
}
