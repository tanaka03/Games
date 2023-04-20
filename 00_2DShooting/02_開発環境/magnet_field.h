#ifndef _MAGNETFIELD_H_
#define _MAGNETFIELD_H_

#include "skill.h"

class CMagnetField : public CSkill
{
public:
	CMagnetField();
	~CMagnetField();

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