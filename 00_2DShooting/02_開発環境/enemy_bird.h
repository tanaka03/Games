//
//Enemy_Bird.h
//
#ifndef _ENEMYBIRD_H_
#define _ENEMYBIRD_H_

#include "enemy.h"

class CItem;
class CBullet;

class CEnemyBird : public CEnemy
{
public:
	CEnemyBird();
	~CEnemyBird() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

	void SetFirstMove(D3DXVECTOR3 move) { m_firstMove = move; }

	D3DXVECTOR3 GetFirstMove() { return m_firstMove; }

private:
	void Draw() override;
	D3DXVECTOR3 m_firstMove;
	ENEMYDATA m_data;
	CItem *m_pItem;
	CBullet *m_pBullet;
	int m_nDamageTime;
	int m_nBulletTime;
	int m_nCntBullet = 0;
	float m_fAngle;
	bool m_bOnce = true;
};

#endif