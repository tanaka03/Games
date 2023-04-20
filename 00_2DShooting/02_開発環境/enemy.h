//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//Enemy.h
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "object2d.h"

#define MAX_ENEMY	(256)

class CEnemyBullet;

class CEnemy : public CObject2D
{
public:
	enum ENEMYTYPE
	{
		ENEMYTYPE_NONE,
		ENEMYTYPE_DOG,
		ENEMYTYPE_CAT,
		ENEMYTYPE_BIRD,
		ENEMYTYPE_GHOST,
		ENEMYTYPE_FAIRYFIRE,
		ENEMYTYPE_FAIRYAQUA,
		ENEMYTYPE_GIRL,
		ENEMYTYPE_MIRROR,
		ENEMYTYPE_SENSOR,
		ENEMYTYPE_LANDMINE,
		ENEMYTYPE_MAX
	};

	enum ENEMYSTATE
	{
		ENEMYSTATE_NONE = 0,
		ENEMYSTATE_DEFAULT,
		ENEMYSTATE_DAMAGE,
		ENEMYSTATE_MAX
	};

	struct ENEMYDATA
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR2 size;
		D3DXCOLOR col;
		int nLife;
		int nPoptime;
		float fAttenuation;
		float fRadius;
		float fMinAngle;
		float fMaxAngle;
	};

	CEnemy();
	virtual ~CEnemy();

	static CEnemy *Create(D3DXVECTOR3 pos, ENEMYTYPE type);

	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;

	//セッター
	void SetEnemyType(ENEMYTYPE type) { m_type = type; }
	void SetState(ENEMYSTATE state) { m_state = state; }
	void SetFiringTime(int time) { m_nFiringTime = time; }
	void SetKillScore(int score) { m_nScore = score; }
	void SetPlayerDamage(int hit) { m_nPlayerDamage = hit; }
	void SetBulletLife(int life) { m_nBulletLife = life; }
	void SetIdx(int idx) { m_nIdx = idx; }

	//ゲッター
	ENEMYTYPE GetEnemyType() { return m_type; }
	ENEMYSTATE GetState() { return m_state; }
	int GetFiringTime() { return m_nFiringTime; }
	int GetKillScore() { return m_nScore; }
	int GetPlayerDamage() { return m_nPlayerDamage; }
	int GetBulletLife() { return m_nBulletLife; }
	int GetIdx() { return m_nIdx; }

private:
	virtual void Draw() = 0;
	D3DXVECTOR3 m_pos;
	ENEMYTYPE m_type;
	ENEMYSTATE m_state;
	ENEMYDATA m_data;
	CEnemyBullet *m_pBullet;
	int m_nCounterAnim;
	int m_nPatternAnim;
	int m_nFiringTime;
	int m_nBulletTime;
	int m_nBulletLife;
	int m_nDamageTime;
	int m_nPlayerDamage;
	int m_nScore;
	int m_nIdx;
	bool m_bOnce;
};

#endif