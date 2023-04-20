//
//Enemy_Girl.h
//
#ifndef _ENEMYGIRL_H_
#define _ENEMYGIRL_H_

#include "enemy.h"

class CItem;
class CBullet;
class CEffect;
class CEnemyFunnel;

class CEnemyGirl : public CEnemy
{
public:
	CEnemyGirl();
	~CEnemyGirl() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

private:
	void Draw() override;
	D3DXVECTOR3 m_pos;
	ENEMYDATA m_data;
	CItem *m_pItem;
	CBullet *m_pBullet;
	CEffect *m_pEffect;
	CEnemyFunnel *m_pFunnel[2];
	int m_nDamageTime;
	int m_nBulletTime;
	int m_nItemTime;
	bool m_bFunnel;
};

#endif