#include "StdAfx.h"
#include "TileMgr.h"
#include "Mouse.h"

CTileMgr* CTileMgr::m_pInstance;
CTileMgr::CTileMgr(void)
{
}

CTileMgr::~CTileMgr(void)
{
}

void CTileMgr::Initialize(void)
{
	m_bShowRect=false;
}
int  CTileMgr::Progress(void)
{
	if(GetAsyncKeyState(VK_F3) & 1 )
	{
		if(m_bShowRect==true)
			m_bShowRect=false;
		else
			m_bShowRect=true;
	}	
	return 0;
}

void CTileMgr::Release(void)
{
	vector<TILE*>::iterator iter=m_vecTile.begin();
	vector<TILE*>::iterator iter_end=m_vecTile.end();

	for( iter ; iter != iter_end ; ++iter)
	{
		delete *iter;
	}
	m_vecTile.clear();


}

void CTileMgr::DrawTile(int _DrawID, POINT m_ptScroll , POINT _Index, int _iImage, int _iOption )
{
	POINT ptMouse = CMouse::GetMousePos();

	//Ÿ���� 64 * 64�� �������� �������ش�.
ptMouse.x = ((ptMouse.x - m_ptScroll.x) /g_iTileCX)*g_iTileCX;
	ptMouse.y = ((ptMouse.y - m_ptScroll.y) /g_iTileCY)*g_iTileCY;




	

	if( _iImage > 1)
	{
		vector<TILE*>::iterator iter=m_vecTile.begin();
	vector<TILE*>::iterator iter_end=m_vecTile.end();

		for( iter ; iter != iter_end ; ++iter)
		{

			if( _iOption != 0) //���� Ÿ���� �浹üũ Ÿ���϶� 
			{
				if( (*iter)->m_fX == ptMouse.x + g_iTileCX/2   // ��ġ�� ���ٸ�
					&& (*iter)->m_fY == ptMouse.y + g_iTileCY/2 )
				{

					if( (*iter)->m_iOption == 0 ) // �� Ÿ���� �浹Ÿ���� �ƴҶ�
					{
						/*(*iter)->m_iDrawID=_DrawID;
						(*iter)->m_iImage=_iImage;
						(*iter)->m_iOption = _iOption;*/
					}
					else // �浹üũ Ÿ���� �ٸ��� �ٲ���
					{
						(*iter)->m_iOption = _iOption;
						return ;
					}

				}
			} 
			else //���� Ÿ���� �浹 Ÿ���� �ƴҶ� 
			{
				if( (*iter)->m_fX == ptMouse.x + g_iTileCX/2  //��ġ�� ���ٸ�
					&& (*iter)->m_fY == ptMouse.y + g_iTileCY/2 )
				{
					if((*iter)->m_iOption != 0) //�� ����� �浹 Ÿ�� �϶� 
					{
						/*(*iter)->m_iDrawID=_DrawID;
						(*iter)->m_iImage=_iImage;
						(*iter)->m_iOption = _iOption;*/
					}
					else
					{
						(*iter)->m_iDrawID=_DrawID;
						(*iter)->m_iImage=_iImage;
						return ;
					}

				}
			}
			
		}
		m_vecTile.push_back(new TILE(static_cast<float>(ptMouse.x + g_iTileCX /2) //����
				,static_cast<float>(ptMouse.y + g_iTileCY /2)  //����
				,g_iTileCX - g_iTileCX /2
				,g_iTileCY - g_iTileCY /2
				,_iOption			// Ÿ���� �ɼ�
				,_DrawID	// Ÿ���� x
				,_iImage) );// Ÿ���� y
	}
	else
	{
		vector<TILE*>::iterator iter_Back=m_vecTile_Back.begin();
		vector<TILE*>::iterator iter_Back_end=m_vecTile_Back.end();

		for( iter_Back ; iter_Back != iter_Back_end ; ++iter_Back)
		{

			if( _iOption != 0) //���� Ÿ���� �浹üũ Ÿ���϶� 
			{
				if( (*iter_Back)->m_fX == ptMouse.x + g_iTileCX/2   // ��ġ�� ���ٸ�
					&& (*iter_Back)->m_fY == ptMouse.y + g_iTileCY/2 )
				{

					if( (*iter_Back)->m_iOption == 0 ) // �� Ÿ���� �浹Ÿ���� �ƴҶ�
					{
						/*(*iter)->m_iDrawID=_DrawID;
						(*iter)->m_iImage=_iImage;
						(*iter)->m_iOption = _iOption;*/
					}
					else // �浹üũ Ÿ���� �ٸ��� �ٲ���
					{
						(*iter_Back)->m_iOption = _iOption;
						return ;
					}

				}
			} 
			else //���� Ÿ���� �浹 Ÿ���� �ƴҶ� 
			{
				if( (*iter_Back)->m_fX == ptMouse.x + g_iTileCX/2  //��ġ�� ���ٸ�
					&& (*iter_Back)->m_fY == ptMouse.y + g_iTileCY/2 )
				{
					if((*iter_Back)->m_iOption != 0) //�� ����� �浹 Ÿ�� �϶� 
					{
						/*(*iter)->m_iDrawID=_DrawID;
						(*iter)->m_iImage=_iImage;
						(*iter)->m_iOption = _iOption;*/
					}
					else
					{ 
						/*if( _DrawID ==14)*/
								break;
							(*iter_Back)->m_iDrawID=_DrawID;
							(*iter_Back)->m_iImage=_iImage;
						
						return ;
					}

				}
			}
		}




		m_vecTile_Back.push_back(new TILE(static_cast<float>(ptMouse.x + g_iTileCX /2) //����
			,static_cast<float>(ptMouse.y + g_iTileCY /2)  //����
			,g_iTileCX - g_iTileCX /2
			,g_iTileCY - g_iTileCY /2
			,_iOption			// Ÿ���� �ɼ�
			,_DrawID	// Ÿ���� x
			,_iImage) );// Ÿ���� y

	}	




}
void CTileMgr::SaveTile(void)
{
	FILE* pFile = NULL;

	fopen_s(&pFile, "../Data/SaveDataFile2.dat", "wb");

	int iTileSize = m_vecTile.size();

	fwrite(&iTileSize, sizeof(int), 1, pFile);

	for(int i = 0; i < iTileSize; ++i)
	{
		fwrite(m_vecTile[i], sizeof(TILE), 1, pFile);
	}

	iTileSize = m_vecTile_Back.size();

	fwrite(&iTileSize, sizeof(int), 1, pFile);

	for(int i = 0; i < iTileSize; ++i)
	{
		fwrite(m_vecTile_Back[i], sizeof(TILE), 1, pFile);
	}
	fclose(pFile);

}
void CTileMgr::SaveTileBack(void)
{
	FILE* pFile = NULL;

	fopen_s(&pFile, "../Data/SaveDataFile3_Back.dat", "wb");
	int iTileSize = m_vecTile_Back.size();

	fwrite(&iTileSize, sizeof(int), 1, pFile);

	for(int i = 0; i < iTileSize; ++i)
	{
		fwrite(m_vecTile_Back[i], sizeof(TILE), 1, pFile);
	}
	fclose(pFile);

}
void CTileMgr::LoadTile(void)
{
	FILE* pFile = NULL;

	fopen_s(&pFile, "../Data/SaveDataFile2.dat", "rb");

	int iTileSize = m_vecTile.size();

	fread(&iTileSize, sizeof(int), 1, pFile);


	for(size_t i = 0; i < m_vecTile.size(); ++i)
	{
		delete m_vecTile[i];
		m_vecTile[i] = NULL;
	}
	m_vecTile.clear();


	for(int  i = 0; i < iTileSize; ++i)
	{
		PTILE pTile = new TILE;

		fread(pTile, sizeof(TILE), 1, pFile);

		m_vecTile.push_back(pTile);
	}

	iTileSize = m_vecTile_Back.size();
	fread(&iTileSize, sizeof(int), 1, pFile);



	for(size_t i = 0; i < m_vecTile_Back.size(); ++i)
	{
		delete m_vecTile_Back[i];
		m_vecTile_Back[i] = NULL;
	}
	m_vecTile_Back.clear();


	for(int  i = 0; i < iTileSize; ++i)
	{
		PTILE pTile = new TILE;

		fread(pTile, sizeof(TILE), 1, pFile);

		m_vecTile_Back.push_back(pTile);
	}

	fclose(pFile);

}
void CTileMgr::LoadTileBack(void)
{
	FILE* pFile = NULL;

	fopen_s(&pFile, "../Data/SaveDataFile2_Back.dat", "rb");

	int iTileSize = m_vecTile_Back.size();
	fread(&iTileSize, sizeof(int), 1, pFile);



	for(size_t i = 0; i < m_vecTile_Back.size(); ++i)
	{
		delete m_vecTile_Back[i];
		m_vecTile_Back[i] = NULL;
	}
	m_vecTile_Back.clear();


	for(int  i = 0; i < iTileSize; ++i)
	{
		PTILE pTile = new TILE;

		fread(pTile, sizeof(TILE), 1, pFile);

		m_vecTile_Back.push_back(pTile);
	}

	fclose(pFile);
}

vector<TILE*>* CTileMgr::GetvecTile(void)
{
	return &m_vecTile;
}
vector<TILE*>* CTileMgr::GetvecTileBack(void)
{
	return &m_vecTile_Back;
}
void CTileMgr::Render(HDC _hdc, HDC _Tilehdc )
{


	vector<TILE*>::iterator iter=m_vecTile.begin();
	vector<TILE*>::iterator iter_end=m_vecTile.end();

	for( iter ; iter != iter_end ; ++iter)
	{
		//�ø�: ȭ��� ���̴� �͸��� �����Ѵ�.
		//���� Ÿ�� ��ǥ��  ȭ��ȿ� ������ �����Ѵ�.
		//Ȯ�� �ϱ����ؼ� ���� x �� y ���� �ϳ��� 0���� �ϰ� Ȯ���ϸ�
		//// �����̳� ���� Ÿ���� �߰��뿡 ������°��� �� �� �ִ�.
		//if( ((*iter)->m_fX - g_iTileCX / 2 + m_ptScroll->x >=-m_ptScroll->x / g_iTileCX
		//	&& (*iter)->m_fX - g_iTileCX / 2 + m_ptScroll->x <=-m_ptScroll->x / g_iTileCX + g_iWINCX / g_iTileCX + 2)
		//	&& ((*iter)->m_fY - g_iTileCY / 2 + m_ptScroll->y >=-g_iTileCY +m_ptScroll->y
		//	&& (*iter)->m_fY - g_iTileCY / 2 + m_ptScroll->y <=g_iWINCY +m_ptScroll->y))
		//{

		if((*iter)->m_iOption !=0 )
		{
			HPEN MyBrush, OldBrush;
			if(m_bShowRect ==true)
			{	
				if((*iter)->m_iOption == 1)
					MyBrush = (HPEN)CreatePen(4,5,(RGB(255,0,0)));

				else if((*iter)->m_iOption ==2 )
					MyBrush = (HPEN)CreatePen(4,5,(RGB(255,255,0)));
				else if((*iter)->m_iOption ==3 )
					MyBrush = (HPEN)CreatePen(4,5,(RGB(255,255,255)));
				else if((*iter)->m_iOption ==4 )
					MyBrush = (HPEN)CreatePen(4,5,(RGB(255,0,255)));
				else if((*iter)->m_iOption ==5 )
					MyBrush = (HPEN)CreatePen(4,5,(RGB(0,255,255)));

				OldBrush = (HPEN)SelectObject(_hdc, MyBrush);
				Rectangle(_hdc, 
					static_cast<int>((*iter)->m_fX - g_iTileCX / 2 + m_ptScroll.x),
					static_cast<int>((*iter)->m_fY - g_iTileCY / 2+ m_ptScroll.y),
					static_cast<int>((*iter)->m_fX - g_iTileCX / 2 + m_ptScroll.x+g_iTileCX),
					static_cast<int>((*iter)->m_fY - g_iTileCY / 2+ m_ptScroll.y+g_iTileCY));

				SelectObject(_hdc, GetStockObject(NULL_BRUSH));
				DeleteObject(MyBrush);
			}
		}
		else
		{
			TransparentBlt(_hdc, 
				static_cast<int>((*iter)->m_fX - g_iTileCX / 2 + m_ptScroll.x), //��ũ���� �����϶� Ÿ�ϵ� �����̰� �ϱ� ����
				static_cast<int>((*iter)->m_fY - g_iTileCY / 2+ m_ptScroll.y),
				g_iTileCX, 
				g_iTileCY,
				_Tilehdc,
				(*iter)->m_iDrawID * g_iTileCX, // �̹����� x
				(*iter)->m_iImage * g_iTileCY, // �̹����� y
				g_iTileCX,
				g_iTileCY,
				RGB(255,255,255));
		}
		//}
	}




}
void CTileMgr::Render_Back(HDC _hdc, HDC _Tilehdc )
{
	vector<TILE*>::iterator iter=m_vecTile_Back.begin();
	vector<TILE*>::iterator iter_end=m_vecTile_Back.end();

	for( iter ; iter != iter_end ; ++iter)
	{
		//�ø�: ȭ��� ���̴� �͸��� �����Ѵ�.
		//���� Ÿ�� ��ǥ��  ȭ��ȿ� ������ �����Ѵ�.
		//Ȯ�� �ϱ����ؼ� ���� x �� y ���� �ϳ��� 0���� �ϰ� Ȯ���ϸ�
		//// �����̳� ���� Ÿ���� �߰��뿡 ������°��� �� �� �ִ�.
		//if( ((*iter)->m_fX - g_iTileCX / 2 + m_ptScroll->x >=-m_ptScroll->x / g_iTileCX
		//	&& (*iter)->m_fX - g_iTileCX / 2 + m_ptScroll->x <=-m_ptScroll->x / g_iTileCX + g_iWINCX / g_iTileCX + 2)
		//	&& ((*iter)->m_fY - g_iTileCY / 2 + m_ptScroll->y >=-g_iTileCY +m_ptScroll->y
		//	&& (*iter)->m_fY - g_iTileCY / 2 + m_ptScroll->y <=g_iWINCY +m_ptScroll->y))
		//{


		TransparentBlt(_hdc, 
			static_cast<int>((*iter)->m_fX - g_iTileCX / 2 + m_ptScroll.x), //��ũ���� �����϶� Ÿ�ϵ� �����̰� �ϱ� ����
			static_cast<int>((*iter)->m_fY - g_iTileCY / 2+ m_ptScroll.y),
			g_iTileCX, 
			g_iTileCY,
			_Tilehdc,
			(*iter)->m_iDrawID * g_iTileCX, // �̹����� x
			(*iter)->m_iImage * g_iTileCY, // �̹����� y
			g_iTileCX,
			g_iTileCY,
			RGB(255,255,255));

		//}
	}
}