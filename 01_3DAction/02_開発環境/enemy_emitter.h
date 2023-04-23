//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//EnemyEmitter.h
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#ifndef _ENEMIEMITTER_H_
#define _ENEMIEMITTER_H_

#include "enemy.h"

class CEnemy;

class CEnemyEmitter
{
public:
	CEnemyEmitter();
	~CEnemyEmitter();

	static CEnemyEmitter* Create();

	HRESULT Init();
	void Uninit();
	void Update();
	void AfterRelease() { m_afterRelease = true; }

	//セッター
	void SetPos(D3DXVECTOR3& pos) { m_popPos = pos; }

	//ゲッター
	D3DXVECTOR3& GetPos() { return m_popPos; }

private:
	int maxPopEnemy;

	std::vector<CEnemy*> m_enemy;
	std::vector<CEnemy::SInfo> m_enemyInfo;
	D3DXVECTOR3 m_popPos;
	int m_time;
	int m_spawnCounter;
	int m_spawnTimer;
	bool m_afterRelease;
};

#endif