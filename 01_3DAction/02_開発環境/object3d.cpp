#include "application.h"
#include "object3d.h"
#include "input.h"
#include "keyboard.h"
#include "texture.h"

//��������������������������������������������������������������
// �I�u�W�F�N�g�RD�̃R���X�g���N�^
//��������������������������������������������������������������
CObject3D::CObject3D() :
	m_pTexture(nullptr)
{
	SetObjState(CObject::OBJSTATE_3D);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_scale = D3DXVECTOR3(100.0f, 0.0f, 100.0f);
	m_Zfunc = D3DCMP_EQUAL;
}

//��������������������������������������������������������������
// �I�u�W�F�N�g�RD�̃f�X�g���N�^
//��������������������������������������������������������������
CObject3D::~CObject3D()
{
}

//��������������������������������������������������������������
// �I�u�W�F�N�g�RD�̏�����
//��������������������������������������������������������������
HRESULT CObject3D::Init()
{
	//���_�o�b�t�@�̐���
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D* pVtx = NULL;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_scale.x, -m_scale.y, m_scale.z);
	pVtx[1].pos = D3DXVECTOR3(m_scale.x, -m_scale.y, m_scale.z);
	pVtx[2].pos = D3DXVECTOR3(-m_scale.x, m_scale.y, -m_scale.z);
	pVtx[3].pos = D3DXVECTOR3(m_scale.x, m_scale.y, -m_scale.z);

	//�e���_�̖@���̐ݒ�@���@�x�N�g���̑傫����1�ɂ���K�v������
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//��������������������������������������������������������������
// �I�u�W�F�N�g�RD�̏I��
//��������������������������������������������������������������
void CObject3D::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	Destroy();
}

//��������������������������������������������������������������
// �I�u�W�F�N�g�RD�̍X�V
//��������������������������������������������������������������
void CObject3D::Update()
{
	auto pos = GetPos();
	pos += GetMove();

	SetPos(pos);

	VERTEX_3D* pVtx = NULL;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = m_objpos + D3DXVECTOR3(-GetScale().x, -GetScale().y, GetScale().z);
	pVtx[1].pos = m_objpos + D3DXVECTOR3(GetScale().x, -GetScale().y, GetScale().z);
	pVtx[2].pos = m_objpos + D3DXVECTOR3(-GetScale().x, GetScale().y, -GetScale().z);
	pVtx[3].pos = m_objpos + D3DXVECTOR3(GetScale().x, GetScale().y, -GetScale().z);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//��������������������������������������������������������������
// �I�u�W�F�N�g�RD�̕`��
//��������������������������������������������������������������
void CObject3D::Draw()
{
	// �e�N�X�`���̃|�C���^���擾
	CTexture* pTexture = CApplication::GetInstance()->GetTexture();

	// �f�o�C�X�̃|�C���^���擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	//�e�N�X�`���̐ݒ��߂�
	pDevice->SetTexture(0, NULL);

	switch (m_blend)
	{
	case BLEND_ADDITIVE:
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;

	case BLEND_SUBSTRUCT:
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;

	default:
		break;
	}

	//���[���h�}�g���b�N�X��������
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_objpos.x, m_objpos.y, m_objpos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//Z�e�X�g
	pDevice->SetRenderState(D3DRS_ZFUNC, m_Zfunc);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//�J�����O����
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);

	//�ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	//�J�����O�̐ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//��������������������������������������������������������������
// �I�u�W�F�N�g�RD�̃e�N�X�`�����o�C���h
//��������������������������������������������������������������
void CObject3D::BindTexture(std::string inPath)
{
	m_pTexture = CApplication::GetInstance()->GetTexture()->GetTexture(inPath);		//�e�N�X�`���̃|�C���^
}

//��������������������������������������������������������������
// �I�u�W�F�N�g�RD�̃e�N�X�`����UV���W��ݒ�
//��������������������������������������������������������������
void CObject3D::SetUV(float Xtop, float Xbottom, float Ytop, float Ybottom)
{
	VERTEX_3D* pVtx;        //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(Xtop, Ytop);
	pVtx[1].tex = D3DXVECTOR2(Xbottom, Ytop);
	pVtx[2].tex = D3DXVECTOR2(Xtop, Ybottom);
	pVtx[3].tex = D3DXVECTOR2(Xbottom, Ybottom);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//��������������������������������������������������������������
// �I�u�W�F�N�g�RD�̕��ʔ���
//��������������������������������������������������������������
bool CObject3D::PlaneCollision(D3DXVECTOR3 pos, D3DXVECTOR3 Destpos, float Length, float CollisionVal)
{
	float fDistance = ((Destpos.x - pos.x) * (Destpos.x - pos.x)) +
		((Destpos.z - pos.z) * (Destpos.z - pos.z));

	D3DXVECTOR3 vec = Destpos - pos;
	float fYDistance = ((Destpos.y - pos.y) * (Destpos.y - pos.y));
	float Y = D3DXVec3Dot(&D3DXVECTOR3(0, 1, 0), &vec);

	float fRad = powf((Length + Length), CollisionVal);

	if (fDistance <= fRad && fYDistance <= Y)
	{
		return true;
	}
	return false;
}