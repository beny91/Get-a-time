#include "StdAfx.h"
#include "BlackKnight.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "KeyMgr.h"
#include "Effect.h"
#include "SoundMgr.h"
#include "Player.h"
#include "Bullet.h"


CBlackKnight::CBlackKnight(void)
{
}

CBlackKnight::CBlackKnight(string strName, float fx, float fy, float fcx, float fcy , int Hp , int Mp , int Att )
:CObj(strName, fx, fy, fcx, fcy, Hp, Mp, Att)
{

}

CBlackKnight::~CBlackKnight(void)
{
}
void CBlackKnight::Initialize(void)
{
	m_Adc=NULL;
	m_HitTime=70; // 한대 맞으면 이 시간동안 맞지 않는다.
	m_bHit =false; // 맞으면 true
	m_iMapSize=0;
	m_ptMapSize.x = 4000; //처음 맵의 스크롤 
	m_ptMapSize.y = 600;
	m_tFrame = FRAME(5,0,1,100);//프레임 초기화
	m_Money=0;

	memset(&m_ptScroll, 0, sizeof(POINT));
	m_Gravity=0;
	m_Jump=40;

	m_fTime=0.0f;
	m_Weapontime=0;
	m_fSpeed=7;
	m_bJump=false;
	m_bShow=false;
	m_bCollision=false;
	m_bCollision1=false;
	m_ladder=false;
	m_bDeadCheck = false;

	m_dwFrameTime=GetTickCount();
	m_eDir = DIR_LEFT;
	m_dwState = STATE_SKILL;
	m_ePATTERN = LAUGH;
	//CSoundMgr::GetInstance()->PlayMonsterSound(L"sfx_blackknight_laugh.mp3");
					
	//충돌 박스 초기화
	m_tBodyBox=INFO(m_tInfo.m_fX,m_tInfo.m_fY,50,120);

}

int CBlackKnight::Progress(void)
{
	//#ifdef _DEBUG_TYPE_
	//	cout<<endl<<endl;
	//	cout << "m_tBodyBox.m_fX : " << m_tBodyBox.m_fX << endl;
	//	cout << "m_tBodyBox.m_fY : " << m_tBodyBox.m_fY << endl;
	//#endif
	if( m_Hp <= 0)
	{
		m_dwState = STATE_DEAD;
		m_bDeadCheck =true;
	}

	
		





	
	if(CCollisionMgr::GetInstance()->CollisionAttack2(this, OBJ_PLAYER))// 플레이어의 무기와 몬스터의 충돌
	{
		if( m_dwState == STATE_ATTACK_DOWN )
		{
			m_fTime=0.0f;
			m_bJump=true;

		m_pEffect = new CEffect("SPAK",m_tAttackBox.m_fX,m_tAttackBox.m_fY ,150,36);

		m_pEffect->SetType(EFFECT_ATTTECK_DOWN);
		m_pEffect->SetDeadTime(10);
		m_pEffect->SetFrame(0,3,0,100);
		m_pEffect->Initialize();
		CObjMgr::GetInstance()->AddObject(m_pEffect,OBJ_EFFECT);
				CSoundMgr::GetInstance()->PlayEffectSound(L"sfx_ironknight_thrust.mp3");
		}
		memset(&m_tAttackBox,0,sizeof(INFO));
	}
	//if(CCollisionMgr::GetInstance()->CollisionAttack(this, OBJ_OTHER))// 플레이어의 무기와 오브젝트의 충돌
	//{	
	//	if( m_dwState == STATE_ATTACK_DOWN )
	//	{
	//	m_pEffect = new CEffect("SPAK",m_tAttackBox.m_fX,m_tAttackBox.m_fY ,150,36);
	//	
	//	m_pEffect->SetType(EFFECT_ATTTECK_DOWN);
	//	m_pEffect->SetDeadTime(10);
	//	m_pEffect->SetFrame(0,3,0,100);
	//	m_pEffect->Initialize();
	//	CObjMgr::GetInstance()->AddObject(m_pEffect,OBJ_EFFECT);
	//	CSoundMgr::GetInstance()->PlayMonsterSound(L"sfx_knight_dig.mp3");
	//	CSoundMgr::GetInstance()->PlayEffectSound(L"sfx_ironknight_thrust.mp3");
	//	
	//	
	//		m_fTime=0.0f;
	//		m_bJump=true;
	//	}
	//	memset(&m_tAttackBox,0,sizeof(INFO));
	//}

	//if( CCollisionMgr::GetInstance()->CollisionRect(this, OBJ_MONSTER) ) // 플레이어와 몬스터의 충돌
	//{
	//	if( m_bHit == false) //맞지 않은 상태라면 피를깍고 맞은상태로 만든다.
	//	{
	//			m_Hp-=10;
	//		if(m_Hp <0)
	//			m_Hp =0;
	//		m_bHit =true;

	//		CSoundMgr::GetInstance()->PlayEffectSound(L"sfx_knight_hurt.mp3");
	//	}
	//}	

	//CCollisionMgr::GetInstance()->CollisionItem(this, OBJ_ITEM);// 플레이어와 아이템

	//if(CCollisionMgr::GetInstance()->CollisionRect(this, OBJ_OTHER) == true) //플레이어와 다른 오브젝트와 밀어내기
	//{
	//	if( m_dwState == STATE_JUMP_DOWN || m_dwState == STATE_ATTACK_DOWN    )
	//	{
	//		m_bJump=false;
	//		m_dwState=STATE_STAND;
	//	}
	//	
	//	m_bCollision=true;
	//	m_fTime=0;
	//}
	//else
	//{	
	//	if( m_bCollision ==true && m_dwState !=STATE_LADDER)
	//		m_bCollision=false;
	//	m_bCollision1=false;
	//}




	if(CCollisionMgr::GetInstance()->CollisionRectTile1(this) == 1) //플레이어와 타일과 충돌
	{
		if( m_dwState == STATE_JUMP_DOWN || m_dwState == STATE_ATTACK_DOWN  )
		{
			CSoundMgr::GetInstance()->PlayEffectSound(L"sfx_knight_land.mp3");
			m_bJump=false;
			m_dwState=STATE_STAND;
		}
		
		m_bCollision=true;
		m_fTime=0;
	}
	else if( CCollisionMgr::GetInstance()->CollisionRectTile1(this) == 2 )
	{
		m_ladder =true;
		m_bJump=false;
		
	}
	else if( CCollisionMgr::GetInstance()->CollisionRectTile1(this) == 3 )
	{
		m_ladder =false;
		m_bJump=false;
		
	}
	else
	{	
		if (m_bCollision == false)
			m_bCollision=false;
}
	//if(CCollisionMgr::GetInstance()->CollisionRectTile3(this) == 1)
	//{
	//	m_bCollision=true;
	//	m_ladder =true;
	//	m_bJump=false;
	//}
	//else
	//{
	//	m_ladder =false;
	//}

	//if( m_bCollision == false && m_dwState !=STATE_ATTACK_DOWN && m_dwState !=STATE_JUMP && m_dwState !=STATE_ATTACK)
	//	{
	//		m_dwState =STATE_JUMP_DOWN;
	//		
	//	}
	/*

	Jump();
	*/
	if(m_bDeadCheck == false)
	{
	
	KeyCheck();
	Pattern();
	}
	HitCheck();
	FrameCheck();

	CObj::Progress();





	return 0;
}

void CBlackKnight::Render(HDC _hdc)
{
	
	
		TransparentBlt(_hdc,
			static_cast<int>(m_tInfo.m_fX - m_tInfo.m_fCX / 2 )+ m_ptScroll.x,
			static_cast<int>(m_tInfo.m_fY - m_tInfo.m_fCY / 2)+ m_ptScroll.y,
			static_cast<int>(m_tInfo.m_fCX),
			static_cast<int>(m_tInfo.m_fCY),
			(*m_mapBmp)[m_strName]->GetMemDC(),
			static_cast<int>(m_tFrame.m_iFrameStart * m_tInfo.m_fCX),			//출력되는 이미지의 시작 X값.
			static_cast<int>(m_tFrame.m_iImage * m_tInfo.m_fCY),
			static_cast<int>(m_tInfo.m_fCX),		//이미지 출력 범위 지정.
			static_cast<int>(m_tInfo.m_fCY),
			RGB(0, 255, 0));		//빼고 싶은 색.s
	
	if( m_bShow == true ) //충돌 박스를 보여주는 경우
	{
		//바디 박스
		HPEN MyBrush, OldBrush;
		MyBrush = (HPEN)CreatePen(4,5,(RGB(0,255,0)));
		OldBrush = (HPEN)SelectObject((*m_mapBmp)["BACK_BUFFER"]->GetMemDC(), MyBrush);
		Rectangle((*m_mapBmp)["BACK_BUFFER"]->GetMemDC(), 
			static_cast<int>( m_tBodyBox.m_fX - m_tBodyBox.m_fCX/2 )+ m_ptScroll.x, 
			static_cast<int>( m_tBodyBox.m_fY - m_tBodyBox.m_fCY/2)+ m_ptScroll.y,
			static_cast<int>(m_tBodyBox.m_fX + m_tBodyBox.m_fCX/2)+ m_ptScroll.x,
			static_cast<int>(m_tBodyBox.m_fY + m_tBodyBox.m_fCY/2)+ m_ptScroll.y);
		SelectObject((*m_mapBmp)["BACK_BUFFER"]->GetMemDC(), GetStockObject(NULL_BRUSH));
		DeleteObject(MyBrush);

		// 무기 박스

		MyBrush = (HPEN)CreatePen(4,5,(RGB(0,54,255)));
		OldBrush = (HPEN)SelectObject((*m_mapBmp)["BACK_BUFFER"]->GetMemDC(), MyBrush);
		Rectangle((*m_mapBmp)["BACK_BUFFER"]->GetMemDC()
			, m_AttackRect.left + m_ptScroll.x
			, m_AttackRect.top + m_ptScroll.y   
			, m_AttackRect.right + m_ptScroll.x 
			, m_AttackRect.bottom + m_ptScroll.y );
		SelectObject((*m_mapBmp)["BACK_BUFFER"]->GetMemDC(), GetStockObject(NULL_BRUSH));
		DeleteObject(MyBrush);


	}

}

void CBlackKnight::Release(void)
{

}

void CBlackKnight::KeyCheck(void)
{
	if( m_dwState == STATE_ATTACK || m_dwState == STATE_SKILL 
		|| m_dwState == STATE_WAIT ||m_dwState == STATE_HIT ) //공격, 스킬 도중에 이동금지
		return ;

	if( m_tInfo.m_fX <8550 )
	{
		m_tInfo.m_fX+=1;
		
		m_tBodyBox.m_fX+=1;
		return;
	}
	if(m_tInfo.m_fX >9250)
	{
		m_tInfo.m_fX-=1;
			
		m_tBodyBox.m_fX-=1;
		return;
	}

	if( m_eDir == DIR_LEFT)
	{
		m_strName="BLACK_KNIGHT_LEFT";
		m_tInfo.m_fX-=m_fSpeed;
		m_tBodyBox.m_fX-=m_fSpeed;
	}

	if( m_eDir == DIR_RIGHT)
	{
		m_strName="BLACK_KNIGHT_RIGHT";
		m_tInfo.m_fX+=m_fSpeed;
		m_tBodyBox.m_fX+=m_fSpeed;
	}
	

	m_tInfo.m_fY+=m_fSpeed;
		m_tBodyBox.m_fY+=m_fSpeed;
}

void CBlackKnight::Jump(void)
{
	if(m_bJump == false )
		return;

	/*
	m_dwCurTime = GetTickCount();

	float fTime = (m_dwCurTime - m_dwOldTime) * 0.001f;

	m_fTime += fTime; 

	m_tInfo.m_fY += 10 * -1 + (9.8 * m_fTime * m_fTime) / 2;

	m_dwOldTime = m_dwCurTime;
	*/



	m_fTime += 0.4f;		//GetTickCount....
	//m_Gravity+=0.2f;
	//점프 공식
	//sin(90 * 3.14 / 180) : 1				||			-sin(90 * 3.14 / 180)
	//힘 * -1 + (중력가속도:9.8 * 시간 * 시간) / 2
	if(/*(15-m_Gravity)<0*/ (20 * -1 + (0.98 * m_fTime * m_fTime) / 2 )>0) //점프 상태에서 최대점을 찍고 내려오는 시점에서의 상태값
	{
		m_bJump =true;
		if( m_dwState != STATE_ATTACK_DOWN )
			m_dwState = STATE_JUMP_DOWN;
	}
	m_tInfo.m_fY += static_cast<float>(20 * -1 + (0.98 * m_fTime * m_fTime) / 2);
	m_tBodyBox.m_fY += static_cast<float>( 20* -1 + (0.98 * m_fTime * m_fTime) / 2);

	/*m_tInfo.m_fY -=15-m_Gravity;
	m_tBodyBox.m_fY -= 15-m_Gravity;*/
}
void CBlackKnight::FrameCheck(void)
{
	if(m_strName == "BLACK_KNIGHT_RIGHT")
	{
		switch(m_dwState)
		{
		case STATE_WAIT:
			FrameMove(STATE_STAND,0,1,0,100);
			break;

		case STATE_STAND:
			FrameMove(STATE_STAND,0,1,1,200);
			break;

		case STATE_WALK:
			FrameMove(STATE_WALK,0,5,2,200);
			break;

		case STATE_JUMP:
			FrameMove(STATE_JUMP,0,0,3,100);
			break;

		case STATE_JUMP_DOWN:
			FrameMove(STATE_JUMP_DOWN,0,0,4,100);
			break;

		case STATE_ATTACK:
			FrameMove(STATE_ATTACK,0,3,5,100);
			break;

		case STATE_ATTACK_DOWN:
			FrameMove(STATE_ATTACK_DOWN,0,2,6,200);
			break;

		case STATE_HIT:
			FrameMove(STATE_HIT,0,0,7,100);
			break;
		case STATE_SKILL:

			if( m_tFrame.m_iImage == 9 && m_tFrame.m_iFrameStart == 3)
			{
					m_pBullet = new CBullet("BLACKBALL",m_tInfo.m_fX +60, m_tInfo.m_fY+10,70,40);
				m_pBullet->Initialize();
				m_pBullet->SetDir(DIR_RIGHT);
				CObjMgr::GetInstance()->AddObject(m_pBullet,OBJ_BULLET);
				CSoundMgr::GetInstance()->PlayMonsterSound(L"sfx_blackknight_fireball.mp3");

				m_tFrame.m_iImage=8;
				m_tFrame.m_iFrameStart=0;	
			}

			if( m_tFrame.m_iImage == 9)
			{
				FrameMove(STATE_SKILL,0,3,9,200);
			}	
			else
			{
				FrameMove(STATE_SKILL,0,3,8,200);
				if( m_tFrame.m_iFrameStart == 3)
				{
					m_tFrame.m_iImage = 9;
					m_tFrame.m_iFrameStart =0;
				}
			}

			break;
		case STATE_DEAD:
			FrameMove(STATE_DEAD,0,1,12,200);
			break;
		}
	}
	else if(m_strName == "BLACK_KNIGHT_LEFT")
	{
		switch(m_dwState)
		{
		case STATE_WAIT:
			FrameMoveReverse(STATE_STAND,5,4,0,200);
			break;
		case STATE_STAND:
			FrameMoveReverse(STATE_STAND,5,4,1,200);
			break;

		case STATE_WALK:
			FrameMoveReverse(STATE_WALK,5,0,2,200);
			break;

		case STATE_JUMP:
			FrameMoveReverse(STATE_JUMP,5,5,3,100);
			break;

		case STATE_JUMP_DOWN:
			FrameMoveReverse(STATE_JUMP_DOWN,5,5,4,100);
			break;

		case STATE_ATTACK:
			FrameMoveReverse(STATE_ATTACK,5,2,5,100);
			break;

		case STATE_ATTACK_DOWN:
			FrameMoveReverse(STATE_ATTACK_DOWN,5,3,6,200);
			break;
		case STATE_SKILL:
			
			if( m_tFrame.m_iImage == 9 && m_tFrame.m_iFrameStart == 2)
			{
				m_pBullet = new CBullet("BLACKBALL",m_tInfo.m_fX -60, m_tInfo.m_fY+10,70,40);
				m_pBullet->Initialize();
				m_pBullet->SetDir(DIR_LEFT);
				CObjMgr::GetInstance()->AddObject(m_pBullet,OBJ_BULLET);
				CSoundMgr::GetInstance()->PlayMonsterSound(L"sfx_blackknight_fireball.mp3");
	
				m_tFrame.m_iImage=8;
				m_tFrame.m_iFrameStart=5;	
			}

			if( m_tFrame.m_iImage == 9)
			{
				FrameMoveReverse(STATE_SKILL,5,2,9,200);
			}	
			else
			{
				FrameMoveReverse(STATE_SKILL,5,2,8,200);
				if( m_tFrame.m_iFrameStart == 2)
				{
					m_tFrame.m_iImage = 9;
					m_tFrame.m_iFrameStart =5;
				}
			}

			break;
		case STATE_HIT:
			FrameMoveReverse(STATE_HIT,5,5,7,100);
			break;
		case STATE_DEAD:
			FrameMoveReverse(STATE_DEAD,5,4,12,200);
			break;
		}
	}
}

void CBlackKnight::CreateAttackBox(void)
{
	if( m_dwState==STATE_ATTACK  &&   m_eDir == DIR_LEFT)
	{
		m_tAttackBox.m_fX = m_tInfo.m_fX -70;
		m_tAttackBox.m_fY = m_tInfo.m_fY +17.5f  ;
		m_tAttackBox.m_fCX = 25;
		m_tAttackBox.m_fCY = 25;
	}
	else if( m_dwState==STATE_ATTACK  && m_eDir == DIR_RIGHT)
	{
		m_tAttackBox.m_fX = m_tInfo.m_fX +70;
		m_tAttackBox.m_fY = m_tInfo.m_fY +17.5f ;
		m_tAttackBox.m_fCX = 30;
		m_tAttackBox.m_fCY = 30;
	}
	else if( m_dwState==STATE_ATTACK_DOWN  && (m_eDir == DIR_DOWN || m_eDir == DIR_RIGHT || m_eDir == DIR_LEFT))
	{
		m_tAttackBox.m_fX = m_tBodyBox.m_fX  ;
		m_tAttackBox.m_fY = m_tBodyBox.m_fY + m_tBodyBox.m_fCY/2   ;
		m_tAttackBox.m_fCX = 30;
		m_tAttackBox.m_fCY = 30;
	}
}
void CBlackKnight::HitCheck(void)
{

	if( m_HitTime >50 && m_bHit == true)
	{
		m_dwState = STATE_HIT;
	}
	else if(m_HitTime <30 && m_bHit == true) //맞았을때 일정시간이 지나면 원상태로 돌아온다.
	{
		if(m_dwState == STATE_HIT)
			m_dwState =STATE_STAND;
	}

	if(m_HitTime >0 && m_bHit == true)
	{
		m_HitTime--;
	}
	else
	{
		m_HitTime=70;
		m_bHit = false;
	}

}
void CBlackKnight::Pattern(void)
{
	OBJ_ITER iter = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].begin();
	OBJ_ITER iter_end = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].end();

	float disX = abs((*iter)->GetBodyBox()->m_fX - m_tBodyBox.m_fX) ;
	if( disX>700)
		m_dwState = STATE_WAIT;
	else if( ((CPlayer*)(*iter))->GetbHit() ==true) //플레이어가 피격불가상태일경우
	{
		if( disX <400) // 일정거리이하인 경우  거리를 벌려준다.
		{
			
				if( (*iter)->GetBodyBox()->m_fX <  m_tBodyBox.m_fX) //플레이어가 왼쪽에 있는 경우
				{
					m_dwState = STATE_WALK;
					if(m_eDir != DIR_RIGHT)
					{
						m_eDir=DIR_RIGHT;
					}
				}
				else if( (*iter)->GetBodyBox()->m_fX >  m_tBodyBox.m_fX ) //플레이어가 오른쪽에 있는경우
				{
					m_dwState = STATE_WALK;
					if(m_eDir != DIR_LEFT)
					{
						m_eDir=DIR_LEFT;
					}
				}
			
		}
		else //일정거리를 벌려준 경우
		{
			if( (*iter)->GetBodyBox()->m_fX >  m_tBodyBox.m_fX) // 왼쪽을 보고있을 경우
				{					//오른쪽을 보고 공격한다.
					m_eDir=DIR_RIGHT;
					m_dwState = STATE_WAIT;
					m_strName="BLACK_KNIGHT_RIGHT";
					CSoundMgr::GetInstance()->PlayMonsterSound(L"sfx_blackknight_laugh.mp3");
					
				}
				else if( (*iter)->GetBodyBox()->m_fX <  m_tBodyBox.m_fX ) // 오른쪽을 보고 있을경우
				{								//왼쪽을 보고 공격한다.
					m_eDir=DIR_LEFT;
					m_dwState = STATE_WAIT;
					m_strName="BLACK_KNIGHT_LEFT";
					CSoundMgr::GetInstance()->PlayMonsterSound(L"sfx_blackknight_laugh.mp3");
					
				}
		}
	}
	else //플레이어가 공격 가능 한 상태인 경우.
	{
		if( disX <400) // 일정거리이하인 경우 
		{
			if(disX >100)// 공격하러 달려온다.
			{
				if( (*iter)->GetBodyBox()->m_fX <  m_tBodyBox.m_fX) //플레이어가 왼쪽에 있는 경우
				{
					m_dwState = STATE_WALK;
					if(m_eDir != DIR_LEFT)
					{
						m_eDir=DIR_LEFT;
					}
				}
				else if( (*iter)->GetBodyBox()->m_fX >  m_tBodyBox.m_fX ) //플레이어가 오른쪽에 있는경우
				{
					m_dwState = STATE_WALK;
					if(m_eDir != DIR_RIGHT)
					{
						m_eDir=DIR_RIGHT;
					}
				}
			}
			else // 공격한다.
			{
				if( (*iter)->GetBodyBox()->m_fX <  m_tBodyBox.m_fX) //플레이어가 왼쪽
				{
					m_dwState = STATE_ATTACK;
					if(m_eDir != DIR_LEFT)
					{
						m_eDir=DIR_LEFT;
		
					}
					if( m_tFrame.m_iFrameStart ==3)
						CreateAttackBox();
				
				}
				else if( (*iter)->GetBodyBox()->m_fX >  m_tBodyBox.m_fX  ) //플레이어가 오른쪽
				{
					m_dwState = STATE_ATTACK;
					if(m_eDir != DIR_RIGHT)
					{
						m_eDir=DIR_RIGHT;
					}
					if( m_tFrame.m_iFrameStart ==2)
						CreateAttackBox();
				}
			}
		}
		else //공격가능 상태에서 일정거리 이상 벌려준 경우.
		{
			if( (*iter)->GetBodyBox()->m_fX <  m_tBodyBox.m_fX) //플레이어가 왼쪽에 있는 경우
				{
					m_dwState = STATE_SKILL;
					if(m_eDir != DIR_LEFT)
					{
						m_eDir=DIR_LEFT;
					}
				}
				else if( (*iter)->GetBodyBox()->m_fX >  m_tBodyBox.m_fX ) //플레이어가 오른쪽에 있는경우
				{
					m_dwState = STATE_SKILL;
					if(m_eDir != DIR_RIGHT)
					{
						m_eDir=DIR_RIGHT;
					}
				}
		}
	  }

		/*switch(m_ePATTERN)
		{
		case LAUGH:
		m_dwState = STATE_WAIT;
		break;
		case ATTACK:
		m_dwState = STATE_ATTACK;
		break;
		case STAND:
		m_dwState = STATE_STAND;
		break;
		case THRUST:
		m_dwState = STATE_ATTACK_DOWN;
		break;

		}*/

	}