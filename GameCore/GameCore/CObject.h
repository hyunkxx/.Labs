#pragma once
enum class OBJ_STATE { NONE, ACTIVE, PAUSE, DEAD };

class CCollider;

class CObject
{
public:
	CObject();
	CObject(float _x, float _y, float _salce);
	CObject(Vector2D _value, float _scale);
	virtual ~CObject();
public:
	virtual void Initalize();
	virtual int Update(double _fDeltaTime);
	virtual void LateUpdate(double _fDeltaTime);
	virtual void Render(HDC _hdc) const;
	virtual void Release();
	virtual void ComponentUpdate(double _fDeltaTime) final;
	virtual void ComponentRender(HDC _hdc) final;
public:
	void SetX(float _value) { m_vPos.fX = _value; }
	void SetY(float _value) { m_vPos.fY = _value; }
	const float& GetX() const { return m_vPos.fX; }
	const float& GetY() const { return m_vPos.fY; }
	void SetPosition(Vector2D _value) { m_vPos = _value; }
	const Vector2D& GetPosition() const { return m_vPos; }
	void SetScale(float _value) { m_fScale = _value; }
	const float& GetScale() const { return m_fScale; }

	bool CompareState(OBJ_STATE _eType) { return m_eState == _eType; }
	const OBJ_STATE& GetState() const { return m_eState; }
	void SetState(OBJ_STATE _eType) { m_eState = _eType; }
public:
	virtual void OnCollisionEnter(CObject* _coll);
	virtual void OnCollisionStay(CObject* _coll);
	virtual void OnCollisionExit(CObject* _coll);
public:
	CCollider* GetCollider() { if (m_pCollider) return m_pCollider; else return nullptr; }
	void CreateCollider();
private://Components
	CCollider* m_pCollider;
private:
	void setRect();
protected:
	RECT m_rcRect;
	Vector2D m_vPos;
	OBJ_STATE m_eState;
	
	float m_fScale;
};

