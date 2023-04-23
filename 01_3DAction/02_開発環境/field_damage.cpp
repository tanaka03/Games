#include "field_damage.h"
#include "utility.h"
#include "application.h"
#include "debugproc.h"
#include "game.h"
#include "enemy.h"
#include "3deffect_emitter.h"
#include "player.h"
#include "number.h"

CDamageField::CDamageField() :
	m_scale(1.0f)
{
}

CDamageField::~CDamageField()
{
}

CDamageField * CDamageField::Create(const D3DXVECTOR3 pos, int priority)
{
	CDamageField *pSkill = nullptr;
	pSkill = new CDamageField;

	//�k���`�F�b�N
	if (pSkill != nullptr)
	{
		pSkill->m_pos = pos;
		pSkill->Init();
	}

	return pSkill;
}

HRESULT CDamageField::Init()
{
	m_p3DEffect = C3DEffectEmitter::Create("DamageField");
	m_scale = m_p3DEffect->GetEffect(0)->GetScale().x;
	m_scale *= 10.0f;

	return S_OK;
}

void CDamageField::Uninit()
{
	if (m_p3DEffect != nullptr)
	{
		m_p3DEffect->Uninit();
		delete m_p3DEffect;
		m_p3DEffect = nullptr;
	}

	Destroy();
}

void CDamageField::Update()
{
	CPlayer *pPlayer = CApplication::GetInstance()->GetMode()->GetGame()->GetPlayer();

	m_p3DEffect->Update();
	m_p3DEffect->SetPos(pPlayer->GetPos());

	m_time++;

	m_scale += 4.0f;

	// �v���C���[�ƓG�̓����蔻��
	CObject *pObject = CObject::GetTop(PRIORITY_THIRD);
	while (pObject != nullptr)
	{
		if (pObject == this)
		{
			pObject = pObject->GetNext();
			continue;
		}

		// �I�u�W�F�N�g�̃^�C�v���擾
		CObject::EObjType objType = pObject->GetObjType();

		if (objType != OBJTYPE_ENEMY)
		{
			pObject = pObject->GetNext();
			continue;
		}

		// �I�u�W�F�N�g�^�C�v���G�̏ꍇ�ʂ�

		CEnemy *pObj = (CEnemy*)pObject;
		CEnemy::SModelData enemyModelData = *pObj->GetModelData(0);

		// ���f���̔��a
		D3DXVECTOR3 enemyModelRadius = (enemyModelData.maxModel - enemyModelData.minModel) / 2;

		if (CUtility::isCircleCollision(m_pos, m_scale, pObj->GetPos(), enemyModelRadius.x))
		{	// �X�L���͓��ɓG������ꍇ
			if ((m_time % 50) == 0)
			{
				CApplication::GetInstance()->GetMode()->GetGame()->GetCombo()->AddValue(1);
				pObj->AddLife(-2);

				m_pDamage = CNumber::Create(D3DXVECTOR3(pObj->GetPos().x, pObj->GetPos().y + 70.0f, pObj->GetPos().z), D3DXVECTOR2(15.0f, 15.0f), CNumber::NUMBER_DAMAGE, "NUMBER2", 3, CObject::PRIORITY_THIRD);
				m_pDamage->SetValue(2);
			}
		}

		//�|�C���^�����ɐi�߂�
		pObject = pObject->GetNext();
	}

	// �X�L���̐�������
	if (m_time > 95)
	{
		Destroy();
	}
}