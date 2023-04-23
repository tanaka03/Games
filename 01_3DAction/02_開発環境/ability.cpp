#include "ability.h"
#include "player.h"
#include "application.h"
#include "game.h"
#include "3deffect_emitter.h"
#include "hp.h"

#include "utility.h"
#include "particle.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// アビリティのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CAbility::CAbility() : m_afterRelease(false)
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// アビリティのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CAbility::~CAbility()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// アビリティの生成
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CAbility * CAbility::Create(int type)
{
	CAbility *pSkill = nullptr;
	pSkill = new CAbility;

	//ヌルチェック
	if (pSkill != nullptr)
	{
		pSkill->m_type = (EAbilityType)type;
		pSkill->Init();
	}

	return pSkill;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// アビリティの初期化
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
HRESULT CAbility::Init()
{
	CPlayer *pPlayer = CApplication::GetInstance()->GetMode()->GetGame()->GetPlayer();
	CPlayer::SSkill pSkill = pPlayer->GetSkill();
	int nValue = 0;
	float fValue = 0.0f;

	// パーティクル
	std::vector<std::string> list;
	CParticle::SInfo particle = {};
	int popParticleValue;

	switch (m_type)
	{
	case ABILITY_OVERHP:
		nValue = pPlayer->GetHPGauge()->GetMaxValue();
		nValue += 30;
		pPlayer->GetHPGauge()->SetMaxValue(nValue);

		// パーティクル
		particle.pos = pPlayer->GetPos();
		particle.scale = D3DXVECTOR3(15.0f,15.0f,0.0f);
		particle.col = D3DXCOLOR(0.5f, 0.5f, 0.0f, 1.0f);
		particle.destCol = D3DXCOLOR(0.0f, 0.5f, 1.0f, 0.0f);
		particle.colAttenuation = 0.8f;
		particle.destroyTime = 100;
		particle.rotateValue = 0.1f;

		CUtility::stringMultiPush(list, "Rotate, ColorTransition");
		particle.infoProperty = list;

		popParticleValue = 35;

		for (int i = 0; i < popParticleValue; i++)
		{
			particle.move = D3DXVECTOR3(-sinf((i * ((360 / popParticleValue) * (D3DX_PI / 180)))), 1.3f, -cosf((i * ((360 / popParticleValue) * (D3DX_PI / 180))))) * 2.5f;
			CParticle::Create(particle, "STAR", CObject::PRIORITY_THIRD);
		}
		break;

	case ABILITY_HPHEAL:
		nValue = pPlayer->GetHPGauge()->GetValue();
		nValue += (int)round((nValue * 0.75f));
		pPlayer->GetHPGauge()->SetValue(nValue);
		break;

	case ABILITY_POWERUP:
		nValue = pPlayer->GetPower();
		nValue += 3;
		pPlayer->SetPower(nValue);
		break;

	case ABILITY_STRONGPOWERUP:
		nValue = pPlayer->GetPower();
		nValue += 6;
		pPlayer->SetPower(nValue);
		break;

	case ABILITY_WALKSPEEDUP:
		fValue = pPlayer->GetBasicWalkSpeed();
		fValue += 0.5f;
		pPlayer->SetBasicWalkSpeed(fValue);
		break;

	case ABILITY_BEAM:
		pSkill.m_beam = true;
		pPlayer->SetSkill(pSkill);
		break;

	case ABILITY_FIELD_DAMAGE:
		pSkill.m_damageField = true;
		pPlayer->SetSkill(pSkill);
		break;

	default:
		break;
	}

	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// アビリティの終了
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CAbility::Uninit()
{
	if (m_p3DEffect != nullptr)
	{
		if (!m_afterRelease)
		{
			m_p3DEffect->Uninit();
		}
		delete m_p3DEffect;
		m_p3DEffect = nullptr;
	}

	delete this;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// アビリティの更新
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CAbility::Update()
{
	if (m_pause)
	{
		return;
	}

	CPlayer *pPlayer = CApplication::GetInstance()->GetMode()->GetGame()->GetPlayer();

	if (m_p3DEffect != nullptr)
	{
		m_p3DEffect->Update();
		m_p3DEffect->SetPos(pPlayer->GetPos());
	}
}