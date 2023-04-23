#ifndef _SKILL_H_
#define _SKILL_H_

#include "object.h"

class CSkill : public CObject
{
public:
	CSkill();
	~CSkill();

	static CSkill *Create(const D3DXVECTOR3 pos, int priority);

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
	int m_time;
	int m_priority;
	float m_scale;
	bool m_bRelease;
};

#endif