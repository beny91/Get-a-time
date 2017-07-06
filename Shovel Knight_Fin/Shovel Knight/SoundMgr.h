#pragma once

class CSoundMgr
{
private:
	static CSoundMgr* m_pInstance;

public:
	static CSoundMgr* GetInstance()
	{
		if(m_pInstance == NULL)
		{
			m_pInstance = new CSoundMgr;
		}
		return m_pInstance;
	}

	void Destroy()
	{
		if(m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = NULL;
		}
	}

//사운드 관리자의 기능.
//fmod에 대한 인터페이스

private:
	FMOD_SYSTEM*	m_pSystem;		//fmod 시스템 포인터.
	FMOD_CHANNEL*	m_pEffect;		//이펙트 채널.
	FMOD_CHANNEL*	m_pBGM;			//BGM    채널.
	FMOD_CHANNEL*	m_pSkill;		//스킬   채널.
	FMOD_CHANNEL*	m_pMonster;		//몬스터 채널.

	FMOD_RESULT		m_Result;		//에러 체크를 하기 위한 변수.

	unsigned int m_iVersion;		//시스템의 버전정보.

private:		//사운드 관리.
	map<TCHAR*, FMOD_SOUND*>		m_mapSound;

public:
	void Initialize(void);
	void LoadSoundFile(void);
	void PlayEffectSound(TCHAR* SoundKey);
	void PlayBGMSound(TCHAR* SoundKey);
	void PlayMonsterSound(TCHAR* SoundKey);
	void PlaySkillSound(TCHAR* SoundKey);
	void StopBGM(void);
	void StopAll(void);

public:
	map<TCHAR*, FMOD_SOUND*>* GetSoundMap(void)
	{
		return &m_mapSound;
	}

private:
	void ErrorCheck(FMOD_RESULT _result);

private:
	CSoundMgr(void);
public:
	~CSoundMgr(void);
};
