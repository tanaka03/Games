//
//Ability.h
//
#ifndef _ABILITY_H_
#define _ABILITY_H_

#include "object2d.h"

class CAbility : public CObject2D
{
public:
	enum EAbilityType
	{
		ABILITYTYPE_NONE = 0,
		ABILITYTYPE_BEAM,
		ABILITYTYPE_MAGNET,
		ABILITYTYPE_MAX
	};

	CAbility();
	~CAbility();

	static CAbility *Create(D3DXVECTOR3 pos, EAbilityType type);
	static CAbility *Create(D3DXVECTOR3 pos, int EnableTime,EAbilityType type);

	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;

	void SetEnableTime(int time) { m_nLife = time; }
	void SetState(bool state) { m_bState = state; }
	void SetABType(EAbilityType type) { m_type = type; }

	static int GetNumAll() { return m_nNumAll; }
	int GetEnableTime() { return m_nLife; }
	bool GetState() { return m_bState; }
	EAbilityType GetABType() { return m_type; }

private:
	static CAbility *m_apAbility;
	static int m_nNumAll;

	virtual void Draw() = 0;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	EAbilityType m_type;
	int m_nLife;
	float m_Radius;
	bool m_bState;
	bool m_Once;
};

#endif