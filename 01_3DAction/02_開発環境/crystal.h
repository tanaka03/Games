#ifndef _CRYSTAL_H_
#define _CRYSTAL_H_

#include "object.h"

class C3DEffectEmitter;
class CNumber;

class CCrystal : public CObject
{
public:
	CCrystal();
	~CCrystal();

	static CCrystal *Create(const D3DXVECTOR3 pos, int priority);

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw() override {};
	void Destroy() { m_bRelease = true; }

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }

	D3DXVECTOR3 GetPos() { return m_pos; }
	bool GetDestroy() { return m_bRelease; }

private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	C3DEffectEmitter *m_p3DEffect;
	CNumber *m_pDamage;
	int m_time;
	int m_priority;
	float m_scale;
	bool m_bRelease;
};

#endif