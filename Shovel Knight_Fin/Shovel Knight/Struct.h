#ifndef _STRUCT_H_
#define _STRUCT_H_

typedef struct tagInfo
{
	

	
	float m_fX;	//객체의 중심 좌표 X
	float m_fY;	//객체의 중심 좌표 Y

	float m_fCX;	//객체의 지름 X
	float m_fCY;	//객체의 지름 Y

	tagInfo(float _fx, float _fy, float _fcx, float _fcy)
		:m_fX(_fx) ,m_fY(_fy), m_fCX(_fcx), m_fCY(_fcy){}

	tagInfo(void){}
}INFO, *PINFO;


typedef struct tagFrame
{
	int m_iFrameStart;		
	int m_iFrameEnd;		

	int m_iImage;
	DWORD m_dwFrameTime;	

	tagFrame(void){}

	tagFrame(int _iFrameStart, int _iFrameEnd, int _iImage, DWORD _dwFrameTime)
		:m_iFrameStart(_iFrameStart) ,m_iFrameEnd(_iFrameEnd), m_iImage(_iImage), m_dwFrameTime(_dwFrameTime)	{}

}FRAME;

typedef struct tagLine
{
	float m_fStartX;	//시작 좌표 X
	float m_fStartY;	//시작 좌표 Y

	float m_fEndX;	
	float m_fEndY;	

	tagLine(float _fStartX, float _fStartY, float _fEndX, float _fEndY)
		:m_fStartX(_fStartX) ,m_fStartY(_fStartY), m_fEndX(_fEndX), m_fEndY(_fEndY)	{}

	tagLine(void){}
}LINE, *PLINE;

typedef struct tagTile
{
	float m_fX;	
	float m_fY;	

	float m_fCX;	
	float m_fCY;	

	int m_iOption;		//타일의 타입
	int m_iDrawID;		//타일 이미지의 x
	int m_iImage;		//타일 이미지의 y

	tagTile(float _fx, float _fy, float _fcx, float _fcy, int _iOption, int _iDrawID ,int _iImage)
		:m_fX(_fx)
		,m_fY(_fy)
		,m_fCX(_fcx)
		,m_fCY(_fcy)
		,m_iOption(_iOption)
		,m_iDrawID(_iDrawID)
		,m_iImage (_iImage){}

	tagTile(void){}

	//tagTile GetInfo(void)
	//{
	//	TILE temp;
	//	temp.m_fX=m_fX;
	//	temp.m_fY=m_fY;
	//	temp.m_fCX=m_fCX;
	//	temp.m_fCY=m_fCY;

	//	return temp;
	//}

	INFO GetInfo(void)
	{
		INFO temp;
		temp.m_fX=m_fX;
		temp.m_fY=m_fY;
		temp.m_fCX=m_fCX;
		temp.m_fCY=m_fCY;

		return temp;
	}
	
	RECT GetRect(void)
	{
		RECT rcTile=
		{
			long(m_fX - m_fCX / 2),
			long(m_fY - m_fCY / 2),
			long(m_fX + m_fCX / 2),
			long(m_fY + m_fCY / 2),
		};
				return rcTile;
	};

	

}TILE, *PTILE;

typedef struct tObjInfo
{
	tagInfo m_tInfo;
	string m_strName;
	eDIRT_TYPE m_eType;
}OBJINFO;

#endif	//_STRUCT_H_