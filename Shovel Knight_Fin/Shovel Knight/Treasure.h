#pragma once
#include "item.h"

class CTreasure :
	public CItem
{
private:
	eTREASURES m_eType;
	bool m_bSparkle;
	bool m_bJump;
	float m_fTime;
	eDIR_TYPE m_eDir;
private:
	void CreateTreasure(void);
	void MoveCheck(void);
	void Jump(void);
public:
	void SetType(eTREASURES _eType) {m_eType = _eType;};
	void SetDir(eDIR_TYPE _dir) {m_eDir = _dir;};
public:
	int GetPrice(void) {return m_iPrice;};

public:
	virtual void Initialize(void);
	virtual int	 Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);
public:
	CTreasure(void);
	CTreasure(string strName, float fx, float fy, float fcx, float fcy ,int _price=0, int Hp =0, int Mp =0, int Att =10 );
	virtual ~CTreasure(void);
};
