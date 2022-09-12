#pragma once

class CObject;

class CCollisionMgr
{
private:
	//Singleton
	CCollisionMgr();
	~CCollisionMgr();
	CCollisionMgr(const CCollisionMgr& _rhs) = delete;
	CCollisionMgr& operator=(const CCollisionMgr& _rhs) = delete;
public:
	static CCollisionMgr* pInstance;
	static CCollisionMgr* GetInstance()
	{
		if (!pInstance)
		{
			pInstance = new CCollisionMgr;
		}
		return pInstance;
	};
	static void Destroy()
	{
		if (pInstance)
		{
			delete pInstance;
			pInstance = nullptr;
		}
	};
public:
	void CollisionRect(list<CObject*>* _lhs, list<CObject*>* _rhs);
	void CollisionSphere(list<CObject*>* _lhs, list<CObject*>* _rhs);
	bool CheckSphere(CObject* _lhs, CObject* _rhs);
private:
	void setPosition(CObject* _lhs, CObject* _rhs, RECT* _rc);
};