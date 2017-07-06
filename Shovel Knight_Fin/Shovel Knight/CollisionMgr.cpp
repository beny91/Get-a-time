#include "StdAfx.h"
#include "CollisionMgr.h"
#include "TileMgr.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "Player.h"
#include "Treasure.h"
#include "DirtPile.h"
#include "Bord.h"
#include "BubbleDragon.h"
#include "Potion.h"
#include "SoundMgr.h"
#include "BlackKnight.h"
#include "Bullet.h"
CCollisionMgr* CCollisionMgr::m_pInstance = NULL;

CCollisionMgr::CCollisionMgr(void)
{
}

CCollisionMgr::~CCollisionMgr(void)
{
}

bool CCollisionMgr::CollisionSphere(CObj* pObj1, CObj* pObj2)
{
	//�������� ��.
	float fSum = pObj1->GetInfo()->m_fCX / 2 + pObj2->GetInfo()->m_fCX / 2;

	float fX = pObj1->GetInfo()->m_fX - pObj2->GetInfo()->m_fX;
	float fY = pObj1->GetInfo()->m_fY - pObj2->GetInfo()->m_fY;

	float fDist = sqrtf(fX * fX + fY * fY);	//pow()����

	if(fDist < fSum)
		return true;

	return false;
}

bool CCollisionMgr::CollisionSphere(CObj* pObj, eOBJ_TYPE eType)
{
	const INFO* pDestInfo = pObj->GetInfo();

	OBJ_ITER iter	  = CObjMgr::GetInstance()->GetList()[eType].begin();
	OBJ_ITER iter_end = CObjMgr::GetInstance()->GetList()[eType].end();

	for(iter; iter != iter_end; ++iter)
	{
		const INFO* pSourceInfo = (*iter)->GetInfo();

		float fX = pSourceInfo->m_fX - pDestInfo->m_fX;
		float fY = pSourceInfo->m_fY - pDestInfo->m_fY;

		float fDist = sqrtf(fX * fX + fY * fY);

		float fSum = pDestInfo->m_fCX / 2 + pSourceInfo->m_fCX / 2;

		if(fDist < fSum)
		{
			//CObjMgr::GetInstance()->GetList()[eType].erase(iter);
			(*iter)->SetDeadCheck();

			return true;
		}
	}

	return false;
}

/*
CObj* CCollisionMgr::GetCloseMonster(CObj* pObj)
{
CObj*		pMonster = NULL;		//���� ����� ����.

float fCloseDist = -1;

const INFO& pDestInfo = (*(pObj)->GetInfo());

OBJ_ITER iter	  = CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].begin();
OBJ_ITER iter_end = CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].end();

for(iter; iter != iter_end; ++iter)
{
const INFO& pSourceInfo = (*(*iter)->GetInfo());

float fX = pSourceInfo.m_fX - pDestInfo.m_fX;
float fY = pSourceInfo.m_fY - pDestInfo.m_fY;

float fDist = sqrtf(fX * fX + fY * fY);

if(fDist < fCloseDist || fCloseDist == -1)
{
fCloseDist = fDist;
pMonster = (*iter);
}
}

return pMonster;
}
*/

//##���� �̿���..
//CObj* CCollisionMgr::GetCloseMonster(CObj* pObj)
//{
//	CObj*		pMonster = NULL;		//���� ����� ����.
//
//	map<float, CObj*> mapObj;
//
//	const INFO& pDestInfo = (*(pObj)->GetInfo());
//
//	OBJ_ITER iter	  = CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].begin();
//	OBJ_ITER iter_end = CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].end();
//
//	for(iter; iter != iter_end; ++iter)
//	{
//		const INFO& pSourceInfo = (*(*iter)->GetInfo());
//
//		float fX = pSourceInfo.m_fX - pDestInfo.m_fX;
//		float fY = pSourceInfo.m_fY - pDestInfo.m_fY;
//
//		float fDist = sqrtf(fX * fX + fY * fY);
//
//		mapObj.insert( make_pair(fDist, (*iter) ) );
//	}
//
//	if(mapObj.empty() == true)
//		return NULL;
//
//	return mapObj.begin()->second;
//}


bool CCollisionMgr::CollisionRect(CObj* pObj, eOBJ_TYPE eType)
{
	const INFO*	 pDestInfo = pObj->GetBodyBox();

	OBJ_ITER iter	  = CObjMgr::GetInstance()->GetList()[eType].begin();
	OBJ_ITER iter_end = CObjMgr::GetInstance()->GetList()[eType].end();

	for(iter; iter != iter_end; ++iter)
	{
		if((*iter)->GetDeadCheck() == true)
			continue;

		INFO* pSourceInfo;
			pSourceInfo = (*iter)->GetBodyBox();

		//�浹 �����ϸ�ȴ�.

		float fDistX = abs(pSourceInfo->m_fX - pDestInfo->m_fX);
		float fDistY = abs(pSourceInfo->m_fY - pDestInfo->m_fY);

		if( fDistX < (pDestInfo->m_fCX / 2 + pSourceInfo->m_fCX / 2)
			&& fDistY < (pDestInfo->m_fCY / 2 + pSourceInfo->m_fCY / 2) )
		{
			

			if( eType == OBJ_OTHER)
			{
				if( typeid(*(*iter))== typeid(CDirtPile) ) //������Ʈ Ÿ���϶� DirtPile �̶�� �о�� �ʴ´�.
				{
					
					return false;
				}
			}
			//���� �浹.

			//������ ���� ���غ���.(��ġ ������ ���ؼ�)
			float fOverlabX = (pDestInfo->m_fCX / 2 + pSourceInfo->m_fCX / 2) - fDistX;
			float fOverlabY = (pDestInfo->m_fCY / 2 + pSourceInfo->m_fCY / 2) - fDistY;


			//�浹�� ��ġ.

			if(pDestInfo->m_fY < pSourceInfo->m_fY)		//���� ����, ���� ����, ���� ������
			{
				if(fOverlabX > fOverlabY)		//���ʿ��� �ε�����.
				{
					pObj->SetPos(pDestInfo->m_fX, 
						pSourceInfo->m_fY - (pSourceInfo->m_fCY/2) - (pDestInfo->m_fCY/2));
					pObj->SetBodyPos(pDestInfo->m_fX,
						pSourceInfo->m_fY - (pSourceInfo->m_fCY/2) - (pDestInfo->m_fCY/2));
					if( typeid(*(*iter)) == typeid(CBord))// �������� ���� �ִ� ���
					{
						if( ((CBord*)(*iter))->GetDir() ==DIR_RIGHT )
						{
						pObj->SetPos(pDestInfo->m_fX+2, 
						pSourceInfo->m_fY - (pSourceInfo->m_fCY/2) - (pDestInfo->m_fCY/2));
							pObj->SetBodyPos(pDestInfo->m_fX+2,
						pSourceInfo->m_fY - (pSourceInfo->m_fCY/2) - (pDestInfo->m_fCY/2));
						}
						else
						{
								pObj->SetPos(pDestInfo->m_fX-2, 
						pSourceInfo->m_fY - (pSourceInfo->m_fCY/2) - (pDestInfo->m_fCY/2));
							pObj->SetBodyPos(pDestInfo->m_fX-2,
						pSourceInfo->m_fY - (pSourceInfo->m_fCY/2) - (pDestInfo->m_fCY/2));
						}

					}

					return true;
				}
			}
			else	//���� �Ʒ���, �Ʒ� ����, �Ʒ� ������
			{
				if(fOverlabX > fOverlabY)		//���ʿ��� �ε�����.
				{
					pObj->SetPos(pDestInfo->m_fX, 
						pSourceInfo->m_fY + (pSourceInfo->m_fCY / 2) + (pDestInfo->m_fCY / 2));
					pObj->SetBodyPos(pDestInfo->m_fX, 
						pSourceInfo->m_fY + (pSourceInfo->m_fCY / 2) + (pDestInfo->m_fCY / 2));
				if( ((CPlayer*)pObj)->GetDwState() == STATE_JUMP)
				{
				((CPlayer*)pObj)->SetJump(false);
				((CPlayer*)pObj)->SetbCollision(true);
				((CPlayer*)pObj)->SetDwState(STATE_STAND);
				}

					return true;
				}

			}

			//���ʿ� �����̳� �������� ���ɼ��� �ִ�.
			if(pDestInfo->m_fX >= pSourceInfo->m_fX)  //������
			{
				pObj->SetPos(pSourceInfo->m_fX + (pSourceInfo->m_fCX/2) + (pDestInfo->m_fCX/2),
					pDestInfo->m_fY);
				pObj->SetBodyPos(pSourceInfo->m_fX + (pSourceInfo->m_fCX/2) + (pDestInfo->m_fCX/2),
					pDestInfo->m_fY);
			}
			else	//����
			{
				pObj->SetPos(pSourceInfo->m_fX- (pSourceInfo->m_fCX/2) - (pDestInfo->m_fCX/2),
					pDestInfo->m_fY);
				pObj->SetBodyPos(pSourceInfo->m_fX - (pSourceInfo->m_fCX/2) - (pDestInfo->m_fCX/2),
					pDestInfo->m_fY);
			}
			return true;
		}
	}

	return false;
}
bool CCollisionMgr::CollisionItem(CObj* pObj, eOBJ_TYPE eType)
{
	const INFO*	 pDestInfo = pObj->GetBodyBox();

	OBJ_ITER iter	  = CObjMgr::GetInstance()->GetList()[eType].begin();
	OBJ_ITER iter_end = CObjMgr::GetInstance()->GetList()[eType].end();

	for(iter; iter != iter_end; ++iter)
	{
		if((*iter)->GetDeadCheck() == true)
			continue;

		INFO* pSourceInfo;
			pSourceInfo = (*iter)->GetInfo();
	

		//�浹 �����ϸ�ȴ�.

		float fDistX = abs(pSourceInfo->m_fX - pDestInfo->m_fX);
		float fDistY = abs(pSourceInfo->m_fY - pDestInfo->m_fY);

		if( fDistX < (pDestInfo->m_fCX / 2 + pSourceInfo->m_fCX / 2)
			&& fDistY < (pDestInfo->m_fCY / 2 + pSourceInfo->m_fCY / 2) )
		{
			if( eType == OBJ_ITEM) // ������ Ÿ���̸� �Ҹ� ��Ų�� �����Ѵ�.
			{
				(*iter)->SetDeadCheck(true);
				CSoundMgr::GetInstance()->PlayMonsterSound(L"sfx_gem_01.mp3");
				pObj->SetMoney(pObj->GetMoney() + ((CTreasure*)(*iter))->GetPrice());

				if ( typeid(*(*iter)) == typeid(CPotion))
				{
					CSoundMgr::GetInstance()->PlayEffectSound(L"sfx_food.mp3");
				((CPlayer*)pObj)->SetHp( ((CPlayer*)pObj)->GetHp() +  ((CPotion*)(*iter))->GetHp());
				((CPlayer*)pObj)->SetMp( ((CPlayer*)pObj)->GetMp() +  ((CPotion*)(*iter))->GetMp());
				}
				
			}
		}
	}
	return true;
}



bool CCollisionMgr::CollisionAttack(CObj* pObj, eOBJ_TYPE eType)
{
	RECT rc;

	const INFO*	 pDestInfo = pObj->GetAttackBox();

	OBJ_ITER iter	  = CObjMgr::GetInstance()->GetList()[eType].begin();
	OBJ_ITER iter_end = CObjMgr::GetInstance()->GetList()[eType].end();

	for(iter; iter != iter_end; ++iter)
	{
		if( (*iter)->GetDeadCheck() == true)
			continue;
		const INFO* pSourceInfo = (*iter)->GetBodyBox();
		//�浹 �����ϸ�ȴ�.

		if( typeid(*(*iter)) == typeid(CBubbleDragon) )
		{
			if(IntersectRect(&rc, &pObj->GetAttackRect(), &(*iter)->GetAttackRect() ) == TRUE)
			{
				return true;
			}
		}

		float fDistX = abs(pSourceInfo->m_fX - pDestInfo->m_fX);
		float fDistY = abs(pSourceInfo->m_fY - pDestInfo->m_fY);

		if( fDistX < (pDestInfo->m_fCX / 2 + pSourceInfo->m_fCX / 2)
			&& fDistY < (pDestInfo->m_fCY / 2 + pSourceInfo->m_fCY / 2) )
		{
			//���� �浹.


			if(  typeid(*(*iter)) == typeid(CBlackKnight) 
					&& ((CBlackKnight*)(*iter))->GetbHit() == true)
					return false;
			//������ ���� ���غ���.(��ġ ������ ���ؼ�)
			if(IntersectRect(&rc, &pObj->GetAttackRect(), &(*iter)->GetBodyRect() ) == TRUE)
			{
			
				 //���ݷ� ��ŭ �Ǹ� ��´�.
				
				
					if(  typeid(*(*iter)) == typeid(CBlackKnight) 
					&& ((CBlackKnight*)(*iter))->GetbHit() == false)
				{
					CSoundMgr::GetInstance()->PlayMonsterSound(L"sfx_knight_hurt.mp3");
					((CBlackKnight*)(*iter))->SetbHit(); //������ ��Ʈ�� �ٲ㼭 �����ð����� �ǰ� ���� �ʰ� �Ѵ�.
					(*iter)->SetHp( (*iter)->GetHp() - ((CPlayer*)pObj)->GetAtt() );
					return true;
				}
					
					
						(*iter)->SetHp( (*iter)->GetHp() - ((CPlayer*)pObj)->GetAtt() );
					

				if( typeid(*(*iter))== typeid(CDirtPile) )
				{
					CSoundMgr::GetInstance()->PlayMonsterSound(L"sfx_knight_digpile.mp3");
				((CDirtPile*)(*iter))->SetHit(); //�������� ������������ ó��

				}
				return true;
			}

		}
	}

	return false;
}

bool CCollisionMgr::CollisionAttack2(CObj* pObj, eOBJ_TYPE eType)
{
	RECT rc;

	const INFO*	 pDestInfo = pObj->GetAttackBox();

	OBJ_ITER iter	  = CObjMgr::GetInstance()->GetList()[eType].begin();
	OBJ_ITER iter_end = CObjMgr::GetInstance()->GetList()[eType].end();

	for(iter; iter != iter_end; ++iter)
	{
		if( (*iter)->GetDeadCheck() == true)
			continue;
		const INFO* pSourceInfo = (*iter)->GetBodyBox();
		//�浹 �����ϸ�ȴ�.

		if( typeid(*(*iter)) == typeid(CBubbleDragon) )
		{
			if(IntersectRect(&rc, &pObj->GetAttackRect(), &(*iter)->GetAttackRect() ) == TRUE)
			{
				return true;
			}
		}

		float fDistX = abs(pSourceInfo->m_fX - pDestInfo->m_fX);
		float fDistY = abs(pSourceInfo->m_fY - pDestInfo->m_fY);

		if( fDistX < (pDestInfo->m_fCX / 2 + pSourceInfo->m_fCX / 2)
			&& fDistY < (pDestInfo->m_fCY / 2 + pSourceInfo->m_fCY / 2) )
		{
			//���� �浹.

			//������ ���� ���غ���.(��ġ ������ ���ؼ�)
			if(IntersectRect(&rc, &pObj->GetAttackRect(), &(*iter)->GetBodyRect() ) == TRUE)
			{
			
				// ���Ͱ� �÷��̾ ���������ÿ� ���ϴ� ����.
				 //���ݷ� ��ŭ �Ǹ� ��´�.

				if(  typeid(*(*iter)) == typeid(CPlayer) 
					&& ((CPlayer*)(*iter))->GetbHit() == false)
				{
					CSoundMgr::GetInstance()->PlayEffectSound(L"sfx_knight_hurt.mp3");
					((CPlayer*)(*iter))->SetbHit(); //������ ��Ʈ�� �ٲ㼭 �����ð����� �ǰ� ���� �ʰ� �Ѵ�.
					(*iter)->SetHp( (*iter)->GetHp() - ((CPlayer*)pObj)->GetAtt() );
				}
				if( typeid(*(*iter))== typeid(CDirtPile) )
				{
					CSoundMgr::GetInstance()->PlayMonsterSound(L"sfx_knight_digpile.mp3");
				((CDirtPile*)(*iter))->SetHit(); //�������� ������������ ó��

				}
				return true;
			}

		}
	}

	return false;
}
bool CCollisionMgr::CollisionBullet(CObj* pObj, eOBJ_TYPE eType)
{
	RECT rc;

	const INFO*	 pDestInfo = pObj->GetAttackBox();

	OBJ_ITER iter	  = CObjMgr::GetInstance()->GetList()[eType].begin();
	OBJ_ITER iter_end = CObjMgr::GetInstance()->GetList()[eType].end();

	for(iter; iter != iter_end; ++iter)
	{
		if( (*iter)->GetDeadCheck() == true)
			continue;
		const INFO* pSourceInfo = (*iter)->GetBodyBox();
		//�浹 �����ϸ�ȴ�.

	

		


		
			//������ ���� ���غ���.(��ġ ������ ���ؼ�)
			if(IntersectRect(&rc, &pObj->GetAttackRect(), &(*iter)->GetBodyRect() ) == TRUE)
			{
			
				 //���ݷ� ��ŭ �Ǹ� ��´�.
				
				
				if( ((CBullet*)(*iter))->GetDir() ==DIR_RIGHT )
					((CBullet*)(*iter))->SetDir(DIR_LEFT);
				else
					((CBullet*)(*iter))->SetDir(DIR_RIGHT);
					
					
					
					

				
				return true;
			}

		
	}

	return false;
}

int CCollisionMgr::CollisionRectTile1(CObj* pObj) //Ÿ�� �浹
{
	RECT rc;
	const INFO*	 pDestInfo = pObj->GetBodyBox();

	vector<TILE*>::iterator iter	  = CTileMgr::GetInstance()->GetvecTile()->begin();
	vector<TILE*>::iterator iter_end = CTileMgr::GetInstance()->GetvecTile()->end();

	int i=0;
	for(iter; iter != iter_end; ++iter)
	{
			INFO& pSourceInfo = (*iter)->GetInfo();
		if( (*iter)->m_iOption == 0 || (*iter)->m_iOption == 5 || (*iter)->m_iOption == 4) //�浹���� �ʴ� Ÿ���̶�� ���ǿ� ���� �ʿ䰡 ����.
			continue;
		
	
		//Ÿ�Ͽ� ��ȣ�� �־ ��� Ÿ���̶� �浹�ϴ����� �����Ѵ�.
	

		if( (pDestInfo->m_fX >= pSourceInfo.m_fX - pSourceInfo.m_fCX && pDestInfo->m_fX <= pSourceInfo.m_fX + pSourceInfo.m_fCX)
			&&
			(pDestInfo->m_fY +	pDestInfo->m_fCY/2 <= pSourceInfo.m_fY + pSourceInfo.m_fCY && pDestInfo->m_fY + pDestInfo->m_fCY/2 >= pSourceInfo.m_fY - pSourceInfo.m_fCY)

			||

			(pDestInfo->m_fX >= pSourceInfo.m_fX - pSourceInfo.m_fCX && pDestInfo->m_fX <= pSourceInfo.m_fX + pSourceInfo.m_fCX)
			&&
			(pDestInfo->m_fY -	pDestInfo->m_fCY/2 <= pSourceInfo.m_fY + pSourceInfo.m_fCY/2 && pDestInfo->m_fY - pDestInfo->m_fCY/2 >= pSourceInfo.m_fY - pSourceInfo.m_fCY/2)


			)
		{
			
				//�÷��̾ �������� ���� �������� ���浹�� �Ͼ��. //����ǰ�
			if( pDestInfo->m_fY   < pSourceInfo.m_fY ) //���ʿ��� �浹
			{
				
						
				pObj->SetPos(pDestInfo->m_fX, 
					pSourceInfo.m_fY - (pSourceInfo.m_fCY/2 ) - (pDestInfo->m_fCY/2)
					);
				pObj->SetBodyPos(pDestInfo->m_fX, 
					pSourceInfo.m_fY - (pSourceInfo.m_fCY/2 ) - (pDestInfo->m_fCY/2)
					);
				//���� ������� ���� ���°� �ƴҶ��� ���ĵ� ���·� �ٲ۴�.
				if( ((CPlayer*)pObj)->GetDwState() == STATE_JUMP_DOWN || ((CPlayer*)pObj)->GetDwState() == STATE_ATTACK_DOWN )
				{
				((CPlayer*)pObj)->SetJump(false);
				((CPlayer*)pObj)->SetbCollision(true);
				((CPlayer*)pObj)->SetDwState(STATE_STAND);
				}
				 if((*iter)->m_iOption == 1)
					 return 1;

					++i;
				continue ;
			}
			else if(  pDestInfo->m_fY  > pSourceInfo.m_fY )
			{
				pObj->SetPos(pDestInfo->m_fX, 
					pSourceInfo.m_fY + (pSourceInfo.m_fCY / 2) + (pDestInfo->m_fCY/2)
					);
				pObj->SetBodyPos(pDestInfo->m_fX, 
					pSourceInfo.m_fY + (pSourceInfo.m_fCY / 2) + (pDestInfo->m_fCY/2)
					);
			if( ((CPlayer*)pObj)->GetDwState() == STATE_JUMP)
				{
				((CPlayer*)pObj)->SetJump(false);
				((CPlayer*)pObj)->SetbCollision(true);
				((CPlayer*)pObj)->SetDwState(STATE_STAND);
				}
				++i;
				continue;
			}

			
		
		}
		 if(
			(pDestInfo->m_fX  >= pSourceInfo.m_fX - pSourceInfo.m_fCX && pDestInfo->m_fX  <= pSourceInfo.m_fX + pSourceInfo.m_fCX)
			&&
			(pDestInfo->m_fY <= pSourceInfo.m_fY + pSourceInfo.m_fCY && pDestInfo->m_fY  >= pSourceInfo.m_fY - pSourceInfo.m_fCY)

			/*||

			(pDestInfo->m_fX >= pSourceInfo.m_fX - pSourceInfo.m_fCX/2 && pDestInfo->m_fX <= pSourceInfo.m_fX + pSourceInfo.m_fCX/2)
			&&
			(pDestInfo->m_fY  <= pSourceInfo.m_fY + pSourceInfo.m_fCY && pDestInfo->m_fY >= pSourceInfo.m_fY - pSourceInfo.m_fCY)*/


			)
		{
			//���ʿ� �����̳� �������� ���ɼ��� �ִ�.
			if(pDestInfo->m_fX > pSourceInfo.m_fX  && ((CPlayer*)pObj)->GetDwState() !=STATE_JUMP )  //�������� �ε�����
			{
				

				pObj->SetPos(pSourceInfo.m_fX + (pSourceInfo.m_fCX/2 ) + (pDestInfo->m_fCX/2 ),
					pDestInfo->m_fY
					);
				pObj->SetBodyPos(pSourceInfo.m_fX + (pSourceInfo.m_fCX/2 ) + (pDestInfo->m_fCX/2 ),
					pDestInfo->m_fY
					);

				//�ε����� ��ũ���� �и��°� ����
				POINT temp;
				if(pObj->GetScroll().x !=0)
				{
				temp.x=pObj->GetScroll().x - ((CPlayer*)pObj)->GetSpeed();
				temp.y=pObj->GetScroll().y;
				pObj->SetScroll(temp);
					}
				return 1;

			}
			else  //���������� �ε�����
			{
				
				pObj->SetPos(pSourceInfo.m_fX - (pSourceInfo.m_fCX/2 )+10 - (pDestInfo->m_fCX/2 ),
					pDestInfo->m_fY);
				pObj->SetBodyPos(pSourceInfo.m_fX - (pSourceInfo.m_fCX/2 )+10 - (pDestInfo->m_fCX/2 ),
					pDestInfo->m_fY);
				////�ε����� ��ũ���� �и��°� ����
				POINT temp;
				if(pObj->GetScroll().x !=0)
				{
				temp.x=pObj->GetScroll().x + ((CPlayer*)pObj)->GetSpeed();
				temp.y=pObj->GetScroll().y;
				pObj->SetScroll(temp);
				}
				return 1;
			}	
		
		}
		
	
		
		
	}
	if( i>0)
		return 1;

	return false;
	
}
int CCollisionMgr::CollisionRectTile2(CObj* pObj)
{
	const INFO*	 pDestInfo = pObj->GetBodyBox();

	vector<TILE*>::iterator iter	  = CTileMgr::GetInstance()->GetvecTile()->begin();
	vector<TILE*>::iterator iter_end = CTileMgr::GetInstance()->GetvecTile()->end();

	int i=0;
	for(iter; iter != iter_end; ++iter)
	{
		if( (*iter)->m_iOption == 0 || (*iter)->m_iOption == 5 ) //�浹���� �ʴ� Ÿ���̶�� ���ǿ� ���� �ʿ䰡 ����.
			continue;
		//Ÿ�Ͽ� ��ȣ�� �־ ��� Ÿ���̶� �浹�ϴ����� �����Ѵ�.
		INFO& pSourceInfo = (*iter)->GetInfo();

		if( (pDestInfo->m_fX >= pSourceInfo.m_fX - pSourceInfo.m_fCX && pDestInfo->m_fX <= pSourceInfo.m_fX + pSourceInfo.m_fCX)
			&&
			(pDestInfo->m_fY +	pDestInfo->m_fCY/2 <= pSourceInfo.m_fY + pSourceInfo.m_fCY && pDestInfo->m_fY + pDestInfo->m_fCY/2 >= pSourceInfo.m_fY - pSourceInfo.m_fCY)

			||

			(pDestInfo->m_fX >= pSourceInfo.m_fX - pSourceInfo.m_fCX && pDestInfo->m_fX <= pSourceInfo.m_fX + pSourceInfo.m_fCX)
			&&
			(pDestInfo->m_fY -	pDestInfo->m_fCY/2 <= pSourceInfo.m_fY + pSourceInfo.m_fCY/2 && pDestInfo->m_fY - pDestInfo->m_fCY/2 >= pSourceInfo.m_fY - pSourceInfo.m_fCY/2)


			)
		{

				//�÷��̾ �������� ���� �������� ���浹�� �Ͼ��. //����ǰ�
			if( pDestInfo->m_fY   < pSourceInfo.m_fY ) //���ʿ��� �浹
			{
				
						
				pObj->SetPos(pDestInfo->m_fX, 
					pSourceInfo.m_fY - (pSourceInfo.m_fCY/2 ) - (pDestInfo->m_fCY-22)
					);
				pObj->SetBodyPos(pDestInfo->m_fX, 
					pSourceInfo.m_fY - (pSourceInfo.m_fCY/2 ) - (pDestInfo->m_fCY-22)
					);
				//���� ������� ���� ���°� �ƴҶ��� ���ĵ� ���·� �ٲ۴�.
				if( ((CPlayer*)pObj)->GetDwState() == STATE_JUMP_DOWN || ((CPlayer*)pObj)->GetDwState() == STATE_ATTACK_DOWN )
				{
				((CPlayer*)pObj)->SetJump(false);
				((CPlayer*)pObj)->SetbCollision(true);
				((CPlayer*)pObj)->SetDwState(STATE_STAND);
				}
				 if((*iter)->m_iOption == 1)
					 return 1;

					++i;
				continue ;
			}
			else if(  pDestInfo->m_fY  > pSourceInfo.m_fY )
			{
				pObj->SetPos(pDestInfo->m_fX, 
					pSourceInfo.m_fY + (pSourceInfo.m_fCY / 2) + (pDestInfo->m_fCY/2)
					);
				pObj->SetBodyPos(pDestInfo->m_fX, 
					pSourceInfo.m_fY + (pSourceInfo.m_fCY / 2) + (pDestInfo->m_fCY/2)
					);
			if( ((CPlayer*)pObj)->GetDwState() == STATE_JUMP)
				{
				((CPlayer*)pObj)->SetJump(false);
				((CPlayer*)pObj)->SetbCollision(true);
				((CPlayer*)pObj)->SetDwState(STATE_STAND);
				}
				++i;
				continue;
			}

			
		
		}
		 if(
			(pDestInfo->m_fX  >= pSourceInfo.m_fX - pSourceInfo.m_fCX/2 && pDestInfo->m_fX  <= pSourceInfo.m_fX + pSourceInfo.m_fCX/2)
			&&
			(pDestInfo->m_fY-20 <= pSourceInfo.m_fY + pSourceInfo.m_fCY && pDestInfo->m_fY  >= pSourceInfo.m_fY - pSourceInfo.m_fCY)

			/*||

			(pDestInfo->m_fX >= pSourceInfo.m_fX - pSourceInfo.m_fCX/2 && pDestInfo->m_fX <= pSourceInfo.m_fX + pSourceInfo.m_fCX/2)
			&&
			(pDestInfo->m_fY  <= pSourceInfo.m_fY + pSourceInfo.m_fCY && pDestInfo->m_fY >= pSourceInfo.m_fY - pSourceInfo.m_fCY)*/


			)
		{
			//���ʿ� �����̳� �������� ���ɼ��� �ִ�.
			if(pDestInfo->m_fX > pSourceInfo.m_fX  && ((CPlayer*)pObj)->GetDwState() !=STATE_JUMP )  //�������� �ε�����
			{
				((CPlayer*)pObj)->SetMoney(((CPlayer*)pObj)->GetMoney()+1);

				pObj->SetPos(pSourceInfo.m_fX + (pSourceInfo.m_fCX/4 ) + (pDestInfo->m_fCX/4 ),
					pDestInfo->m_fY
					);
				pObj->SetBodyPos(pSourceInfo.m_fX + (pSourceInfo.m_fCX/4 ) + (pDestInfo->m_fCX/4 ),
					pDestInfo->m_fY
					);

				//�ε����� ��ũ���� �и��°� ����
				POINT temp;
				temp.x=pObj->GetScroll().x - ((CPlayer*)pObj)->GetSpeed();
				temp.y=pObj->GetScroll().y;
				pObj->SetScroll(temp);
				return 2;

			}
			else  //���������� �ε�����
			{
				((CPlayer*)pObj)->SetMoney(((CPlayer*)pObj)->GetMoney()+1);
				pObj->SetPos(pSourceInfo.m_fX - (pSourceInfo.m_fCX/4 ) - (pDestInfo->m_fCX/4 ),
					pDestInfo->m_fY);
				pObj->SetBodyPos(pSourceInfo.m_fX - (pSourceInfo.m_fCX/4 ) - (pDestInfo->m_fCX/4 ),
					pDestInfo->m_fY);
				////�ε����� ��ũ���� �и��°� ����
				POINT temp;
				temp.x=pObj->GetScroll().x + ((CPlayer*)pObj)->GetSpeed();
				temp.y=pObj->GetScroll().y;
				pObj->SetScroll(temp);

				return 2;
			}	
		
		}
		
	
		
		
	}
	if( i>0)
		return 1;

	return false;
}

int CCollisionMgr::CollisionRectTile3(CObj* pObj)
{
	RECT rc;
	const INFO*	 pDestInfo = pObj->GetBodyBox();

	vector<TILE*>::iterator iter	  = CTileMgr::GetInstance()->GetvecTile()->begin();
	vector<TILE*>::iterator iter_end = CTileMgr::GetInstance()->GetvecTile()->end();

	int i=0;
	for(iter; iter != iter_end; ++iter)
	{
			INFO& pSourceInfo = (*iter)->GetInfo();
		if( (*iter)->m_iOption == 0 || (*iter)->m_iOption == 5) //�浹���� �ʴ� Ÿ���̶�� ���ǿ� ���� �ʿ䰡 ����.
			continue;
		
		if( IntersectRect(&rc , &pObj->GetBodyRect(), &(*iter)->GetRect()))
		{
			
			if( (*iter)->m_iOption ==4 )
			{
			//	if( pSourceInfo.m_fY > pDestInfo->m_fY)
			//{
			//	if ( ((CPlayer*)pObj)->Getladder() ==false)
			//	{
			//		/*pObj->SetPos(pDestInfo->m_fX, 
			//		pSourceInfo.m_fY - (pSourceInfo.m_fCY/2 ) - (pDestInfo->m_fCY/2)
			//		);
			//	pObj->SetBodyPos(pDestInfo->m_fX, 
			//		pSourceInfo.m_fY - (pSourceInfo.m_fCY/2 ) - (pDestInfo->m_fCY/2)
			//		);*/
			//	}
			//	return 3;
			//}
				if ( ((CPlayer*)pObj)->GetDwState() ==STATE_LADDER)
				{
				pObj->SetPos(pSourceInfo.m_fX, 
					pDestInfo->m_fY
					);
				pObj->SetBodyPos(pSourceInfo.m_fX, 
					pDestInfo->m_fY
					);
				}
				return 1;
			}
		}
	}
}