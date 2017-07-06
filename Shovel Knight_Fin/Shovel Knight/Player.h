#pragma once
#include "obj.h"
#include "Define.h"

class CEffect;
class CPlayer :
	public CObj
{
private:

	HDC			m_Adc; //¾ËÆÄºí·»µù dc
	CEffect* m_pEffect;
	float m_Gravity;
	float m_Jump;
	float m_fTime;
	float m_fSpeed;
	bool m_bJump;
	bool m_bShow;
	bool m_bCollision;
	bool m_bCollision1;
	bool m_ladder;
	int m_iMapSize;
	int m_Weapontime;
	int m_HitTime;
	bool m_bHit;

	
	
	eDIR_TYPE		m_eDir;
private:

public:
	void SetJump(bool _bool = true) {m_bJump = _bool;}; 
	void SetTime(float _ftime = 0.0f) {m_fTime = _ftime;};	
	void Setm_MapSize(int _Mapsize){m_iMapSize = _Mapsize;};
	void SetSpeed(float _fSpeed) {m_fSpeed=_fSpeed;};
	void SetbCollision(bool _bCollision) {m_bCollision=_bCollision;};
	void SetbHit(bool _bHit = true) {m_bHit = _bHit;};
public:
	float GetSpeed(void) {return m_fSpeed;};
	bool GetbCollision(void) {return m_bCollision;};
	bool Getladder(void) {return m_ladder;};
	bool GetbHit(void) {return m_bHit;};
public:
	
	eDIR_TYPE GetDir(void) {return m_eDir; };
public:
	virtual void Initialize(void);
	virtual int	 Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);

public:
	void HitCheck(void);
	void KeyCheck(void);
	void Jump(void);
	void FrameCheck(void);
	void CreateAttackBox(void);

	//void SetBulletList(list<CObj*>* pList);
public:
	CPlayer(void);
	CPlayer(string strName, float fx, float fy, float fcx, float fcy , int Hp =0, int Mp =0, int Att =10 );
	virtual ~CPlayer(void);
};
