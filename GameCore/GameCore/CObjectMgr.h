#pragma once
class CObject;

class CObjectMgr
{
private:
	CObjectMgr();
	~CObjectMgr();
	CObjectMgr& operator=(const CObjectMgr& rhs) = delete;
	CObjectMgr(const CObjectMgr& rhs) = delete;
public:
	static CObjectMgr* pInstance;
	static CObjectMgr* GetInstance();
	static void Destroy();
public:
	void Initalize();
	void Update(double _fDeltaTime);
	void LateUpdate(double _fDeltaTime);
	void Render(HDC _hdc);
	void Release();
	void compoenentUpdate(double _fDeltaTime);
	void compoenentRender(HDC _hdc);
public:
	void AddObject(class CObject* _pObj, OBJ_TYPE _eType);
	list<CObject*>* GetObjectList(OBJ_TYPE _eType) { return &m_arrObjList[(UINT)_eType]; }
private:
	list<CObject*> m_arrObjList[(UINT)OBJ_TYPE::COUNT];
};

