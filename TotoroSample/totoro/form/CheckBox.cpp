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

#include "CheckBox.h"

using namespace totoro;

CheckBox::CheckBox() : mTextureNormal(NULL), mTextureNormalChecked(NULL), mTextureDisabled(NULL), mTextureDisabledChecked(NULL), mOnClickProc(NULL), mIsDisabled(FALSE), mIsChecked(FALSE)
{
	ScheduleUpdate();
	UnScheduleListener();
	AddListener();
}

CheckBox::~CheckBox()
{
}

CheckBox * CheckBox::Create(String fileName)
{
	CheckBox * result = new CheckBox;
	if (result && result->_Initialize(fileName))
	{
		return result;
	}

	DELETE_PTR(result);
	return NULL;
}

BOOL CheckBox::_Initialize(String fileName)
{
	std::map<String, String> params = Text::GetCfg(fileName);

	String sImgNormal = params[TEXT("img_normal")], sImgNormalChecked = params[TEXT("img_normal_checked")];
	String sImgDisabled = params[TEXT("img_disabled")], sImgDisabledChecked = params[TEXT("img_disabled_checked")];
	String sPosX = params[TEXT("pos_x")], sPosY = params[TEXT("pos_y")];
	String sIsDisabled = params[TEXT("is_disabled")], sIsChecked = params[TEXT("is_checked")];

	if (sImgNormal.IsEmpty())
	{
		return FALSE;
	}

	if (sImgNormalChecked.IsEmpty())
	{
		return FALSE;
	}

	if (sImgDisabled.IsEmpty())
	{
		sImgDisabled = sImgNormal;
	}

	if (sImgDisabledChecked.IsEmpty())
	{
		sImgDisabledChecked = sImgNormalChecked;
	}

	mTextureNormal = TextureRegistry::AddImage(sImgNormal, sImgNormal);
	if (mTextureNormal == NULL)
	{
		return FALSE;
	}

	mTextureNormalChecked = TextureRegistry::AddImage(sImgNormalChecked, sImgNormalChecked);
	if (mTextureNormalChecked == NULL)
	{
		return FALSE;
	}

	mTextureDisabled = TextureRegistry::AddImage(sImgDisabled, sImgDisabled);
	if (mTextureDisabled == NULL)
	{
		return FALSE;
	}

	mTextureDisabledChecked = TextureRegistry::AddImage(sImgDisabledChecked, sImgDisabledChecked);
	if (mTextureDisabledChecked == NULL)
	{
		return FALSE;
	}

	mSprite = Sprite::Create(mTextureNormal);
	if (mSprite == NULL)
	{
		return FALSE;
	}

	FLOAT posX = 0, posY = 0;
	BOOL isDisabled = FALSE, isChecked = FALSE;

	if (!sPosX.IsEmpty())       posX = sPosX.ToFloat();
	if (!sPosY.IsEmpty())       posY = sPosY.ToFloat();
	if (!sIsDisabled.IsEmpty()) isDisabled = (sIsDisabled.ToInt() == 0) ? FALSE : TRUE;
	if (!sIsChecked.IsEmpty())  isChecked = (sIsChecked.ToInt() == 0) ? FALSE : TRUE;

	SetName(fileName);
	SetPos(posX, posY);
	SetDisabled(isDisabled);
	SetChecked(isChecked);

	return TRUE;
}

BOOL CheckBox::Update()
{
	if (IsDisabled())
	{
		if (IsChecked())
		{
			mSprite->SetTexture(mTextureDisabledChecked);
		}
		else
		{
			mSprite->SetTexture(mTextureDisabled);
		}
	}
	else
	{
		if (IsChecked())
		{
			mSprite->SetTexture(mTextureNormalChecked);
		}
		else
		{
			mSprite->SetTexture(mTextureNormal);
		}
	}

	return TRUE;
}

BOOL CheckBox::SetOnClickProc(CHECKBOX_CLICK_PROC onClickProc)
{
	mOnClickProc = onClickProc;
	return TRUE;
}

BOOL CheckBox::IsDisabled() CONST
{
	return mIsDisabled;
}

BOOL CheckBox::SetDisabled(BOOL isDisabled)
{
	mIsDisabled = isDisabled;
	return TRUE;
}

BOOL CheckBox::IsChecked() CONST
{
	return mIsChecked;
}

BOOL CheckBox::SetChecked(BOOL isChecked)
{
	mIsChecked = isChecked;
	return TRUE;
}

VOID * CheckBox::GetMessage() CONST
{
	return mMessage;
}

BOOL CheckBox::SetMessage(VOID * message)
{
	if (message == NULL)
	{
		return FALSE;
	}

	mMessage = message;
	return TRUE;
}

BOOL CALLBACK CheckBox::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (IsDisabled())
	{
		return TRUE;
	}

	if (message == WM_LBUTTONDOWN)
	{
		CONST POSITION * pos = GetWindow()->GetCursorPos();
		CONST RECT4P * box = GetBox();
		if (Collider::IsCollide(pos, box))
		{
			mIsChecked = !mIsChecked;
			if (mOnClickProc != NULL) mOnClickProc(mMessage);
			return IsPropagationListener();
		}
	}

	return TRUE;
}
