//
//Skill.h
//
#ifndef _SKILL_H_
#define _SKILL_H_

#include "object2d.h"

class CSkill : public CObject2D
{
public:
	enum EType
	{
		SKILLTYPE_NONE = 0,
		SKILLTYPE_MAGNETFIELD,
		SKILLTYPE_REFLECTSPHERE,
		SKILLTYPE_EVASIONTECHNIQUE,
		SKILLTYPE_MAX
	};

	CSkill();
	~CSkill();

	static CSkill *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int EnableTime, EType type);
	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	void SetSkillType(EType type) { m_type = type; }
	void SetEnableTime(int time) { m_nEnableTime = time; }

	EType GetSkillType() { return m_type; }
	int GetEnableTime() { return m_nEnableTime; }

private:
	static CSkill *m_apSkill;
	EType m_type;
	int m_nEnableTime;
};

#endif