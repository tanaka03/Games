#include "main.h"
#include "application.h"
#include "billboard.h"
#include "object3d.h"
#include "damage.h"
#include "camera.h"

//��������������������������������������������������������������
// �_���[�W�̃R���X�g���N�^
//��������������������������������������������������������������
CDamage::CDamage(int priority) :
	CBillboard(priority),
	m_damage(0)
{
}

//��������������������������������������������������������������
// �_���[�W�̃f�X�g���N�^
//��������������������������������������������������������������
CDamage::~CDamage()
{
}

//��������������������������������������������������������������
// �_���[�W�̏�����
//��������������������������������������������������������������
HRESULT CDamage::Init()
{
	m_beginPos = GetPos();

	CBillboard::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CBillboard::Init();

	VERTEX_3D*pVtx;        // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//��������������������������������������������������������������
// �_���[�W�̏I��
//��������������������������������������������������������������
void CDamage::Uninit()
{
	CBillboard::Uninit();
}

//��������������������������������������������������������������
// �_���[�W�̍X�V
//��������������������������������������������������������������
void CDamage::Update()
{
	CBillboard::Update();

	D3DXVECTOR3 pos = GetPos();
	pos.y += 1.0f;
	SetPos(pos);

	// �J�����̌����Ɍ������ăx�N�g�����v�Z
	CCamera *pCamera = CApplication::GetInstance()->GetCamera();
	D3DXVECTOR3 rot = pCamera->GetCamera()->rot;
	rot.y += D3DX_PI / 90;
	D3DXVECTOR3 vec = D3DXVECTOR3(sinf(rot.y), cosf(rot.y), 0.0f);

	if (m_beginPos.y + 30.0f < pos.y)
	{
		End();
	}

	if (m_damage < 0)
	{
		m_damage = 0;
	}
}

//��������������������������������������������������������������
// �_���[�W�̕`��
//��������������������������������������������������������������
void CDamage::Draw()
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

//��������������������������������������������������������������
// �_���[�W�̐ݒ�
//��������������������������������������������������������������
void CDamage::SetDamage(int score)
{
	if (score >= m_maxDamage)
	{
		return;
	}

	m_damage = score;

	VERTEX_3D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f + m_posTexU * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f + m_posTexU * 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + m_posTexU * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + m_posTexU * 0.1f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//��������������������������������������������������������������
// �_���[�W�̍ő�̐��l��ݒ�
//��������������������������������������������������������������
void CDamage::SetMaxDamage(int digit)
{
	m_maxDamage = powf(10, digit + 1);
	m_maxDamage--;
}