#include "pch.h"
#include "CObject.h"
#include "CObjectMgr.h"

CObjectMgr* CObjectMgr::pInstance;

CObjectMgr::CObjectMgr()
{
}
CObjectMgr::~CObjectMgr()
{
	for (int index = 0; index < (UINT)OBJ_TYPE::COUNT; ++index)
	{
		for (auto iter = m_arrObjList[index].begin()
			; iter != m_arrObjList[index].end(); ++iter)
		{
			delete *iter;
		}
	}
}

CObjectMgr* CObjectMgr::GetInstance()
{
	if (!pInstance)
		pInstance = new CObjectMgr();

	return pInstance;
}

void CObjectMgr::Destroy()
{
	if (pInstance)
	{
		delete pInstance;
		pInstance = nullptr;
	}
}

void CObjectMgr::Initalize()
{
	for (int index = 0; index < (UINT)OBJ_TYPE::COUNT; ++index)
	{
		for (auto iter = m_arrObjList[index].begin()
			; iter != m_arrObjList[index].end() ; ++iter)
		{
			(*iter)->Initalize();
		}
	}
}

void CObjectMgr::Update(double _fDeltaTime)
{
	for (int index = 0; index < (UINT)OBJ_TYPE::COUNT; ++index)
	{
		for (auto iter = m_arrObjList[index].begin()
			; iter != m_arrObjList[index].end(); )
		{
			(*iter)->Update(_fDeltaTime);
			if ((*iter)->CompareState(OBJ_STATE::DEAD))
			{
				delete *iter;
				iter = m_arrObjList[index].erase(iter);
			}
			else
				iter++;
		}
	}
}

void CObjectMgr::LateUpdate(double _fDeltaTime)
{
	for (int index = 0; index < (UINT)OBJ_TYPE::COUNT; ++index)
	{
		for (auto iter = m_arrObjList[index].begin()
			; iter != m_arrObjList[index].end(); ++iter)
		{
			(*iter)->LateUpdate(_fDeltaTime);
		}
	}
}

void CObjectMgr::Render(HDC _hdc)
{
	for (int index = 0; index < (UINT)OBJ_TYPE::COUNT; ++index)
	{
		for (auto iter = m_arrObjList[index].begin()
			; iter != m_arrObjList[index].end(); ++iter)
		{
			(*iter)->Render(_hdc);
		}
	}
}

void CObjectMgr::Release()
{
	for (int index = 0; index < (UINT)OBJ_TYPE::COUNT; ++index)
	{
		for (auto iter = m_arrObjList[index].begin()
			; iter != m_arrObjList[index].end(); ++iter)
		{
			(*iter)->Release();
		}
	}
}

void CObjectMgr::compoenentUpdate(double _fDeltaTime)
{
	for (int index = 0; index < (UINT)OBJ_TYPE::COUNT; ++index)
	{
		for (auto iter = m_arrObjList[index].begin()
			; iter != m_arrObjList[index].end(); ++iter)
		{
			(*iter)->ComponentUpdate(_fDeltaTime);
		}
	}
}

void CObjectMgr::compoenentRender(HDC _hdc)
{
	for (int index = 0; index < (UINT)OBJ_TYPE::COUNT; ++index)
	{
		for (auto iter = m_arrObjList[index].begin()
			; iter != m_arrObjList[index].end(); ++iter)
		{
			(*iter)->ComponentRender(_hdc);
		}
	}
}

void CObjectMgr::AddObject(CObject* _pObj, OBJ_TYPE _eType)
{
	if (_pObj == nullptr || (UINT)_eType >= (UINT)OBJ_TYPE::COUNT)
		return;

	m_arrObjList[(UINT)_eType].emplace_back(_pObj);
}
