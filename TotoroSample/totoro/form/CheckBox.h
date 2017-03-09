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

#ifndef CHECK_BOX_H_
#define CHECK_BOX_H_

#include "..\service\Basic.h"
#include "..\util\Collider.h"

namespace totoro
{
typedef LRESULT(CALLBACK* CHECKBOX_CLICK_PROC)(VOID * message);

/**
 * CheckBox class file
 * ∏¥—°øÚ¿‡
 *
 * @author ÀŒª∂ <trotri@yeah.net>
 * @version $Id: CheckBox.h 1 2015-04-06 19:22:06Z huan.song $
 * @since 1.0
 */
class CheckBox : public Basic
{
private:
	Texture * mTextureNormal;
	Texture * mTextureNormalChecked;
	Texture * mTextureDisabled;
	Texture * mTextureDisabledChecked;
	CHECKBOX_CLICK_PROC mOnClickProc;
	BOOL mIsDisabled;
	BOOL mIsChecked;
	VOID * mMessage;

protected:
	CheckBox();

public:
	~CheckBox();

public:
	static CheckBox * Create(String fileName);

public:
	BOOL _Initialize(String fileName);

public:
	BOOL Update();
	BOOL SetOnClickProc(CHECKBOX_CLICK_PROC onClickProc);
	BOOL IsDisabled() CONST;
	BOOL SetDisabled(BOOL isDisabled);
	BOOL IsChecked() CONST;
	BOOL SetChecked(BOOL isChecked);
	VOID * GetMessage() CONST;
	BOOL SetMessage(VOID * message);
	BOOL CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

}

#endif /* !CHECK_BOX_H_ */
