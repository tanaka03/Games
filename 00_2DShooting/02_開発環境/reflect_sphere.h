#ifndef _REFLECTSPHERE_H_
#define _REFLECTSPHERE_H_

#include "skill.h"

class CBullet;

class CReflectSphere : public CSkill
{
public:
	enum NormalVec
	{
		VEC_NONE,
		VEC_RIGHT,
		VEC_LEFT,
		VEC_TOP,
		VEC_BOTTOM,
		VEC_MAX
	};

	CReflectSphere();
	~CReflectSphere();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

private:
	void Draw() override;
	D3DXVECTOR3 CReflectSphere::ReflectMotion(D3DXVECTOR3* vec, NormalVec type);
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_startPos;
	D3DXVECTOR3 m_move;
	CBullet *m_apBullet;
	int m_nEnableTime;
	int m_CollisionTime;
	float m_fAttenuation;
	float m_fCollision;
	float m_fScale;
};

#endif