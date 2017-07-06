#pragma once

#include "Define.h"

class CScene;

class CSceneMgr
{
CREATE_SINGLTONE(CSceneMgr)

private:
	CScene*		m_pScene;

	eSCENE_TYPE m_eType;
	bool		m_bChangeScene;

public:
	void Initialize(void);
	int  Progress(void);
	void Render(HDC _hdc);
	void Release(void);

public:
	void SetScene(eSCENE_TYPE eType);
	void SetChangeScene(eSCENE_TYPE eType);

private:
	CSceneMgr(void);
public:
	~CSceneMgr(void);
};
