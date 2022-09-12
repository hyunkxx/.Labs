#include "pch.h"
#include "CObject.h"
#include "CInputMgr.h"
#include "CCollider.h"

CObject::CObject()
	: m_vPos(0.f,0.f)
	, m_fScale(0.f)
	, m_rcRect({})
	, m_eState(OBJ_STATE::NONE)
	, m_pCollider(nullptr)
{
}

CObject::CObject(float _x, float _y, float _scale)
	: m_vPos(_x, _y)
	, m_fScale(_scale)
	, m_rcRect({})
	, m_eState(OBJ_STATE::NONE)
	, m_pCollider(nullptr)
{
}

CObject::CObject(Vector2D _value, float _scale)
	: m_vPos(_value)
	, m_fScale(_scale)
	, m_rcRect({})
	, m_eState(OBJ_STATE::NONE)
	, m_pCollider(nullptr)
{
}

CObject::~CObject()
{
}

void CObject::Initalize()
{
	CreateCollider();
	m_eState = OBJ_STATE::ACTIVE;
}

int CObject::Update(double _fDeltaTime)
{
	setRect();

	return EVENT_NONE;
}

void CObject::Render(HDC _hdc) const
{
	Rectangle(_hdc, m_rcRect.left, m_rcRect.top, m_rcRect.right, m_rcRect.bottom);
}

void CObject::LateUpdate(double _fDeltaTime)
{
}

void CObject::Release()
{
}

void CObject::ComponentUpdate(double _fDeltaTime)
{
	if(m_pCollider != nullptr)
		m_pCollider->Update(_fDeltaTime);
}

void CObject::ComponentRender(HDC _hdc)
{
	if (m_pCollider != nullptr)
		m_pCollider->Render(_hdc);
}


void CObject::OnCollisionEnter(CObject* _coll)
{
}

void CObject::OnCollisionStay(CObject* _coll)
{
}

void CObject::OnCollisionExit(CObject* _coll)
{
}

void CObject::CreateCollider()
{
	if (!m_pCollider)
	{
		m_pCollider = new CCollider;
		m_pCollider->m_pOwner = this;
		m_pCollider->SetOffset(0.f,0.f);
		m_pCollider->SetScale(m_fScale);
	}
}

void CObject::setRect()
{
	m_rcRect.left	= (LONG)(m_vPos.fX - m_fScale);
	m_rcRect.top	= (LONG)(m_vPos.fY - m_fScale);
	m_rcRect.right  = (LONG)(m_vPos.fX + m_fScale);
	m_rcRect.bottom = (LONG)(m_vPos.fY + m_fScale);
}
