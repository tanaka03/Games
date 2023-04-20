#ifndef _REGENERATION_H_
#define _REGENERATION_H_

#include "ability.h"

class CRegene : public CAbility
{
public:
	CRegene();
	~CRegene();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

private:
	void Draw() override { ; }
	int m_nTime;
};

#endif