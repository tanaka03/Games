#include "bullet.h"
#include "object2d.h"
#include "enemybullet.h"
#include "main.h"
#include "playerbullet.h"
#include "texture.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//静的メンバ変数宣言
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CBullet *CBullet::m_apBullet;

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//弾のコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CBullet::CBullet()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_fBulletCollision = 5.0f;
	m_fAngle = 0.0f;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//弾のデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CBullet::~CBullet()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//弾の生成
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CBullet * CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int life, EType type, ETag tag)
{
	switch (tag)
	{
	case BULLETTAG_PLAYER:
		m_apBullet = new CPlayerBullet;
		break;

	case BULLETTAG_ENEMY:
		m_apBullet = new CEnemyBullet;
		break;

	default:
		break;
	}

	//ヌルチェック
	if (m_apBullet != nullptr)
	{
		m_apBullet->SetPos(pos);
		m_apBullet->SetMove(move);
		m_apBullet->SetCol(col);
		m_apBullet->SetLife(life);
		m_apBullet->SetSound(true);
		m_apBullet->Init();
		m_apBullet->SetBulletType(type);
	}

	return m_apBullet;
}

CBullet * CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int life,bool sound, EType type, ETag tag)
{
	switch (tag)
	{
	case BULLETTAG_PLAYER:
		m_apBullet = new CPlayerBullet;
		break;

	case BULLETTAG_ENEMY:
		m_apBullet = new CEnemyBullet;
		break;

	default:
		break;
	}

	//ヌルチェック
	if (m_apBullet != nullptr)
	{
		m_apBullet->SetPos(pos);
		m_apBullet->SetMove(move);
		m_apBullet->SetCol(col);
		m_apBullet->SetLife(life);
		m_apBullet->SetSound(sound);
		m_apBullet->Init();
		m_apBullet->SetBulletType(type);
	}

	return m_apBullet;
}

D3DXVECTOR3 CBullet::TypeMotion(EType type)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 move = GetMove();
	SetBulletType(type);

	switch (type)
	{
	case BULLETTYPE_NORMAL:
		break;

	case BULLETTYPE_SETTING:
		move.y += 0.5f;

		if (move.y >= 0.0f)
		{
			move.y = 0.0f;
		}
		break;

	case BULLETTYPE_CURVE:
		m_fAngle += 10.0f;
		move = m_pBulletUtility->CurveMotion(&GetMove(), m_fAngle, 40.0f);
		break;

	case BULLETTYPE_REFLECTION:
		if (pos.y <= 0.0f)
		{
			D3DXVECTOR3 CollisionPos = GetPos();
			D3DXVECTOR3 vec = CollisionPos - GetFirstPos();

			move = m_pBulletUtility->ReflectMotion(&vec, m_pBulletUtility->VEC_TOP) * 0.02f;
		}

		if (pos.y >= SCREEN_HEIGHT)
		{
			D3DXVECTOR3 CollisionPos = GetPos();
			D3DXVECTOR3 vec = CollisionPos - GetFirstPos();

			move = m_pBulletUtility->ReflectMotion(&vec, m_pBulletUtility->VEC_BOTTOM) * 0.02f;
		}

		if (pos.x <= 0.0f)
		{
			D3DXVECTOR3 CollisionPos = GetPos();
			D3DXVECTOR3 vec = CollisionPos - GetFirstPos();

			move = m_pBulletUtility->ReflectMotion(&vec, m_pBulletUtility->VEC_LEFT) * 0.02f;
		}

		if (pos.x >= SCREEN_WIDTH)
		{
			D3DXVECTOR3 CollisionPos = GetPos();
			D3DXVECTOR3 vec = CollisionPos - GetFirstPos();

			move = m_pBulletUtility->ReflectMotion(&vec, m_pBulletUtility->VEC_RIGHT) * 0.02f;
		}
		break;

	default:
		break;
	}

	return move;
}