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
	//반지름의 합.
	float fSum = pObj1->GetInfo()->m_fCX / 2 + pObj2->GetInfo()->m_fCX / 2;

	float fX = pObj1->GetInfo()->m_fX - pObj2->GetInfo()->m_fX;
	float fY = pObj1->GetInfo()->m_fY - pObj2->GetInfo()->m_fY;

	float fDist = sqrtf(fX * fX + fY * fY);	//pow()제곱

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
CObj*		pMonster = NULL;		//가장 가까운 몬스터.

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

//##맵을 이용한..
//CObj* CCollisionMgr::GetCloseMonster(CObj* pObj)
//{
//	CObj*		pMonster = NULL;		//가장 가까운 몬스터.
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

		//충돌 구현하면된다.

		float fDistX = abs(pSourceInfo->m_fX - pDestInfo->m_fX);
		float fDistY = abs(pSourceInfo->m_fY - pDestInfo->m_fY);

		if( fDistX < (pDestInfo->m_fCX / 2 + pSourceInfo->m_fCX / 2)
			&& fDistY < (pDestInfo->m_fCY / 2 + pSourceInfo->m_fCY / 2) )
		{
			

			if( eType == OBJ_OTHER)
			{
				if( typeid(*(*iter))== typeid(CDirtPile) ) //오브젝트 타입일때 DirtPile 이라면 밀어내지 않는다.
				{
					
					return false;
				}
			}
			//실제 충돌.

			//겹쳐진 값을 구해보자.(위치 보정을 위해서)
			float fOverlabX = (pDestInfo->m_fCX / 2 + pSourceInfo->m_fCX / 2) - fDistX;
			float fOverlabY = (pDestInfo->m_fCY / 2 + pSourceInfo->m_fCY / 2) - fDistY;


			//충돌된 위치.

			if(pDestInfo->m_fY < pSourceInfo->m_fY)		//내가 위쪽, 위쪽 왼쪽, 위쪽 오른쪽
			{
				if(fOverlabX > fOverlabY)		//위쪽에서 부딪혔다.
				{
					pObj->SetPos(pDestInfo->m_fX, 
						pSourceInfo->m_fY - (pSourceInfo->m_fCY/2) - (pDestInfo->m_fCY/2));
					pObj->SetBodyPos(pDestInfo->m_fX,
						pSourceInfo->m_fY - (pSourceInfo->m_fCY/2) - (pDestInfo->m_fCY/2));
					if( typeid(*(*iter)) == typeid(CBord))// 무빙보드 위에 있는 경우
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
			else	//내가 아래쪽, 아래 왼쪽, 아래 오른쪽
			{
				if(fOverlabX > fOverlabY)		//위쪽에서 부딪혔다.
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

			//위쪽에 왼쪽이나 오른쪽일 가능성이 있다.
			if(pDestInfo->m_fX >= pSourceInfo->m_fX)  //오른쪽
			{
				pObj->SetPos(pSourceInfo->m_fX + (pSourceInfo->m_fCX/2) + (pDestInfo->m_fCX/2),
					pDestInfo->m_fY);
				pObj->SetBodyPos(pSourceInfo->m_fX + (pSourceInfo->m_fCX/2) + (pDestInfo->m_fCX/2),
					pDestInfo->m_fY);
			}
			else	//왼쪽
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
	

		//충돌 구현하면된다.

		float fDistX = abs(pSourceInfo->m_fX - pDestInfo->m_fX);
		float fDistY = abs(pSourceInfo->m_fY - pDestInfo->m_fY);

		if( fDistX < (pDestInfo->m_fCX / 2 + pSourceInfo->m_fCX / 2)
			&& fDistY < (pDestInfo->m_fCY / 2 + pSourceInfo->m_fCY / 2) )
		{
			if( eType == OBJ_ITEM) // 아이템 타입이면 소멸 시킨후 리턴한다.
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
		//충돌 구현하면된다.

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
			//실제 충돌.


			if(  typeid(*(*iter)) == typeid(CBlackKnight) 
					&& ((CBlackKnight*)(*iter))->GetbHit() == true)
					return false;
			//겹쳐진 값을 구해보자.(위치 보정을 위해서)
			if(IntersectRect(&rc, &pObj->GetAttackRect(), &(*iter)->GetBodyRect() ) == TRUE)
			{
			
				 //공격력 만큼 피를 깎는다.
				
				
					if(  typeid(*(*iter)) == typeid(CBlackKnight) 
					&& ((CBlackKnight*)(*iter))->GetbHit() == false)
				{
					CSoundMgr::GetInstance()->PlayMonsterSound(L"sfx_knight_hurt.mp3");
					((CBlackKnight*)(*iter))->SetbHit(); //때리면 히트로 바꿔서 일정시간동안 피가 달지 않게 한다.
					(*iter)->SetHp( (*iter)->GetHp() - ((CPlayer*)pObj)->GetAtt() );
					return true;
				}
					
					
						(*iter)->SetHp( (*iter)->GetHp() - ((CPlayer*)pObj)->GetAtt() );
					

				if( typeid(*(*iter))== typeid(CDirtPile) )
				{
					CSoundMgr::GetInstance()->PlayMonsterSound(L"sfx_knight_digpile.mp3");
				((CDirtPile*)(*iter))->SetHit(); //아이템을 내보내기위한 처리

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
		//충돌 구현하면된다.

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
			//실제 충돌.

			//겹쳐진 값을 구해보자.(위치 보정을 위해서)
			if(IntersectRect(&rc, &pObj->GetAttackRect(), &(*iter)->GetBodyRect() ) == TRUE)
			{
			
				// 몬스터가 플레이어를 공격했을시에 변하는 값들.
				 //공격력 만큼 피를 깎는다.

				if(  typeid(*(*iter)) == typeid(CPlayer) 
					&& ((CPlayer*)(*iter))->GetbHit() == false)
				{
					CSoundMgr::GetInstance()->PlayEffectSound(L"sfx_knight_hurt.mp3");
					((CPlayer*)(*iter))->SetbHit(); //때리면 히트로 바꿔서 일정시간동안 피가 달지 않게 한다.
					(*iter)->SetHp( (*iter)->GetHp() - ((CPlayer*)pObj)->GetAtt() );
				}
				if( typeid(*(*iter))== typeid(CDirtPile) )
				{
					CSoundMgr::GetInstance()->PlayMonsterSound(L"sfx_knight_digpile.mp3");
				((CDirtPile*)(*iter))->SetHit(); //아이템을 내보내기위한 처리

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
		//충돌 구현하면된다.

	

		


		
			//겹쳐진 값을 구해보자.(위치 보정을 위해서)
			if(IntersectRect(&rc, &pObj->GetAttackRect(), &(*iter)->GetBodyRect() ) == TRUE)
			{
			
				 //공격력 만큼 피를 깎는다.
				
				
				if( ((CBullet*)(*iter))->GetDir() ==DIR_RIGHT )
					((CBullet*)(*iter))->SetDir(DIR_LEFT);
				else
					((CBullet*)(*iter))->SetDir(DIR_RIGHT);
					
					
					
					

				
				return true;
			}

		
	}

	return false;
}

int CCollisionMgr::CollisionRectTile1(CObj* pObj) //타일 충돌
{
	RECT rc;
	const INFO*	 pDestInfo = pObj->GetBodyBox();

	vector<TILE*>::iterator iter	  = CTileMgr::GetInstance()->GetvecTile()->begin();
	vector<TILE*>::iterator iter_end = CTileMgr::GetInstance()->GetvecTile()->end();

	int i=0;
	for(iter; iter != iter_end; ++iter)
	{
			INFO& pSourceInfo = (*iter)->GetInfo();
		if( (*iter)->m_iOption == 0 || (*iter)->m_iOption == 5 || (*iter)->m_iOption == 4) //충돌하지 않는 타일이라면 조건에 들어올 필요가 없다.
			continue;
		
	
		//타일에 번호를 주어서 어느 타일이랑 충돌하는지를 봐야한다.
	

		if( (pDestInfo->m_fX >= pSourceInfo.m_fX - pSourceInfo.m_fCX && pDestInfo->m_fX <= pSourceInfo.m_fX + pSourceInfo.m_fCX)
			&&
			(pDestInfo->m_fY +	pDestInfo->m_fCY/2 <= pSourceInfo.m_fY + pSourceInfo.m_fCY && pDestInfo->m_fY + pDestInfo->m_fCY/2 >= pSourceInfo.m_fY - pSourceInfo.m_fCY)

			||

			(pDestInfo->m_fX >= pSourceInfo.m_fX - pSourceInfo.m_fCX && pDestInfo->m_fX <= pSourceInfo.m_fX + pSourceInfo.m_fCX)
			&&
			(pDestInfo->m_fY -	pDestInfo->m_fCY/2 <= pSourceInfo.m_fY + pSourceInfo.m_fCY/2 && pDestInfo->m_fY - pDestInfo->m_fCY/2 >= pSourceInfo.m_fY - pSourceInfo.m_fCY/2)


			)
		{
			
				//플레이어가 떨어지는 상태 값에서만 윗충돌이 일어난다. //재우의견
			if( pDestInfo->m_fY   < pSourceInfo.m_fY ) //위쪽에서 충돌
			{
				
						
				pObj->SetPos(pDestInfo->m_fX, 
					pSourceInfo.m_fY - (pSourceInfo.m_fCY/2 ) - (pDestInfo->m_fCY/2)
					);
				pObj->SetBodyPos(pDestInfo->m_fX, 
					pSourceInfo.m_fY - (pSourceInfo.m_fCY/2 ) - (pDestInfo->m_fCY/2)
					);
				//땅에 닿았을때 점프 상태가 아닐때만 스탠드 상태로 바꾼다.
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
			//위쪽에 왼쪽이나 오른쪽일 가능성이 있다.
			if(pDestInfo->m_fX > pSourceInfo.m_fX  && ((CPlayer*)pObj)->GetDwState() !=STATE_JUMP )  //왼쪽으로 부딪힐때
			{
				

				pObj->SetPos(pSourceInfo.m_fX + (pSourceInfo.m_fCX/2 ) + (pDestInfo->m_fCX/2 ),
					pDestInfo->m_fY
					);
				pObj->SetBodyPos(pSourceInfo.m_fX + (pSourceInfo.m_fCX/2 ) + (pDestInfo->m_fCX/2 ),
					pDestInfo->m_fY
					);

				//부딪힐때 스크롤이 밀리는걸 방지
				POINT temp;
				if(pObj->GetScroll().x !=0)
				{
				temp.x=pObj->GetScroll().x - ((CPlayer*)pObj)->GetSpeed();
				temp.y=pObj->GetScroll().y;
				pObj->SetScroll(temp);
					}
				return 1;

			}
			else  //오른쪽으로 부딪힐때
			{
				
				pObj->SetPos(pSourceInfo.m_fX - (pSourceInfo.m_fCX/2 )+10 - (pDestInfo->m_fCX/2 ),
					pDestInfo->m_fY);
				pObj->SetBodyPos(pSourceInfo.m_fX - (pSourceInfo.m_fCX/2 )+10 - (pDestInfo->m_fCX/2 ),
					pDestInfo->m_fY);
				////부딪힐때 스크롤이 밀리는걸 방지
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
		if( (*iter)->m_iOption == 0 || (*iter)->m_iOption == 5 ) //충돌하지 않는 타일이라면 조건에 들어올 필요가 없다.
			continue;
		//타일에 번호를 주어서 어느 타일이랑 충돌하는지를 봐야한다.
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

				//플레이어가 떨어지는 상태 값에서만 윗충돌이 일어난다. //재우의견
			if( pDestInfo->m_fY   < pSourceInfo.m_fY ) //위쪽에서 충돌
			{
				
						
				pObj->SetPos(pDestInfo->m_fX, 
					pSourceInfo.m_fY - (pSourceInfo.m_fCY/2 ) - (pDestInfo->m_fCY-22)
					);
				pObj->SetBodyPos(pDestInfo->m_fX, 
					pSourceInfo.m_fY - (pSourceInfo.m_fCY/2 ) - (pDestInfo->m_fCY-22)
					);
				//땅에 닿았을때 점프 상태가 아닐때만 스탠드 상태로 바꾼다.
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
			//위쪽에 왼쪽이나 오른쪽일 가능성이 있다.
			if(pDestInfo->m_fX > pSourceInfo.m_fX  && ((CPlayer*)pObj)->GetDwState() !=STATE_JUMP )  //왼쪽으로 부딪힐때
			{
				((CPlayer*)pObj)->SetMoney(((CPlayer*)pObj)->GetMoney()+1);

				pObj->SetPos(pSourceInfo.m_fX + (pSourceInfo.m_fCX/4 ) + (pDestInfo->m_fCX/4 ),
					pDestInfo->m_fY
					);
				pObj->SetBodyPos(pSourceInfo.m_fX + (pSourceInfo.m_fCX/4 ) + (pDestInfo->m_fCX/4 ),
					pDestInfo->m_fY
					);

				//부딪힐때 스크롤이 밀리는걸 방지
				POINT temp;
				temp.x=pObj->GetScroll().x - ((CPlayer*)pObj)->GetSpeed();
				temp.y=pObj->GetScroll().y;
				pObj->SetScroll(temp);
				return 2;

			}
			else  //오른쪽으로 부딪힐때
			{
				((CPlayer*)pObj)->SetMoney(((CPlayer*)pObj)->GetMoney()+1);
				pObj->SetPos(pSourceInfo.m_fX - (pSourceInfo.m_fCX/4 ) - (pDestInfo->m_fCX/4 ),
					pDestInfo->m_fY);
				pObj->SetBodyPos(pSourceInfo.m_fX - (pSourceInfo.m_fCX/4 ) - (pDestInfo->m_fCX/4 ),
					pDestInfo->m_fY);
				////부딪힐때 스크롤이 밀리는걸 방지
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
		if( (*iter)->m_iOption == 0 || (*iter)->m_iOption == 5) //충돌하지 않는 타일이라면 조건에 들어올 필요가 없다.
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