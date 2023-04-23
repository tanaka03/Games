//
//EXP.h
//
#ifndef _EXP_H_
#define _EXP_H_

#include "gauge.h"

class CExp : public CGauge
{
public:
	CExp(int priority);
	~CExp();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

private:
	void Draw() override;
	float m_Width;
	float m_Height;
};

#endif