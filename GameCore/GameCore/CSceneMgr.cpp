#include "pch.h"
#include "CScene.h"
#include "CIntroScene.h"
#include "CSceneMgr.h"

CSceneMgr* CSceneMgr::pInstance;

CSceneMgr::CSceneMgr()
	:m_nCurScene(nullptr)
{
	m_vScenes.emplace_back(new CIntroScene(L"Intro1"));
	m_vScenes.emplace_back(new CIntroScene(L"Intro1"));
	m_vScenes.emplace_back(new CIntroScene(L"Intro1"));

	m_nCurScene = m_vScenes[0];
}
CSceneMgr::~CSceneMgr()
{
}

CSceneMgr* CSceneMgr::GetInstance()
{
	if (!pInstance)
		pInstance = new CSceneMgr();

	return pInstance;
}

void CSceneMgr::Destroy()
{
	if (pInstance)
	{
		delete pInstance;
		pInstance = nullptr;
	}
}