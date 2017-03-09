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

#include "Audio.h"

using namespace totoro;

Audio::Audio() : mDisabled(FALSE)
{
	BASS_Init(-1, 44100, 0, Window::GetInstance()->GetHandle(), 0);
}

Audio::~Audio()
{
	BASS_Free();
}

HSTREAM Audio::StreamCreate(String fileName, DWORD flags)
{
	HSTREAM hStream = BASS_StreamCreateFile(FALSE, fileName.c_str(), 0, 0, flags);
	return hStream;
}

BOOL Audio::StreamFree(HSTREAM hStream)
{
	return BASS_StreamFree(hStream);
}

BOOL Audio::Play(HSTREAM hStream, BOOL restart)
{
	if (IsDisabled())
	{
		return TRUE;
	}

	return BASS_ChannelPlay(hStream, restart);
}

BOOL Audio::Pause(HSTREAM hStream)
{
	return BASS_ChannelPause(hStream);
}

BOOL Audio::IsDisabled() CONST
{
	return mDisabled;
}

VOID Audio::SetDisabled(BOOL disabled)
{
	mDisabled = disabled;
}
