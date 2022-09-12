#pragma once

class CScene;

class CSceneMgr
{
private:
	CSceneMgr();
	~CSceneMgr();
	CSceneMgr& operator=(const CSceneMgr& rhs) = delete;
	CSceneMgr(const CSceneMgr& rhs) = delete;
public:
	static CSceneMgr* pInstance;
	static CSceneMgr* GetInstance();
	static void Destroy();
public:
	void SetCurScene(CScene* _curScene) { m_nCurScene = _curScene; }
	CScene* GetCurScene() { return m_nCurScene; }
private:
	CScene* m_nCurScene;
	vector<class CScene*> m_vScenes;
};


