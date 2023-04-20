#ifndef _MAGNET_H_
#define _MAGNET_H_

#include "ability.h"

class CMagnet : public CAbility
{
public:
	CMagnet();
	~CMagnet();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

private:
	void Draw() override { ; }
	int m_nTime;
};

#endif