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

#include "AudioRegistry.h"

using namespace totoro;

CONST TCHAR * AudioRegistry::TAG = TEXT("AudioRegistry");
std::map<String, HSTREAM> AudioRegistry::sLoops;
std::map<String, HSTREAM> AudioRegistry::sOnces;

AudioRegistry::AudioRegistry()
{
}

AudioRegistry::~AudioRegistry()
{
}

BOOL AudioRegistry::PlayLoop(String fileName)
{
	return PlayLoop(fileName, FALSE);
}

BOOL AudioRegistry::PlayLoop(String fileName, BOOL restart)
{
	return Process(fileName, TRUE, FALSE, restart);
}

BOOL AudioRegistry::PlayOnce(String fileName)
{
	return PlayOnce(fileName, FALSE);
}

BOOL AudioRegistry::PlayOnce(String fileName, BOOL restart)
{
	return Process(fileName, FALSE, FALSE, restart);
}

BOOL AudioRegistry::PauseLoop(String fileName)
{
	return Process(fileName, TRUE, TRUE, FALSE);
}

BOOL AudioRegistry::PauseOnce(String fileName)
{
	return Process(fileName, FALSE, TRUE, FALSE);
}

BOOL AudioRegistry::Process(String fileName, BOOL isLoop, BOOL isPause, BOOL restart)
{
	std::map<String, HSTREAM>::iterator begin = isLoop ? sLoops.begin() : sOnces.begin();
	std::map<String, HSTREAM>::iterator end = isLoop ? sLoops.end() : sOnces.end();

	HSTREAM hStream = NULL;
	for (std::map<String, HSTREAM>::iterator it = begin; it != end; it++)
	{
		if (fileName == it->first)
		{
			hStream = it->second;
			break;
		}
	}

	if (hStream == NULL)
	{
		return FALSE;
	}

	isPause ? Audio::GetInstance()->Pause(hStream) : Audio::GetInstance()->Play(hStream, restart);
	return TRUE;
}

BOOL AudioRegistry::LoadLoop(String fileName)
{
	return LoadAudio(fileName, TRUE);
}

BOOL AudioRegistry::LoadOnce(String fileName)
{
	return LoadAudio(fileName, FALSE);
}

BOOL AudioRegistry::LoadAudio(String fileName, BOOL isLoop)
{
	if (isLoop)
	{
		if (sLoops[fileName] != NULL)
		{
			return TRUE;
		}
	}
	else
	{
		if (sOnces[fileName] != NULL)
		{
			return TRUE;
		}
	}

	DWORD flags = BASS_SAMPLE_MONO;
	if (isLoop)
	{
		flags |= BASS_SAMPLE_LOOP;
	}

	HSTREAM hStream = Audio::GetInstance()->StreamCreate(fileName, flags);
	if (hStream)
	{
		if (isLoop)
		{
			sLoops[fileName] = hStream;
		}
		else
		{
			sOnces[fileName] = hStream;
		}

		Log::d(TAG, TEXT("LoadAudio '%s' Create Stream Success!\n"), fileName.c_str());
		return TRUE;
	}

	Log::d(TAG, TEXT("LoadAudio '%s' Create Stream Failure!\n"), fileName.c_str());
	return FALSE;
}

VOID AudioRegistry::ClearLoop()
{
	HSTREAM tmp = NULL;
	Audio * obj = Audio::GetInstance();

	for (std::map<String, HSTREAM>::iterator it = sLoops.begin(); it != sLoops.end(); it++)
	{
		tmp = it->second;
		obj->StreamFree(tmp);
	}

	sLoops.clear();
}

VOID AudioRegistry::ClearOnce()
{
	HSTREAM tmp = NULL;
	Audio * obj = Audio::GetInstance();

	for (std::map<String, HSTREAM>::iterator it = sOnces.begin(); it != sOnces.end(); it++)
	{
		tmp = it->second;
		obj->StreamFree(tmp);
	}

	sOnces.clear();
}

VOID AudioRegistry::ClearAll()
{
	ClearLoop();
	ClearOnce();
	Audio * obj = Audio::GetInstance();
	DELETE_PTR(obj);
}

BOOL AudioRegistry::IsDisabled()
{
	return Audio::GetInstance()->IsDisabled();
}

VOID AudioRegistry::SetDisabled(BOOL disabled)
{
	Audio::GetInstance()->SetDisabled(disabled);
}
