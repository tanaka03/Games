//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//EnemyFunnel.h
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#ifndef _ENEMYFUNNEL_H_
#define _ENEMYFUNNEL_H_

#include "object2d.h"

class CBullet;
class CEffect;

class CEnemyFunnel : public CObject2D
{
public:
	enum EType
	{
		FUNNEL_BULLET,
		FUNNEL_MAX,
		FUNNEL_INVALID = 0
	};

	CEnemyFunnel();
	~CEnemyFunnel();

	static CEnemyFunnel *Create(D3DXVECTOR3 pos, EType type);

	HRESULT Init();
	void Uninit();
	void Update();

	void SetFunnel(EType type) { m_type = type; }

	EType GetFunnel() { return m_type; }

private:
	void Draw();
	D3DXVECTOR3 m_pos;
	EType m_type;
	int m_nPressTime = 0;
	int m_nEffectTime = 0;
	float m_fAngle;
	CBullet *m_pBullet;
	CEffect *m_pEffect;

	//回転用
	float m_fRotZ = 0.0f;

	// 形成する四角形の基準値
	const D3DXVECTOR3 sVtx[4] =
	{
		D3DXVECTOR3(-1.0f, -1.0f, 0.0f),
		D3DXVECTOR3(+1.0f, -1.0f, 0.0f),
		D3DXVECTOR3(-1.0f, +1.0f, 0.0f),
		D3DXVECTOR3(+1.0f, +1.0f, 0.0f),
	};

	// タイマー
	float m_fTimer;
};

#endif