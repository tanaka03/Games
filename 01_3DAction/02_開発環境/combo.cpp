#include "main.h"
#include "application.h"
#include "object2d.h"
#include "combo.h"
#include "2deffect.h"
#include "utility.h"
#include "game.h"

//��������������������������������������������������������������
// �R���{�̃R���X�g���N�^
//��������������������������������������������������������������
CCombo::CCombo(int priority) :
	CObject2D(priority),
	m_combo(0)
{
}

//��������������������������������������������������������������
// �R���{�̃f�X�g���N�^
//��������������������������������������������������������������
CCombo::~CCombo()
{
}

//��������������������������������������������������������������
// �R���{�̏�����
//��������������������������������������������������������������
HRESULT CCombo::Init()
{
	CObject2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	CObject2D::Init();

	return S_OK;
}

//��������������������������������������������������������������
// �R���{�̏I��
//��������������������������������������������������������������
void CCombo::Uninit()
{
	CObject2D::Uninit();
}

//��������������������������������������������������������������
// �R���{�̍X�V
//��������������������������������������������������������������
void CCombo::Update()
{
	CObject2D::Update();
	D3DXCOLOR col = CObject2D::GetCol();

	if (m_combo <= 0)
	{	//�R���{�����O�ȉ��������ꍇ
		m_combo = 0;
		col.a = 0.0f;
	}

	m_time--;
	if (m_time <= 0)
	{
		col.a -= 0.01f;
		m_time = 0;

		if (col.a <= 0.0f)
		{
			CApplication::GetInstance()->GetMode()->GetGame()->ComboDisappear();
			m_combo = 0;
		}
	}
	else
	{
		col.a = 1.0f;
	}

	CObject2D::SetCol(col);
}

//��������������������������������������������������������������
// �R���{�̕`��
//��������������������������������������������������������������
void CCombo::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	//�A���t�@�e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	CObject2D::Draw();

	//�A���t�@�e�X�g�𖳌�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//��������������������������������������������������������������
// �R���{�̐ݒ�
//��������������������������������������������������������������
void CCombo::SetCombo(int combo)
{
	if (combo >= m_maxCombo)
	{
		return;
	}

	m_combo = combo;

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
// �R���{�̍ő�̐��l��ݒ�
//��������������������������������������������������������������
void CCombo::SetMaxCombo(int digit)
{
	m_maxCombo = (int)powf(10.0f, digit + 1.0f);
	m_maxCombo--;
}
