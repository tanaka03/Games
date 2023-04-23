#include "application.h"
#include "billboard.h"
#include "object3d.h"
#include "input.h"
#include "keyboard.h"
#include "texture.h"

//��������������������������������������������������������������
// �r���{�[�h�̃R���X�g���N�^
//��������������������������������������������������������������
CBillboard::CBillboard(int nPriority) : 
	m_Zfunc(D3DCMP_LESS),
	m_bIsRotate(false),
	m_bAnimation(false),
	m_pTexture(nullptr)
{
	SetObjState(CObject::OBJSTATE_3D);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_scale = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	m_blend = BLEND_NONE;
}

//��������������������������������������������������������������
// �r���{�[�h�̃f�X�g���N�^
//��������������������������������������������������������������
CBillboard::~CBillboard()
{
}

//��������������������������������������������������������������
// �r���{�[�h�̐���
//��������������������������������������������������������������
CBillboard * CBillboard::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, int priority)
{
	CBillboard *pObj = nullptr;
	pObj = new CBillboard(priority);

	//�k���`�F�b�N
	if (pObj != nullptr)
	{
		pObj->SetPos(pos);
		pObj->SetScale(scale);
		pObj->Init();
	}

	return pObj;
}

//��������������������������������������������������������������
// �r���{�[�h�̏�����
//��������������������������������������������������������������
HRESULT CBillboard::Init()
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
	pVtx[0].pos = D3DXVECTOR3(-m_scale.x, m_scale.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_scale.x, m_scale.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_scale.x, -m_scale.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_scale.x, -m_scale.y, 0.0f);

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
// �r���{�[�h�̏I��
//��������������������������������������������������������������
void CBillboard::Uninit()
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
// �r���{�[�h�̍X�V
//��������������������������������������������������������������
void CBillboard::Update()
{
	m_objpos += m_move;

	m_rot.z += m_destRotate;

	VERTEX_3D* pVtx = NULL;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_scale.x, m_scale.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_scale.x, m_scale.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_scale.x, -m_scale.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_scale.x, -m_scale.y, 0.0f);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	if (m_bAnimation)
	{// �e�N�X�`���A�j���[�V����������ꍇ
		m_CntTime++;

		if (m_CntTime >= m_Timer)
		{
			m_AnimationSpdCnt++;
			if (m_AnimationSpdCnt >= m_AnimationSpeed)
			{
				m_AnimationSpdCnt = 0;
				m_PatternAnimX++;

				if (m_PatternAnimX > m_DivisionX)
				{//�A�j���[�V����
					m_PatternAnimX = 0;
					m_PatternAnimY++;
					if (m_PatternAnimY >= m_DivisionY)
					{
						m_PatternAnimY = 0;
						if (!m_bLoop)
						{
							Uninit();
						}
						return;
					}
				}

				float U = 1.0f / (m_DivisionX);
				float V = 1.0f / (m_DivisionY);

				SetUV(U * (m_PatternAnimX)
					, U *(m_PatternAnimX)+U
					, V * (m_PatternAnimY)
					, V * (m_PatternAnimY)+V);
			}
		}
	}
}

//��������������������������������������������������������������
// �r���{�[�h�̕`��
//��������������������������������������������������������������
void CBillboard::Draw()
{
	CTexture* pTexture = CApplication::GetInstance()->GetTexture();
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();
	D3DXMATRIX mtxTrans, mtxView, mtxRot;				//�v�Z�p�}�g���b�N�X

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

	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�J�����̋t�s���ݒ�
	if (m_bIsRotate)
	{
		m_mtxWorld._11 = mtxView._11;
		m_mtxWorld._12 = mtxView._21;
		m_mtxWorld._13 = mtxView._31;
		m_mtxWorld._31 = mtxView._13;
		m_mtxWorld._32 = mtxView._23;
		m_mtxWorld._33 = mtxView._33;
	}
	else
	{
		m_mtxWorld._11 = mtxView._11;
		m_mtxWorld._12 = mtxView._21;
		m_mtxWorld._13 = mtxView._31;
		m_mtxWorld._21 = mtxView._12;
		m_mtxWorld._22 = mtxView._22;
		m_mtxWorld._23 = mtxView._32;
		m_mtxWorld._31 = mtxView._13;
		m_mtxWorld._32 = mtxView._23;
		m_mtxWorld._33 = mtxView._33;
	}

	if (m_bIsAlphaTest)
	{	// �A���t�@�e�X�g
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	}

	//�J�������猩�ċ߂��������㏑��
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);	//�s���]�֐�(�������Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);				//�s��|���Z�֐�(��2���� * ��O������������Ɋi�[)

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_objpos.x, m_objpos.y, m_objpos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

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

	// �A���t�@�e�X�g�𖳌�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);
}

//��������������������������������������������������������������
// �r���{�[�h�̃e�N�X�`�����o�C���h
//��������������������������������������������������������������
void CBillboard::BindTexture(std::string inPath)
{
	m_pTexture = CApplication::GetInstance()->GetTexture()->GetTexture(inPath);		//�e�N�X�`���̃|�C���^
}

//��������������������������������������������������������������
// �r���{�[�h�̃e�N�X�`����UV���W��ݒ�
//��������������������������������������������������������������
void CBillboard::SetUV(float Xtop, float Xbottom, float Ytop, float Ybottom)
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
// �r���{�[�h�̃A�j���[�V������ݒ�
//��������������������������������������������������������������
void CBillboard::SetAnimation(const int U, const int V, const int Speed, const int Drawtimer, const bool loop)
{
	m_DivisionX = U;
	m_DivisionY = V;
	m_DivisionMAX = m_DivisionY*m_DivisionX;

	m_PatternAnimX = 1;
	m_PatternAnimY = 1;
	m_AnimationSpeed = Speed;
	m_Timer = Drawtimer;
	m_bAnimation = true;
	m_bLoop = loop;

	//�\�����W���X�V
	SetUV(1.0f / m_DivisionX * (m_PatternAnimX / (m_DivisionX))
		, 1.0f / m_DivisionX *(m_PatternAnimX / (m_DivisionX)) + 1.0f / m_DivisionX
		, 1.0f / m_DivisionY * (m_PatternAnimY % (m_DivisionY))
		, 1.0f / m_DivisionY * (m_PatternAnimY % (m_DivisionY)+1.0f / m_DivisionY* m_DivisionY));
}