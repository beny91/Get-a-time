#include "StdAfx.h"
#include "MapEdit.h"
#include "Obj.h"
#include "Mouse.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "Background.h"
#include "TileMgr.h"
#include "Dirt.h"
#include "DirtPile.h"
#include "Bord.h"
#include "SceneMgr.h"

CMapEdit::CMapEdit(void)
{
}

CMapEdit::~CMapEdit(void)
{
	Release();
}


void CMapEdit::Initialize(void)
{
	m_iType=0; //Ÿ�� ���� ������Ʈ���� üũ
	m_iDrawID = 0;
	m_iImage  =0;
	m_iOption =0;
	m_iStage  =0;
	m_eStage =STAGE_1;
	m_strStageName ="TILE_2";

	memset(&m_ptScroll, 0, sizeof(POINT));

	//CTileMgr::GetInstance()->SetScroll(&m_ptScroll);
	//CTileMgr::GetInstance()->SetDrawID(&m_iDrawID);
	CObj::SetBitBmp(&m_mapBmp);

	m_mapBmp.insert( make_pair("BACK_BUFFER", (new CBitBmp)->LoadBmp(L"../Resource/background/back_1.bmp") ) );
	m_mapBmp.insert( make_pair("BACK_GROUND", (new CBitBmp)->LoadBmp(L"../Resource/background/back_2.bmp") ) );
	m_mapBmp.insert( make_pair("BACK_CASTLE", (new CBitBmp)->LoadBmp(L"../Resource/background/castle.bmp") ) );
	m_mapBmp.insert( make_pair("TREE1", (new CBitBmp)->LoadBmp(L"../Resource/background/tree1.bmp") ) );
	m_mapBmp.insert( make_pair("TREE3", (new CBitBmp)->LoadBmp(L"../Resource/background/tree3.bmp") ) );
	m_mapBmp.insert( make_pair("TREE4", (new CBitBmp)->LoadBmp(L"../Resource/background/tree4.bmp") ) );

	m_mapBmp.insert( make_pair("DIRT_SMALL",(new CBitBmp)->LoadBmp(L"../Resource/obj/Dirt_small.bmp")));
	m_mapBmp.insert( make_pair("DIRT_BIG",(new CBitBmp)->LoadBmp(L"../Resource/obj/Dirt_big.bmp")));
	m_mapBmp.insert( make_pair("DIRTPILE",(new CBitBmp)->LoadBmp(L"../Resource/obj/DirtPile.bmp")));
	m_mapBmp.insert( make_pair("MOVINGBORD",(new CBitBmp)->LoadBmp(L"../Resource/obj/MovingBord.bmp")));

	m_mapBmp.insert( make_pair("TILE_1", (new CBitBmp)->LoadBmp(L"../Resource/Tile/Tile_1.bmp") ) );
	m_mapBmp.insert( make_pair("TILE_2", (new CBitBmp)->LoadBmp(L"../Resource/Tile/Tile_1_1.bmp") ) );


	//��׶��� ����
	CObj* pObj= new CBackground("BACK_GROUND",0 ,0,static_cast<float>(g_iWINCX), static_cast<float>(g_iWINCY));
	CObjMgr::GetInstance()->AddObject(pObj , OBJ_BACKGROUND );

	pObj = new CBackground("BACK_CASTLE",0 ,0,static_cast<float>(1200), static_cast<float>(g_iWINCY));
	((CBackground*)pObj)->SetScrollSpeed(10);
	CObjMgr::GetInstance()->AddObject(pObj , OBJ_BACKGROUND );

	pObj= new CBackground("TREE1",0 ,0,static_cast<float>(2000), static_cast<float>(g_iWINCY));
	((CBackground*)pObj)->SetScrollSpeed(6);
	CObjMgr::GetInstance()->AddObject(pObj , OBJ_BACKGROUND );

	pObj= new CBackground("TREE4",0 ,0,static_cast<float>(2500), static_cast<float>(g_iWINCY));
	((CBackground*)pObj)->SetScrollSpeed(2);
	CObjMgr::GetInstance()->AddObject(pObj , OBJ_BACKGROUND );

	pObj= new CBackground("TREE3",0 ,0,static_cast<float>(3000), static_cast<float>(600));
	((CBackground*)pObj)->SetScrollSpeed(3);
	CObjMgr::GetInstance()->AddObject(pObj , OBJ_BACKGROUND );

	//	m_pBack= new CBackground("BACK_GROUND",0 ,0,static_cast<float>(g_iWINCX), static_cast<float>(g_iWINCY));
	////CObjMgr::GetInstance()->AddObject(pObj , OBJ_BACKGROUND );
	//m_pBack1 = new CBackground("BACK_CASTLE",0 ,0,static_cast<float>(1200), static_cast<float>(g_iWINCY));
	//((CBackground*)m_pBack1)->SetScrollSpeed(10);
	//m_pBack2= new CBackground("TREE1",0 ,0,static_cast<float>(2000), static_cast<float>(g_iWINCY));
	//((CBackground*)m_pBack2)->SetScrollSpeed(6);
	//m_pBack3= new CBackground("TREE3",0 ,0,static_cast<float>(2750), static_cast<float>(550));
	//((CBackground*)m_pBack3)->SetScrollSpeed(4);
	//	m_pBack4= new CBackground("TREE4",0 ,0,static_cast<float>(2500), static_cast<float>(g_iWINCY));
	//((CBackground*)m_pBack4)->SetScrollSpeed(2);
	////



}

int CMapEdit::Progress(void)
{

	CTileMgr::GetInstance()->SetScroll(m_ptScroll);
	CTileMgr::GetInstance()->Progress();
	POINT ptMouse = CMouse::GetMousePos();
	DWORD dwKey = CKeyMgr::GetInstance()->GetKeyState();

#ifdef _DEBUG_TYPE_
	system("cls");
	cout<<"m_iDrawID : " << m_iDrawID <<endl;
	cout<<"m_iOption : " << m_iOption <<endl;
	cout<<" m_iImage : " <<m_iImage <<endl;
#endif
	if(dwKey & KEY_LEFT)
	{
		m_ptScroll.x += 10;
	}

	if(dwKey & KEY_RIGHT)
	{
		m_ptScroll.x -= 10;
	}

	if(dwKey & KEY_UP)
	{
		m_ptScroll.y += 10;
		OBJ_ITER iter = CObjMgr::GetInstance()->GetList()[OBJ_BACKGROUND].begin();
	OBJ_ITER iter_end = CObjMgr::GetInstance()->GetList()[OBJ_BACKGROUND].end();

	for( iter ; iter != iter_end ; ++iter)
	{
		(*iter)->GetInfo()->m_fY-=10;
	}

	}

	if(dwKey & KEY_DOWN)
	{
		m_ptScroll.y -= 10;
			OBJ_ITER iter = CObjMgr::GetInstance()->GetList()[OBJ_BACKGROUND].begin();
	OBJ_ITER iter_end = CObjMgr::GetInstance()->GetList()[OBJ_BACKGROUND].end();

	for( iter ; iter != iter_end ; ++iter)
	{
		(*iter)->GetInfo()->m_fY+=10;
	}
	}

	if(m_iType ==0)
	{
		if(dwKey & KEY_LBUTTON) //����Ÿ���� ����
		{
			//�ش� Ÿ���� ������.

			POINT pIndex;
			pIndex.x= (ptMouse.x - m_ptScroll.x) ;
			pIndex.y= (ptMouse.y - m_ptScroll.y);

			CTileMgr::GetInstance()->DrawTile(m_iDrawID,m_ptScroll,pIndex,m_iImage);
		}
		if(GetAsyncKeyState(VK_RBUTTON) ) //�浹Ÿ���� ����
		{
			POINT pIndex;
			pIndex.x= (ptMouse.x - m_ptScroll.x) ;
			pIndex.y= (ptMouse.y - m_ptScroll.y);

			CTileMgr::GetInstance()->DrawTile(m_iDrawID,m_ptScroll,pIndex,3,m_iOption);
		}

		if(GetAsyncKeyState('1') & 1)//��������Ʈ X
		{
			m_iDrawID+= 1;
			if(m_iDrawID>22)
				m_iDrawID=1;
		}

		if(GetAsyncKeyState('2') & 1)
		{
			m_iDrawID -= 1;
		}
		if(GetAsyncKeyState('3') & 1)//��������Ʈ y
		{
			m_iImage += 1;
			if(m_iImage >3)
				m_iImage =0;
		}
		if(GetAsyncKeyState('4') & 1) 
		{
			m_iImage -= 1;
			if(m_iImage <0)
				m_iImage=1;
		}
		if(GetAsyncKeyState('5') & 1) //�ɼ� ���� �÷��� ����Ÿ������ �浹Ÿ������ ����
		{
			m_iOption +=1;

			if(m_iOption == 6)
				m_iOption=0;
		}
		if(GetAsyncKeyState('6') & 1)   //���������� üũ�Ͽ� Ÿ�� ���� �����Ѵ�.
		{

			m_iStage+=1;
			m_eStage=(eSTAGE_TYPE)m_iStage;

			if( m_eStage == STAGE_End )
			{
				m_eStage = STAGE_1;
				m_iStage = 0;
			}
			CheckStage(m_eStage);  //m_iStage �� üũ�Ͽ� strname�� Ÿ���̸��� �ٲپ� �ش�.

		}
	}
	else //������Ʈ �κ��� ��´�.
	{
		CObj* pObj;
		if(GetAsyncKeyState('1') & 1)//��������Ʈ X
		{
			m_iDrawID+= 1;
			if(m_iDrawID>3)
				m_iDrawID=0;
		}
		if(GetAsyncKeyState(VK_LBUTTON) & 1 ) //����Ÿ���� ����
		{
			//�ش� Ÿ���� ������.

		
			
			if( m_iDrawID ==0)
			{
					POINT pIndex;
				pIndex.x= ((ptMouse.x - m_ptScroll.x ) /48)*48 ;
				pIndex.y= ((ptMouse.y - m_ptScroll.y) /48)*48;

			pObj = new CDirt("DIRT_SMALL",static_cast<float>(pIndex.x + 48/2),static_cast<float>(pIndex.y + 48/2),48,48);
			((CDirt*)pObj)->SetType(DIRT_SMALL);
			pObj->Initialize();
			CObjMgr::GetInstance()->AddObject(pObj,OBJ_OTHER);
			}
			else if( m_iDrawID ==1)
			{
					POINT pIndex;
				pIndex.x= ((ptMouse.x - m_ptScroll.x ) /96)*96 ;
				pIndex.y= ((ptMouse.y - m_ptScroll.y) /96)*96;
			pObj = new CDirt("DIRT_BIG",static_cast<float>(pIndex.x +96/2),static_cast<float>(pIndex.y +96/2),96,96);
			((CDirt*)pObj)->SetType(DIRT_BIG);
			pObj->Initialize();
			CObjMgr::GetInstance()->AddObject(pObj,OBJ_OTHER);
			}
			else if( m_iDrawID ==2)
			{
					POINT pIndex;
				pIndex.x= ((ptMouse.x - m_ptScroll.x ) /110)*110 ;
				pIndex.y= ((ptMouse.y - m_ptScroll.y) /55)*55;
			pObj = new CDirtPile("DIRTPILE",static_cast<float>(pIndex.x +110/2),static_cast<float>(pIndex.y+20 ),110,55,50,0,0);
			((CDirtPile*)pObj)->Initialize();
			CObjMgr::GetInstance()->AddObject(pObj,OBJ_OTHER);
			}
			else
			{
					POINT pIndex;
				pIndex.x= ((ptMouse.x - m_ptScroll.x ) /144)*144 ;
				pIndex.y= ((ptMouse.y - m_ptScroll.y) /48)*48;
			pObj = new CBord("MOVINGBORD",static_cast<float>(pIndex.x +144/2),static_cast<float>(pIndex.y + 48/2 ),144,48);
			((CBord*)pObj)->Initialize();
			CObjMgr::GetInstance()->AddObject(pObj,OBJ_OTHER);
			}
			
		}
	}
	if(GetAsyncKeyState('Q') & 1)
	{
		if( m_iType == 0)
			m_iType =1;
		else
			m_iType =0;
	}

	if(GetAsyncKeyState('S') & 1)
	{
		CTileMgr::GetInstance()->SaveTile();
		CObjMgr::GetInstance()->SaveObj();
		MessageBox(g_hWnd, L"���� �Ϸ�!", L"Ÿ�� ����", 0);
	}

	if(GetAsyncKeyState('L') & 1)
	{
		CTileMgr::GetInstance()->LoadTile();
		CObjMgr::GetInstance()->LoadObj();
		MessageBox(g_hWnd, L"�ε� �Ϸ�!", L"Ÿ�� �ε�", 0);
	}
	
	if(GetAsyncKeyState(VK_F12) & 1)
	{
		CSceneMgr::GetInstance()->SetChangeScene(SCENE_GAMEMENU);
	}

	return 0;
}

void CMapEdit::Render(HDC _hdc)
{
	//��׶��� ����

	OBJ_ITER iter = CObjMgr::GetInstance()->GetList()[OBJ_BACKGROUND].begin();
	OBJ_ITER iter_end = CObjMgr::GetInstance()->GetList()[OBJ_BACKGROUND].end();

	POINT TempScroll;
	TempScroll.x = m_ptScroll.x;
	TempScroll.y = m_ptScroll.y;
	
	for( iter ; iter != iter_end ; ++iter)
	{
		(*iter)->SetScroll(TempScroll);
		if( ((CBackground*)(*iter))->GetName()=="BACK_GROUND") //��׶���� RGB���� ���� �ʴ´�.
		{
			((CBackground*)(*iter))->Render2(m_mapBmp["BACK_BUFFER"]->GetMemDC());
		}
		else
		{
			((CBackground*)(*iter))->Render2(m_mapBmp["BACK_BUFFER"]->GetMemDC());
		}
	}


	//CObjMgr::GetInstance()->Render(m_mapBmp["BACK_BUFFER"]->GetMemDC());
	//Ÿ�� �Ŵ��� ����
	CTileMgr::GetInstance()->Render_Back(m_mapBmp["BACK_BUFFER"]->GetMemDC(), m_mapBmp[m_strStageName.data()]->GetMemDC());
	CTileMgr::GetInstance()->Render(m_mapBmp["BACK_BUFFER"]->GetMemDC(), m_mapBmp[m_strStageName.data()]->GetMemDC());
	//������Ʈ ����
	OBJ_ITER iter_other = CObjMgr::GetInstance()->GetList()[OBJ_OTHER].begin();//
	OBJ_ITER iter_other_end = CObjMgr::GetInstance()->GetList()[OBJ_OTHER].end();

	for( iter_other ; iter_other != iter_other_end ; ++iter_other)
	{
		if( typeid(*(*iter_other)) == typeid(CDirt) )
			((CDirt*)(*iter_other))->Render(m_mapBmp["BACK_BUFFER"]->GetMemDC());
		else
			((CDirtPile*)(*iter_other))->Render(m_mapBmp["BACK_BUFFER"]->GetMemDC());
		
	}
	//Ÿ�� �� ��� ������ ���̴°�
	POINT ptMouse = CMouse::GetMousePos();

	if( m_iType ==0)
	{
		if(m_iOption ==0)
		{
			BitBlt(m_mapBmp["BACK_BUFFER"]->GetMemDC(), 
				ptMouse.x, ptMouse.y, 
				g_iTileCX,  g_iTileCY,
				m_mapBmp[m_strStageName.data()]->GetMemDC(), m_iDrawID* g_iTileCX,
				m_iImage *g_iTileCY,
				SRCCOPY);
		}
		else if(m_iOption !=0) //������ �� ���� Ÿ���� ǥ���Ѵ�.
		{

			HPEN MyBrush, OldBrush;
			if( m_iOption == 1) // 4���� �浹�� üũ�ϴ� Ÿ���� ��Ÿ���� 
				MyBrush = (HPEN)CreatePen(4,5,(RGB(255,0,0))); // ����
			else if( m_iOption  ==2 ) //���κи� �浹�ϴ� ��Ʈ
				MyBrush = (HPEN)CreatePen(4,5,(RGB(255,255,0))); //����
			else if( m_iOption  ==3 ) //���Ʒ� �浹�ϴ� ��Ʈ
				MyBrush = (HPEN)CreatePen(4,5,(RGB(255,255,255))); //����
			else if( m_iOption  ==4 ) // ��ٸ�
				MyBrush = (HPEN)CreatePen(4,5,(RGB(255,0,255))); //����
			else if( m_iOption  ==5 ) // �浹���ϴ� ��Ʈ
				MyBrush = (HPEN)CreatePen(4,5,(RGB(0,255,255))); //����

			OldBrush = (HPEN)SelectObject(m_mapBmp["BACK_BUFFER"]->GetMemDC(), MyBrush);
			Rectangle(m_mapBmp["BACK_BUFFER"]->GetMemDC(), ptMouse.x, ptMouse.y, ptMouse.x + g_iTileCX, ptMouse.y + g_iTileCY);
			SelectObject(m_mapBmp["BACK_BUFFER"]->GetMemDC(), GetStockObject(NULL_BRUSH));
			DeleteObject(MyBrush);


		}
	}
	else //������Ʈ�� �ִ� ���๰���� �����ش�.
	{
		if(m_iDrawID == 0)
		{
			BitBlt(m_mapBmp["BACK_BUFFER"]->GetMemDC(), 
				ptMouse.x, ptMouse.y, 
				48,  48,
				m_mapBmp["DIRT_SMALL"]->GetMemDC(),
				0,
				0,
				SRCCOPY);
		}
		else if( m_iDrawID == 1)
		{
			BitBlt(m_mapBmp["BACK_BUFFER"]->GetMemDC(), 
				ptMouse.x, ptMouse.y, 
				96,  96,
				m_mapBmp["DIRT_BIG"]->GetMemDC(),
				0,
				0,
				SRCCOPY);
		}
		else if( m_iDrawID ==2)
		{
			BitBlt(m_mapBmp["BACK_BUFFER"]->GetMemDC(), 
				ptMouse.x, ptMouse.y, 
				110,  55,
				m_mapBmp["DIRTPILE"]->GetMemDC(),
				0,
				0,
				SRCCOPY);
		}
		else if( m_iDrawID ==3)
		{
				BitBlt(m_mapBmp["BACK_BUFFER"]->GetMemDC(), 
				ptMouse.x, ptMouse.y, 
				144,  48,
				m_mapBmp["MOVINGBORD"]->GetMemDC(),
				0,
				0,
				SRCCOPY);
		}
	}
	//���ۿ� �׸��� ������ â���� �ø��°�
	BitBlt(_hdc, 
		0, 0, 
		800, 600,
		m_mapBmp["BACK_BUFFER"]->GetMemDC(),
		0,0,
		SRCCOPY);


}

void CMapEdit::Release(void)
{
	

	
	

	for(size_t i = 0; i < OBJ_END; ++i)
	{
		OBJ_ITER iter = CObjMgr::GetInstance()->GetList()[i].begin();
		OBJ_ITER iter_end = CObjMgr::GetInstance()->GetList()[i].end();

		for(iter; iter != iter_end; ++iter)
		{
			delete (*iter) ;
		}
	}
	CObjMgr::GetInstance()->GetList()->clear();
	CObjMgr::GetInstance()->Destroy();

	vector<TILE*>::iterator iter = CTileMgr::GetInstance()->GetvecTile()->begin();
	vector<TILE*>::iterator iter_end = CTileMgr::GetInstance()->GetvecTile()->end();

	for( iter ; iter != iter_end ; ++iter)
	{
		delete *iter;
	}
	CTileMgr::GetInstance()->GetvecTile()->clear();

	iter = CTileMgr::GetInstance()->GetvecTileBack()->begin();
	iter_end = CTileMgr::GetInstance()->GetvecTileBack()->end();

	for( iter ; iter != iter_end ; ++iter)
	{
		delete *iter;
	}
	CTileMgr::GetInstance()->GetvecTileBack()->clear();
}



void CMapEdit::CheckStage(eSTAGE_TYPE _eStage)
{
	switch(_eStage)
	{
	case STAGE_1:
		m_strStageName = "TILE_1";
		break;
	case STAGE_2:
		m_strStageName = "TILE_2";
		break;
	}
}