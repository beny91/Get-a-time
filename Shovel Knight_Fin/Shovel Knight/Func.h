#pragma once

class CStringCMP
{
private:
	const TCHAR* m_pString;

public:
	CStringCMP(const TCHAR* pKey)
		:m_pString(pKey){}
	~CStringCMP(){}

public:
	template<typename T>
	bool operator() (T data)
	{
		return !lstrcmp(data.first, m_pString);
	}
};