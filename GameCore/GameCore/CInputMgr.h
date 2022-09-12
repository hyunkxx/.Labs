#pragma once
class CInputMgr
{
public:
	CInputMgr();
	~CInputMgr();
	CInputMgr(const CInputMgr& rhs) = delete;
	CInputMgr& operator=(const CInputMgr& rhs) = delete;
public:
	static CInputMgr* pInstance;
	static CInputMgr* GetInstance();
	static void Destroy();
public:
	bool KeyPress(int iKey);
	bool KeyDown(int iKey);
	bool KeyUp(int iKey);
private:
	bool m_bPrevPressed[VK_COUNT];
};

