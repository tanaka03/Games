//
//HP.h
//
#ifndef _HP_H_
#define _HP_H_

#include "object2d.h"
#include "gauge.h"

class CGaugeFrame;
class CCharUI;

class CHp : public CGauge
{
public:
	CHp();
	~CHp();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

private:
	void Draw() override;
	D3DXVECTOR3 m_pos;
	CGaugeFrame *m_pGaugeFrame;
	CCharUI *m_pChar;
	int m_hp;
	int m_maxHp;
	float m_Width;
	float m_Height;
};

#endif