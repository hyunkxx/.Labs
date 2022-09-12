#include "pch.h"
#include "CCore.h"

#include "CPlayer.h"
#include "CObject.h"
#include "CObjectMgr.h"
#include "CCollisionMgr.h"

CCore* CCore::pInstance;
double CCore::DeltaTime;

CCore::CCore()
	: m_fDeltaTime(0.0)
	, m_hWnd(0)
	, m_hdc(0)
	, m_subDC(0)
{
	QueryPerformanceCounter(&beginTimer);
	QueryPerformanceFrequency(&tickCount);
	m_fTimeScale = 1.0 / tickCount.QuadPart;

	m_szTitle = new WCHAR[TEXT_LENGTH];

	ZeroMemory(&beginTimer, sizeof(LARGE_INTEGER));
	ZeroMemory(&endTimer, sizeof(LARGE_INTEGER));
}
CCore::~CCore()
{
	CObjectMgr::GetInstance()->Destroy();
}

CCore* CCore::GetInstance()
{
	if (!pInstance)
		pInstance = new CCore();

	return pInstance;
}

void CCore::Destroy()
{
	if (pInstance)
	{
		delete pInstance;
		pInstance = nullptr;
	}
}

void CCore::Initalize(HWND _hWnd, HINSTANCE _hInstance, RECT _clientRect)
{
	m_hWnd = _hWnd;
	m_clientRect = _clientRect;
	m_hdc = GetDC(m_hWnd);
	m_hBit = CreateCompatibleBitmap(m_hdc, WIDTH, HEIGHT);
	m_subDC = CreateCompatibleDC(m_hdc);
	HBITMAP hDefaultBitmap = (HBITMAP)SelectObject(m_subDC, m_hBit);

	//Manager Init
	CObjectMgr::GetInstance()->AddObject(new CPlayer(400.f,300.f, 10.f),OBJ_TYPE::PLAYER);
	CObjectMgr::GetInstance()->AddObject(new CObject(400.f, 400.f, 10.f), OBJ_TYPE::ENEMY);
	 

	CObjectMgr::GetInstance()->Initalize();

	DeleteObject(hDefaultBitmap);
}

void CCore::Process()
{
	update();
	lateUpdate();
	componentUpdate();

	render();
	componentRender();
}

void CCore::update()
{
	setDeltaTime(true);
	CObjectMgr::GetInstance()->Update(m_fDeltaTime);
}

void CCore::lateUpdate()
{
	CObjectMgr::GetInstance()->LateUpdate(m_fDeltaTime);
	CCollisionMgr::GetInstance()->CollisionRect(
			(CObjectMgr::GetInstance()->GetObjectList(OBJ_TYPE::PLAYER)),
			(CObjectMgr::GetInstance()->GetObjectList(OBJ_TYPE::ENEMY)));
}

void CCore::render()
{
	drawBackground(m_subDC);

	CObjectMgr::GetInstance()->Render(m_subDC);
}

void CCore::componentUpdate()
{
	CObjectMgr::GetInstance()->compoenentUpdate(m_fDeltaTime);
}

void CCore::componentRender()
{
	CObjectMgr::GetInstance()->compoenentRender(m_subDC);
	BitBlt(m_hdc, 0, 0, WIDTH, HEIGHT, m_subDC, 0, 0, SRCCOPY);
}

void CCore::drawBackground(HDC _hdc)
{
	HBRUSH myBrush, backgroundColor;
	backgroundColor = (HBRUSH)CreateSolidBrush(RGB(121, 121, 121));
	myBrush = (HBRUSH)SelectObject(_hdc, backgroundColor);
	Rectangle(_hdc, -1, -1, WIDTH + 1, HEIGHT + 1);
	SelectObject(_hdc, myBrush);
	DeleteObject(backgroundColor);
}

void CCore::setDeltaTime(bool _showTitle)
{
	QueryPerformanceCounter(&endTimer);
	m_fDeltaTime = (double)(endTimer.QuadPart - beginTimer.QuadPart) * m_fTimeScale;
	beginTimer = endTimer;
	CCore::DeltaTime = m_fDeltaTime;

	if (_showTitle)
	{
		swprintf_s(m_szTitle, 64, L"DeltaTime %g", m_fDeltaTime);
		SetWindowText(m_hWnd, m_szTitle);
	}
	else
		return;
}

void CCore::Release()
{
	CObjectMgr::GetInstance()->Release();

	ReleaseDC(m_hWnd, m_hdc);
	ReleaseDC(m_hWnd, m_subDC);
}
