#include "StdAfx.h"
#include "SoundMgr.h"
#include "Func.h"

CSoundMgr* CSoundMgr::m_pInstance = NULL;

CSoundMgr::CSoundMgr(void)
{
	m_pSystem = NULL;
	m_iVersion = 0;

	Initialize();
}

CSoundMgr::~CSoundMgr(void)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter = m_mapSound.begin();
	map<TCHAR*, FMOD_SOUND*>::iterator iter_end = m_mapSound.end();

	for(iter; iter != iter_end;/* ++iter*/)
	{
		m_Result = FMOD_Sound_Release(iter->second);

		ErrorCheck(m_Result);

		delete [] (iter->first);

		iter = m_mapSound.erase(iter);
		iter_end = m_mapSound.end();

		if(iter == iter_end)
			break;
	}

	m_Result = FMOD_System_Close(m_pSystem);
	ErrorCheck(m_Result);

	m_Result = FMOD_System_Release(m_pSystem);
	ErrorCheck(m_Result);
}

void CSoundMgr::Initialize(void)
{
	m_Result = FMOD_System_Create(&m_pSystem);
	ErrorCheck(m_Result);

	m_Result = FMOD_System_GetVersion(m_pSystem, &m_iVersion);
	ErrorCheck(m_Result);

	m_Result = FMOD_System_Init(m_pSystem, 32, FMOD_INIT_NORMAL, NULL);
	ErrorCheck(m_Result);
}


void CSoundMgr::LoadSoundFile(void)
{
	_finddata_t fd;

	long handle = 0;
	int iResult = 1;

	handle = _findfirst("../SoundFile/*.*", &fd);		//해당 경로에 있는 파일을 모두 읽어온다.

	if(handle == -1)
		return;

	while(iResult != -1)		//폴더전체 검색이 끝나면 -1을 리턴한다.
	{
		TCHAR szName[256] = {0};		//해당경로에서 얻은 파일명.

		ZeroMemory(szName, sizeof(szName));

		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, 
							fd.name, strlen(fd.name), szName, 256);
		//멀티바이트 유니코드로 변경시켜주는 함수.

		TCHAR* pName = new TCHAR[256];
		ZeroMemory(pName, sizeof(TCHAR) * 256);

		lstrcpy(pName, szName);			//pName : 파일명(유니코드).

		char szFullPath[256];
		ZeroMemory(szFullPath, sizeof(szFullPath));

		strcpy_s(szFullPath, "../SoundFile/");	
		strcat_s(szFullPath, fd.name);			//"../SoundFile/Boom4.ogg"

		FMOD_SOUND* pSound;

		m_Result = FMOD_System_CreateSound(m_pSystem, szFullPath,
							FMOD_HARDWARE, 0, &pSound);

		if(m_Result == FMOD_OK)
		{
			m_mapSound.insert( make_pair(pName, pSound) );
		}
		else
		{
			delete [] pName;
			pName = NULL;
		}

		iResult = _findnext(handle, &fd);
	}

	_findclose(handle);

	m_Result = FMOD_System_Update(m_pSystem);

	ErrorCheck(m_Result);
}

void CSoundMgr::PlayEffectSound(TCHAR* SoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCMP(SoundKey) );

	if(iter == m_mapSound.end() )
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
									iter->second, 0, &m_pEffect);

	ErrorCheck(m_Result);
}

void CSoundMgr::PlayBGMSound(TCHAR* SoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCMP(SoundKey) );

	if(iter == m_mapSound.end() )
		return;

	FMOD_Sound_SetMode(iter->second, FMOD_LOOP_NORMAL);

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pBGM);

	ErrorCheck(m_Result);
}

void CSoundMgr::PlayMonsterSound(TCHAR* SoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCMP(SoundKey) );

	if(iter == m_mapSound.end() )
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pMonster);

	ErrorCheck(m_Result);
}

void CSoundMgr::PlaySkillSound(TCHAR* SoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCMP(SoundKey) );

	if(iter == m_mapSound.end() )
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pSkill);

	ErrorCheck(m_Result);
}

void CSoundMgr::StopBGM(void)
{
	m_Result = FMOD_Channel_Stop(m_pBGM);
	ErrorCheck(m_Result);
}

void CSoundMgr::StopAll(void)
{
	m_Result = FMOD_Channel_Stop(m_pBGM);
	ErrorCheck(m_Result);

	m_Result = FMOD_Channel_Stop(m_pEffect);
	ErrorCheck(m_Result);
}

void CSoundMgr::ErrorCheck(FMOD_RESULT _result)
{
	if(_result != FMOD_OK)
	{
		cout << "오류 발생!" << endl;
		return;
	}
}


