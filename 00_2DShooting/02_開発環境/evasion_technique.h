#ifndef _EVASIONTECHNIQUE_H_
#define _EVASIONTECHNIQUE_H_

#include "skill.h"

class CEvasionTechnique : public CSkill
{
public:
	CEvasionTechnique();
	~CEvasionTechnique();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

private:
	void Draw() override;
	D3DXVECTOR3 m_pos;
	int m_nEnableTime;
	float m_fCollision;

	static int m_nCntAll;
};

#endif