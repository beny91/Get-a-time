#pragma once
#include "obj.h"

class CEffect :
	public CObj
{
private:
	int m_DeadTime;
	int m_itype;
	bool m_bJump;
	eEFFECT_TYPE m_eType;
	eDIR_TYPE m_eDir;
	float m_fTime;
public:
	void MoveCheck(void);
	void Jump(void);
	void FrameCheck(void);
public:
	void SetType(eEFFECT_TYPE _type) {m_eType = _type;};
	void SetDir(eDIR_TYPE _type) {m_eDir = _type;};
	void SetDeadTime(int _time) {m_DeadTime = _time;};
	void SetiType(int _itype) {m_itype = _itype;};
public:
	eEFFECT_TYPE GetType(void) {return m_eType;};
	eDIR_TYPE GetDir(void) {return m_eDir;};
public:
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);
public:
	CEffect(void);
	CEffect(string strName, float fx, float fy, float fcx, float fcy , int Hp =0, int Mp =0, int Att =10 );
	~CEffect(void);
};
