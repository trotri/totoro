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

#include "String.h"

using namespace totoro;

String::String() : STRING(TEXT(""))
{
}

String::String(CONST TCHAR *_Ptr) : STRING(_Ptr)
{
}

String::String(STRING _Ptr) : STRING(_Ptr)
{
}

String::~String()
{
}

BOOL String::StartWith(String _Ptr) CONST
{
	return StartWith(_Ptr, FALSE);
}

BOOL String::StartWith(String _Ptr, BOOL _IsIgnoreCase) CONST
{
	if (IsEmpty() || _Ptr.IsEmpty())
	{
		return FALSE;
	}

	String tmp(substr(0, _Ptr.size()));
	if (_IsIgnoreCase)
	{
		tmp.ToUpper();
		_Ptr.ToUpper();
	}

	return (tmp == _Ptr) ? TRUE : FALSE;
}

BOOL String::EndWith(String _Ptr) CONST
{
	return EndWith(_Ptr, FALSE);
}

BOOL String::EndWith(String _Ptr, BOOL _IsIgnoreCase) CONST
{
	if (IsEmpty() || _Ptr.IsEmpty())
	{
		return FALSE;
	}

	if (size() < _Ptr.size())
	{
		return FALSE;
	}

	String tmp(substr((size() - _Ptr.size()), npos));
	if (_IsIgnoreCase)
	{
		tmp.ToUpper();
		_Ptr.ToUpper();
	}

	return (tmp == _Ptr) ? TRUE : FALSE;
}

BOOL String::IsEmpty() CONST
{
	return empty();
}

VOID String::ToUpper()
{
	std::transform(begin(), end(), begin(), toupper);
}

VOID String::ToLower()
{
	std::transform(begin(), end(), begin(), tolower);
}

VOID String::Trim()
{
	TrimL();
	TrimR();
}

VOID String::TrimL()
{
	INT space = find_first_not_of(TEXT(' '), 0);
	if (space > 0)
	{
		erase(0, space);
	}
}

VOID String::TrimR()
{
	INT space = find_last_not_of(TEXT(' '), npos);
	erase(space + 1, npos);
}

VOID String::RemoveSpace()
{
	TCHAR space = TEXT(' ');
	INT i = find(space);
	while (i >= 0)
	{
		erase(i, 1);
		i = find(space);
	}
}

INT String::ToInt() CONST
{
#ifndef UNICODE
	return atoi(c_str());
#else
	return _wtoi(c_str());
#endif // !UNICODE
}

UINT String::ToUInt() CONST
{
	return static_cast<UINT>(ToULong());
}

LONG String::ToLong() CONST
{
#ifndef UNICODE
	return atol(c_str());
#else
	return _wtol(c_str());
#endif // !UNICODE
}

ULONG String::ToULong() CONST
{
#ifndef UNICODE
	return static_cast<ULONG>(atoll(c_str()));
#else
	return static_cast<ULONG>(_wtoll(c_str()));
#endif // !UNICODE
}

FLOAT String::ToFloat() CONST
{
	return static_cast<FLOAT>(ToDouble());
}

DOUBLE String::ToDouble() CONST
{
#ifndef UNICODE
	return atof(c_str());
#else
	return _wtof(c_str());
#endif // !UNICODE
}

String String::FromInt(INT _Num) CONST
{
	TCHAR Ptr[128];
#ifndef UNICODE
	sprintf_s(Ptr, TEXT("%d"), _Num);
#else
	swprintf_s(Ptr, TEXT("%d"), _Num);
#endif // !UNICODE

	return String(Ptr);
}
