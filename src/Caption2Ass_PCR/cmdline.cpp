
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <strsafe.h>



VOID _tMyPrintf(IN	LPCTSTR tracemsg, ...);
enum {
	FORMAT_SRT = 1,
// mark10als
//	FORMAT_ASS = 2
	FORMAT_ASS = 2,
	FORMAT_TAW = 3,
	FORMAT_DUAL = 4
// mark10als
};

extern DWORD format;
extern TCHAR *pFileName;
extern TCHAR *pTargetFileName;
extern USHORT PMTPid;
// mark10als
extern long delayTime;
extern BOOL bLogMode;
extern TCHAR *passType;
// mark10als

BOOL ParseCmd(int argc, char **argv)
{
	if (argc < 2) {
ERROR_PARAM:
		_tMyPrintf(_T("Caption2Ass.exe [OPTIONS] source.ts [target filename]\r\n\r\n"));
		_tMyPrintf(_T("-PMT_PID PID  PID is HEX value. Ex: -PMT_PID 1f2\r\n"));
		_tMyPrintf(_T("-format {srt|ass|taw|dual}. Ex: -format srt\r\n"));
		_tMyPrintf(_T("-delay TIME   TIME is mili-sec. Ex: -delay 500\r\n"));
		_tMyPrintf(_T("-asstype TYPE . Ex: -asstype Default\r\n"));
		_tMyPrintf(_T("-log. make log-file\r\n"));

		return FALSE;
	}
	_tcscpy(passType, _T("Default"));
	bLogMode = FALSE;
	for (int i = 1; i< argc; i++) {
		if (_tcsicmp(argv[i], _T("-PMT_PID")) == 0) {
			i++;
			if (i > argc)
				goto ERROR_PARAM;

			if (_stscanf_s(argv[i], _T("%x"), &PMTPid) <= 0)
				goto ERROR_PARAM;

			continue;
		}
		else if (_tcsicmp(argv[i], _T("-format")) == 0) {
			i++;
			if (i > argc)
				goto ERROR_PARAM;

			if (_tcsicmp(argv[i], _T("srt")) == 0) {
				format = FORMAT_SRT;
			}
			else if (_tcsicmp(argv[i], _T("ass")) == 0) {
				format = FORMAT_ASS;
			}
// mark10als
			else if (_tcsicmp(argv[i], _T("taw")) == 0) {
				format = FORMAT_TAW;
			}
			else if (_tcsicmp(argv[i], _T("dual")) == 0) {
				format = FORMAT_DUAL;
			}
// mark10als
			else
				goto ERROR_PARAM;

			continue;
		}
// mark10als
		else if (_tcsicmp(argv[i], _T("-i")) == 0) {
			i++;
			if (i > argc)
				goto ERROR_PARAM;

			pFileName = argv[i];
			continue;
		}
		else if (_tcsicmp(argv[i], _T("-o")) == 0) {
			i++;
			if (i > argc)
				goto ERROR_PARAM;

			pTargetFileName = argv[i];
			continue;
		}
		else if (_tcsicmp(argv[i], _T("-delay")) == 0) {
			i++;
			if (i > argc)
				goto ERROR_PARAM;

			if (_stscanf_s(argv[i], _T("%d"), &delayTime) <= 0)
				goto ERROR_PARAM;

			continue;
		}
		else if (_tcsicmp(argv[i], _T("-asstype")) == 0) {
			i++;
			if (i > argc)
				goto ERROR_PARAM;

			passType = argv[i];
			continue;
		}
		else if (_tcsicmp(argv[i], _T("-log")) == 0) {
			bLogMode = TRUE;
			continue;
		}
// mark10als

		if (!pFileName) {
			pFileName = argv[i];
			continue;
		}

		if (!pTargetFileName) {
			pTargetFileName = argv[i];
			continue;
		}
	}
	return TRUE;
}


VOID _tMyPrintf(
	IN	LPCTSTR tracemsg,
	...
	)
{
// mark10als
//	TCHAR buf[1024] = {0};
	TCHAR buf[MAX_PATH + 2048] = {0};
// mark10als
	HRESULT ret;

	__try {
		va_list ptr;
		va_start(ptr,tracemsg);

		ret = StringCchVPrintf(
			buf,
			MAX_PATH + 2048,
			tracemsg,
			ptr
			);

		if (ret == S_OK) {
			DWORD ws;
			WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), buf, _tcsclen(buf), &ws, NULL);

		}
	}
	__finally {
	}

	return;
}
