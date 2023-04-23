#ifndef _ABILITY_SELECT_H_
#define _ABILITY_SELECT_H_

class CObject2D;
class CAbility;

class CAbilitySelect
{
public:
	CAbilitySelect();
	~CAbilitySelect();

	static CAbilitySelect *Create();

	HRESULT Init();
	void Uninit();
	void Update();
	void AfterRelease() { m_afterRelease = true; }
	void Start();

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }

	D3DXVECTOR3 GetPos() { return m_pos; }
	CObject2D *GetAbilitySlot(int idx) { return m_pAbilitySlot[idx]; }

private:
	static const int numAbility = 3;

	D3DXVECTOR3 m_pos;
	std::vector<CObject2D*> m_pAbilitySlot;
	std::vector<CObject2D*> m_pSelectFrame;
	std::vector<CAbility*> m_pAbility;
	int m_time;
	int m_divisionX;
	int m_divisionY;
	int m_selectAbility[numAbility];
	int m_selectNum;
	int m_priority;
	bool m_slotStart;
	bool m_afterRelease;
};

#endif