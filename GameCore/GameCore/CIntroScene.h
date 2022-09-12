#pragma once

#include "CScene.h"

class CIntroScene : public CScene
{
public:
	CIntroScene(wstring _szName);
	~CIntroScene();
public:
	void Enter() override;
	void Exit() override;
	void Initalize() override;
	void Update(double _fDeltaTime) override;
	void LateUpdate(double _fDeltaTime) override;
	void Render(HDC _hdc) override;
	void Release() override;
private:
	class CObject* m_pPlayer;
};

