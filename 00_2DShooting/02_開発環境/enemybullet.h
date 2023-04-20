//
//EnemyBullet.h
//
#ifndef _ENEMYBULLET_H_
#define _ENEMYBULLET_H_

#include "bullet.h"

#define MAX_BULLET	(128)
#define NUM_BULLET	(8)

class CEffect;

class CEnemyBullet : public CBullet
{
public:
	CEnemyBullet();
	~CEnemyBullet() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

	void SetGraze(bool set) { m_bGraze = set; }

	bool GetGraze() { return m_bGraze; }

private:
	void Draw() override;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	D3DXVECTOR2 m_scale;
	D3DXCOLOR m_col;
	ETag m_tag;
	CEffect *m_pEffect;
	int m_nLife;
	int m_nCollisionTime;
	float m_fBulletCollision;
	bool m_bGraze = true;
};

#endif