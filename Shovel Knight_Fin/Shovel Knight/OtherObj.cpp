#include "StdAfx.h"
#include "OtherObj.h"

COtherObj::COtherObj(void)
{
}

COtherObj::~COtherObj(void)
{
}

COtherObj::COtherObj(string strName, float fx, float fy, float fcx, float fcy , int Hp, int Mp , int Att )
:CObj(strName,fx,fy,fcx,fcy, Hp, Mp, Att)
{

}

void COtherObj::Initialize(void)
{

}
int	 COtherObj::Progress(void)
{
	return 0;
}
void COtherObj::Render(HDC _hdc)
{

}
void COtherObj::Release(void)
{
}