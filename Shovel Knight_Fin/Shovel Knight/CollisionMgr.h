#pragma once

#include "Define.h"

class CObj;

class CCollisionMgr
{
private:
	static CCollisionMgr* m_pInstance;

public:
	static CCollisionMgr* GetInstance(void)
	{
		if(m_pInstance == NULL)
		{
			m_pInstance = new CCollisionMgr;
		}
		return m_pInstance;
	}

	void DestroyInstance(void)
	{
		SAFE_DELETE(m_pInstance);
	}

public:
	bool CollisionSphere(CObj* pObj1, CObj* pObj2);
	bool CollisionSphere(CObj* pObj, eOBJ_TYPE eType);
	bool CollisionRect(CObj* pObj, eOBJ_TYPE eType);
	bool CollisionItem(CObj* pObj, eOBJ_TYPE eType);
	//bool CollisionRect(CObj* pObj, eOBJ_TYPE eType);
	bool CollisionAttack(CObj* pObj, eOBJ_TYPE eType);
	bool CollisionAttack2(CObj* pObj, eOBJ_TYPE eType);
	bool CollisionBullet(CObj* pObj, eOBJ_TYPE eType);
	int CollisionRectTile1(CObj* pObj);//�÷��̾�� Ÿ��
	int CollisionRectTile2(CObj* pObj);//�����۰� Ÿ��
	int CollisionRectTile3(CObj* pObj);//�÷��̾�� ��ٸ�
	
	CObj*	GetCloseMonster(CObj* pObj);

private:
	CCollisionMgr(void);
public:
	~CCollisionMgr(void);
};
