#pragma once
#include "otherobj.h"

class CEffect;
class CTreasure;
class CPotion;
class CDirtPile :
	public COtherObj
{
	
private:
	CTreasure* m_pTreasure;
	CPotion* m_pPotion;
	CEffect* m_pEffect;
	eDIRT_TYPE m_eType;
	bool m_hit;
	bool m_bSparkle;

public:
	void SetType(eDIRT_TYPE _type) {m_eType = _type;};
	void SetHit(bool _hit = true) { m_hit = _hit; }; 
public:
	eDIRT_TYPE GetType(void) {return m_eType;};
public:
	
	void FrameCheck(void);
	void CreateTreasure(void);
public:
	virtual void Initialize(void);
	virtual int	 Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);
public:
	CDirtPile(void);
	CDirtPile(string strName, float fx, float fy, float fcx, float fcy , int Hp =10, int Mp =0, int Att =10 );
	virtual ~CDirtPile(void);
};
