#pragma once

enum class COL_STATE
{
	NONE,
	ENTER,
	STAY,
	EXIT
};

class CCollider
{
	friend class CObject;
public:
	CCollider();
	~CCollider();
public:
	void Update(double _fDeltaTieme);
	void Render(HDC _hdc);
public:
	Vector2D GetOffset() { return m_vOffset; }
	void SetOffset(float _x, float _y) { m_vOffset = Vector2D(_x,_y); };
	Vector2D GetOriginPos() { return m_vOriginPos; }
	void SetOriginPos(Vector2D _vOriginPos) { m_vOriginPos = _vOriginPos; };
	float GetScale() { return m_fScale; }
	void SetScale(float _fScale) { m_fScale = _fScale; }
	COL_STATE GetState() { return m_eState; }

	const RECT& GetRect() { return m_rcCollision; };

	void setRect()
	{
		m_rcCollision.left = (int)(m_vOriginPos.fX + m_vOffset.fX - m_fScale);
		m_rcCollision.top = (int)(m_vOriginPos.fY + m_vOffset.fY - m_fScale);
		m_rcCollision.right = (int)(m_vOriginPos.fX + m_vOffset.fX + m_fScale);
		m_rcCollision.bottom = (int)(m_vOriginPos.fY + m_vOffset.fY + m_fScale);
	}
public:
	void Enter(CObject* _coll);
	void Exit(CObject* _coll);
private:
	RECT m_rcCollision;
	CObject* m_pOwner;
	Vector2D m_vOffset; 
	Vector2D m_vOriginPos;
	float m_fScale;

	bool m_bPrevHit;
	COL_STATE m_eState;
};

