#pragma once
#include "ui.h"

class CMyFont :
	public CUi
{
private:
	int m_iNum;
	int m_iPosition;
	int m_iLifePos;
	int m_iStart;
	int m_iEnd;
public:
	void SetNumber(int _iNum) { m_iNum = _iNum ; };
	void SetFrame(int _iStart , int _iEnd, int _iImage=0 , int _iFrameTime =100);
	void SetPosition(int _iPosition){m_iPosition = _iPosition;};
	void SetLifePos(int _iLifePos){m_iLifePos = _iLifePos;};
public:
	string GetName(void) {return m_strName;};

public:
	void CheckNumber(void);
public:
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);
public:
	CMyFont(void);
	CMyFont(string strName, float fx, float fy, float fcx, float fcy);
	virtual ~CMyFont(void);
};
