//
//Enemy_Dog.h
//
#ifndef _ENEMYDOG_H_
#define _ENEMYDOG_H_

#include "enemy.h"

class CItem;

class CEnemyDog : public CEnemy
{
public:
	CEnemyDog();
	~CEnemyDog() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

private:
	void Draw() override;
	D3DXVECTOR3 m_pos;
	ENEMYDATA m_data;
	CItem *m_pItem;
	int m_nDamageTime;
};

#endif