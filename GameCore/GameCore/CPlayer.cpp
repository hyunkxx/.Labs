#include "pch.h"
#include "CPlayer.h"
#include "CInputMgr.h"
#include "CCollider.h"

CPlayer::CPlayer()
	: CObject()
	, enterCnt(0)
	, stayCnt(0)
	, endCnt(0)
{
}

CPlayer::CPlayer(float _x, float _y, float _salce)
	: CObject(_x, _y, _salce)
	, enterCnt(0)
	, stayCnt(0)
	, endCnt(0)
{
}

CPlayer::CPlayer(Vector2D _value, float _scale)
	: CObject(_value, _scale)
	, enterCnt(0)
	, stayCnt(0)
	, endCnt(0)
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Initalize()
{
	CreateCollider();
	GetCollider()->SetScale(20.f);
}

int CPlayer::Update(double _fDeltaTime)
{
	CObject::Update(_fDeltaTime);

	if (CInputMgr::GetInstance()->KeyPress(VK_RIGHT))
		m_vPos.fX += 100.f * (float)_fDeltaTime;
	if (CInputMgr::GetInstance()->KeyPress(VK_LEFT))
		m_vPos.fX -= 100.f * (float)_fDeltaTime;
	if (CInputMgr::GetInstance()->KeyPress(VK_UP))
		m_vPos.fY -= 100.f * (float)_fDeltaTime;
	if (CInputMgr::GetInstance()->KeyPress(VK_DOWN))
		m_vPos.fY += 100.f * (float)_fDeltaTime;

	return EVENT_NONE;
}

void CPlayer::LateUpdate(double _fDeltaTime)
{
}

void CPlayer::Render(HDC _hdc) const
{
	Rectangle(_hdc, m_rcRect.left, m_rcRect.top, m_rcRect.right, m_rcRect.bottom);
	SetBkMode(_hdc, TRANSPARENT);
	wchar_t* buff = new WCHAR[2000];
	wsprintf(buff, L"CollisionEnter() %d  , OnCollisionStay() %d ", enterCnt, endCnt);
	TextOut(_hdc, 100, 100, buff, lstrlen(buff));
}

void CPlayer::Release()
{
}

void CPlayer::OnCollisionEnter(CObject* _coll)
{
	enterCnt++;
}
void CPlayer::OnCollisionStay(CObject* _coll)
{
	stayCnt++;
}
void CPlayer::OnCollisionExit(CObject* _coll)
{
	endCnt++;
}
