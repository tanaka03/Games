#include "application.h"
#include "game.h"
#include "hp.h"
#include "object.h"
#include "player.h"
#include "object3d.h"

//��������������������������������������������������������������
// HP�̃R���X�g���N�^
//��������������������������������������������������������������
CHp::CHp(int priority)
{
}

//��������������������������������������������������������������
// HP�̃f�X�g���N�^
//��������������������������������������������������������������
CHp::~CHp()
{
}

//��������������������������������������������������������������
// HP�̏�����
//��������������������������������������������������������������
HRESULT CHp::Init()
{
	m_Width = GetScale().x;
	m_Height = GetScale().y;

	CBillboard::BindTexture("GAUGE");
	CBillboard::Init();

	m_pFrame = CBillboard::Create(GetPos(), D3DXVECTOR3(m_Width - 25.0f, m_Height, 0.0f), CObject::PRIORITY_FOURTH);
	m_pFrame->BindTexture("GAUGEFRAME");
	m_pFrame->AlphaTest();

	return S_OK;
}

//��������������������������������������������������������������
// HP�̏I��
//��������������������������������������������������������������
void CHp::Uninit()
{
	CBillboard::Uninit();

	m_pFrame->Destroy();
}

//��������������������������������������������������������������
// HP�̍X�V
//��������������������������������������������������������������
void CHp::Update()
{
	D3DXVECTOR3 pos = CBillboard::GetPos();
	int max = C3DGauge::GetMaxValue();
	int currentValue = C3DGauge::GetValue();

	m_pFrame->SetPos(D3DXVECTOR3(pos.x , pos.y , pos.z ));

	if (max < currentValue)
	{
		currentValue = max;
	}

	//���_���W�̐ݒ�
	VERTEX_3D *pVtx;        //���_���ւ̃|�C���^ 

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-(m_Width / 2), m_Height, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(-(m_Width / 2) + (m_Width / 100) * ((currentValue * 100) / max), m_Height, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-(m_Width / 2), -m_Height, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(-(m_Width / 2) + (m_Width / 100) * ((currentValue * 100) / max), -m_Height, 0.0f);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//��������������������������������������������������������������
// HP�̕`��
//��������������������������������������������������������������
void CHp::Draw()
{
	// �f�o�C�X�̃|�C���^���擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	// ���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	CBillboard::Draw();

	// ���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}