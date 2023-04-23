#include "application.h"
#include "game.h"
#include "sp.h"
#include "object.h"
#include "player.h"

//��������������������������������������������������������������
// �o���l�Q�[�W�̃R���X�g���N�^
//��������������������������������������������������������������
CSp::CSp(int priority)
{
	//m_Width = 100.0f;
	//m_Height = 10.0f;
}

//��������������������������������������������������������������
// �o���l�Q�[�W�̃f�X�g���N�^
//��������������������������������������������������������������
CSp::~CSp()
{
}

//��������������������������������������������������������������
// �o���l�Q�[�W�̏�����
//��������������������������������������������������������������
HRESULT CSp::Init()
{
	m_Width = GetScale().x;
	m_Height = GetScale().y;

	CObject2D::BindTexture("GAUGE");
	CObject2D::Init();
	return S_OK;
}

//��������������������������������������������������������������
// �o���l�Q�[�W�̏I��
//��������������������������������������������������������������
void CSp::Uninit()
{
	CObject2D::Uninit();
}

//��������������������������������������������������������������
// �o���l�Q�[�W�̍X�V
//��������������������������������������������������������������
void CSp::Update()
{
	CObject2D::Update();

	D3DXVECTOR3 pos = CObject2D::GetPos();
	int max = CGauge::GetMaxValue();
	int currentValue = CGauge::GetValue();
	float rot = CGauge::GetRot();

	if (max < currentValue)
	{
		currentValue = max;
	}

	D3DXMATRIX mtx;    // �v�Z�p�}�g���b�N�X
	D3DXVECTOR3 afterPos[4];

	//�Q�[�W�̒��_���W
	const D3DXVECTOR3 Vtx[4] =
	{
		D3DXVECTOR3(pos.x - (m_Width / 2), pos.y - m_Height, 0.0f),
		D3DXVECTOR3(pos.x - (m_Width / 2) + (m_Width / 100) * ((currentValue * 100) / max), pos.y - m_Height, 0.0f),
		D3DXVECTOR3(pos.x - (m_Width / 2), pos.y + m_Height, 0.0f),
		D3DXVECTOR3(pos.x - (m_Width / 2) + (m_Width / 100) * ((currentValue * 100) / max), pos.y + m_Height, 0.0f),
	};

	//���_���W�̐ݒ�
	VERTEX_2D*pVtx;        //���_���ւ̃|�C���^ 

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �}�g���b�N�X�̐���
	D3DXMatrixIdentity(&mtx);

	// ���[�A�s�b�`�A���[�����w�肵�ă}�g���b�N�X���쐬
	D3DXMatrixRotationYawPitchRoll(&mtx, 0.0f, 0.0f, D3DXToRadian(rot));

	// ���_���W�̍X�V
	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&afterPos[i], &Vtx[i], &mtx);
		pVtx[i].pos = afterPos[i];
	}

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//��������������������������������������������������������������
// �o���l�Q�[�W�̕`��
//��������������������������������������������������������������
void CSp::Draw()
{
	CObject2D::Draw();
}