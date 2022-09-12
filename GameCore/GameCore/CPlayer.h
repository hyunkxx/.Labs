#pragma once

#include "CObject.h"

class CPlayer : public CObject
{
public:
	CPlayer();
	CPlayer(float _x, float _y, float _salce);
	CPlayer(Vector2D _value, float _scale);
	~CPlayer();
public:
	virtual void Initalize();
	virtual int  Update(double _fDeltaTime);
	virtual void LateUpdate(double _fDeltaTime);
	virtual void Render(HDC _hdc) const;
	virtual void Release();
public:
	virtual void OnCollisionEnter(CObject* _coll);
	virtual void OnCollisionStay(CObject* _coll);
	virtual void OnCollisionExit(CObject* _coll);
private:
	int enterCnt;
	int stayCnt;
	int endCnt;
};

