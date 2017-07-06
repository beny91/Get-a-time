#pragma once
#include "obj.h"
#include "Define.h"

class CMonster :
	public CObj
{
protected:

	float m_Jump;
	float m_fTime;
	float m_fSpeed;
	bool m_bJump;
	bool m_bShow;
	int m_iDeadTime;

	

	eDIR_TYPE		m_eDir;

public:
	
public:
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);
public:
	CMonster(void);
	CMonster(string strName, float fx, float fy, float fcx, float fcy , int Hp =0, int Mp =0, int Att =10 );
	virtual ~CMonster(void);
};
