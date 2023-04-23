//
//Damage.h
//
#ifndef _DAMAGE_H_
#define _DAMAGE_H_

#include "number.h"
#include "billboard.h"

class CNumber;

class CDamage : public CBillboard
{
public:
	CDamage(int priority);
	~CDamage() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void End() { m_end = true; }

	void SetDamage(int score);
	void SetMaxDamage(int digit);
	void SetDigit(int digit) { m_digit = digit; }
	void SetPosTexU(int pos) { m_posTexU = pos; }

	bool GetEnd() { return m_end; }

private:
	void Draw() override;

	D3DXVECTOR3 m_beginPos;
	int m_posTexU;
	int m_digit;
	int m_damage;
	int m_maxDamage;
	bool m_end;
};

#endif