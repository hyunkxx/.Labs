#include "pch.h"
#include "CObject.h"
#include "CScene.h"

CScene::CScene(wstring _szSceneName)
	:m_szSceneName(_szSceneName)
{
}

CScene::~CScene()
{
    for (int index = 0; index < (UINT)OBJ_TYPE::COUNT; index++)
    {
        auto iter = m_arrObjList[index].begin();
        for (; iter != m_arrObjList[index].end();)
            delete* iter;
    }
}

void CScene::AddObject(CObject* _pObj, OBJ_TYPE _eType)
{
	m_arrObjList[(UINT)_eType].push_back(_pObj);
}
