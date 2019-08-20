/*********************************************************************
 * RPC for the Windows NT Operating System
 * 1993 by Martin F. Gergeleit
 *
 * RPC for the Windows NT Operating System COMES WITH ABSOLUTELY NO 
 * WARRANTY, NOR WILL I BE LIABLE FOR ANY DAMAGES INCURRED FROM THE 
 * USE OF. USE ENTIRELY AT YOUR OWN RISK!!!
 *********************************************************************/

#include <rpc/rpc.h>
#include <stdio.h>

extern void sun_rpc_report(const char* lpszMsg);
extern int sun_rpc_init(void);
extern int sun_rpc_exit(void);


static int s_init = 0;

int sun_rpc_init(void)
{
	if (!s_init) {
		WSADATA aWSAData;
		WORD wVersionRequested = MAKEWORD(2, 2);

		if (WSAStartup(wVersionRequested, &aWSAData)) {
			sun_rpc_report("WSAStartup failed\n");
			WSACleanup();
			return -1;
		}

		s_init = 1;
	}
	return 0;
}

int sun_rpc_exit(void)
{
	int nReturn = 0;

	if(s_init){
		nReturn = WSACleanup();
		if(!nReturn){
			s_init = 0;
		}
	}

	return nReturn;
}

void
sun_rpc_report(const char* lpszMsg)
{
    char    chMsg[256];
    HANDLE  hEventSource;
    const char*  lpszStrings[2];

    // Use event logging to log the error.
    //
    hEventSource = RegisterEventSourceA(NULL,"RPC.log");

    snprintf(chMsg,255, "sunrpc report: %d", GetLastError());
    lpszStrings[0] = chMsg;
    lpszStrings[1] = lpszMsg;

    if (hEventSource != NULL) {
        ReportEventA(hEventSource, // handle of event source
            EVENTLOG_WARNING_TYPE, // event type
            0,                    // event category
            0,                    // event ID
            NULL,                 // current user's SID
            2,                    // strings in lpszStrings
            0,                    // no bytes of raw data
            lpszStrings,          // array of error strings
            NULL);                // no raw data

        (VOID) DeregisterEventSource(hEventSource);
    }
}

