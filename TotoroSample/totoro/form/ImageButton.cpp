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

#include "ImageButton.h"

using namespace totoro;

ImageButton::ImageButton() : mStatus(BUTTON_STATUS::BS_NORMAL), mPrevStatus(BUTTON_STATUS::BS_NORMAL), mTextureNormal(NULL), mTextureOnMouseOver(NULL), mTextureOnMouseClick(NULL), mTextureDisabled(NULL), mOnClickProc(NULL), mMessage(NULL), mPlayMouseOverAudio(FALSE)
{
	ScheduleUpdate();
	UnScheduleListener();
	AddListener();
}

ImageButton::~ImageButton()
{
}

ImageButton * ImageButton::Create(String fileName)
{
	ImageButton * result = new ImageButton;
	if (result && result->_Initialize(fileName))
	{
		return result;
	}

	DELETE_PTR(result);
	return NULL;
}

BOOL ImageButton::_Initialize(String fileName)
{
	std::map<String, String> params = Text::GetCfg(fileName);

	String sImgNormal = params[TEXT("img_normal")];
	String sImgOnMouseOver = params[TEXT("img_onmouseover")];
	String sImgOnMouseClick = params[TEXT("img_onmouseclick")];
	String sImgDisabled = params[TEXT("img_disabled")];
	String sAudioOnMouseOver = params[TEXT("audio_onmouseover")];
	String sAudioOnMouseClick = params[TEXT("audio_onmouseclick")];
	String sPosX = params[TEXT("pos_x")];
	String sPosY = params[TEXT("pos_y")];
	String sZIndex = params[TEXT("z_index")];
	String sIsDisabled = params[TEXT("is_disabled")];

	if (sImgNormal.IsEmpty())
	{
		return FALSE;
	}

	if (sImgOnMouseOver.IsEmpty())
	{
		sImgOnMouseOver = sImgNormal;
	}

	if (sImgOnMouseClick.IsEmpty())
	{
		sImgOnMouseClick = sImgOnMouseOver;
	}

	if (sImgDisabled.IsEmpty())
	{
		sImgDisabled = sImgNormal;
	}

	mTextureNormal = TextureRegistry::AddImage(sImgNormal, sImgNormal);
	if (mTextureNormal == NULL)
	{
		return FALSE;
	}

	mTextureOnMouseOver = TextureRegistry::AddImage(sImgOnMouseOver, sImgOnMouseOver);
	if (mTextureOnMouseOver == NULL)
	{
		return FALSE;
	}

	mTextureOnMouseClick = TextureRegistry::AddImage(sImgOnMouseClick, sImgOnMouseClick);
	if (mTextureOnMouseClick == NULL)
	{
		return FALSE;
	}

	mTextureDisabled = TextureRegistry::AddImage(sImgDisabled, sImgDisabled);
	if (mTextureDisabled == NULL)
	{
		return FALSE;
	}

	mSprite = Sprite::Create(mTextureNormal);
	if (mSprite == NULL)
	{
		return FALSE;
	}

	FLOAT posX = 0, posY = 0, zIndex = 0;
	BOOL isDisabled = FALSE;

	if (!sPosX.IsEmpty()) posX = sPosX.ToFloat();
	if (!sPosY.IsEmpty()) posY = sPosY.ToFloat();
	if (!sZIndex.IsEmpty()) zIndex = sZIndex.ToFloat();
	if (!sIsDisabled.IsEmpty()) isDisabled = (sIsDisabled.ToInt() == 0) ? FALSE : TRUE;

	SetName(fileName);
	SetPos(posX, posY);
	SetZIndex(zIndex);
	SetDisabled(isDisabled);

	if (!sAudioOnMouseOver.IsEmpty())
	{
		if (AudioRegistry::LoadOnce(sAudioOnMouseOver))
		{
			mAudioOnMouseOver = sAudioOnMouseOver;
		}
	}

	if (!sAudioOnMouseClick.IsEmpty())
	{
		if (AudioRegistry::LoadOnce(sAudioOnMouseClick))
		{
			mAudioOnMouseClick = sAudioOnMouseClick;
		}
	}

	return TRUE;
}

BOOL ImageButton::Update()
{
	if (IsDisabled())
	{
		if (mSprite->GetTexture() != mTextureDisabled)
		{
			mSprite->SetTexture(mTextureDisabled);
		}

		return TRUE;
	}

	mPrevStatus = mStatus;
	CONST POSITION * pos = GetWindow()->GetCursorPos();
	CONST RECT4P * box = GetBox();
	mStatus = Collider::IsCollide(pos, box) ? BUTTON_STATUS::BS_ONMOUSEOVER : BUTTON_STATUS::BS_NORMAL;

	if (GetAsyncKeyState(VK_LBUTTON) && IsOnMouseOver())
	{
		mStatus = BUTTON_STATUS::BS_ONMOUSECLICK;
	}

	if (mPrevStatus == mStatus)
	{
		return TRUE;
	}

	switch (mStatus)
	{
	case BUTTON_STATUS::BS_NORMAL:
		mSprite->SetTexture(mTextureNormal);
		break;
	case BUTTON_STATUS::BS_ONMOUSEOVER:
		mSprite->SetTexture(mTextureOnMouseOver);
		mPlayMouseOverAudio = TRUE;
		break;
	case BUTTON_STATUS::BS_ONMOUSECLICK:
		mSprite->SetTexture(mTextureOnMouseClick);
		break;
	}

	return TRUE;
}

BOOL ImageButton::SetOnClickProc(BUTTON_ON_CLICK_PROC onClickProc)
{
	mOnClickProc = onClickProc;
	return TRUE;
}

BOOL ImageButton::SetOnOverProc(BUTTON_ON_OVER_PROC onOverProc)
{
	mOnOverProc = onOverProc;
	return TRUE;
}

BOOL ImageButton::IsOnMouseOver() CONST
{
	return (mStatus == BUTTON_STATUS::BS_ONMOUSEOVER) ? TRUE : FALSE;
}

BOOL ImageButton::IsDisabled() CONST
{
	return (mStatus == BUTTON_STATUS::BS_DISABLED) ? TRUE : FALSE;
}

BOOL ImageButton::SetDisabled(BOOL isDisabled)
{
	mStatus = isDisabled ? BUTTON_STATUS::BS_DISABLED : BUTTON_STATUS::BS_NORMAL;
	return TRUE;
}

VOID * ImageButton::GetMessage() CONST
{
	return mMessage;
}

BOOL ImageButton::SetMessage(VOID * message)
{
	if (message == NULL)
	{
		return FALSE;
	}

	mMessage = message;
	return TRUE;
}

BOOL CALLBACK ImageButton::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_LBUTTONDOWN)
	{
		if (mStatus == BUTTON_STATUS::BS_ONMOUSECLICK)
		{
			if (mOnClickProc != NULL)
			{
				if (!mAudioOnMouseClick.IsEmpty()) AudioRegistry::PlayOnce(mAudioOnMouseClick, TRUE);
				mOnClickProc(mMessage);
			}

			return IsPropagationListener();
		}
	}

	if (mStatus == BUTTON_STATUS::BS_ONMOUSEOVER && mPlayMouseOverAudio)
	{
		mPlayMouseOverAudio = FALSE;
		if (!mAudioOnMouseOver.IsEmpty()) AudioRegistry::PlayOnce(mAudioOnMouseOver, TRUE);
	}

	return TRUE;
}
