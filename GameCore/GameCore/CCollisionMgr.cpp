#include "pch.h"
#include "CCollisionMgr.h"

#include "CObject.h"
#include "CCollider.h"

CCollisionMgr* CCollisionMgr::pInstance;

CCollisionMgr::CCollisionMgr()
{
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::CollisionRect(list<CObject*>* _lhs, list<CObject*>* _rhs)
{
	static RECT lhsRect, rhsRect;
	static RECT collArea;

	for (auto& lhs : *_lhs)
	{
		if (lhs->GetCollider() == nullptr)
			continue;
		for (auto& rhs : *_rhs)
		{
			if (rhs->GetCollider() == nullptr)
				continue;

			lhsRect = lhs->GetCollider()->GetRect();
			rhsRect = rhs->GetCollider()->GetRect();
			
			if (IntersectRect(&collArea, &lhsRect, &rhsRect))
			{
				
				setPosition(lhs, rhs, &collArea);

				lhs->GetCollider()->Enter(rhs);
				rhs->GetCollider()->Enter(lhs);
			}
			else
			{
				lhs->GetCollider()->Exit(rhs);
				rhs->GetCollider()->Exit(lhs);
			}
		}
	}
}


void CCollisionMgr::CollisionSphere(list<CObject*>* _lhs, list<CObject*>* _rhs)
{
	for (auto& lhs : *_lhs)
	{
		if (lhs->GetCollider() == nullptr)
			continue;
		for (auto& rhs : *_rhs)
		{
			if (rhs->GetCollider() == nullptr)
				continue;

			if (CheckSphere(lhs, rhs))
			{
				lhs->GetCollider()->Enter(rhs);
				rhs->GetCollider()->Enter(lhs);
			}
			else
			{
				if (lhs->GetCollider()->GetState() == COL_STATE::ENTER)
				{
					lhs->GetCollider()->Exit(rhs);
					rhs->GetCollider()->Exit(lhs);
				}
			}
		}
	}
}

bool CCollisionMgr::CheckSphere(CObject* _lhs, CObject* _rhs)
{
	float xDiff = _lhs->GetX() - _rhs->GetX();
	float yDiff = _lhs->GetY() - _rhs->GetY();
	
	float fDistance = sqrtf(xDiff * xDiff + yDiff * yDiff);
    float fRadius = fabsf(_lhs->GetScale() +  _rhs->GetScale());

	return fRadius >= fDistance;
}

void CCollisionMgr::setPosition(CObject* _lhs, CObject* _rhs, RECT* _rc)
{
	assert(_lhs); assert(_rhs);	assert(_rc);

	if (_rc->right - _rc->left > _rc->bottom - _rc->top)
	{
		if (_lhs->GetY() < _rhs->GetY())
		{
			_lhs->SetY(_lhs->GetCollider()->GetOriginPos().fY + (_rc->top - _rc->bottom));
		}
		else
		{
			_lhs->SetY(_lhs->GetCollider()->GetOriginPos().fY - (_rc->top - _rc->bottom));
		}

		return;
	}
	
	if (_rc->right - _rc->left < _rc->bottom - _rc->top)
	{
		if (_lhs->GetX() < _rhs->GetX())
		{
			_lhs->SetX(_lhs->GetCollider()->GetOriginPos().fX - (_rc->right - _rc->left));
		}
		else
		{
			_lhs->SetX(_lhs->GetCollider()->GetOriginPos().fX + (_rc->right - _rc->left));
		}

		return;
	}
}
