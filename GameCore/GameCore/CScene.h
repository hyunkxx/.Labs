#pragma once
class CScene
{
public:
	CScene(wstring _szSceneName);
	virtual ~CScene();
public:
	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual void Initalize() = 0;
	virtual void Update(double _fDeltaTime) = 0;
	virtual void LateUpdate(double _fDeltaTime) = 0;
	virtual void Render(HDC _hdc) =0;
	virtual void Release() = 0;
public:
	wstring GetName() const { return m_szSceneName; }
	void SetName(wstring _szStr) { m_szSceneName = _szStr; }
protected:
	void AddObject(class CObject* _pObj, OBJ_TYPE _eType);
protected:
	wstring m_szSceneName;
	list<class CObject*> m_arrObjList[(UINT)OBJ_TYPE::COUNT];
};
