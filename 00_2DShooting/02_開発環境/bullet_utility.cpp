#include "bullet_utility.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//弾の動作のコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CBulletUtility::CBulletUtility()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//弾の動作のデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CBulletUtility::~CBulletUtility()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//弾の動作（追従）
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
D3DXVECTOR3 CBulletUtility::AdulationMotion(D3DXVECTOR3* pos, D3DXVECTOR3* Destpos)
{
	D3DXVECTOR3 Pos = *pos;
	D3DXVECTOR3 DestPos = *Destpos;

	D3DXVECTOR3 vec = DestPos - Pos;

	//正規化
	D3DXVec3Normalize(&vec, &vec);

	//追従
	D3DXVECTOR3 move = vec;
	return move;
}

D3DXVECTOR3 CBulletUtility::AdulationMotion(D3DXVECTOR3* vec)
{
	D3DXVECTOR3 Vec = *vec;

	//正規化
	D3DXVec3Normalize(&Vec, &Vec);

	//追従
	D3DXVECTOR3 move = Vec;
	return move;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//弾の動作（カーブ）
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
D3DXVECTOR3 CBulletUtility::CurveMotion(D3DXVECTOR3* move, float angle, float width)
{
	D3DXVECTOR3 Move = *move;

	Move.x = sinf((D3DX_PI / 180) - (angle / width));
	Move.y = powf(cosf((D3DX_PI / 90) - (angle / width)),2);

	return Move * 10.0f;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//弾の動作（反射）
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
D3DXVECTOR3 CBulletUtility::ReflectMotion(D3DXVECTOR3* vec, D3DXVECTOR3* Normalvec)
{
	D3DXVECTOR3 DestVec = *vec;
	D3DXVECTOR3 Vec = *Normalvec;

	D3DXVec3Normalize(&Vec, &Vec);
	float fDot = D3DXVec3Dot(&Vec, &(-DestVec));

	return (2 * fDot * Vec) + DestVec;
}

D3DXVECTOR3 CBulletUtility::ReflectMotion(D3DXVECTOR3* vec, NormalVec type)
{
	D3DXVECTOR3 DestVec = *vec;
	D3DXVECTOR3 Vec = D3DXVECTOR3(0.0f,0.0f,0.0f);

	switch (type)
	{
	case VEC_TOP:
		Vec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		break;

	case VEC_BOTTOM:
		Vec = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		break;

	case VEC_LEFT:
		Vec = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
		break;

	case VEC_RIGHT:
		Vec = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		break;

	default:
		break;
	}

	D3DXVec3Normalize(&Vec, &Vec);
	float fDot = D3DXVec3Dot(&Vec, &(-DestVec));

	return (2 * fDot * Vec) + DestVec;
}