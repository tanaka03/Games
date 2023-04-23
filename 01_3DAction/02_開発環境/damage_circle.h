#ifndef _DAMAGE_CIRCLE_H_
#define _DAMAGE_CIRCLE_H_

#include "object.h"

class C3DEffectEmitter;
class CNumber;

class CDamageCircle : public CObject
{
public:
	CDamageCircle();
	~CDamageCircle();

	static CDamageCircle *Create(const D3DXVECTOR3 pos, int priority);

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
	C3DEffectEmitter *m_p3DEffect;
	CNumber *m_pDamage;
	int m_time;
	int m_priority;
	float m_scale;
	bool m_bRelease;
};

#endif