//
//Enemy_FairyFire.h
//
#ifndef _ENEMYFAIRYFIRE_H_
#define _ENEMYFAIRYFIRE_H_

#include "enemy.h"

class CItem;
class CBullet;

class CEnemyFairyFire : public CEnemy
{
public:
	CEnemyFairyFire();
	~CEnemyFairyFire() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	
private:
	void Draw() override;
	D3DXVECTOR3 m_pos;
	ENEMYDATA m_data;
	CItem *m_pItem;
	CBullet *m_pBullet;
	int m_nDamageTime;
	int m_nBulletTime;
};

#endif