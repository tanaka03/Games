#include "crystal.h"
#include "utility.h"
#include "application.h"
#include "debugproc.h"
#include "game.h"
#include "enemy.h"
#include "3deffect_emitter.h"
#include "player.h"
#include "damage_circle.h"
#include "number.h"

//��������������������������������������������������������������
// �N���X�^���̃R���X�g���N�^
//��������������������������������������������������������������
CCrystal::CCrystal()
{
}

//��������������������������������������������������������������
// �N���X�^���̃f�X�g���N�^
//��������������������������������������������������������������
CCrystal::~CCrystal()
{
}

//��������������������������������������������������������������
// �N���X�^���̐���
//��������������������������������������������������������������
CCrystal * CCrystal::Create(const D3DXVECTOR3 pos, int priority)
{
	CCrystal *pSkill = nullptr;
	pSkill = new CCrystal;

	//�k���`�F�b�N
	if (pSkill != nullptr)
	{
		pSkill->m_pos = pos;
		pSkill->Init();
	}

	return pSkill;
}

//��������������������������������������������������������������
// �N���X�^���̏�����
//��������������������������������������������������������������
HRESULT CCrystal::Init()
{
	CPlayer *pPlayer = CApplication::GetInstance()->GetMode()->GetGame()->GetPlayer();

	m_p3DEffect = C3DEffectEmitter::Create("CRYSTAL");
	m_scale = m_p3DEffect->GetEffect(0)->GetScale().x;
	m_scale = 100.0f;

	m_move = pPlayer->GetVec() * 1.5f;

	return S_OK;
}

//��������������������������������������������������������������
// �N���X�^���̏I��
//��������������������������������������������������������������
void CCrystal::Uninit()
{
	if (m_p3DEffect != nullptr)
	{
		m_p3DEffect->Uninit();
		delete m_p3DEffect;
		m_p3DEffect = nullptr;
	}

	// ���S�t���O
	Destroy();
}

//��������������������������������������������������������������
// �N���X�^���̍X�V
//��������������������������������������������������������������
void CCrystal::Update()
{	
	m_p3DEffect->Update();
	m_p3DEffect->SetPos(m_pos);

	m_pos += m_move;

	m_time++;

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
			if ((m_time % 10) == 0)
			{
				CApplication::GetInstance()->GetMode()->GetGame()->GetCombo()->AddValue(1);
				pObj->AddLife(-8);

				m_pDamage = CNumber::Create(D3DXVECTOR3(pObj->GetPos().x, pObj->GetPos().y + 70.0f, pObj->GetPos().z), D3DXVECTOR2(15.0f, 15.0f), CNumber::NUMBER_DAMAGE, "NUMBER2", 3, CObject::PRIORITY_THIRD);
				m_pDamage->SetValue(8);
			}
		}

		//�|�C���^�����ɐi�߂�
		pObject = pObject->GetNext();
	}

	// �X�L���̐�������
	if (m_time > 100)
	{
		CDamageCircle::Create(m_pos, CObject::PRIORITY_THIRD);
		Destroy();
	}
}