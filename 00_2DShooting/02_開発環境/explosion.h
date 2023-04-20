//
//Explosion.h
//
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

class CExplosion : public CObject2D
{
public:
	CExplosion();
	~CExplosion() override;

	static CExplosion *Create(D3DXVECTOR3 pos);

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

private:
	void Draw() override;
};

#endif