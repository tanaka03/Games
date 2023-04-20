//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//Player.h
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "object2d.h"

//前方宣言
class CAbility;
class CBullet;
class CEffect;
class CFunnel;
class CSkill;
class CFragment;
class CGauge;

class CPlayer : public CObject2D
{
public:
	enum ESTATE
	{
		STATE_NONE = 0,
		STATE_DEFAULT,
		STATE_DAMAGE,
		STATE_INVINCIBLE,
		STATE_MAX
	};

	CPlayer();
	~CPlayer() override;

	static CPlayer *Create();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

	//セッター
	void SetMP(int mp) { m_nMp = mp; }
	void SetInvincible(int time) { m_nInvincibleTime = time; }
	void SetMoving(bool move) { m_bMoving = move; }
	void SetFunnel(bool use) { m_bFunnel = use; }
	void SetState(ESTATE state) { m_state = state; }

	//ゲッター
	int GetMP() { return m_nMp; }
	int GetInvincible() { return m_bInvincible; }
	bool GetMoving() { return m_bMoving; }
	bool GetFunnel() { return m_bFunnel; }
	ESTATE GetState() { return m_state; }

private:
	void Draw() override;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	D3DXCOLOR m_col;
	ESTATE m_state;
	CAbility *m_pAbility;
	CBullet *m_pBullet = nullptr;
	CEffect *m_pEffect = nullptr;
	CGauge *m_pGauge = nullptr;
	CSkill *m_pSkill = nullptr;
	CFragment *m_pFragment = nullptr;
	CFunnel *m_pFunnel[2] = {};
	int m_nDamageTime = 0;
	int m_nInvincibleTime = 0;
	int m_nPressTime = 0;
	int m_InitCounter = 0;
	int m_nTime = 0;
	int m_nMp = 0;
	float m_fSpeed = 10.0f;
	bool m_bMoving = false;
	bool m_bInvincible = false;
	bool m_bFunnel = false;
	bool m_bOnce = true;

	//回転用
	float m_fRotZ = 0.0f;

	// 形成する四角形の基準値
	const D3DXVECTOR3 sVtx[4] =
	{
		D3DXVECTOR3(-1.0f, -1.0f, 0.0f),
		D3DXVECTOR3(+1.0f, -1.0f, 0.0f),
		D3DXVECTOR3(-1.0f, +2.0f, 0.0f),
		D3DXVECTOR3(+1.0f, +2.0f, 0.0f),
	};

	// タイマー
	float m_fTimer;
};

#endif