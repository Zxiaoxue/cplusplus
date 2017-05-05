#include <iostream>

using namespace std;

class cMyString
{
public:
	cMyString(char* pData = NULL);
	cMyString(const cMyString& str);
	~cMyString(void);
	//first commit
	/*cMyString& operator=(const cMyString& str)
	{
		if(this == &str)
			return *this;
		delete[] m_pData;
		m_pData = NULL;
		m_pData = new char[strlen(str.m_pData)+1];
		strcpy(m_pData, str.m_pData);
		return *this;
	}*/
	//second commit
	/*cMyString& operator=(const cMyString& str)
	{
		if(this != &str)
		{
			cMyString temp(str);

			char* ptmp = temp.m_pData;
			temp.m_pData = m_pData;
			m_pData = ptmp;
		}

		return *this;
	}*/
	//third commit
	cMyString& operator=(cMyString str)
	{
		if(this != &str)
		{
			swap(m_pData, str.m_pData);
		}
		return *this;
	}

private:
	char* m_pData;
};


