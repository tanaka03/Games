#include "effect.h"
#include "enemy_funnel.h"
#include "application.h"
#include "input.h"
#include "keyboard.h"
#include "bullet.h"
#include "texture.h"

//����������������������������������������
//�����̃R���X�g���N�^
//����������������������������������������
CEnemyFunnel::CEnemyFunnel()
{
	m_fAngle = 0;
}

//����������������������������������������
//�����̃f�X�g���N�^
//����������������������������������������
CEnemyFunnel::~CEnemyFunnel()
{
}

//����������������������������������������
//�t�@���l���̐���
//����������������������������������������
CEnemyFunnel * CEnemyFunnel::Create(D3DXVECTOR3 pos, EType type)
{
	CEnemyFunnel *pFunnel = nullptr;
	pFunnel = new CEnemyFunnel;

	//�k���`�F�b�N
	if (pFunnel != nullptr)
	{
		// �|���S���̏���������
		pFunnel->SetFunnel(type);
		pFunnel->Init();
		pFunnel->SetPos(pos);
	}

	return pFunnel;
}

//����������������������������������������
//�t�@���l���̏���������
//����������������������������������������
HRESULT CEnemyFunnel::Init()
{
	CObject2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CObject2D::SetScale(38.0f, 38.0f);
	CObject2D::Init();

	switch (GetFunnel())
	{
	case FUNNEL_BULLET:
		CObject2D::SetTexture(CTexture::TEXTURE_FUNNEL2);
		break;

	default:
		break;
	}

	return S_OK;
}

//����������������������������������������
//�t�@���l���̏I������
//����������������������������������������
void CEnemyFunnel::Uninit()
{
	CObject2D::Uninit();
	CObject2D::Release();
}

//����������������������������������������
//�t�@���l���̍X�V����
//����������������������������������������
void CEnemyFunnel::Update()
{
	D3DXVECTOR3 addPos[4];
	D3DXMATRIX mtx;    // �v�Z�p�}�g���b�N�X
	m_pos = GetPos();
	m_fTimer++;
	m_nEffectTime++;
	m_nPressTime++;

	CObject2D::Update();

	switch (GetFunnel())
	{
	case FUNNEL_BULLET:
		//�o���b�g�N���X�̐���
		if ((m_nPressTime % 80) == 0)
		{
			for (int i = 0; i < 5; i++)
			{
				m_pBullet = m_pBullet->Create(m_pos, D3DXVECTOR3(sinf((i * ((360 / 5) * (D3DX_PI / 180))) * m_fAngle), cosf((i * ((360 / 5) * (D3DX_PI / 180))) * m_fAngle), 0.0f) * 2.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 500, false, CBullet::BULLETTYPE_NORMAL, CBullet::BULLETTAG_ENEMY);
				m_pBullet->SetTexture(CTexture::TEXTURE_REDBULLET);
				m_pBullet->SetScale(15.0f, 15.0f);
				m_pBullet->SetCollisionScale(3.0f);
			}
			m_fAngle += 0.05f;
		}
		break;

	default:
		break;
	}

	if ((m_nEffectTime % 5) == 0)
	{
		m_pEffect = m_pEffect->Create(m_pos, D3DXVECTOR3(0.0f, -3.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), 120, CEffect::EFFECTTYPE_ASTER);
		m_pEffect->SetBehavior(CEffect::BEHAVIOR_ROTATION);
	}

	SetPos(m_pos);

	VERTEX_2D*pVtx;        //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �}�g���b�N�X�̐���
	D3DXMatrixIdentity(&mtx);

	// ���[�A�s�b�`�A���[�����w�肵�ă}�g���b�N�X���쐬
	D3DXMatrixRotationYawPitchRoll(&mtx, 0.0f, 0.0f, ((D3DX_PI * 1.5f) / 100.0f) * m_fTimer);

	// ���_���W            �����_��
	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&addPos[i], &sVtx[i], &mtx);
		pVtx[i].pos = m_pos + addPos[i] * (35.0f);    //<-�T�C�Y�ύX
	}

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//����������������������������������������
//�t�@���l���̕`�揈��
//����������������������������������������
void CEnemyFunnel::Draw()
{
	CObject2D::Draw();
}
