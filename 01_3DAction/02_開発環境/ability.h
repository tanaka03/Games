#ifndef _ABILITY_H_
#define _ABILITY_H_

class C3DEffectEmitter;

class CAbility
{
public:
	enum EAbilityType
	{
		ABILITY_OVERHP = 0,
		ABILITY_HPHEAL,
		ABILITY_POWERUP,
		ABILITY_STRONGPOWERUP,
		ABILITY_WALKSPEEDUP,
		ABILITY_BEAM,
		ABILITY_FIELD_DAMAGE,
		ABILITY_MAX,
		ABILITY_NONE
	};

	CAbility();
	~CAbility();

	static CAbility *Create(int type);

	HRESULT Init();
	void Uninit();
	void Update();
	void Release() { m_release = true; }
	void AfterRelease() { m_afterRelease = true; }
	void Pause() { m_pause = true; }
	void Resume() { m_pause = false; }

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }

	D3DXVECTOR3 GetPos() { return m_pos; }
	bool GetRelease() { return m_release; }

private:
	D3DXVECTOR3 m_pos;
	EAbilityType m_type;
	C3DEffectEmitter *m_p3DEffect;
	int m_priority;
	bool m_pause;
	bool m_release;
	bool m_afterRelease;
};

#endif