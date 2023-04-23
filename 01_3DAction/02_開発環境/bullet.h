//
//Bullet.h
//
#ifndef _BULLET_H_
#define _BULLET_H_

#include "billboard.h"

class CBullet : public CBillboard
{
public:
	explicit CBullet(int priority);
	~CBullet() override;

	static CBullet* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int life, int priority);

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetLife(int life) { m_life = life; }

	int GetLife() { return m_life; }

private:
	int m_life;			//’e‚Ì¶‘¶ŠÔ
};

#endif