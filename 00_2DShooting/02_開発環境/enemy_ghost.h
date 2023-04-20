//
//Enemy_Ghost.h
//
#ifndef _ENEMYGHOST_H_
#define _ENEMYGHOST_H_

#include "enemy.h"

class CBullet;
class CItem;

class CEnemyGhost : public CEnemy
{
public:
	CEnemyGhost();
	~CEnemyGhost() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

private:
	void Draw() override;
	D3DXVECTOR3 m_pos;
	ENEMYDATA m_data;
	CBullet *m_pBullet;
	CItem *m_pItem;
	int m_nDamageTime;
	int m_nBulletTime;
};

#endif