#include "bullet.h"
#include "object3d.h"
#include "enemy.h"
#include "utility.h"
#include "application.h"
#include "game.h"
#include "combo.h"
#include "mode.h"
#include "player.h"
#include "gauge.h"

//��������������������������������������������������������������
// �e�̃R���X�g���N�^
//��������������������������������������������������������������
CBullet::CBullet(int priority) : CBillboard(CObject::PRIORITY_THIRD)
{
	SetObjType(OBJTYPE_BULLET);
	m_life = 0;
}

//��������������������������������������������������������������
// �e�̃f�X�g���N�^
//��������������������������������������������������������������
CBullet::~CBullet()
{
}

//��������������������������������������������������������������
// �e�̐���
//��������������������������������������������������������������
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int life, int priority)
{
	CBullet *pObj = nullptr;
	pObj = new CBullet(priority);

	if (pObj != nullptr)
	{
		pObj->SetPos(pos);
		pObj->SetMove(move);
		pObj->SetLife(life);
		pObj->Init();
	}

	return pObj;
}

//��������������������������������������������������������������
// �e�̏�����
//��������������������������������������������������������������
HRESULT CBullet::Init()
{
	SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetScale(D3DXVECTOR3(10.0f, 10.0f, 0.0f));
	CBillboard::BindTexture("BULLET");
	CBillboard::Init();
	SetBlend(BLEND_NONE);

	return S_OK;
}

//��������������������������������������������������������������
// �e�̏I��
//��������������������������������������������������������������
void CBullet::Uninit()
{
	CBillboard::Uninit();
}

//��������������������������������������������������������������
// �e�̍X�V
//��������������������������������������������������������������
void CBullet::Update()
{
	CGame *pGame = CApplication::GetInstance()->GetMode()->GetGame();
	CPlayer *pPlayer = pGame->GetPlayer();

	CBillboard::Update();

	D3DXVECTOR3 pos = CBillboard::GetPos();

	// �G�ƒe�̓����蔻��
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
		D3DXVECTOR3 enemyModelRadius = (enemyModelData.maxModel - enemyModelData.minModel) / 2;

		if (CUtility::isCircleCollision(pos, 20.0f, pObj->GetPos(), enemyModelRadius.x))
		{	// �v���C���[�ƓG�����������ꍇ
			CApplication::GetInstance()->GetMode()->GetGame()->GetCombo()->AddValue(1);
			pObj->SetState(CEnemy::STATE_DAMAGE);
			pObj->AddLife(-(pPlayer->GetPower()));
			this->Destroy();
		}

		// �|�C���^�����ɐi�߂�
		pObject = pObject->GetNext();
	}

	m_life--;
	if (m_life <= 0)
	{
		Uninit();
		return;
	}
}

//��������������������������������������������������������������
// �e�̕`��
//��������������������������������������������������������������
void CBullet::Draw()
{
	// �f�o�C�X�̃|�C���^���擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	// ���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �A���t�@�e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	CBillboard::Draw();

	// ���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// �A���t�@�e�X�g�𖳌�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}