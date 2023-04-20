#include "skill.h"
#include "magnet_field.h"
#include "reflect_sphere.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//静的メンバ変数宣言
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CSkill *CSkill::m_apSkill;

CSkill::CSkill()
{
}

CSkill::~CSkill()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//スキルの生成
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CSkill * CSkill::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int EnableTime, EType type)
{
	switch (type)
	{
	case SKILLTYPE_MAGNETFIELD:
		m_apSkill = new CMagnetField;
		break;

	case SKILLTYPE_REFLECTSPHERE:
		m_apSkill = new CReflectSphere;
		break;

	default:
		break;
	}

	//ヌルチェック
	if (m_apSkill != nullptr)
	{
		m_apSkill->SetPos(pos);
		m_apSkill->SetMove(move);
		m_apSkill->SetType(CObject::OBJTYPE_SKILL);
		m_apSkill->SetEnableTime(EnableTime);
		m_apSkill->Init();
	}

	return m_apSkill;
}