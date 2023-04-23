#include "damage_circle.h"
#include "utility.h"
#include "application.h"
#include "debugproc.h"
#include "game.h"
#include "enemy.h"
#include "3deffect_emitter.h"
#include "player.h"
#include "number.h"

//��������������������������������������������������������������
// �_���[�W�T�[�N���̃R���X�g���N�^
//��������������������������������������������������������������
CDamageCircle::CDamageCircle() : 
	m_scale(1.0f)
{
}

//��������������������������������������������������������������
// �_���[�W�T�[�N���̃f�X�g���N�^
//��������������������������������������������������������������
CDamageCircle::~CDamageCircle()
{
}

//��������������������������������������������������������������
// �_���[�W�T�[�N���̐���
//��������������������������������������������������������������
CDamageCircle * CDamageCircle::Create(const D3DXVECTOR3 pos, int priority)
{
	CDamageCircle *pSkill = nullptr;
	pSkill = new CDamageCircle;

	//�k���`�F�b�N
	if (pSkill != nullptr)
	{
		pSkill->m_pos = pos;
		pSkill->Init();
	}

	return pSkill;
}

//��������������������������������������������������������������
// �_���[�W�T�[�N���̏�����
//��������������������������������������������������������������
HRESULT CDamageCircle::Init()
{
	m_p3DEffect = C3DEffectEmitter::Create("DamageCircle");
	m_scale = m_p3DEffect->GetEffect(0)->GetScale().x;
	m_scale *= 10.0f;

	return S_OK;
}

//��������������������������������������������������������������
// �_���[�W�T�[�N���̏I��
//��������������������������������������������������������������
void CDamageCircle::Uninit()
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
// �_���[�W�T�[�N���̍X�V
//��������������������������������������������������������������
void CDamageCircle::Update()
{
	m_p3DEffect->Update();
	m_p3DEffect->SetPos(m_pos);

	m_time++;

	m_scale += 2.0f;

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
			if ((m_time % 15) == 0)
			{
				CApplication::GetInstance()->GetMode()->GetGame()->GetCombo()->AddValue(1);
				pObj->AddLife(-1);

				m_pDamage = CNumber::Create(D3DXVECTOR3(pObj->GetPos().x, pObj->GetPos().y + 70.0f, pObj->GetPos().z), D3DXVECTOR2(15.0f, 15.0f), CNumber::NUMBER_DAMAGE, "NUMBER2", 3, CObject::PRIORITY_THIRD);
				m_pDamage->SetValue(1);
			}
		}

		//�|�C���^�����ɐi�߂�
		pObject = pObject->GetNext();
	}

	// �X�L���̐�������
	if (m_time > 300)
	{
		Destroy();
	}
}