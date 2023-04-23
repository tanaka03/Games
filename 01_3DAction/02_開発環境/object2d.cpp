#include "application.h"
#include "object2d.h"
#include "input.h"
#include "keyboard.h"
#include "texture.h"

//��������������������������������������������������������������
// �I�u�W�F�N�g�QD�̃R���X�g���N�^
//��������������������������������������������������������������
CObject2D::CObject2D(int priority) :
	m_nCounterAnim(0),
	m_nPatternAnim(0),
	m_bAnimation(false),
	m_pTexture(nullptr)
{
	SetObjState(CObject::OBJSTATE_2D);
	m_col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	m_objpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntY = 0;
}

//��������������������������������������������������������������
// �I�u�W�F�N�g�QD�̃f�X�g���N�^
//��������������������������������������������������������������
CObject2D::~CObject2D()
{
}

//��������������������������������������������������������������
// �I�u�W�F�N�g�QD�̐���
//��������������������������������������������������������������
CObject2D * CObject2D::Create(D3DXVECTOR3 pos, D3DXVECTOR2 scale, std::string tex, int priority, D3DXCOLOR col)
{
	CObject2D *pObj = nullptr;
	pObj = new CObject2D(priority);

	//�k���`�F�b�N
	if (pObj != nullptr)
	{
		// �|���S���̏���������
		pObj->SetPos(pos);
		pObj->SetScale(scale);
		pObj->SetCol(col);
		pObj->BindTexture(tex);
		pObj->Init();
	}

	return pObj;
}

//��������������������������������������������������������������
// �I�u�W�F�N�g�QD�̏�����
//��������������������������������������������������������������
HRESULT CObject2D::Init()
{
	// �f�o�C�X�̃|�C���^���擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,		// �m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,									// ���\�[�X�̎g�p���@
		FVF_VERTEX_2D,										// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,									// ���\�[�X�z�u�̃v�[���^�C�v
		&m_pVtxBuff,										// ���_�o�b�t�@���\�[�X
		NULL);

	VERTEX_2D*pVtx;        //���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//��������������������������������������������������������������
// �I�u�W�F�N�g�QD�̏I��
//��������������������������������������������������������������
void CObject2D::Uninit()
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
// �I�u�W�F�N�g�QD�̍X�V
//��������������������������������������������������������������
void CObject2D::Update()
{
	VERTEX_2D*pVtx;        //���_���ւ̃|�C���^ 

	m_objpos += m_move;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//// ���_���W�̍X�V
	//pVtx[0].pos = D3DXVECTOR3(m_objpos.x - m_Width, m_objpos.y - m_Height, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(m_objpos.x + m_Width, m_objpos.y - m_Height, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(m_objpos.x - m_Width, m_objpos.y + m_Height, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(m_objpos.x + m_Width, m_objpos.y + m_Height, 0.0f);

	D3DXMATRIX mtx;    // �v�Z�p�}�g���b�N�X
	D3DXVECTOR3 afterPos[4];

	//�Q�[�W�̒��_���W
	const D3DXVECTOR3 Vtx[4] =
	{
		D3DXVECTOR3(m_objpos.x - m_Width, m_objpos.y - m_Height, 0.0f),
		D3DXVECTOR3(m_objpos.x + m_Width, m_objpos.y - m_Height, 0.0f),
		D3DXVECTOR3(m_objpos.x - m_Width, m_objpos.y + m_Height, 0.0f),
		D3DXVECTOR3(m_objpos.x + m_Width, m_objpos.y + m_Height, 0.0f),
	};

	 //���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �}�g���b�N�X�̐���
	D3DXMatrixIdentity(&mtx);

	// ���[�A�s�b�`�A���[�����w�肵�ă}�g���b�N�X���쐬
	D3DXMatrixRotationYawPitchRoll(&mtx, 0.0f, 0.0f, D3DXToRadian(m_rot));

	// ���_���W�̍X�V
	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&afterPos[i], &Vtx[i], &mtx);
		pVtx[i].pos = afterPos[i];
	}

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	// ���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	if (m_bAnimation)
	{	// �e�N�X�`���A�j���[�V����������ꍇ
		m_CntTime++;

		if (m_CntTime >= m_Timer)
		{
			m_AnimationSpdCnt++;
			if (m_AnimationSpdCnt >= m_AnimationSpeed)
			{
				m_AnimationSpdCnt = 0;
				m_PatternAnimX++;

				if (m_PatternAnimX > m_DivisionX)
				{	//�A�j���[�V����
					m_PatternAnimX = 0;
					m_PatternAnimY++;

					if (m_PatternAnimY >= m_DivisionY)
					{
						m_PatternAnimY = 0;

						if (!m_bLoop)
						{	//���[�v���Ȃ��ꍇ
							Uninit();
							return;
						}
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
// �I�u�W�F�N�g�QD�̕`��
//��������������������������������������������������������������
void CObject2D::Draw()
{
	// �e�N�X�`���̃|�C���^���擾
	CTexture* pTexture = CApplication::GetInstance()->GetTexture();

	// �f�o�C�X�̃|�C���^���擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
		0,											// �ŏ��̒��_�C���f�b�N�X
		2);											// �v���~�e�B�u(�|���S��)��

	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}

//��������������������������������������������������������������
// �I�u�W�F�N�g�QD�̃e�N�X�`�����o�C���h
//��������������������������������������������������������������
void CObject2D::BindTexture(std::string inPath)
{
	m_pTexture = CApplication::GetInstance()->GetTexture()->GetTexture(inPath);		// �e�N�X�`���̃|�C���^
}

//��������������������������������������������������������������
// �I�u�W�F�N�g�QD�̃e�N�X�`����UV���W��ݒ�
//��������������������������������������������������������������
void CObject2D::SetUV(float Xtop, float Xbottom, float Ytop, float Ybottom)
{
	VERTEX_2D*pVtx;				// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(Xtop, Ytop);
	pVtx[1].tex = D3DXVECTOR2(Xbottom, Ytop);
	pVtx[2].tex = D3DXVECTOR2(Xtop, Ybottom);
	pVtx[3].tex = D3DXVECTOR2(Xbottom, Ybottom);

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//��������������������������������������������������������������
// �I�u�W�F�N�g�QD�̃A�j���[�V�����̐ݒ�
//��������������������������������������������������������������
void CObject2D::SetAnimation(const int U, const int V, const int Speed, const int Drawtimer, const bool loop)
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

//��������������������������������������������������������������
// �I�u�W�F�N�g�QD�̎l�p����
//��������������������������������������������������������������
bool CObject2D::SquareCollision(D3DXVECTOR3 pos, D3DXVECTOR3 Destpos, float Length, float CollisionVal)
{
	float fDistance = ((Destpos.x - pos.x) * (Destpos.x - pos.x)) +
		((Destpos.y - pos.y) * (Destpos.y - pos.y));

	float fRad = powf((Length + Length), CollisionVal);

	if (fDistance <= fRad)
	{
		return true;
	}
	return false;
}

//��������������������������������������������������������������
// �I�u�W�F�N�g�QD�̊۔���
//��������������������������������������������������������������
bool CObject2D::CircleCollision(D3DXVECTOR3 pos, D3DXVECTOR3 Destpos, float Radius, float CollisionVal)
{
	float fDistance = ((Destpos.x - pos.x) * (Destpos.x - pos.x)) +
		((Destpos.y - pos.y) * (Destpos.y - pos.y));

	float fRad = powf((Radius + Radius) * D3DX_PI, CollisionVal);

	if (fDistance <= fRad)
	{
		return true;
	}
	return false;
}