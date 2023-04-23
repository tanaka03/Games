//
//HP.h
//
#ifndef _HP_H_
#define _HP_H_

#include "3dgauge.h"

class CHp : public C3DGauge
{
public:
	CHp(int priority);
	~CHp();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

private:
	void Draw() override;

	CBillboard* m_pFrame;

	float m_Width;
	float m_Height;
};

#endif