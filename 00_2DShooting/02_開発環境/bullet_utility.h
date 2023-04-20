//
//Bullet_Utility.h
//
#ifndef _BULLET_UTILITY_H_
#define _BULLET_UTILITY_H_

#include "bullet.h"

class CBulletUtility
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

	CBulletUtility();
	~CBulletUtility();

	D3DXVECTOR3 AdulationMotion(D3DXVECTOR3* pos, D3DXVECTOR3* Destpos);
	D3DXVECTOR3 AdulationMotion(D3DXVECTOR3* vec);
	D3DXVECTOR3 CurveMotion(D3DXVECTOR3* move, float angle, float width);
	D3DXVECTOR3 ReflectMotion(D3DXVECTOR3* vec, NormalVec type);
	D3DXVECTOR3 ReflectMotion(D3DXVECTOR3* vec, D3DXVECTOR3* Destvec);

private:
	NormalVec m_vec;
};

#endif