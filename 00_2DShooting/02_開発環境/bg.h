//
//BackGround.h
//
#ifndef _BG_H_
#define _BG_H_

#include "object.h"

class CObject2D;

class CBg : public CObject
{
public:
	enum EBGType
	{
		BG_NONE = 0,
		BG_TITLE,
		BG_TITLELACE1,
		BG_GAME1,
		BG_GAMECLOUD,
		BG_GAMEBRIGHT,
		BG_GAMELACE1,
		BG_RESULT,
		BG_TUTORIAL,
		BG_MAX
	};

	CBg();
	~CBg() override;

	static CBg *Create(EBGType type, bool alpha);

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

	void SetPos(D3DXVECTOR3 pos) override { m_pos = pos; }
	void SetBg(EBGType type) { m_bg = type; }
	void SetRange(D3DXVECTOR2 range) { m_range = range; }
	void SetAlpha(float alpha) { m_col.a = alpha; }
	void SetScroll(bool scroll) { m_bScroll = scroll; }
	void SetScroll(bool scroll, float speed) { m_bScroll = scroll, m_fSpeed = speed; }
	void SetScroll(bool scroll, float speed, bool horizon) { m_bScroll = scroll, m_fSpeed = speed, m_bHorizon = horizon; }
	void SetAlphaBlend(bool blend) { m_bAdditive = blend; }

	D3DXVECTOR3 GetPos() override { return m_pos; }
	EBGType GetBg() { return m_bg; }
	D3DXVECTOR2 GetRange() { return m_range; }
	float GetAlpha() { return m_col.a; }
	bool GetScroll() { return m_bScroll; }
	bool GetHorizon() { return m_bHorizon; }
	bool GetAlphaBlend() { return m_bAdditive; }

private:
	void Draw() override;
	CObject2D *m_apObject2D;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR2 m_range;
	D3DXCOLOR m_col;
	EBGType m_bg;
	float m_fV;
	float m_fSpeed = 0.005f;
	bool m_bScroll;
	bool m_bHorizon = false;
	bool m_bAdditive;
};

#endif