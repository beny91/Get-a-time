#pragma once
#include "obj.h"

class CBullet :
	public CObj
{
private:
	float m_Jump;
	float m_fTime;
	float m_fSpeed;
	bool m_bJump;
	bool m_bShow;
	int m_iDeadTime;
	eDIR_TYPE		m_eDir;

public:
	void SetDir(eDIR_TYPE _dir) {m_eDir = _dir;};
	eDIR_TYPE GetDir(void) {return m_eDir;};
	void FrameCheck(void);
private:
	void KeyCheck(void);
public:
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);
public:
	CBullet(void);
	CBullet(string strName, float fx, float fy, float fcx, float fcy , int Hp =0, int Mp =0, int Att =20 );
	~CBullet(void);
};
