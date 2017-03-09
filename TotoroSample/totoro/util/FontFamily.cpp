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

#include "FontFamily.h"

using namespace totoro;

CONST String FontFamily::F_1001 = TEXT("ËÎÌå");
CONST String FontFamily::F_1002 = TEXT("¿¬Ìå");
CONST String FontFamily::F_1003 = TEXT("ºÚÌå");

FontFamily::FontFamily()
{
	_Initialize();
}

FontFamily::~FontFamily()
{
	mFamilies.clear();
}

BOOL FontFamily::_Initialize()
{
	mFamilies.insert(make_pair(1001, F_1001));
	mFamilies.insert(make_pair(1002, F_1002));
	mFamilies.insert(make_pair(1003, F_1003));
	return TRUE;
}

String FontFamily::GetName(UINT id)
{
	return mFamilies[id].IsEmpty() ? F_1001 : mFamilies[id];
}
