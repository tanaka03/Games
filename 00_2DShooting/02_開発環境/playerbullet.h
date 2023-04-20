//
//PlayerBullet.h
//
#ifndef _PLAYERBULLET_H_
#define _PLAYERBULLET_H_

#include "bullet.h"

#define MAX_BULLET	(128)
#define NUM_BULLET	(8)

class CEffect;

class CPlayerBullet : public CBullet
{
public:
	CPlayerBullet();
	~CPlayerBullet() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

private:
	void Draw() override;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_Destpos;
	D3DXVECTOR3 m_startPos;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_vec;
	D3DXCOLOR m_col;
	ETag m_tag;
	CBulletUtility *m_pBulletUtility;
	CEffect *m_pEffect;
	int m_nLife;
	int m_nCollisionTime;
	float m_fBulletCollision;
	bool m_bOnce;
};


#endif