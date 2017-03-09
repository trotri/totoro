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

#ifndef STRING_H_
#define STRING_H_

#include <string>
#include <algorithm>
#include "Macros.h"

typedef std::wstring WSTRING;
typedef std::string  ASTRING;

#ifdef UNICODE
typedef WSTRING STRING;
#else
typedef ASTRING STRING;
#endif // !UNICODE

namespace totoro
{
/**
 * String class file
 * ×Ö·û´®Àà
 *
 * @author ËÎ»¶ <trotri@yeah.net>
 * @version $Id: String.h 1 2015-01-29 10:02:06Z huan.song $
 * @since 1.0
 */
class String : public STRING
{
public:
	CONST TCHAR * TAG = TEXT("String");

public:
	String();
	String(CONST TCHAR *_Ptr);
	String(STRING _Ptr);
	virtual ~String();

public:
	BOOL StartWith(String _Ptr) CONST;
	BOOL StartWith(String _Ptr, BOOL _IsIgnoreCase) CONST;
	BOOL EndWith(String _Ptr) CONST;
	BOOL EndWith(String _Ptr, BOOL _IsIgnoreCase) CONST;
	BOOL IsEmpty() CONST;
	VOID ToUpper();
	VOID ToLower();
	VOID Trim();
	VOID TrimL();
	VOID TrimR();
	VOID RemoveSpace();
	INT ToInt() CONST;
	UINT ToUInt() CONST;
	LONG ToLong() CONST;
	ULONG ToULong() CONST;
	FLOAT ToFloat() CONST;
	DOUBLE ToDouble() CONST;
	String FromInt(INT _Num) CONST;
};

}

#endif /* !STRING_H_ */
