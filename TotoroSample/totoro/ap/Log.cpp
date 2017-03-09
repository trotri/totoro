/*
 * Copyright (C) 2015 The C++ Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Log.h"

using namespace totoro;

CONST UINT Log::VERBOSE = 2;
CONST UINT Log::DBUG    = 3;
CONST UINT Log::INFO    = 4;
CONST UINT Log::WARN    = 5;
CONST UINT Log::ERR     = 6;
CONST UINT Log::ASSERT  = 7;

UINT Log::sLogId = 0;
UINT Log::sProcessId = 0;
TCHAR Log::sDirectory[MAX_DIRECTORY];

Log::Log()
{
}

Log::~Log()
{
}

UINT Log::v(CONST TCHAR * tag, CONST TCHAR * msg, ...)
{
	UINT priority = VERBOSE;
	LOG_DECLARE_WRITE
}

UINT Log::d(CONST TCHAR * tag, CONST TCHAR * msg, ...)
{
	UINT priority = DBUG;
	LOG_DECLARE_WRITE
}

UINT Log::i(CONST TCHAR * tag, CONST TCHAR * msg, ...)
{
	UINT priority = INFO;
	LOG_DECLARE_WRITE
}

UINT Log::w(CONST TCHAR * tag, CONST TCHAR * msg, ...)
{
	UINT priority = WARN;
	LOG_DECLARE_WRITE
}

UINT Log::e(CONST TCHAR * tag, CONST TCHAR * msg, ...)
{
	UINT priority = ERR;
	LOG_DECLARE_WRITE
}

UINT Log::GetLogId()
{
	return sLogId;
}

UINT Log::GetProcessId()
{
	return sProcessId;
}

VOID Log::Initialize()
{
	sLogId = 0;
	sProcessId = _getpid();

	memset(sDirectory, 0, sizeof(sDirectory));

#ifdef UNICODE
	wcscpy_s(sDirectory, DIR_LOG);
#else
	strcpy_s(sDirectory, sizeof(sDirectory), DIR_LOG);
#endif // !UNICODE

#ifdef UNICODE
	wcscat_s(sDirectory, TEXT("\\"));
#else
	strcat_s(sDirectory, TEXT("\\"));
#endif // !UNICODE
}

UINT Log::Write(UINT priority, CONST TCHAR * tag, CONST TCHAR * msg)
{
	static BOOL isInitialized = FALSE;

	if (!isInitialized)
	{
		isInitialized = TRUE;
		Initialize();
	}

	TCHAR timestr[48], fileName[48], prioritystr[32];
	time_t tt = time(NULL);
	struct tm nowtime;
	localtime_s(&nowtime, &tt);

#ifdef UNICODE
	swprintf_s(fileName, TEXT("%04d%02d%02d%02d"), nowtime.tm_year + 1900, nowtime.tm_mon + 1, nowtime.tm_mday, nowtime.tm_hour);
#else
	sprintf_s(fileName, TEXT("%04d%02d%02d%02d"), nowtime.tm_year + 1900, nowtime.tm_mon + 1, nowtime.tm_mday, nowtime.tm_hour);
#endif // !UNICODE

#ifdef UNICODE
	wcscat_s(fileName, TEXT(".log"));
#else
	strcat_s(fileName, TEXT(".log"));
#endif // !UNICODE

	switch (priority)
	{
	case ERR:
#ifdef UNICODE
		wcscat_s(fileName, TEXT(".err"));
		wcscpy_s(prioritystr, TEXT("ERR"));
#else
		strcat_s(fileName, TEXT(".err"));
		strcpy_s(prioritystr, TEXT("ERR"));
#endif // !UNICODE
		break;
	case WARN:
#ifdef UNICODE
		wcscat_s(fileName, TEXT(".wf"));
		wcscpy_s(prioritystr, TEXT("WARN"));
#else
		strcat_s(fileName, TEXT(".wf"));
		strcpy_s(prioritystr, TEXT("WARN"));
#endif // !UNICODE
		break;
	case INFO:
#ifdef UNICODE
		wcscpy_s(prioritystr, TEXT("INFO"));
#else
		strcpy_s(prioritystr, TEXT("INFO"));
#endif // !UNICODE
		break;
	case DBUG:
#ifdef UNICODE
		wcscpy_s(prioritystr, TEXT("DEBUG"));
#else
		strcpy_s(prioritystr, TEXT("DEBUG"));
#endif // !UNICODE
		break;
	case VERBOSE:
	default:
#ifdef UNICODE
		wcscpy_s(prioritystr, TEXT("VERBOSE"));
#else
		strcpy_s(prioritystr, TEXT("VERBOSE"));
#endif // !UNICODE
		break;
	}

	TCHAR filePath[MAX_PATH];
#ifdef UNICODE
	wcscpy_s(filePath, sDirectory);
	wcscat_s(filePath, fileName);
#else
	strcpy_s(filePath, sDirectory);
	strcat_s(filePath, fileName);
#endif // !UNICODE

#ifdef UNICODE
	swprintf_s(timestr, TEXT("%04d-%02d-%02d %02d:%02d:%02d"), nowtime.tm_year + 1900, nowtime.tm_mon + 1, nowtime.tm_mday, nowtime.tm_hour, nowtime.tm_min, nowtime.tm_sec);
#else
	sprintf_s(timestr, TEXT("%04d-%02d-%02d %02d:%02d:%02d"), nowtime.tm_year + 1900, nowtime.tm_mon + 1, nowtime.tm_mday, nowtime.tm_hour, nowtime.tm_min, nowtime.tm_sec);
#endif // !UNICODE

	FILE * fp;
	errno_t errNo;
	INT result;

#ifdef UNICODE
	errNo = _wfopen_s(&fp, filePath, TEXT("a"));
#else
	errNo = fopen_s(&fp, filePath, TEXT("a"));
#endif // !UNICODE

	if (errNo != 0)
	{
		return 0;
	}

#ifdef UNICODE
	result = fwprintf(fp, TEXT("%s %d-%d %s/%s %s"), timestr, GetProcessId(), ++sLogId, prioritystr, tag, msg);
#else
	result = fprintf(fp, TEXT("%s %d-%d %s/%s %s"), timestr, GetProcessId(), ++sLogId, prioritystr, tag, msg);
#endif // !UNICODE

	fflush(fp);
	fclose(fp);

	return (result > 0) ? result : 0;
}
