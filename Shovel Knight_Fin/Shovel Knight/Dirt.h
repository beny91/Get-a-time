#pragma once
#include "otherobj.h"

class CEffect;
class CTreasure;
class CDirt :
	public COtherObj
{
private:
	CTreasure* m_pTreasure;
	CEffect* m_pEffect;
	eDIRT_TYPE m_eType;
	bool m_bSparkle;
public:
	void SetType(eDIRT_TYPE _type) {m_eType = _type;};
public:
	eDIRT_TYPE GetType(void) {return m_eType;};
public:
	void CreateDirt(void);
	void FrameCheck(void);
	void CreateTreasure(void);
public:
	virtual void Initialize(void);
	virtual int	 Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);
public:
	CDirt(void);
	CDirt(string strName, float fx, float fy, float fcx, float fcy , int Hp =10, int Mp =0, int Att =10 );
	virtual ~CDirt(void);
};
