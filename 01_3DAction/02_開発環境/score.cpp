#include "main.h"
#include "application.h"
#include "object2d.h"
#include "score.h"

//��������������������������������������������������������������
// �X�R�A�̃R���X�g���N�^
//��������������������������������������������������������������
CScore::CScore(int priority) : 
	CObject2D(priority),
	m_score(0)
{
}

//��������������������������������������������������������������
// �X�R�A�̃f�X�g���N�^
//��������������������������������������������������������������
CScore::~CScore()
{
}

//��������������������������������������������������������������
// �X�R�A�̏�����
//��������������������������������������������������������������
HRESULT CScore::Init()
{
	CObject2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CObject2D::Init();

	VERTEX_2D*pVtx;        // ���_���ւ̃|�C���^

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
// �X�R�A�̏I��
//��������������������������������������������������������������
void CScore::Uninit()
{
	CObject2D::Uninit();
}

//��������������������������������������������������������������
// �X�R�A�̍X�V
//��������������������������������������������������������������
void CScore::Update()
{
	CObject2D::Update();
	if (m_score < 0)
	{
		m_score = 0;
	}
}

//��������������������������������������������������������������
// �X�R�A�̕`��
//��������������������������������������������������������������
void CScore::Draw()
{
	// �f�o�C�X�̃|�C���^���擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	// �A���t�@�e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	CObject2D::Draw();

	// �A���t�@�e�X�g�𖳌�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//��������������������������������������������������������������
// �X�R�A�̐ݒ�
//��������������������������������������������������������������
void CScore::SetScore(int score)
{
	if (score >= m_maxScore)
	{
		return;
	}

	m_score = score;

	VERTEX_2D*pVtx;

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
// �X�R�A�̍ő�̐��l��ݒ�
//��������������������������������������������������������������
void CScore::SetMaxScore(int digit)
{
	m_maxScore = powf(10, digit + 1);
	m_maxScore--;
}