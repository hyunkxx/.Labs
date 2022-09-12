#pragma once
class CCore
{
private:
	CCore();
	~CCore();
public:
	static double DeltaTime;
	static CCore* pInstance;
	static CCore* GetInstance();
	static void Destroy();
public:
	void Initalize(HWND _hWnd, HINSTANCE _hInstance, RECT _clientRect);
	void Process();
	void Release();
public:
	const double& GetDeltaTime() { return m_fDeltaTime; }
	const HWND& GetHWND() { return m_hWnd; }
private:
	void update();
	void lateUpdate();
	void render();
	void componentUpdate();
	void componentRender();
private:
	void drawBackground(HDC _hdc);
	void setDeltaTime(bool _showTitle);
private://Windows value
	HDC			m_hdc;
	HDC			m_subDC;
	HBITMAP		m_hBit;
	HWND		m_hWnd;
	HINSTANCE	m_hInstance;
	RECT		m_clientRect;
	LPWSTR		m_szTitle;
private://Timer values
	double m_fTimeScale;
	double m_fDeltaTime;
	LARGE_INTEGER tickCount, beginTimer, endTimer;
private://Managers

};