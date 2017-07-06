#include "StdAfx.h"
#include "Stage.h"
#include "Mouse.h"
#include "Obj.h"
#include "Ui.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "Background.h"
#include "TileMgr.h"
#include "Player.h"
#include "Beeto.h"
#include "Blorb.h"
#include "Skeleton.h"
#include "Divedrake.h"
#include "StateWindow.h"
#include "Background.h"
#include "Treasure.h"
#include "Potion.h"
#include "Dirt.h"
#include "DirtPile.h"
#include "Bubble.h"
#include "Bord.h"
#include "BubbleDragon.h"
#include "SoundMgr.h"
#include "Blackknight.h"

CStage::CStage(void)
{
}

CStage::~CStage(void)
{
	Release();
}

void CStage::Initialize(void)
{


	


	m_bShowRect=false;
	m_bCreate =false;
	m_pBack= new CBackground("BACK_GROUND",0 ,0,static_cast<float>(g_iWINCX), static_cast<float>(g_iWINCY));
	//CObjMgr::GetInstance()->AddObject(pObj , OBJ_BACKGROUND );
	m_pBack1 = new CBackground("BACK_CASTLE",0 ,0,static_cast<float>(1200), static_cast<float>(g_iWINCY));
	((CBackground*)m_pBack1)->SetScrollSpeed(10);
	m_pBack2= new CBackground("TREE1",0 ,0,static_cast<float>(2000), static_cast<float>(g_iWINCY));
	((CBackground*)m_pBack2)->SetScrollSpeed(6);
	m_pBack3= new CBackground("TREE3",0 ,0,static_cast<float>(2750), static_cast<float>(550));
	((CBackground*)m_pBack3)->SetScrollSpeed(2);
		m_pBack4= new CBackground("TREE4",0 ,0,static_cast<float>(2500), static_cast<float>(g_iWINCY));
	((CBackground*)m_pBack4)->SetScrollSpeed(4);

	//m_pBack5= new CBackground("BACK_GROUND",7000 ,-600,static_cast<float>(g_iWINCX), static_cast<float>(g_iWINCY));
	////CObjMgr::GetInstance()->AddObject(pObj , OBJ_BACKGROUND );
	//m_pBack6 = new CBackground("BACK_CASTLE",7000 ,-600,static_cast<float>(1200), static_cast<float>(g_iWINCY));
	//((CBackground*)m_pBack1)->SetScrollSpeed(10);
	//m_pBack7= new CBackground("TREE1",7000 ,-600,static_cast<float>(2000), static_cast<float>(g_iWINCY));
	//((CBackground*)m_pBack2)->SetScrollSpeed(6);
	//m_pBack8= new CBackground("TREE3",7000 ,-600,static_cast<float>(2750), static_cast<float>(550));
	//((CBackground*)m_pBack3)->SetScrollSpeed(2);
	//	m_pBack9= new CBackground("TREE4",7000 ,-600,static_cast<float>(2500), static_cast<float>(g_iWINCY));
	//((CBackground*)m_pBack4)->SetScrollSpeed(4);
	
	CTileMgr::GetInstance()->LoadTile();
	CObjMgr::GetInstance()->LoadObj();
	//플레이어
	CObj*pObj = new CPlayer("KNIGHT_RIGHT", 100, 400, 200,200,80,30,10);
	pObj->Initialize();
	CObjMgr::GetInstance()->AddObject(pObj ,OBJ_PLAYER);
	//블랙나이트
	pObj = new CBlackKnight("BLACK_KNIGHT_LEFT", 9200, -220, 200,200,80,30,10);
	pObj->Initialize();
	CObjMgr::GetInstance()->AddObject(pObj ,OBJ_MONSTER);

	/*pObj = new CBlackKnight("BLACK_KNIGHT_LEFT", 600, 400, 200,200,80,30,10);
	pObj->Initialize();
	CObjMgr::GetInstance()->AddObject(pObj ,OBJ_MONSTER);*/

	pObj = new CBeeto("BEETO", 940,450, 75, 75,10,0,10);
	pObj->Initialize();
	CObjMgr::GetInstance()->AddObject(pObj ,OBJ_MONSTER);

	pObj = new CBeeto("BEETO", 2095,450, 75, 75,10,0,10);
	pObj->Initialize();
	CObjMgr::GetInstance()->AddObject(pObj ,OBJ_MONSTER);

	pObj = new CBeeto("BEETO", 2716,450, 75, 75,10,0,10);
	pObj->Initialize();
	CObjMgr::GetInstance()->AddObject(pObj ,OBJ_MONSTER);

	pObj = new CBeeto("BEETO", 4887,450, 75, 75,10,0,10);
	pObj->Initialize();
	CObjMgr::GetInstance()->AddObject(pObj ,OBJ_MONSTER);


	
	pObj = new CBubbleDragon("BUBBLEDRAGON", 7482, -200, 500,243, 60,0,0);
	pObj->Initialize();
	CObjMgr::GetInstance()->AddObject(pObj, OBJ_MONSTER);

	/*pObj = new CBeeto("BEETO", 1416,150, 75, 75,10,0,10);
	pObj->Initialize();
	CObjMgr::GetInstance()->AddObject(pObj ,OBJ_MONSTER);

	pObj = new CBeeto("BEETO", 1920,450, 75, 75,10,0,10);
	pObj->Initialize();
	CObjMgr::GetInstance()->AddObject(pObj ,OBJ_MONSTER);

	pObj = new CBeeto("BEETO", 2179,450, 75, 75,10,0,10);
	pObj->Initialize();
	CObjMgr::GetInstance()->AddObject(pObj ,OBJ_MONSTER);

	pObj = new CBeeto("BEETO", 2893,450, 75, 75,10,0,10);
	pObj->Initialize();
	CObjMgr::GetInstance()->AddObject(pObj ,OBJ_MONSTER);

		pObj = new CBeeto("BEETO", 3264,450, 75, 75,10,0,10);
	pObj->Initialize();
	CObjMgr::GetInstance()->AddObject(pObj ,OBJ_MONSTER);*/
	//pObj = new CBlorb("BLORB", 300,400, 100, 100,20,0,10);
	//pObj->Initialize();
	//CObjMgr::GetInstance()->AddObject(pObj ,OBJ_MONSTER);

	pObj = new CSkeleton("SKELETON", 5260,350, 150, 150,10,0,10);
	pObj->Initialize();
	CObjMgr::GetInstance()->AddObject(pObj ,OBJ_MONSTER);

	pObj = new CDivedrake("DIVEDRAKE", 5800,-200, 150, 150,10,0,10);
	pObj->Initialize();
	((CDivedrake*)pObj)->SetPattern(0);
	CObjMgr::GetInstance()->AddObject(pObj ,OBJ_MONSTER);

	

	//pObj = new CTreasure("GEM_GRAY", 200,400, 18, 18);
	//((CTreasure*)pObj)->SetType(TREASURES_GRAY);
	//pObj->Initialize();
	//CObjMgr::GetInstance()->AddObject(pObj ,OBJ_ITEM);

	//pObj = new CTreasure("GEM_BLUE", 300,400, 20, 20);
	//((CTreasure*)pObj)->SetType(TREASURES_BLUE);
	//pObj->Initialize();
	//CObjMgr::GetInstance()->AddObject(pObj ,OBJ_ITEM);

	//pObj = new CTreasure("GEM_GREEN", 350,400, 27, 35);
	//((CTreasure*)pObj)->SetType(TREASURES_GREEN);
	//pObj->Initialize();
	//CObjMgr::GetInstance()->AddObject(pObj ,OBJ_ITEM);

	//pObj = new CTreasure("GEM_YELLOW", 400,400, 36, 25);
	//((CTreasure*)pObj)->SetType(TREASURES_YELLOW);
	//pObj->Initialize();
	//CObjMgr::GetInstance()->AddObject(pObj ,OBJ_ITEM);

	//pObj = new CTreasure("GEM_RED", 200,450, 52, 40);
	//((CTreasure*)pObj)->SetType(TREASURES_RED);
	//pObj->Initialize();
	//CObjMgr::GetInstance()->AddObject(pObj ,OBJ_ITEM);

	//pObj = new CTreasure("GEM_VIOLET", 300,450, 66, 50);
	//((CTreasure*)pObj)->SetType(TREASURES_VIOLET);
	//pObj->Initialize();
	//CObjMgr::GetInstance()->AddObject(pObj ,OBJ_ITEM);

	//pObj = new CPotion("POTION_APPLE", 300,100, 22, 20);
	//((CPotion*)pObj)->SetType(RECOVER_ITEM_APPLE);
	//pObj->Initialize();
	//CObjMgr::GetInstance()->AddObject(pObj ,OBJ_ITEM);

	//pObj = new CPotion("POTION_CARROT", 350,100, 63, 20);
	//((CPotion*)pObj)->SetType(RECOVER_ITEM_CARROT);
	//pObj->Initialize();
	//CObjMgr::GetInstance()->AddObject(pObj ,OBJ_ITEM);

	//pObj = new CPotion("POTION_CHICKEN", 400,100, 90, 60);
	//((CPotion*)pObj)->SetType(RECOVER_ITEM_CHICKEN);
	//pObj->Initialize();
	//CObjMgr::GetInstance()->AddObject(pObj ,OBJ_ITEM);

	//pObj = new CPotion("POTION_SMALL_MANA", 250,100, 16, 20);
	//((CPotion*)pObj)->SetType(RECOVER_ITEM_SMALL_MANA);
	//pObj->Initialize();
	//CObjMgr::GetInstance()->AddObject(pObj ,OBJ_ITEM);

	//pObj = new CPotion("POTION_TALL_MANA", 200,100, 30, 30);
	//((CPotion*)pObj)->SetType(RECOVER_ITEM_TALL_MANA);
	//pObj->Initialize();
	//CObjMgr::GetInstance()->AddObject(pObj ,OBJ_ITEM);

	//pObj = new CDirt("DIRT_SMALL", 400,460,48,48);
	//((CDirt*)pObj)->SetType(DIRT_SMALL);
	//pObj->Initialize();
	//CObjMgr::GetInstance()->AddObject(pObj ,OBJ_OTHER);

	//pObj = new CDirt("DIRT_BIG", 500,440,96,96);
	//((CDirt*)pObj)->SetType(DIRT_BIG);
	//pObj->Initialize();
	//CObjMgr::GetInstance()->AddObject(pObj ,OBJ_OTHER);

	//pObj = new CDirtPile("DIRTPILE", 100,300,110,55,50,0,0);
	//pObj->Initialize();
	//CObjMgr::GetInstance()->AddObject(pObj ,OBJ_OTHER);

	pObj = new CBord("MOVINGBORD", 5764,-320,144,48);
	pObj->Initialize();
	CObjMgr::GetInstance()->AddObject(pObj ,OBJ_OTHER);

	pObj = new CBord("MOVINGBORD", 6500,-120,144,48);
	pObj->Initialize();
	CObjMgr::GetInstance()->AddObject(pObj ,OBJ_OTHER);


	m_pUi = new CStateWindow("BORDER", 0,0, 800,50);
	m_pUi->Initialize();

	
	

	CObj::SetBitBmp(&m_mapBmp);
	CUi::SetBitBmp(&m_mapBmp);

	m_mapBmp.insert( make_pair("BACK_BUFFER", (new CBitBmp)->LoadBmp(L"../Resource/background/back_1.bmp") ) );
	m_mapBmp.insert( make_pair("BACK_GROUND", (new CBitBmp)->LoadBmp(L"../Resource/background/back_2.bmp") ) );
	m_mapBmp.insert( make_pair("BACK_CASTLE", (new CBitBmp)->LoadBmp(L"../Resource/background/castle.bmp") ) );
	m_mapBmp.insert( make_pair("TREE1", (new CBitBmp)->LoadBmp(L"../Resource/background/tree1.bmp") ) );
	m_mapBmp.insert( make_pair("TREE3", (new CBitBmp)->LoadBmp(L"../Resource/background/tree3.bmp") ) );
	m_mapBmp.insert( make_pair("TREE4", (new CBitBmp)->LoadBmp(L"../Resource/background/tree4.bmp") ) );

	m_mapBmp.insert( make_pair("KNIGHT_RIGHT", (new CBitBmp)->LoadBmp(L"../Resource/ShovelKnight_right_1.bmp") ) );
	m_mapBmp.insert( make_pair("KNIGHT_LEFT", (new CBitBmp)->LoadBmp(L"../Resource/ShovelKnight_left_1.bmp") ) );
	m_mapBmp.insert( make_pair("BLACK_KNIGHT_LEFT", (new CBitBmp)->LoadBmp(L"../Resource/enemy/stage1/Black_knight_left.bmp") ) );
	m_mapBmp.insert( make_pair("BLACK_KNIGHT_RIGHT", (new CBitBmp)->LoadBmp(L"../Resource/enemy/stage1/Black_knight_right.bmp") ) );

	m_mapBmp.insert( make_pair("BEETO", (new CBitBmp)->LoadBmp(L"../Resource/enemy/stage1/Beeto1.bmp") ) );
	m_mapBmp.insert( make_pair("BLORB", (new CBitBmp)->LoadBmp(L"../Resource/enemy/stage1/Blorb.bmp") ) );
	m_mapBmp.insert( make_pair("SKELETON", (new CBitBmp)->LoadBmp(L"../Resource/enemy/stage1/Skeleton.bmp") ) );
	m_mapBmp.insert( make_pair("DIVEDRAKE", (new CBitBmp)->LoadBmp(L"../Resource/enemy/stage1/Divedrake.bmp") ) );
	m_mapBmp.insert( make_pair("BUBBLE", (new CBitBmp)->LoadBmp(L"../Resource/enemy/stage1/Bubble.bmp") ) );
	m_mapBmp.insert( make_pair("BUBBLEDRAGON", (new CBitBmp)->LoadBmp(L"../Resource/enemy/stage1/BubbleDragon.bmp") ) );
	m_mapBmp.insert( make_pair("BLACKBALL", (new CBitBmp)->LoadBmp(L"../Resource/enemy/stage1/blackball.bmp") ) );

	m_mapBmp.insert( make_pair("TILE_1", (new CBitBmp)->LoadBmp(L"../Resource/Tile/Tile_1.bmp") ) );
	m_mapBmp.insert( make_pair("TILE_2", (new CBitBmp)->LoadBmp(L"../Resource/Tile/Tile_1_1.bmp") ) );


	m_mapBmp.insert( make_pair("BORDER", (new CBitBmp)->LoadBmp(L"../Resource/ui/border.bmp") ) );
	m_mapBmp.insert( make_pair("NUMBER",(new CBitBmp)->LoadBmp(L"../Resource/ui/number.bmp")));
	m_mapBmp.insert( make_pair("PLAYER_LIFE",(new CBitBmp)->LoadBmp(L"../Resource/ui/Player_life.bmp")));
	m_mapBmp.insert( make_pair("BOSS_LIFE",(new CBitBmp)->LoadBmp(L"../Resource/ui/Boss_life.bmp")));
	m_mapBmp.insert( make_pair("GEM_GRAY",(new CBitBmp)->LoadBmp(L"../Resource/Item/gems/gray.bmp")));
	m_mapBmp.insert( make_pair("GEM_BLUE",(new CBitBmp)->LoadBmp(L"../Resource/Item/gems/Blue.bmp")));
	m_mapBmp.insert( make_pair("GEM_GREEN",(new CBitBmp)->LoadBmp(L"../Resource/Item/gems/Green.bmp")));
	m_mapBmp.insert( make_pair("GEM_YELLOW",(new CBitBmp)->LoadBmp(L"../Resource/Item/gems/Yellow.bmp")));
	m_mapBmp.insert( make_pair("GEM_RED",(new CBitBmp)->LoadBmp(L"../Resource/Item/gems/Red.bmp")));
	m_mapBmp.insert( make_pair("GEM_VIOLET",(new CBitBmp)->LoadBmp(L"../Resource/Item/gems/Violet.bmp")));

	m_mapBmp.insert( make_pair("POTION_APPLE",(new CBitBmp)->LoadBmp(L"../Resource/Item/potion/apple.bmp")));
	m_mapBmp.insert( make_pair("POTION_CARROT",(new CBitBmp)->LoadBmp(L"../Resource/Item/potion/carrot.bmp")));
	m_mapBmp.insert( make_pair("POTION_CHICKEN",(new CBitBmp)->LoadBmp(L"../Resource/Item/potion/Chicken.bmp")));
	m_mapBmp.insert( make_pair("POTION_SMALL_MANA",(new CBitBmp)->LoadBmp(L"../Resource/Item/potion/mana_small.bmp")));
	m_mapBmp.insert( make_pair("POTION_TALL_MANA",(new CBitBmp)->LoadBmp(L"../Resource/Item/potion/mana_tall.bmp")));

	m_mapBmp.insert( make_pair("DIRT_SMALL",(new CBitBmp)->LoadBmp(L"../Resource/obj/Dirt_small.bmp")));
	m_mapBmp.insert( make_pair("DIRT_BIG",(new CBitBmp)->LoadBmp(L"../Resource/obj/Dirt_big.bmp")));
	m_mapBmp.insert( make_pair("DIRTPILE",(new CBitBmp)->LoadBmp(L"../Resource/obj/DirtPile.bmp")));
	m_mapBmp.insert( make_pair("MOVINGBORD",(new CBitBmp)->LoadBmp(L"../Resource/obj/MovingBord.bmp")));


	m_mapBmp.insert( make_pair("POOFS",(new CBitBmp)->LoadBmp(L"../Resource/Effect/poofs.bmp")));
	m_mapBmp.insert( make_pair("MPOOFS_B",(new CBitBmp)->LoadBmp(L"../Resource/Effect/Mpoofs_b.bmp")));
	m_mapBmp.insert( make_pair("MPOOFS_S",(new CBitBmp)->LoadBmp(L"../Resource/Effect/Mpoofs_s.bmp")));
	m_mapBmp.insert( make_pair("PICES",(new CBitBmp)->LoadBmp(L"../Resource/Effect/dirtPilePices.bmp")));
	m_mapBmp.insert( make_pair("SPAK",(new CBitBmp)->LoadBmp(L"../Resource/Effect/downThrustSpak.bmp")));
	m_mapBmp.insert( make_pair("PICKUP_SPARKLE",(new CBitBmp)->LoadBmp(L"../Resource/Item/pickupSparklePal.bmp")));

	char  szTemp[128];		//재생.
	TCHAR szTemp2[128];		//재생.strcpy(szTemp2, L"Shovel Knight OST - Strike the Earth! Plains of Passage");

	CSoundMgr::GetInstance()->PlayBGMSound(L"Shovel Knight OST - Strike the Earth! Plains of Passage.mp3");

}

int CStage::Progress(void)
{

	KeyCheck();
	Scrolling();
	CObjMgr::GetInstance()->Progress();
	CTileMgr::GetInstance()->SetScroll(((CPlayer*)(*(CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].begin())))->GetScroll());
	CTileMgr::GetInstance()->Progress();
	m_pUi->Progress();
	CreateObjectCheck();
	

	return 0;
}

void CStage::Render(HDC _hdc)
{
	OBJ_ITER iter= CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].begin();


		((CBackground*)m_pBack)->Render(m_mapBmp["BACK_BUFFER"]->GetMemDC());
	((CBackground*)m_pBack1)->Render2(m_mapBmp["BACK_BUFFER"]->GetMemDC());
	((CBackground*)m_pBack2)->Render2(m_mapBmp["BACK_BUFFER"]->GetMemDC());
	((CBackground*)m_pBack4)->Render2(m_mapBmp["BACK_BUFFER"]->GetMemDC());
	((CBackground*)m_pBack3)->Render2(m_mapBmp["BACK_BUFFER"]->GetMemDC());
	

	//CTileMgr::GetInstance()->Render_Back(m_mapBmp["BACK_BUFFER"]->GetMemDC(),m_mapBmp["TILE_2"]->GetMemDC());
	

	CTileMgr::GetInstance()->Render_Back(m_mapBmp["BACK_BUFFER"]->GetMemDC(),m_mapBmp["TILE_2"]->GetMemDC());
	CObjMgr::GetInstance()->Render(m_mapBmp["BACK_BUFFER"]->GetMemDC());
	CTileMgr::GetInstance()->Render(m_mapBmp["BACK_BUFFER"]->GetMemDC(),m_mapBmp["TILE_2"]->GetMemDC());
	



	if( m_bShowRect == true)
	{
		OBJ_ITER iter=CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].begin();
		OBJ_ITER iter_end=CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].end();

		for( iter ; iter != iter_end ; ++iter)
		{
			HPEN MyBrush1, OldBrush1;
			MyBrush1 = (HPEN)CreatePen(0,5,(RGB(255,0,255)));
			OldBrush1 = (HPEN)SelectObject(m_mapBmp["BACK_BUFFER"]->GetMemDC(), MyBrush1);
			Rectangle(m_mapBmp["BACK_BUFFER"]->GetMemDC(), 
				static_cast<int>( (*iter)->GetBodyBox()->m_fX - (*iter)->GetBodyBox()->m_fCX/2 )+ (*iter)->GetScroll().x, 
				static_cast<int>( (*iter)->GetBodyBox()->m_fY - (*iter)->GetBodyBox()->m_fCY/2)+ (*iter)->GetScroll().y,
				static_cast<int>((*iter)->GetBodyBox()->m_fX + (*iter)->GetBodyBox()->m_fCX/2)+ (*iter)->GetScroll().x,
				static_cast<int>((*iter)->GetBodyBox()->m_fY + (*iter)->GetBodyBox()->m_fCY/2)+ (*iter)->GetScroll().y);
			SelectObject(m_mapBmp["BACK_BUFFER"]->GetMemDC(), GetStockObject(NULL_BRUSH));
			DeleteObject(MyBrush1);

			// 무기 박스

			MyBrush1 = (HPEN)CreatePen(0,0,(RGB(0,54,255)));
			OldBrush1 = (HPEN)SelectObject(m_mapBmp["BACK_BUFFER"]->GetMemDC(), MyBrush1);
			Rectangle(m_mapBmp["BACK_BUFFER"]->GetMemDC(),
				(*iter)->GetAttackRect().left   + (*iter)->GetScroll().x,
				(*iter)->GetAttackRect().top    + (*iter)->GetScroll().y, 
				(*iter)->GetAttackRect().right  + (*iter)->GetScroll().x,
				(*iter)->GetAttackRect().bottom + (*iter)->GetScroll().y);
			SelectObject(m_mapBmp["BACK_BUFFER"]->GetMemDC(), GetStockObject(NULL_BRUSH));
			DeleteObject(MyBrush1);
		}
			iter=CObjMgr::GetInstance()->GetList()[OBJ_BULLET].begin();
			iter_end=CObjMgr::GetInstance()->GetList()[OBJ_BULLET].end();
			for( iter ; iter != iter_end ; ++iter)
		{
			HPEN MyBrush1, OldBrush1;
			MyBrush1 = (HPEN)CreatePen(0,5,(RGB(255,0,255)));
			OldBrush1 = (HPEN)SelectObject(m_mapBmp["BACK_BUFFER"]->GetMemDC(), MyBrush1);
			Rectangle(m_mapBmp["BACK_BUFFER"]->GetMemDC(), 
				static_cast<int>( (*iter)->GetBodyBox()->m_fX - (*iter)->GetBodyBox()->m_fCX/2 )+ (*iter)->GetScroll().x, 
				static_cast<int>( (*iter)->GetBodyBox()->m_fY - (*iter)->GetBodyBox()->m_fCY/2)+ (*iter)->GetScroll().y,
				static_cast<int>((*iter)->GetBodyBox()->m_fX + (*iter)->GetBodyBox()->m_fCX/2)+ (*iter)->GetScroll().x,
				static_cast<int>((*iter)->GetBodyBox()->m_fY + (*iter)->GetBodyBox()->m_fCY/2)+ (*iter)->GetScroll().y);
			SelectObject(m_mapBmp["BACK_BUFFER"]->GetMemDC(), GetStockObject(NULL_BRUSH));
			DeleteObject(MyBrush1);

			// 무기 박스

			MyBrush1 = (HPEN)CreatePen(0,0,(RGB(0,54,255)));
			OldBrush1 = (HPEN)SelectObject(m_mapBmp["BACK_BUFFER"]->GetMemDC(), MyBrush1);
			Rectangle(m_mapBmp["BACK_BUFFER"]->GetMemDC(),
				(*iter)->GetAttackRect().left   + (*iter)->GetScroll().x,
				(*iter)->GetAttackRect().top    + (*iter)->GetScroll().y, 
				(*iter)->GetAttackRect().right  + (*iter)->GetScroll().x,
				(*iter)->GetAttackRect().bottom + (*iter)->GetScroll().y);
			SelectObject(m_mapBmp["BACK_BUFFER"]->GetMemDC(), GetStockObject(NULL_BRUSH));
			DeleteObject(MyBrush1);
		}
	}

	((CStateWindow*)m_pUi)->Render(m_mapBmp["BACK_BUFFER"]->GetMemDC());

	BitBlt(_hdc, 
		0, 0, 
		800, 600,
		m_mapBmp["BACK_BUFFER"]->GetMemDC(),
		0,0,
		SRCCOPY);
}

void CStage::Release(void)
{
	map<string, CBitBmp*>::iterator iter = m_mapBmp.begin();
	map<string, CBitBmp*>::iterator iter_end = m_mapBmp.end();

	for( iter ; iter != iter_end ; ++iter)
	{
		delete (*iter).second;
	}
	m_mapBmp.clear();

	
	CSoundMgr::GetInstance()->StopBGM();

}

void CStage::KeyCheck(void)
{
	if(GetAsyncKeyState(VK_F2) & 1)
	{
		if(m_bShowRect == false)
			m_bShowRect = true;
		else
			m_bShowRect = false;
	}
}
void CStage::Scrolling(void)
{
	OBJ_ITER iter= CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].begin();
	POINT Map;
	if ( (*iter)->GetInfo()->m_fX >= CObj::m_ptMapSize.x )
	{
		
			
		if( (*iter)->GetInfo()->m_fX > 8000)
		{
			Map.x = (*iter)->GetScroll().x-800 ;
			Map.y = (*iter)->GetScroll().y+100;
		}
		else
		{
		Map.x = (*iter)->GetScroll().x-800 ;
		Map.y = (*iter)->GetScroll().y;
		}
		(*iter)->SetScroll(Map);
	/*	(*iter)->SetPos((*iter)->GetInfo()->m_fX+2 ,(*iter)->GetInfo()->m_fY);
		(*iter)->SetBodyPos((*iter)->GetBodyBox()->m_fX+2 ,(*iter)->GetBodyBox()->m_fY);*/
		((CPlayer*)(*iter))->Setm_MapSize(CObj::m_ptMapSize.x);
		if( (*iter)->GetScroll().y !=0)
		((CPlayer*)(*iter))->SetMapsize( (*iter)->GetMapsize().x+800, (*iter)->GetMapsize().y);
		else
		((CPlayer*)(*iter))->SetMapsize( (*iter)->GetMapsize().x+2100, (*iter)->GetMapsize().y);
		
	}
	if ( (*iter)->GetInfo()->m_fY <= 0 && (*iter)->GetScroll().y==0  &&   (*iter)->GetDwState() == STATE_LADDER)
	{
		
			

		Map.x = (*iter)->GetScroll().x ;
		Map.y = (*iter)->GetScroll().y+600;
		(*iter)->SetScroll(Map);
	
		((CPlayer*)(*iter))->Setm_MapSize(CObj:: m_ptMapSize.x - g_iWINCX / 2);
		((CPlayer*)(*iter))->SetMapsize( (*iter)->GetMapsize().x+800, (*iter)->GetMapsize().y);
		
	}
	if ( (*iter)->GetInfo()->m_fY >= 0 && (*iter)->GetScroll().y==600  &&   (*iter)->GetDwState() == STATE_LADDER)
	{
		
			

		Map.x = (*iter)->GetScroll().x ;
		Map.y = (*iter)->GetScroll().y-580;
		(*iter)->SetScroll(Map);
	
		((CPlayer*)(*iter))->Setm_MapSize(CObj:: m_ptMapSize.x - g_iWINCX / 2);
		((CPlayer*)(*iter))->SetMapsize( (*iter)->GetMapsize().x+800, (*iter)->GetMapsize().y);
		
	}

}
void CStage::CreateObjectCheck(void)
{
	OBJ_ITER iter= CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].begin();

	if( ((CPlayer*)(*iter))->GetInfo()->m_fX >= 5100 && ((CPlayer*)(*iter))->GetInfo()->m_fX <= 6000)
	{
			//몬스터를 검사해서 버블이 있다면 생성하지 말고 없다면 생성한다.
			OBJ_ITER iter_mon= CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].begin();
			OBJ_ITER iter_mon_end= CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].end();
			for( iter_mon ; iter_mon != iter_mon_end ; ++iter_mon)
			{
				if( typeid(*(*iter_mon)) == typeid(CBubble))
						break;
			}
			if( iter_mon == CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].end() )
			{
				CObj* pObj = new CBubble("BUBBLE",5668,700,100,100,10);
				pObj->Initialize();
				CObjMgr::GetInstance()->AddObject(pObj, OBJ_MONSTER);
				m_bCreate =true;
			}
			else
				m_bCreate =false;
		
		
	}
	if( ((CPlayer*)(*iter))->GetInfo()->m_fX >= 7600 && ((CPlayer*)(*iter))->GetInfo()->m_fX <= 8200)
	{
	 //초록색 드레이크가 제대로 생성이 안된다. 맵 앞쪽에서 이미 생성되어 있기 때문이다.
		//고쳐라

			//몬스터를 검사해서 버블이 있다면 생성하지 말고 없다면 생성한다.
			OBJ_ITER iter_mon= CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].begin();
			OBJ_ITER iter_mon_end= CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].end();
			for( iter_mon ; iter_mon != iter_mon_end ; ++iter_mon)
			{
				if( typeid(*(*iter_mon)) == typeid(CBubble))
				{
					break;
				}
						
			}
			if( iter_mon == CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].end() )
			{
				CObj* pObj = new CBubble("BUBBLE",8000,0,100,100,10);
				pObj->Initialize();
				CObjMgr::GetInstance()->AddObject(pObj, OBJ_MONSTER);
				
				 pObj = new CBubble("BUBBLE",8100,0,100,100,10);
				pObj->Initialize();
				CObjMgr::GetInstance()->AddObject(pObj, OBJ_MONSTER);
			}

			

			iter_mon= CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].begin();
			iter_mon_end= CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].end();
			for( iter_mon ; iter_mon != iter_mon_end ; ++iter_mon)
			{
				if( typeid(*(*iter_mon)) == typeid(CDivedrake))
				{
					break;
				}
						
			}
			if( m_bCreate == false)
			{
			if( iter_mon == CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].end() )
			{
				CObj* pObj = new CDivedrake("DIVEDRAKE",8200,-300,150,150,10,0,10);
				pObj->Initialize();
				((CDivedrake*)pObj)->SetPattern(1);
				CObjMgr::GetInstance()->AddObject(pObj, OBJ_MONSTER);
				
			}
			}
		
			m_bCreate =true;
			
			
		
	}
		if( ((CPlayer*)(*iter))->GetInfo()->m_fX >= 8500 && ((CPlayer*)(*iter))->GetInfo()->m_fX <= 8600)
		{
			if(m_bCreate ==true)
			{
				
				CSoundMgr::GetInstance()->PlayBGMSound(L"Shovel Knight OST - The Rival (Black Knight - First Battle).mp3");
				m_bCreate =false;
			}
		}
}