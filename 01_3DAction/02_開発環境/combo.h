//
//Combo.h
//
#ifndef _COMBO_H_
#define _COMBO_H_

#include "number.h"
#include "object2d.h"

class CCombo : public CObject2D
{
public:
	CCombo(int priority);
	~CCombo() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

	void SetCombo(int combo);
	void SetMaxCombo(int digit);
	void SetBeginTime(int time) { m_time = time; }
	void SetDigit(int digit) { m_digit = digit; }
	void SetPosTexU(int pos) { m_posTexU = pos; }

private:
	void Draw() override;
	
	D3DXVECTOR3 m_pos;
	int m_posTexU;
	int m_digit;
	int m_combo;
	int m_maxCombo;
	int m_time;
};

#endif