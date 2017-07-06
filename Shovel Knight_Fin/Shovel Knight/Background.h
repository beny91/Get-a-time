#pragma once
#include "obj.h"
#include "Define.h"

class CBackground :
	public CObj
{
private:
	int m_ScrollSpeed;
public:
	void SetScrollSpeed(int _speed) {m_ScrollSpeed = _speed;};
public:
	void SetFrame(int _iFrameStart , int _iFrameEnd	, int m_iImage, DWORD _dwFrameTime	);
public:
	virtual void Initialize(void);
	virtual int	 Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Render2(HDC _hdc);
	virtual void Release(void);

public:
	CBackground(void);
	CBackground(string strName, float fx, float fy, float fcx, float fcy);
	~CBackground(void);
};
