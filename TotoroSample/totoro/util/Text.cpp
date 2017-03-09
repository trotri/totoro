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

#include "Text.h"

using namespace totoro;
using namespace std;

CONST TCHAR * Text::TAG = TEXT("Text");
CONST TCHAR * Text::DEFAULT_TAG_NAME = TEXT("unknown");
CONST String Text::TAG_BEGIN = TEXT("Tag"); // Àý Tag Image¡¢TagImage¡¢Tag Font¡¢TagFont
CONST String Text::TAG_END = TEXT("EndTag"); // EndTag »ò End Tag

Text::Text()
{
}

Text::~Text()
{
}

map<String, vector<map<String, String>>> Text::GetCfgs(String fileName)
{
	map<String, vector<map<String, String>>> data;

	list<String> rawlines;
	if (!GetStrings(fileName, &rawlines))
	{
		return data;
	}

	String line, tagName, key, value;
	INT i;
	map<String, String> row;
	map<String, vector<map<String, String>>>::iterator tmp;
	for (list<String>::iterator it = rawlines.begin(); it != rawlines.end(); it++)
	{
		line = (*it);
		line.Trim();

		if (line.IsEmpty())
		{
			continue;
		}
		
		if (line.find_first_of(TEXT('#')) == 0)
		{
			continue;
		}

		if (IsEndTag(line))
		{
			if (tagName.IsEmpty())
			{
				continue;
			}

			vector<map<String, String>> rows;

			tmp = data.find(tagName);
			if (tmp != data.end())
			{
				rows = data[tagName];
				data.erase(tmp);
			}

			rows.push_back(row);
			data.insert(make_pair(tagName, rows));

			tagName = TEXT("");
			row.clear();

			continue;
		}

		if (IsBeginTag(line, tagName))
		{
			row.clear();
			continue;
		}

		i = line.find_first_of(TEXT("="));
		if (i == String::npos)
		{
			continue;
		}

		key = line.substr(0, i);
		key.RemoveSpace();
		key.ToLower();

		value = line.substr(i + 1, String::npos);
		value.TrimL();

		row.insert(make_pair(key, value));
	}

	return data;
}

BOOL Text::IsBeginTag(String line, String &tagName)
{
	if (line.find_first_of(TEXT("=")) != String::npos)
	{
		return FALSE;
	}

	line.RemoveSpace();
	if (line.StartWith(TAG_BEGIN, TRUE))
	{
		tagName = line.substr(TAG_BEGIN.size(), String::npos);
		if (tagName.IsEmpty())
		{
			tagName = DEFAULT_TAG_NAME;
		}
		
		tagName.ToLower();
		return TRUE;
	}

	return FALSE;
}

BOOL Text::IsEndTag(String line)
{
	if (line.find_first_of(TEXT("=")) != String::npos)
	{
		return FALSE;
	}

	line.RemoveSpace();
	return (line.StartWith(TAG_END, TRUE)) ? TRUE : FALSE;
}

map<String, String> Text::GetCfg(String fileName)
{
	map<String, String> data;

	list<String> rawlines;
	if (!GetStrings(fileName, &rawlines))
	{
		return data;
	}

	String line, key, value;
	INT i;
	for (list<String>::iterator it = rawlines.begin(); it != rawlines.end(); it++)
	{
		line = (*it);
		line.Trim();

		if (line.IsEmpty())
		{
			continue;
		}

		if (line.find_first_of(TEXT('#')) == 0)
		{
			continue;
		}

		i = line.find_first_of(TEXT("="));
		if (i == String::npos)
		{
			continue;
		}

		key = line.substr(0, i);
		key.RemoveSpace();
		key.ToLower();

		value = line.substr(i + 1, String::npos);
		value.TrimL();

		data.insert(make_pair(key, value));
	}

	return data;
}

BOOL Text::GetStrings(String fileName, list<String> * data)
{
	if (data == NULL)
	{
		Log::e(TAG, TEXT("GetStrings Failure, Data Is NULL!\n"));
		return FALSE;
	}

#ifdef UNICODE
	std::wifstream in(fileName.c_str());
#else
	std::ifstream in(fileName.c_str());
#endif // !UNICODE

	if (!in)
	{
		Log::e(TAG, TEXT("GetStrings Failure, File '%s' Not Exists Or UnReadable !\n"), fileName.c_str());
		return FALSE;
	}

	String line;
	while (getline(in, line))
	{
		data->push_back(line);
	}

	in.close();
	return TRUE;
}
