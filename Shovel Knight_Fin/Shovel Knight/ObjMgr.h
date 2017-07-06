#pragma once

#include "Define.h"

class CObj;

class CObjMgr
{
CREATE_SINGLTONE(CObjMgr)

private:
	list<CObj*>  m_listObj[OBJ_END];

public:
	void AddObject(CObj* pObj, eOBJ_TYPE eType);

	list<CObj*>*	GetList(void);
public:
	void CreateObj(void);
	void SaveObj(void);
	void LoadObj(void);
public:
	void Initialize(void);
	int  Progress(void);
	void Render(HDC _hdc);
	void Release(void);

private:
	CObjMgr(void);
public:
	~CObjMgr(void);
};
