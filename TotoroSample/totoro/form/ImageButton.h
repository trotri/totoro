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

#ifndef IMAGE_BUTTON_H_
#define IMAGE_BUTTON_H_

#include "..\service\Basic.h"
#include "..\audio\AudioRegistry.h"
#include "..\util\Collider.h"

namespace totoro
{
typedef LRESULT(CALLBACK* BUTTON_ON_CLICK_PROC)(VOID * message);
typedef LRESULT(CALLBACK* BUTTON_ON_OVER_PROC)(VOID * message);

/**
 * ImageButton class file
 * Õº∆¨∞¥≈•¿‡
 *
 * @author ÀŒª∂ <trotri@yeah.net>
 * @version $Id: ImageButton.h 1 2015-04-06 19:22:06Z huan.song $
 * @since 1.0
 */
class ImageButton : public Basic
{
private:
	BUTTON_STATUS mStatus;
	BUTTON_STATUS mPrevStatus;
	Texture * mTextureNormal;
	Texture * mTextureOnMouseOver;
	Texture * mTextureOnMouseClick;
	Texture * mTextureDisabled;
	String mAudioOnMouseOver;
	String mAudioOnMouseClick;
	BOOL mPlayMouseOverAudio;
	BUTTON_ON_CLICK_PROC mOnClickProc;
	BUTTON_ON_OVER_PROC mOnOverProc;
	VOID * mMessage;

protected:
	ImageButton();

public:
	~ImageButton();

public:
	static ImageButton * Create(String fileName);

public:
	BOOL _Initialize(String fileName);

public:
	BOOL Update();
	BOOL SetOnClickProc(BUTTON_ON_CLICK_PROC onClickProc);
	BOOL SetOnOverProc(BUTTON_ON_OVER_PROC onOverProc);
	BOOL IsOnMouseOver() CONST;
	BOOL IsDisabled() CONST;
	BOOL SetDisabled(BOOL isDisabled);
	VOID * GetMessage() CONST;
	BOOL SetMessage(VOID * message);
	BOOL CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

}

#endif /* !IMAGE_BUTTON_H_ */
