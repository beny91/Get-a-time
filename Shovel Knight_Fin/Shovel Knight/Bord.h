#pragma once
#include "otherobj.h"

class CBord :
	public COtherObj
{
private:
	bool m_hit;
	bool m_bSparkle;
	int m_min;
	int m_max;
	eDIR_TYPE m_eDir;
public:
	
	void FrameCheck(void);
	void Move(void);
public:
	eDIR_TYPE GetDir(void) {return m_eDir;};
public:
	virtual void Initialize(void);
	virtual int	 Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);
public:
	CBord(void);
	CBord(string strName, float fx, float fy, float fcx, float fcy , int Hp =10, int Mp =0, int Att =10 );
	virtual ~CBord(void);
};
