#include "effect.h"
#include "funnel.h"
#include "application.h"
#include "input.h"
#include "keyboard.h"
#include "bullet.h"
#include "texture.h"

//����������������������������������������
//�����̃R���X�g���N�^
//����������������������������������������
CFunnel::CFunnel()
{
}

//����������������������������������������
//�����̃f�X�g���N�^
//����������������������������������������
CFunnel::~CFunnel()
{
}

//����������������������������������������
//�t�@���l���̐���
//����������������������������������������
CFunnel * CFunnel::Create(D3DXVECTOR3 pos, EType type)
{
	CFunnel *pFunnel = nullptr;
	pFunnel = new CFunnel;

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
HRESULT CFunnel::Init()
{
	CObject2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CObject2D::SetScale(38.0f, 38.0f);
	CObject2D::Init();

	switch (GetFunnel())
	{
	case FUNNEL_BULLET:
		CObject2D::SetTexture(CTexture::TEXTURE_FUNNEL);
		break;

	default:
		break;
	}

	return S_OK;
}

//����������������������������������������
//�t�@���l���̏I������
//����������������������������������������
void CFunnel::Uninit()
{
	CObject2D::Uninit();
	CObject2D::Release();
}

//����������������������������������������
//�t�@���l���̍X�V����
//����������������������������������������
void CFunnel::Update()
{
	D3DXVECTOR3 addPos[4];
	D3DXMATRIX mtx;    // �v�Z�p�}�g���b�N�X
	m_pos = GetPos();
	m_fTimer++;
	m_nEffectTime++;

	CObject2D::Update();

	switch (GetFunnel())
	{
	case FUNNEL_BULLET:
		if (CApplication::GetInputKeyboard()->GetPress(DIK_SPACE))
		{
			m_nPressTime++;

			//�o���b�g�N���X�̐���
			if ((m_nPressTime % 5) == 0)
			{
				m_pBullet = m_pBullet->Create(m_pos, D3DXVECTOR3(0.0f, -15.0f, 0.0f), D3DXCOLOR(0.0f, 0.4f, 0.8f, 1.0f), 35, false, CBullet::BULLETTYPE_NORMAL, CBullet::BULLETTAG_PLAYER);
				m_pBullet->SetTexture(CTexture::TEXTURE_SQUAREBULLET);
				m_pBullet->SetCollisionScale(5.0f);
				m_nPressTime = 0;
			}
		}
		break;

	default:
		break;
	}

	if ((m_nEffectTime % 5) == 0)
	{
		m_pEffect = m_pEffect->Create(m_pos, D3DXVECTOR3(0.0f, 3.0f, 0.0f),D3DXCOLOR(1.0f,0.5f,0.0f,1.0f),120, CEffect::EFFECTTYPE_ASTER);
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
void CFunnel::Draw()
{
	CObject2D::Draw();
}
