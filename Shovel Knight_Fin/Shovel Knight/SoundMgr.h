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

//���� �������� ���.
//fmod�� ���� �������̽�

private:
	FMOD_SYSTEM*	m_pSystem;		//fmod �ý��� ������.
	FMOD_CHANNEL*	m_pEffect;		//����Ʈ ä��.
	FMOD_CHANNEL*	m_pBGM;			//BGM    ä��.
	FMOD_CHANNEL*	m_pSkill;		//��ų   ä��.
	FMOD_CHANNEL*	m_pMonster;		//���� ä��.

	FMOD_RESULT		m_Result;		//���� üũ�� �ϱ� ���� ����.

	unsigned int m_iVersion;		//�ý����� ��������.

private:		//���� ����.
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
