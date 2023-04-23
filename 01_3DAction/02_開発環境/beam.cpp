#include "beam.h"
#include "utility.h"
#include "application.h"
#include "debugproc.h"
#include "game.h"
#include "enemy.h"
#include "3deffect_emitter.h"
#include "player.h"
#include "enemy.h"
#include "number.h"
#include "sound.h"
#include "3deffect.h"
#include "sp.h"
#include "number.h"

//��������������������������������������������������������������
// �r�[���̃R���X�g���N�^
//��������������������������������������������������������������
CBeam::CBeam() :
	m_scale(1.0f)
{
}

//��������������������������������������������������������������
// �r�[���̃f�X�g���N�^
//��������������������������������������������������������������
CBeam::~CBeam()
{
}

//��������������������������������������������������������������
// �r�[���̐���
//��������������������������������������������������������������
CBeam * CBeam::Create(const D3DXVECTOR3 pos, int time, int priority)
{
	CBeam *pSkill = nullptr;
	pSkill = new CBeam;

	//�k���`�F�b�N
	if (pSkill != nullptr)
	{
		pSkill->m_pos = pos;
		pSkill->m_enableTime = time;
		pSkill->Init();
	}

	return pSkill;
}

//��������������������������������������������������������������
// �r�[���̏�����
//��������������������������������������������������������������
HRESULT CBeam::Init()
{
	m_p3DEffect = C3DEffectEmitter::Create("Beam");

	CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_SE_BEAM);
	return S_OK;
}

//��������������������������������������������������������������
// �r�[���̏I��
//��������������������������������������������������������������
void CBeam::Uninit()
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
// �r�[���̍X�V
//��������������������������������������������������������������
void CBeam::Update()
{
	CPlayer *pPlayer = CApplication::GetInstance()->GetMode()->GetGame()->GetPlayer();
	CGame *pGame = CApplication::GetInstance()->GetMode()->GetGame();

	m_p3DEffect->Update();
	m_p3DEffect->SetPos(D3DXVECTOR3(0.0f,150.0f,0.0f));

	// �G�ƃv���C���[�̓����蔻��
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

		// �I�u�W�F�N�g�^�C�v���v���C���[�̏ꍇ�ʂ�

		CEnemy *pObj = (CEnemy*)pObject;
		CEnemy::SModelData enemyModelData = *pObj->GetModelData(0);

		// ���f���̔��a
		D3DXVECTOR3 enemySize = (enemyModelData.maxModel + enemyModelData.minModel);

		if (CUtility::isCrossCollision(pObj->GetPos(), D3DXVECTOR3(-100.0f,0.0f,-900.0f), D3DXVECTOR3(100.0f,0.0f, 50.0f), m_p3DEffect->GetEffect(0)->GetMtxWorld()))
		{	// �v���C���[�ƓG�����������ꍇ
			CApplication::GetInstance()->GetMode()->GetGame()->GetCombo()->AddValue(1);
			pObj->SetState(CEnemy::STATE_DAMAGE);
			pObj->AddLife(-(pPlayer->GetPower() + 10));

			m_pDamage = CNumber::Create(D3DXVECTOR3(pObj->GetPos().x, pObj->GetPos().y + 70.0f, pObj->GetPos().z), D3DXVECTOR2(15.0f, 15.0f), CNumber::NUMBER_DAMAGE, "NUMBER2", 3, CObject::PRIORITY_THIRD);
			m_pDamage->SetValue((pPlayer->GetPower() + 10));

			pPlayer->GetSPGauge()->AddValue(roundf(pGame->GetCombo()->GetValue() * 0.5f));
		}

		// �|�C���^�����ɐi�߂�
		pObject = pObject->GetNext();
	}

	// �X�L���̐�������
	m_time++;
	if (m_time > m_enableTime)
	{
		// �G�t�F�N�g
		{
			C3DEffect::SInfo info = {};
			info.beginScale = D3DXVECTOR3(10.0f, 1.0f, 10.0f);
			info.beginRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			info.col = D3DXCOLOR(0.0f, 0.5f, 0.5f, 1.0f);
			info.transitionCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			info.alphaAttenuation = 0.005f;
			info.scalingValue = D3DXVECTOR3(0.3f, 0.0f, 0.3f);
			info.rotateValue = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			info.life = 60;
			info.tractPlayer = true;
			info.modelShape = "CIRCLE";
			info.texTag = "CIRCLE";

			C3DEffect::Create(info);
		}

		Destroy();
	}
}

//��������������������������������������������������������������
// �r�[���̔���
//��������������������������������������������������������������
bool CBeam::Collision(D3DXVECTOR3 destPos, D3DXVECTOR3 size)
{
	CPlayer *pPlayer = CApplication::GetInstance()->GetMode()->GetGame()->GetPlayer();

	D3DXMATRIX mtx = m_p3DEffect->GetEffect(0)->GetMtxWorld();
	D3DXVECTOR3 pos = pPlayer->GetPos();

	D3DXVECTOR3 minModel = D3DXVECTOR3(-1.0f, -15.0f,-1.0f);
	D3DXVECTOR3 maxModel = D3DXVECTOR3(1.0f, 10.0f, 1.0f);

	D3DXMATRIX invMtx;
	D3DXVECTOR3 localPos;
	D3DXVECTOR3 worldPos;

	// ���[���h���W���v�Z
	D3DXVec3TransformCoord(&worldPos, &pos, &mtx);

	// �t�s��ɂ���
	D3DXMatrixInverse(&invMtx, NULL, &mtx);

	// �t�s��v�Z�������s������[�J�����W�ϊ�
	D3DXVec3TransformCoord(&localPos, &worldPos, &invMtx);

	float fLeft = localPos.x + minModel.x;		//��
	float fRight = localPos.x + maxModel.x;	//�E
	float fTop = localPos.y + maxModel.y;		//��
	float fBottom = localPos.y + minModel.y;	//��
	float fFront = localPos.z + minModel.z;	//�O
	float fBehind = localPos.z + maxModel.z;	//��

		//�O��
	if (fFront <= destPos.z - (size.z / 2)
		&& fBehind >= destPos.z + (size.z / 2))
	{
		//������E
		if (fLeft < destPos.x + (size.x / 2))
		{
			return true;
		}

		//�E���獶
		else if (fRight > destPos.x - (size.x / 2))
		{
			return true;
		}
	}

	//���E
	if (fLeft < destPos.x - (size.x / 2)
		&& fRight > destPos.x + (size.x / 2))
	{
		//�O�����
		if (fFront < destPos.z + (size.z / 2))
		{
			return true;
		}

		//�ォ��O
		else if (fBehind > destPos.z - (size.z / 2))
		{
			return true;
		}
	}

	return false;
}