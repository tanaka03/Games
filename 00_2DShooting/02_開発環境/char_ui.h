//
//CharacterUI.h
//
#ifndef _CHARUI_H_
#define _CHARUI_H_

#include "object.h"

class CObject2D;

class CCharUI : public CObject
{
public:
	enum ECharType
	{
		UI_RANK_FIRST,
		UI_RANK_SECOND,
		UI_RANK_THIRD,
		UI_RANK_FOUR,
		UI_RANK_FIVE,
		UI_RANK_SIX,
		UI_RANK_SEVEN,
		UI_RANK_EIGHT,
		UI_RANK_NINE,
		UI_RANK_LAST,
		UI_RANK_NEW,
		UI_HP,
		UI_MP,
		UI_NOWSCORE,
		UI_TUTORIAL1,
		UI_TUTORIAL2,
		UI_TUTORIAL3,
		UI_TUTORIAL4,
		UI_TUTORIAL5,
		UI_TUTORIAL6,
		UI_TITLELOGO,
		UI_PRESS_ENTER,
		UI_START,
		UI_TUTORIAL,
		UI_QUIT,
		UI_MAX,
		UI_NONE = 0
	};

	enum ECharState
	{
		STATE_INVALID = 0,
		STATE_SELECT,
		STATE_BLINK,
		STATE_INVISIBLE,
		STATE_MAX
	};

	CCharUI();
	~CCharUI() override;

	static CCharUI *Create(D3DXVECTOR3 pos, D3DXVECTOR2 scale, ECharType type, ECharState state);
	static CCharUI *Create(D3DXVECTOR3 pos, D3DXVECTOR2 scale, int type, ECharState state);

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

	void SetPos(D3DXVECTOR3 pos) override { m_pos = pos; }
	void SetCharUI(ECharType type) { m_UI = type; }
	void SetCharState(ECharState state) { m_state = state; }
	void SetScale(D3DXVECTOR2 scale) { m_scale = scale; }

	D3DXVECTOR3 GetPos() override { return m_pos; }
	ECharType GetCharUI() { return m_UI; }
	ECharState GetCharState() { return m_state; }

private:
	void Draw() override;
	CObject2D *m_apObject2D;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR2 m_scale;
	D3DXCOLOR m_col;
	ECharType m_UI;
	ECharState m_state;
	bool m_bReverse;
	bool m_bRank;
};

#endif