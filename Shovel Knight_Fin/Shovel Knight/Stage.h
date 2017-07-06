#pragma once
#include "scene.h"

class CUi;
class CObj;

class CStage :
	public CScene
{
private:
	CUi* m_pUi;
	bool m_bShowRect;
	bool m_bCreate;
	CObj* m_pBack;
	CObj* m_pBack1;
	CObj* m_pBack2;
	CObj* m_pBack3;
	CObj* m_pBack4;

	CObj* m_pBack5;
	CObj* m_pBack6;
	CObj* m_pBack7;
	CObj* m_pBack8;
	CObj* m_pBack9;
public:
	void CreateObjectCheck(void);
public:
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);
public:
	void KeyCheck(void);
public:
	void Scrolling(void);
public:
	CStage(void);
	virtual ~CStage(void);
};
