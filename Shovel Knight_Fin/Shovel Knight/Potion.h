#pragma once
#include "item.h"

class CPotion :
	public CItem
{
private:
	eRECOVER_ITEM m_eType;
	bool m_bSparkle;
	bool m_bJump;
	float m_fTime;
private:
	void CreateTreasure(void);
	void Jump(void);
public:
	void SetType(eRECOVER_ITEM _eType) {m_eType = _eType;};
public:
	

public:
	virtual void Initialize(void);
	virtual int	 Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);

public:
	CPotion(void);
	CPotion(string strName, float fx, float fy, float fcx, float fcy ,int _price=0, int Hp =0, int Mp =0, int Att =10 );
	virtual ~CPotion(void);
};
