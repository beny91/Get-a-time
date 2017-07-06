#include "StdAfx.h"
#include "LineMgr.h"

CLineMgr* CLineMgr::m_pInstance;

CLineMgr::CLineMgr(void)
{

}

CLineMgr::~CLineMgr(void)
{
}

void CLineMgr::DrawLine(void)
{
	POINT ptMouse;

	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	if(GetAsyncKeyState(VK_LBUTTON) & 0x8000 ) //마우스 왼쪽 버튼
	{
		//마우스의 상태 값이 라인의 시작 값으로 들어간다.
		m_Line.m_fStartX=static_cast <float>(ptMouse.x); 
		m_Line.m_fStartY=static_cast <float>(ptMouse.y);		
	}

	if(GetAsyncKeyState(VK_RBUTTON)  & 0x8000 ) //마우스 오른쪽
	{
		//라인의 끝 좌표가 마우스의 값으로 들어간다.
		m_Line.m_fEndX=static_cast <float>(ptMouse.x);
		m_Line.m_fEndY=static_cast <float>(ptMouse.y);	

		m_Linelist.push_back(new LINE(m_Line.m_fStartX,m_Line.m_fStartY,m_Line.m_fEndX,m_Line.m_fEndY));

		//데이터를 삽입한 다음에 시작 좌표에 끝좌표를 넘겨주어 다음에 오른쪽 버튼을 누르면 바로 이어서 그려진다. 
		m_Line.m_fStartX=ptMouse.x;
		m_Line.m_fStartY=ptMouse.y;
	}


}

list<LINE*>* CLineMgr::GetLineList(void)
{
	return &m_Linelist;
}

void CLineMgr::SaveLine(void)
{
	DWORD dwByte;

	HANDLE hFile = CreateFile(L"../Data/Line.dat", GENERIC_WRITE, 0, NULL
		, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	list<LINE*>::iterator iter = m_Linelist.begin();

	for( ; iter != m_Linelist.end(); ++iter)
	{
		WriteFile(hFile, (*iter), sizeof(LINE), &dwByte, NULL);
	}

	CloseHandle(hFile);
}
void CLineMgr::LoadLine(void)
{
	HANDLE hFile;

	DWORD dwByte = 0;

	hFile =  CreateFile(L"../Data/Line.dat", GENERIC_READ, 0, NULL
		, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	while(true)
	{
		LINE* pLine = new LINE;

		ReadFile(hFile, pLine, sizeof(LINE), &dwByte, NULL);

		if(dwByte == 0)
		{
			//데이터 읽이 종료.
			SAFE_DELETE(pLine);

			break;
		}

		m_Linelist.push_back(pLine);
	}

	CloseHandle(hFile);
}