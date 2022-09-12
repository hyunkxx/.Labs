#include "pch.h"
#include "CObject.h"
#include "CIntroScene.h"

CIntroScene::CIntroScene(wstring _szName)
    :CScene(_szName)
{
}

CIntroScene::~CIntroScene()
{
}

void CIntroScene::Enter()
{
    m_pPlayer = new CObject(200.f, 200.f, 30.f);
    AddObject(m_pPlayer, OBJ_TYPE::PLAYER);
}

void CIntroScene::Exit()
{
    delete m_pPlayer;
}

void CIntroScene::Initalize()
{
}

void CIntroScene::Update(double _fDeltaTime)
{
    for (int index = 0; index < (UINT)OBJ_TYPE::COUNT; index++)
    {
        auto iter = m_arrObjList[index].begin();
        for (;iter != m_arrObjList[index].end();)
        {
            int iEvent;
            iEvent = (*iter)->Update(_fDeltaTime);
            if (iEvent == EVENT_DEAD)
            {
                delete* iter;
                iter = m_arrObjList[index].erase(iter);
            }
            else
                iter++;
        }
    }
}

void CIntroScene::LateUpdate(double _fDeltaTime)
{
    for (int index = 0; index < (UINT)OBJ_TYPE::COUNT; index++)
    {
        auto iter = m_arrObjList[index].begin();
        for (; iter != m_arrObjList[index].end();)
        {
            int iEvent;
            iEvent = (*iter)->LateUpdate(_fDeltaTime);
            if (iEvent == EVENT_DEAD)
            {
                delete* iter;
                iter = m_arrObjList[index].erase(iter);
            }
            else
                iter++;
        }
    }
}

void CIntroScene::Render(HDC _hdc)
{
    for (int index = 0; index < (UINT)OBJ_TYPE::COUNT; index++)
    {
        auto iter = m_arrObjList[index].begin();
        for (; iter != m_arrObjList[index].end();)
           (*iter)->Render(_hdc);
    }
}

void CIntroScene::Release()
{
    for (int index = 0; index < (UINT)OBJ_TYPE::COUNT; index++)
    {
        auto iter = m_arrObjList[index].begin();
        for (; iter != m_arrObjList[index].end();)
            (*iter)->Release();
    }
}
