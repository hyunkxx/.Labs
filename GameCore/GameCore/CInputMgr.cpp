#include "pch.h"
#include "CInputMgr.h"

CInputMgr* CInputMgr::pInstance;

CInputMgr::CInputMgr()
{
	memset(&m_bPrevPressed, false, sizeof(m_bPrevPressed));
}

CInputMgr::~CInputMgr()
{
}

CInputMgr* CInputMgr::GetInstance()
{
	if (!pInstance)
		pInstance = new CInputMgr();

	return pInstance;
}

void CInputMgr::Destroy()
{
	if (pInstance)
	{
		delete pInstance;
		pInstance = nullptr;
	}
}

bool CInputMgr::KeyPress(int iKey)
{
	if (GetAsyncKeyState(iKey) & 0x8000)
		return true;

	return false;
}

bool CInputMgr::KeyDown(int iKey)
{
	if (!m_bPrevPressed[iKey] && GetAsyncKeyState(iKey))
	{
		m_bPrevPressed[iKey] = true;
		return true;
	}

	for (int index = 0; index < VK_COUNT; index++)
	{
		if (m_bPrevPressed[index] && !(GetAsyncKeyState(index)))
			m_bPrevPressed[index] = false;
	}

	return false;
}

bool CInputMgr::KeyUp(int iKey)
{
	if (m_bPrevPressed[iKey] && !(GetAsyncKeyState(iKey)))
	{
		m_bPrevPressed[iKey] = false;
		return true;
	}

	for (int index = 0; index < VK_COUNT; index++)
	{
		if (!m_bPrevPressed[index] && GetAsyncKeyState(index))
			m_bPrevPressed[index] = true;
	}

	return false;
}
