//
//MP.h
//
#ifndef _MP_H_
#define _MP_H_

#include "object2d.h"
#include "gauge.h"

class CGaugeFrame;
class CCharUI;

class CMp : public CGauge
{
public:
	CMp();
	~CMp();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

private:
	void Draw() override;
	D3DXVECTOR3 m_pos;
	CGaugeFrame *m_pGaugeFrame;
	CCharUI *m_pChar;
	int m_mp;
	int m_maxMp;
	float m_Width;
	float m_Height;
};

#endif