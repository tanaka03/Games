//
//Bullet.h
//
#ifndef _BULLET_H_
#define _BULLET_H_

#include "object2d.h"
#include "bullet_utility.h"

#define MAX_BULLET	(128)
#define NUM_BULLET	(8)

class CBulletUtility;

class CBullet : public CObject2D
{
public:
	enum EType
	{
		BULLETTYPE_NONE = 0,
		BULLETTYPE_NORMAL,
		BULLETTYPE_ADULATION,
		BULLETTYPE_SETTING,
		BULLETTYPE_CURVE,
		BULLETTYPE_REFLECTION,
		BULLETTYPE_MAX
	};

	enum ETag
	{
		BULLETTAG_NONE = 0,
		BULLETTAG_PLAYER,
		BULLETTAG_ENEMY,
		BULLETTAG_MAX
	};

	CBullet();
	~CBullet();

	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int life, EType type, ETag tag);
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int life, bool sound, EType type, ETag tag);
	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	D3DXVECTOR3 TypeMotion(EType type);

	void SetFirstPos(D3DXVECTOR3 pos) { m_firstPos = pos; }
	void SetBulletTag(ETag tag) { m_tag = tag; }
	void SetBulletType(EType type) { m_type = type; }
	void SetCollisionScale(float scale) { m_fBulletCollision = scale; }
	void SetSound(bool sound) { m_bSound = sound; }

	D3DXVECTOR3 GetFirstPos() { return m_firstPos; }
	ETag GetBulletTag() { return m_tag; }
	EType GetBulletType() { return m_type; }
	float GetCollisionScale() { return m_fBulletCollision; }
	bool GetSound() { return m_bSound; }

private:
	static CBullet *m_apBullet;

	virtual void Draw() = 0;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_firstPos;
	D3DXVECTOR3 m_move;
	EType m_type;
	ETag m_tag;
	CBulletUtility *m_pBulletUtility;
	int m_nLife;
	float m_fAngle;
	float m_fBulletCollision;
	bool m_bSound;
};


#endif