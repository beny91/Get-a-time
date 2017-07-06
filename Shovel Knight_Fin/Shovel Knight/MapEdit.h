
#pragma once
#include "scene.h"

class CMapEdit :
	public CScene
{
private:
	int					m_iDrawID;
	int					m_iImage;
	int					m_iOption;
	int					m_iStage;
	int					m_iType;
	eSTAGE_TYPE			m_eStage;
	string				m_strStageName;
	POINT				m_ptScroll;


public:
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);
public:
	void CheckStage(eSTAGE_TYPE _eStage);

public:
	CMapEdit(void);
	virtual ~CMapEdit(void);
};
