#include "pch.h"
#include "CObject.h"
#include "CCollider.h"


CCollider::CCollider()
	: m_pOwner(nullptr)
	, m_vOffset(0.f,0.f)
	, m_vOriginPos(0.f,0.f)
	, m_fScale(0.f)
	, m_eState(COL_STATE::NONE)
	, m_bPrevHit(false)
	, m_rcCollision({})
{
}

CCollider::~CCollider()
{
	m_pOwner = nullptr;
}

void CCollider::Update(double _fDeltaTieme)
{
	setRect();
	m_vOriginPos.fX = m_pOwner->GetPosition().fX + m_vOffset.fX;
	m_vOriginPos.fY = m_pOwner->GetPosition().fY + m_vOffset.fY;
}

void CCollider::Render(HDC _hdc)
{
	HBRUSH hMyBrush, hHollowBrush;
	HPEN hMyPen,hNewPen;

	hNewPen = (HPEN)CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
	hHollowBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

	hMyBrush = (HBRUSH)SelectObject(_hdc, hHollowBrush);
	hMyPen = (HPEN)SelectObject(_hdc, hNewPen);

	//Rectangle(_hdc
	//	, (int)(m_vOriginPos.fX - m_fScale)
	//	, (int)(m_vOriginPos.fY - m_fScale)
	//	, (int)(m_vOriginPos.fX + m_fScale)
	//	, (int)(m_vOriginPos.fY + m_fScale));

	Rectangle(_hdc
		, m_rcCollision.left
		, m_rcCollision.top
		, m_rcCollision.right
		, m_rcCollision.bottom);


	SelectObject(_hdc, hMyBrush);
	SelectObject(_hdc, hMyPen);

	DeleteObject(hNewPen);
}

void CCollider::Enter(CObject* _coll)
{
	if (!m_bPrevHit)
	{
		m_bPrevHit = true;
		m_eState = COL_STATE::ENTER;
		m_pOwner->OnCollisionEnter(_coll);
		return;
	}
	else
	{
		m_eState = COL_STATE::STAY;
		m_pOwner->OnCollisionStay(_coll);
	}
	return;
}

void CCollider::Exit(CObject* _coll)
{
	if (m_bPrevHit)
	{
		m_bPrevHit = false;
		m_eState = COL_STATE::EXIT;
		m_pOwner->OnCollisionExit(_coll);
		return;
	}
	else
		m_eState = COL_STATE::NONE;

	return;
}
