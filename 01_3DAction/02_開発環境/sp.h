//
//SP.h
//
#ifndef _SP_H_
#define _SP_H_

#include "gauge.h"

class CSp : public CGauge
{
public:
	CSp(int priority);
	~CSp();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

private:
	void Draw() override;
	float m_Width;
	float m_Height;
};

#endif