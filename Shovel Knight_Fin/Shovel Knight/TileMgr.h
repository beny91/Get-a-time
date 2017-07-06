#pragma once

class CTileMgr
{
private:
	static CTileMgr* m_pInstance;

private:
	POINT		m_ptScroll;
	bool		m_bShowRect;
	vector<TILE*> m_vecTile;
	vector<TILE*> m_vecTile_Back;

public:
	static CTileMgr* GetInstance(void)
	{
		if(m_pInstance==NULL)
		{
			m_pInstance = new CTileMgr;
			m_pInstance->Initialize();
		}
		
		return m_pInstance;
	}

	void Destroy(void)
	{
		SAFE_DELETE(m_pInstance);
		m_pInstance=NULL;
	}

public:
	void DrawTile(int _DrawID, POINT m_ptScroll ,POINT _Index , int _iImage ,int _iOption=0 );
	void SaveTile(void);
	void SaveTileBack(void);
	void LoadTile(void);
	void LoadTileBack(void);

public:
	void SetScroll(POINT _ptScroll) {m_ptScroll= _ptScroll;};
	

public:
	vector<TILE*>* GetvecTile(void);
	vector<TILE*>* GetvecTileBack(void);

public:
	void Initialize(void);
	int  Progress(void);
	void Render(HDC _hdc, HDC _Tilehdc );
	void Render_Back(HDC _hdc, HDC _Tilehdc );
	void Release(void);
private:
	CTileMgr(void);
public:
	~CTileMgr(void);
};
