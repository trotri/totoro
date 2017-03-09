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

#ifndef FONT_FAMILY_H_
#define FONT_FAMILY_H_

#include "..\ap\Defs.h"

namespace totoro
{
/**
 * FontFamily class file
 * ◊÷ÃÂ¿‡
 *
 * @author ÀŒª∂ <trotri@yeah.net>
 * @version $Id: FontFamily.h 1 2015-04-02 16:18:06Z huan.song $
 * @since 1.0
 */
class FontFamily : public ISingleton<FontFamily>
{
public:
	static CONST String F_1001;
	static CONST String F_1002;
	static CONST String F_1003;

private:
	std::map<UINT, String> mFamilies;

public:
	FontFamily();
	virtual ~FontFamily();

protected:
	BOOL _Initialize();

public:
	String GetName(UINT id);
};

}

#endif /* !FONT_FAMILY_H_ */
