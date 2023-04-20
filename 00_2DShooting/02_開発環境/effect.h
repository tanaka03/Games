//
//Effect.h
//
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "object2d.h"

class CEffect : public CObject2D
{
public:
	enum EEffectType
	{
		EFFECTTYPE_NONE = 0,
		EFFECTTYPE_EXPLOSION,
		EFFECTTYPE_BRIGHT,
		EFFECTTYPE_BRIGHT2,
		EFFECTTYPE_ASTER,
		EFFECTTYPE_ROSE,
		EFFECTTYPE_HEART,
		EFFECTTYPE_SPARK,
		EFFECTTYPE_MAGIC,
		EFFECTTYPE_MAGIC2,
		EFFECTTYPE_MAX
	};

	enum EBehavior
	{
		BEHAVIOR_NONE = 0,
		BEHAVIOR_SCALEUP,
		BEHAVIOR_SCALEDOWN,
		BEHAVIOR_INVISIBLE,
		BEHAVIOR_ROTATION,
		BEHAVIOR_PLAYER,
		BEHAVIOR_MAX
	};

	CEffect();
	~CEffect();

	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int life, EEffectType type);

	HRESULT Init(EEffectType type);
	void Uninit() override;
	void Update() override;
	void Behavior_Utility(EBehavior type);

	void SetBehavior(EBehavior typeA) { m_behavior = typeA; }
	void SetBehavior(EBehavior typeA, EBehavior typeB) { m_behavior = typeA, m_behaviorB = typeB; }
	void SetBehavior(EBehavior typeA, EBehavior typeB, EBehavior typeC) { m_behavior = typeA, m_behaviorB = typeB, m_behaviorC = typeC; }
	void SetRotSpeed(float speed) { m_fRotSpeed = speed; }
	void SetAlphaBlend(bool blend) { m_bAlphaBlend = blend; }

	EBehavior GetBehavior() { return m_behavior; }
	EBehavior GetBehaviorB() { return m_behaviorB; }
	EBehavior GetBehaviorC() { return m_behaviorC; }
	float GetRotSpeed() { return m_fRotSpeed; }
	bool GetAlphaBlend() { return m_bAlphaBlend; }

private:
	void Draw() override;
	void Rotation();
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR2 m_scale;
	D3DXCOLOR m_col;
	EBehavior m_behavior , m_behaviorB, m_behaviorC;
	int m_nLife;
	int m_nTimer;
	float m_fRotSpeed;
	bool m_bRotation = false;
	bool m_bAnim = false;
	bool m_bAlphaBlend = true;
};

#endif