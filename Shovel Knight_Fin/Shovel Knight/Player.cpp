#include "StdAfx.h"
#include "Player.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "KeyMgr.h"
#include "Effect.h"
#include "SoundMgr.h"

CPlayer::CPlayer(void)
{
}
CPlayer::CPlayer(string strName, float fx, float fy, float fcx, float fcy , int Hp , int Mp , int Att )
:CObj(strName, fx, fy, fcx, fcy, Hp, Mp, Att)
{

}

CPlayer::~CPlayer(void)
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_Adc=NULL;
	m_HitTime=100; // �Ѵ� ������ �� �ð����� ���� �ʴ´�.
	m_bHit =false; // ������ true
	m_iMapSize=0;
	m_ptMapSize.x = 4000; //ó�� ���� ��ũ�� 
	m_ptMapSize.y = 600;
	m_tFrame = FRAME(0,5,1,100);//������ �ʱ�ȭ
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

	m_dwFrameTime=GetTickCount();
	m_eDir = DIR_RIGHT;
	m_dwState=STATE_STAND;
	
	//�浹 �ڽ� �ʱ�ȭ
	m_tBodyBox=INFO(m_tInfo.m_fX,m_tInfo.m_fY,50,100);

}

int CPlayer::Progress(void)
{
//#ifdef _DEBUG_TYPE_
//	cout<<endl<<endl;
//	cout << "m_tBodyBox.m_fX : " << m_tBodyBox.m_fX << endl;
//	cout << "m_tBodyBox.m_fY : " << m_tBodyBox.m_fY << endl;
//#endif

	
	
	
	KeyCheck();	

	if(CCollisionMgr::GetInstance()->CollisionBullet(this, OBJ_BULLET))
		memset(&m_tAttackBox,0,sizeof(INFO));

	if(CCollisionMgr::GetInstance()->CollisionAttack(this, OBJ_MONSTER))// �÷��̾��� ����� ������ �浹
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
	if(CCollisionMgr::GetInstance()->CollisionAttack(this, OBJ_OTHER))// �÷��̾��� ����� ������Ʈ�� �浹
	{	
		if( m_dwState == STATE_ATTACK_DOWN )
		{
		m_pEffect = new CEffect("SPAK",m_tAttackBox.m_fX,m_tAttackBox.m_fY ,150,36);
		
		m_pEffect->SetType(EFFECT_ATTTECK_DOWN);
		m_pEffect->SetDeadTime(10);
		m_pEffect->SetFrame(0,3,0,100);
		m_pEffect->Initialize();
		CObjMgr::GetInstance()->AddObject(m_pEffect,OBJ_EFFECT);
		CSoundMgr::GetInstance()->PlayMonsterSound(L"sfx_knight_dig.mp3");
		CSoundMgr::GetInstance()->PlayEffectSound(L"sfx_ironknight_thrust.mp3");
		
		
			m_fTime=0.0f;
			m_bJump=true;
		}
		memset(&m_tAttackBox,0,sizeof(INFO));
	}

	if( CCollisionMgr::GetInstance()->CollisionRect(this, OBJ_MONSTER) ) // �÷��̾�� ������ �浹
	{
		if( m_bHit == false) //���� ���� ���¶�� �Ǹ���� �������·� �����.
		{
				m_Hp-=10;
			if(m_Hp <0)
				m_Hp =0;
			m_bHit =true;

			CSoundMgr::GetInstance()->PlayEffectSound(L"sfx_knight_hurt.mp3");
		}
	}	

	CCollisionMgr::GetInstance()->CollisionItem(this, OBJ_ITEM);// �÷��̾�� ������

	if(CCollisionMgr::GetInstance()->CollisionRect(this, OBJ_OTHER) == true) //�÷��̾�� �ٸ� ������Ʈ�� �о��
	{
		if( m_dwState == STATE_JUMP_DOWN || m_dwState == STATE_ATTACK_DOWN    )
		{
			m_bJump=false;
			m_dwState=STATE_STAND;
		}
		
		m_bCollision=true;
		m_fTime=0;
	}
	else
	{	
		if( m_bCollision ==true && m_dwState !=STATE_LADDER)
			m_bCollision=false;
		m_bCollision1=false;
	}




	if(CCollisionMgr::GetInstance()->CollisionRectTile1(this) == 1) //�÷��̾�� Ÿ�ϰ� �浹
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
	if(CCollisionMgr::GetInstance()->CollisionRectTile3(this) == 1)
	{
		m_bCollision=true;
		m_ladder =true;
		m_bJump=false;
	}
	else
	{
		m_ladder =false;
	}

	if( m_bCollision == false && m_dwState !=STATE_ATTACK_DOWN && m_dwState !=STATE_JUMP && m_dwState !=STATE_ATTACK)
		{
			m_dwState =STATE_JUMP_DOWN;
			
		}
	HitCheck();
	Jump();
	FrameCheck();
	
	
	CObj::Progress();

	



	return 0;
}

void CPlayer::Render(HDC _hdc)
{
	if( m_bHit ==true)
	{
		
			HDC			m_Adc	   = CreateCompatibleDC( GetDC(g_hWnd) );

	HBITMAP		bitmapTemp = CreateCompatibleBitmap( GetDC(g_hWnd),static_cast<int>(m_tInfo.m_fCX),
											static_cast<int>(m_tInfo.m_fCY) );

	HBITMAP hOld = (HBITMAP)SelectObject(m_Adc, bitmapTemp);
	
	TransparentBlt(m_Adc,
		0,
		0,
		static_cast<int>(m_tInfo.m_fCX),
		static_cast<int>(m_tInfo.m_fCY),
		_hdc,
		static_cast<int>(m_tInfo.m_fX - m_tInfo.m_fCX / 2) + m_ptScroll.x,		
		static_cast<int>(m_tInfo.m_fY - m_tInfo.m_fCY / 2) + m_ptScroll.y,
		static_cast<int>(m_tInfo.m_fCX),		
		static_cast<int>(m_tInfo.m_fCY),
		RGB(0, 255, 0));		//���� ���� ��.s


	TransparentBlt(m_Adc,
		0,
		0,
		static_cast<int>(m_tInfo.m_fCX),
		static_cast<int>(m_tInfo.m_fCY),
		(*m_mapBmp)[m_strName]->GetMemDC(),
		static_cast<int>(m_tFrame.m_iFrameStart * m_tInfo.m_fCX),			//��µǴ� �̹����� ���� X��.
		static_cast<int>(m_tFrame.m_iImage * m_tInfo.m_fCY),
		static_cast<int>(m_tInfo.m_fCX),		//�̹��� ��� ���� ����.
		static_cast<int>(m_tInfo.m_fCY),
		RGB(0, 255, 0));		//���� ���� ��.s
	
	static	int iAlpha = 100;

	BLENDFUNCTION tFunction;
	tFunction.BlendOp				= AC_SRC_OVER;
	tFunction.BlendFlags			= 0;
	tFunction.AlphaFormat			= 0;
	tFunction.SourceConstantAlpha	= iAlpha;		//���� ����ȭ ��ġ(0~255)


	

	if(iAlpha < 0)
	{
		iAlpha = 255;
	}

	AlphaBlend(_hdc,
		static_cast<int>(m_tInfo.m_fX - m_tInfo.m_fCX / 2) + m_ptScroll.x,
		static_cast<int>(m_tInfo.m_fY - m_tInfo.m_fCY / 2) + m_ptScroll.y,
		static_cast<int>(m_tInfo.m_fCX),
		static_cast<int>(m_tInfo.m_fCY),
		m_Adc,
		0,
		0,
		static_cast<int>(m_tInfo.m_fCX),
		static_cast<int>(m_tInfo.m_fCY),
		tFunction);

	bitmapTemp = (HBITMAP)SelectObject(m_Adc, hOld);
	DeleteObject(bitmapTemp);
	DeleteDC(m_Adc);
	ReleaseDC(g_hWnd,m_Adc);

	}
	else
	{
		TransparentBlt(_hdc,
			static_cast<int>(m_tInfo.m_fX - m_tInfo.m_fCX / 2 )+ m_ptScroll.x,
			static_cast<int>(m_tInfo.m_fY - m_tInfo.m_fCY / 2)+ m_ptScroll.y,
		static_cast<int>(m_tInfo.m_fCX),
		static_cast<int>(m_tInfo.m_fCY),
		(*m_mapBmp)[m_strName]->GetMemDC(),
		static_cast<int>(m_tFrame.m_iFrameStart * m_tInfo.m_fCX),			//��µǴ� �̹����� ���� X��.
		static_cast<int>(m_tFrame.m_iImage * m_tInfo.m_fCY),
		static_cast<int>(m_tInfo.m_fCX),		//�̹��� ��� ���� ����.
		static_cast<int>(m_tInfo.m_fCY),
		RGB(0, 255, 0));		//���� ���� ��.s
	}
	if( m_bShow == true ) //�浹 �ڽ��� �����ִ� ���
	{
		//�ٵ� �ڽ�
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

	 // ���� �ڽ�
	
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

void CPlayer::Release(void)
{

}

void CPlayer::KeyCheck(void)
{

#ifdef _DEBUG_TYPE_
		system("cls");
		cout<<" m_ptScroll.x: "<< m_ptScroll.x<<endl;
		cout<<" m_ptScroll.y : "<<m_ptScroll.y<<endl;
		cout<<" m_tBodyBox : " <<m_tBodyBox.m_fX<<endl;
		cout<<" m_tInfo.x : " <<m_tInfo.m_fX<<endl;
		cout<<" m_tInfo.y : " <<m_tInfo.m_fY<<endl;
		cout<<"m_iMapSize : " <<m_iMapSize<<endl;
		if ((20 * -1 + (0.98 * m_fTime * m_fTime) / 2 )<0)
			cout<<" m_fTime : " <<m_fTime<<endl;
#endif
	DWORD dwKey = CKeyMgr::GetInstance()->GetKeyState();

	if( m_dwState == STATE_HIT)
		return ;

	
	m_Weapontime +=1; // ���� üũ�ڽ� �ð�
	if( m_Weapontime >= 15) //15�� �Ǹ� ����üũ�ڽ��� �ʱ�ȭ
	{
		memset(&m_tAttackBox,0,sizeof(INFO));
		m_Weapontime=0;
	}
	if( m_dwState == STATE_ATTACK)
		return ;
	if( m_dwState == STATE_NEUTRAL)
		return;


	if(!dwKey && m_dwState == STATE_WALK //Ű�������� �ʰ� �ȴ»��¿����� ���ĵ��
		/*&&  m_dwState != STATE_JUMP_DOWN 
		&&  m_dwState != STATE_ATTACK_DOWN*/) // ���� �����϶��� �Ʒ��� ���� ���¿����� ����
	{
		m_dwState = STATE_STAND;
		memset(&m_tAttackBox,0,sizeof(INFO));
	}
	
	if(dwKey & KEY_RIGHT  )		//Ű�� ������ true��ȯ.
	{	
		if( m_dwState == STATE_LADDER)
		{ 
			if(dwKey & KEY_SPACE)
				m_dwState= STATE_DOWN;
			return;
		}
		m_tInfo.m_fX += m_fSpeed;
		m_tBodyBox.m_fX += m_fSpeed;
		
		if(m_tInfo.m_fX >= -m_ptScroll.x + g_iWINCX / 2 && m_ptScroll.x > -(m_ptMapSize.x - g_iWINCX) ) //�ʽ�ũ��
			m_ptScroll.x -= static_cast<long>(m_fSpeed);

		if( m_dwState !=STATE_JUMP && m_dwState !=STATE_JUMP_DOWN && m_dwState !=STATE_ATTACK_DOWN) //���߻��¿����� �Ұ�
			m_dwState = STATE_WALK;
		
		m_strName="KNIGHT_RIGHT";
		
		if(m_eDir == DIR_LEFT) //���⿡ ���� �ʿ��� �������� ������ �޶�� ��������Ʈ�� ����ġ ���ϰ� �����Ÿ��� ��츦 ���� �� �ִ�.
		{
			m_tFrame = FRAME(0,5,1,100);
			m_eDir = DIR_RIGHT;
			if( m_dwState != STATE_JUMP && m_dwState != STATE_JUMP_DOWN && m_dwState != STATE_ATTACK_DOWN)
			m_dwState =STATE_NEUTRAL;//�ȴٰ� ������ �ٲ�� ������ �̹���
		}
		else
			m_eDir = DIR_RIGHT;
	}

	if(dwKey & KEY_LEFT)		//Ű�� ������ true��ȯ.
	{
		if( m_dwState == STATE_LADDER)
		{
			if(dwKey & KEY_SPACE)
				m_dwState= STATE_DOWN;
			return ;
		}
		m_tInfo.m_fX -= m_fSpeed;
		m_tBodyBox.m_fX -= m_fSpeed;

		if(m_ptScroll.x < -m_iMapSize  && m_tInfo.m_fX < m_ptMapSize.x - g_iWINCX / 2)// �ʽ�ũ��
			m_ptScroll.x += static_cast<long>(m_fSpeed);

		if( m_dwState !=STATE_JUMP && m_dwState !=STATE_JUMP_DOWN && m_dwState !=STATE_ATTACK_DOWN) ////���߻��¿����� �Ұ�
			m_dwState = STATE_WALK;
		
		m_strName="KNIGHT_LEFT";
	
		if(m_eDir == DIR_RIGHT) //���⿡ ���� �ʿ��� �������� ������ �޶�� ��������Ʈ�� ����ġ ���ϰ� �����Ÿ��� ��츦 ���� �� �ִ�.
		{
			m_tFrame = FRAME(5,0,1,100);
				m_eDir = DIR_LEFT;
				if( m_dwState != STATE_JUMP && m_dwState != STATE_JUMP_DOWN && m_dwState != STATE_ATTACK_DOWN)
				m_dwState =STATE_NEUTRAL; //�ȴٰ� ������ �ٲ�� ������ �̹���


		}
		else
				m_eDir = DIR_LEFT;

		
	}

	if(dwKey & KEY_UP)		//Ű�� ������ true��ȯ.
	{
		if( m_ladder == true)
		{
			m_dwState= STATE_LADDER;
		}
		if( m_dwState == STATE_LADDER)
		{
			
			m_tInfo.m_fY -=m_fSpeed;
			m_tBodyBox.m_fY -=m_fSpeed;
		}
		m_tInfo.m_fY -=m_fSpeed;
			m_tBodyBox.m_fY -=m_fSpeed;
		/*	if(m_tInfo.m_fY <0 && m_ptScroll.y < 500)
			m_ptScroll.y+=m_fSpeed;*/
		
	}

	if(dwKey & KEY_DOWN)		//Ű�� ������ true��ȯ.
	{
		if( m_ladder == true)
		{
			m_dwState= STATE_LADDER;
		}
		if( m_dwState == STATE_LADDER)
		{
		
			m_tInfo.m_fY +=m_fSpeed;
			m_tBodyBox.m_fY +=m_fSpeed;
			/*if(m_tInfo.m_fY <0 && m_ptScroll.y >0)
				m_ptScroll.y+=m_fSpeed;*/
		}
		else if( m_dwState == STATE_JUMP || m_dwState == STATE_JUMP_DOWN ) //���� �Ʒ� ����
		{	
			m_dwState=STATE_ATTACK_DOWN;
			m_eDir =DIR_DOWN;
					
		}
		
	}

	if(m_dwState == STATE_ATTACK_DOWN) // �Ʒ��� ���ݽÿ� ������ �浹 �ڽ�
	{
		CreateAttackBox();
	}

	if(GetAsyncKeyState('A')  )
	{
		CSoundMgr::GetInstance()->PlayEffectSound(L"sfx_knight_slash.mp3");
		m_dwState = STATE_ATTACK;
		CreateAttackBox(); //���ݽÿ� �浹�ڽ��� �����ȴ�.
		
	}

	if(dwKey & KEY_SPACE && m_dwState != STATE_JUMP && m_bJump == false )		//Ű�� ������ true��ȯ.
	{
		
		CSoundMgr::GetInstance()->PlayEffectSound(L"sfx_knight_jump.mp3");
		
	
			//CObjMgr::GetInstance()->AddObject( CreateBullet(DIR_RIGHT), OBJ_BULLET );
			if( m_ladder ==true)
			{
				m_dwState = STATE_JUMP_DOWN;
				m_bJump = false;
			}
			else
			{
				m_dwState = STATE_JUMP;
				m_bJump=true;
				m_fTime=0.0f;
			
			}
			
		
		if( m_bJump == true && !(GetAsyncKeyState(VK_SPACE)& 0x8000 ))
		{
			 m_bJump = false;
		}
		
	}

	if(GetAsyncKeyState(VK_F1) & 1)
	{
		if(m_bShow == true)
			m_bShow = false;
		else
			m_bShow = true;
	}

	if( m_bJump == false && m_dwState != STATE_LADDER )
	{
	/*	if(m_dwState != STATE_STAND && m_dwState != STATE_WALK && m_dwState != STATE_ATTACK)
		{
			m_dwState =STATE_JUMP_DOWN;
			m_tInfo.m_fY+=3;
			m_tBodyBox.m_fY+=3;
		}*/
		if( m_fTime == 0 )
			m_fTime=6.6f;

		m_fTime += 0.4f;
		m_tInfo.m_fY += static_cast<float>(20 * -1 + (0.98 * m_fTime * m_fTime) / 2);
		m_tBodyBox.m_fY += static_cast<float>( 20* -1 + (0.98 * m_fTime * m_fTime) / 2);
			/*m_tInfo.m_fY+=m_fSpeed;
			m_tBodyBox.m_fY+=m_fSpeed;*/
	}

	
	
}

void CPlayer::Jump(void)
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
	//���� ����
	//sin(90 * 3.14 / 180) : 1				||			-sin(90 * 3.14 / 180)
	//�� * -1 + (�߷°��ӵ�:9.8 * �ð� * �ð�) / 2
	if(/*(15-m_Gravity)<0*/ (20 * -1 + (0.98 * m_fTime * m_fTime) / 2 )>0) //���� ���¿��� �ִ����� ��� �������� ���������� ���°�
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
void CPlayer::FrameCheck(void)
{
	if(m_strName == "KNIGHT_RIGHT")
	{
		switch(m_dwState)
		{
		case STATE_STAND:
			FrameMove(STATE_STAND,0,0,0,100);
			break;
		case STATE_WALK:
			FrameMove(STATE_WALK,0,5,1,100);
			break;
		case STATE_JUMP:
			FrameMove(STATE_JUMP,0,0,2,100);
		case STATE_LADDER:
			FrameMove(STATE_LADDER,0,1,4,100);
			break;
		case STATE_JUMP_DOWN:
			FrameMove(STATE_JUMP_DOWN,0,0,3,100);
			break;
		case STATE_ATTACK:
			FrameMove(STATE_ATTACK,0,4,7,80);
			break;
		case STATE_ATTACK_DOWN:
			FrameMove(STATE_ATTACK_DOWN,0,0,8,100);
			break;
		case STATE_NEUTRAL:
			FrameMove(STATE_NEUTRAL,0,0,6,100);
			break;
		case STATE_HIT:
			FrameMove(STATE_HIT,0,0,13,100);
			break;
		}
	}
	else
	{
		switch(m_dwState)
		{
		case STATE_STAND:
			FrameMoveReverse(STATE_STAND,5,5,0,100);
			break;
		case STATE_WALK:
			FrameMoveReverse(STATE_WALK,5,0,1,100);
			break;
		case STATE_JUMP:
			FrameMoveReverse(STATE_JUMP,5,5,2,100);
			break;
		case STATE_LADDER:
			FrameMoveReverse(STATE_LADDER,5,4,4,100);
			break;
		case STATE_JUMP_DOWN:
			FrameMoveReverse(STATE_JUMP_DOWN,5,5,3,100);
			break;
		case STATE_ATTACK:
			FrameMoveReverse(STATE_ATTACK,5,1,7,80);
			break;
		case STATE_ATTACK_DOWN:
			FrameMoveReverse(STATE_ATTACK_DOWN,5,5,8,100);
			break;
		case STATE_NEUTRAL:
			FrameMoveReverse(STATE_NEUTRAL,5,5,6,100);
			break;
		case STATE_HIT:
			FrameMoveReverse(STATE_HIT,5,5,13,100);
			break;
		}
	}
}

void CPlayer::CreateAttackBox(void)
{
	if( m_dwState==STATE_ATTACK  &&   m_eDir == DIR_LEFT)
	{
		m_tAttackBox.m_fX = m_tInfo.m_fX -70;
		m_tAttackBox.m_fY = m_tInfo.m_fY +17.5f  ;
		m_tAttackBox.m_fCX = 40;
		m_tAttackBox.m_fCY = 40;
	}
	else if( m_dwState==STATE_ATTACK  && m_eDir == DIR_RIGHT)
	{
		m_tAttackBox.m_fX = m_tInfo.m_fX +70;
		m_tAttackBox.m_fY = m_tInfo.m_fY +17.5f ;
		m_tAttackBox.m_fCX = 40;
		m_tAttackBox.m_fCY = 40;
	}
	else if( m_dwState==STATE_ATTACK_DOWN  && (m_eDir == DIR_DOWN || m_eDir == DIR_RIGHT || m_eDir == DIR_LEFT))
	{
		m_tAttackBox.m_fX = m_tBodyBox.m_fX  ;
		m_tAttackBox.m_fY = m_tBodyBox.m_fY + m_tBodyBox.m_fCY/2 + 20 ;
		m_tAttackBox.m_fCX = 40;
		m_tAttackBox.m_fCY = 40;
	}
}
void CPlayer::HitCheck(void)
{

			if( m_HitTime >70 && m_bHit == true)
			{
				m_dwState = STATE_HIT;
			}
			else if(m_HitTime <70 && m_bHit == true) //�¾����� �����ð��� ������ �����·� ���ƿ´�.
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
				m_HitTime=100;
				m_bHit = false;
			}
	
}