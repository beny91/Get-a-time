#include "StdAfx.h"
#include "ObjMgr.h"
#include "Player.h"
#include "Dirt.h"
#include "DirtPile.h"

INIT_SINGLTONE(CObjMgr)

CObjMgr::CObjMgr(void)
{
}

CObjMgr::~CObjMgr(void)
{
	Release();
}

void CObjMgr::Initialize(void)
{
	m_listObj[OBJ_PLAYER].push_back(new CPlayer);
}

int CObjMgr::Progress(void)
{
	for(size_t i = 0; i < OBJ_END; ++i)
	{
		list<CObj*>::iterator iter = m_listObj[i].begin();
		list<CObj*>::iterator iter_end = m_listObj[i].end();

		for(iter; iter != iter_end; )
		{
			if((*iter)->Progress() == 1)
			{
				delete (*iter);
				iter = m_listObj[i].erase(iter);
			}
			else
				++iter;
		}
	}

	return 0;
}

void CObjMgr::Render(HDC _hdc)
{
	for(size_t i = 0; i < OBJ_END; ++i)
	{
		list<CObj*>::iterator iter = m_listObj[i].begin();
		list<CObj*>::iterator iter_end = m_listObj[i].end();

		for(iter; iter != iter_end; ++iter)
		{
			(*iter)->Render(_hdc);
		}
	}
}

void CObjMgr::Release(void)
{
	for(size_t i = 0; i < OBJ_END; ++i)
	{
		list<CObj*>::iterator iter = m_listObj[i].begin();
		list<CObj*>::iterator iter_end = m_listObj[i].end();

		for(iter; iter != iter_end; ++iter)
		{
			delete *iter ;
		}
	}

}

list<CObj*>* CObjMgr::GetList(void)
{
	return m_listObj;
}

void CObjMgr::AddObject(CObj* pObj, eOBJ_TYPE eType)
{
	m_listObj[eType].push_back(pObj);
}
void CObjMgr::CreateObj(void)
{

}
void CObjMgr::SaveObj(void)
{
	FILE* pFile = NULL;

	fopen_s(&pFile, "../Data/ObjFIle1.dat", "wb");
	int iSize =m_listObj[OBJ_OTHER].size();

	fwrite(&iSize, sizeof(int), 1, pFile);

	list<CObj*>::iterator iter = m_listObj[OBJ_OTHER].begin();
	list<CObj*>::iterator iter_end = m_listObj[OBJ_OTHER].end();
	for(iter ; iter != iter_end ; ++iter)
	{
		OBJINFO temp;
		temp.m_strName=((CDirt*)(*iter))->GetName();
		memcpy(&temp.m_tInfo,(((CDirt*)(*iter))->GetInfo()),sizeof(INFO));
		temp.m_eType = ((CDirt*)(*iter))->GetType();
		fwrite(&temp, sizeof(OBJINFO), 1, pFile);
	}
	fclose(pFile);
}
void CObjMgr::LoadObj(void)
{
	FILE* pFile = NULL;

	fopen_s(&pFile, "../Data/ObjFIle1.dat", "rb");

	int iSize =m_listObj[OBJ_OTHER].size();

	fread(&iSize, sizeof(int), 1, pFile);

	list<CObj*>::iterator iter = m_listObj[OBJ_OTHER].begin();
	list<CObj*>::iterator iter_end = m_listObj[OBJ_OTHER].end();

	for(iter ; iter != iter_end ; ++iter)
	{
		delete *iter;
		*iter= NULL;
	}
	m_listObj[OBJ_OTHER].clear();

	iter = m_listObj[OBJ_OTHER].begin();
	iter_end = m_listObj[OBJ_OTHER].end();
	

	for(int i=0 ; i < iSize ; ++i)
	{
		OBJINFO* pInfo = new OBJINFO;

		fread(pInfo, sizeof(OBJINFO), 1, pFile);
		
		CObj* pObj=NULL;
		if( pInfo->m_eType == DIRT_SMALL)
		{
			pObj = new CDirt(pInfo->m_strName, pInfo->m_tInfo.m_fX, pInfo->m_tInfo.m_fY, pInfo->m_tInfo.m_fCX , pInfo->m_tInfo.m_fCY);
			((CDirt*)pObj)->SetType(pInfo->m_eType);
			pObj->Initialize();
			m_listObj[OBJ_OTHER].push_back(pObj);
		}
		else if( pInfo->m_eType == DIRT_BIG)
		{
			pObj = new CDirt(pInfo->m_strName, pInfo->m_tInfo.m_fX, pInfo->m_tInfo.m_fY, pInfo->m_tInfo.m_fCX , pInfo->m_tInfo.m_fCY);
			((CDirt*)pObj)->SetType(pInfo->m_eType);
			pObj->Initialize();
			m_listObj[OBJ_OTHER].push_back(pObj);
		}
		else
		{
			pObj = new CDirtPile(pInfo->m_strName, pInfo->m_tInfo.m_fX, pInfo->m_tInfo.m_fY, pInfo->m_tInfo.m_fCX , pInfo->m_tInfo.m_fCY);
			pObj->Initialize();
			m_listObj[OBJ_OTHER].push_back(pObj);
		}
		
	}


	fclose(pFile);
}