#pragma once

#include "Define.h"

class CBitBmp;

class CObj
{
public:
	virtual void Initialize(void)PURE;
	virtual int Progress(void)PURE;
	virtual void Render(HDC _hdc)PURE;
	virtual void Release(void)PURE;

protected:
	string m_strName;
	int m_Hp;
	int m_HpMax;
	int m_Mp;
	int m_MpMax;
	int m_Att;
	int m_Money;

	INFO	m_tInfo;	//이미지의 사이즈를 가져오기 위한것
	INFO	m_tBodyBox; //몸통의 실제 충돌 사이즈
	INFO	m_tAttackBox; //무기의 실제 충돌 사이즈( 발사체 X)
	
	FRAME	m_tFrame;
	DWORD	m_dwFrameTime;
	DWORD	m_dwState;

	HDC		m_HDC;
	RECT	m_Rect;                             
	RECT	m_BodyRect;
	RECT	m_AttackRect;

	
	
	bool	m_bDeadCheck;

	
public:
	static POINT m_ptScroll;
	static POINT m_ptMapSize;
public:
	static map<string, CBitBmp*>*		m_mapBmp;


public:
	static void SetBitBmp(map<string, CBitBmp*>* mapBmp)
	{
		m_mapBmp = mapBmp;
	}

public:
	void FrameMove(DWORD _dwState, int _iStart, int _iEnd, int _iIamge, DWORD _dwFrameDelayTime);
	void FrameMoveReverse(DWORD _dwState, int _iStart, int _iEnd, int _iIamge, DWORD _dwFrameDelayTime);
public:		//Set 
//기본정보 
	inline void SetPos(float _fx, float _fy)
	{
		m_tInfo.m_fX = _fx;
		m_tInfo.m_fY = _fy;
	}
	inline void SetBodyPos(float _fx, float _fy)
	{
		m_tBodyBox.m_fX = _fx;
		m_tBodyBox.m_fY = _fy;
	}

	void SetRect()
	{
			m_Rect.left		= long(m_tInfo.m_fX - m_tInfo.m_fCX / 2);
	m_Rect.top		= long(m_tInfo.m_fY - m_tInfo.m_fCY / 2);
	m_Rect.right	= long(m_tInfo.m_fX + m_tInfo.m_fCX / 2);
	m_Rect.bottom	= long(m_tInfo.m_fY + m_tInfo.m_fCY / 2);
	}

	void SetBodyRect()
	{
	m_BodyRect.left		= long(m_tBodyBox.m_fX - m_tBodyBox.m_fCX / 2);
	m_BodyRect.top		= long(m_tBodyBox.m_fY - m_tBodyBox.m_fCY / 2);
	m_BodyRect.right	= long(m_tBodyBox.m_fX + m_tBodyBox.m_fCX / 2);
	m_BodyRect.bottom	= long(m_tBodyBox.m_fY + m_tBodyBox.m_fCY / 2);
	}

	void SetDeadCheck(bool _bDead = true)
	{
		m_bDeadCheck = _bDead;
	}

	void SetBodyBox(INFO _info)
	{
		m_tBodyBox.m_fX = _info.m_fX;
		m_tBodyBox.m_fY = _info.m_fY;

		SetBodyRect();
	}
	void SetScroll(POINT _scroll) {m_ptScroll.x = _scroll.x , m_ptScroll.y = _scroll.y;}; 
	void SetMapsize(LONG _x, LONG _y) {m_ptMapSize.x = _x , m_ptMapSize.y = _y;};

	void SetDwState(DWORD _state) {m_dwState = _state;};
	void SetFrame(int _Start, int _End, int _iImage, DWORD _DealayTime);

	

//기본 스텟
	void SetHp(int _hp) { m_Hp = _hp;};
	void SetHpMax(int _hpMax) { m_HpMax = _hpMax;};
	void SetMp(int _mp) { m_Mp = _mp;};
	void SetMpMax(int _mpMax) { m_MpMax = _mpMax;};
	void SetAtt(int _Att) { m_Att = _Att;};
	void SetMoney(int _money) {m_Money = _money;};

public:	//Get
//기본 정보 
	string GetName(void)
	{
		return m_strName;
	}
	INFO* GetInfo(void)
	{
		return &m_tInfo;
	}
	INFO* GetBodyBox(void)
	{
		return &m_tBodyBox;
	}
	INFO* GetAttackBox(void)
	{
		return &m_tAttackBox;
	}
	bool GetDeadCheck(void)
	{
		return m_bDeadCheck;
	}
	FRAME GetFrame(void) {return m_tFrame;};
//기본 스텟 
	int GetHp(void)
	{
		return m_Hp;
	}
	int GetHpMax(void)
	{
		return m_HpMax;
	}
	int GetMp(void)
	{
		return m_Mp;
	}
	int GetMpMax(void)
	{
		return m_MpMax;
	}
	int GetAtt(void)
	{
		return m_Att;
	}
	POINT GetScroll(void)
	{
		return m_ptScroll;
	}
	POINT GetMapsize(void) {return m_ptMapSize;};
	int GetMoney(void) { return m_Money;};
	DWORD GetDwState(void) {return m_dwState;};


//기본정보 렉트
	RECT GetRect(void)
	{
		RECT rcObj = 
		{
			long(m_tInfo.m_fX - m_tInfo.m_fCX / 2),
			long(m_tInfo.m_fY - m_tInfo.m_fCY / 2),
			long(m_tInfo.m_fX + m_tInfo.m_fCX / 2),
			long(m_tInfo.m_fY + m_tInfo.m_fCY / 2),
		};

		return rcObj;
	}

	RECT GetBodyRect(void)
	{
		RECT rcObj = 
		{
			long(m_tBodyBox.m_fX - m_tBodyBox.m_fCX / 2),
			long(m_tBodyBox.m_fY - m_tBodyBox.m_fCY / 2),
			long(m_tBodyBox.m_fX + m_tBodyBox.m_fCX / 2),
			long(m_tBodyBox.m_fY + m_tBodyBox.m_fCY / 2),
		};

		return rcObj;
	}

	RECT GetAttackRect(void)
	{
		RECT rcObj = 
		{
			long(m_tAttackBox.m_fX - m_tAttackBox.m_fCX / 2),
			long(m_tAttackBox.m_fY - m_tAttackBox.m_fCY / 2),
			long(m_tAttackBox.m_fX + m_tAttackBox.m_fCX / 2),
			long(m_tAttackBox.m_fY + m_tAttackBox.m_fCY / 2),
		};

		return rcObj;
	}


public:
	CObj(void);
	CObj(string strName, float fx, float fy, float fcx, float fcy , int Hp =0, int Mp =0, int Att =10 );
	virtual ~CObj(void);
};
