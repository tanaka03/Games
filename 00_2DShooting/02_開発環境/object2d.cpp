#include "application.h"
#include "object2d.h"
#include "input.h"
#include "keyboard.h"
#include "texture.h"

//����������������������������������������
//�I�u�W�F�N�g�Q�c�̃R���X�g���N�^
//����������������������������������������
CObject2D::CObject2D()
{
	m_objpos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_nCntY = 0;
}

//����������������������������������������
//�I�u�W�F�N�g�Q�c�̃f�X�g���N�^
//����������������������������������������
CObject2D::~CObject2D()
{

}

//����������������������������������������
//�I�u�W�F�N�g�Q�c�̏���������
//����������������������������������������
HRESULT CObject2D::Init()
{
	//���_�o�b�t�@�̐���
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
		
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,    //�m�ۂ���o�b�t�@�̃T�C�Y
	D3DUSAGE_WRITEONLY,
	FVF_VERTEX_2D,            //���_�t�H�[�}�b�g
	D3DPOOL_MANAGED,
	&m_pVtxBuff,
	NULL);

	m_texture = CTexture::TEXTURE_NONE;

	VERTEX_2D*pVtx;        //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
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

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//����������������������������������������
//�I�u�W�F�N�g�Q�c�̏I������
//����������������������������������������
void CObject2D::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//����������������������������������������
//�I�u�W�F�N�g�Q�c�̍X�V����
//����������������������������������������
void CObject2D::Update()
{
	if (m_bUseMyCol)
	{
		switch (GetMyCol())
		{
		case COLOR_RED:				//��
			CObject2D::SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			break;

		case COLOR_ORANGE:			//��
			CObject2D::SetCol(D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f));
			break;

		case COLOR_YELLOW:			//��
			CObject2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
			break;

		case COLOR_LIGHTGREEN:		//����
			CObject2D::SetCol(D3DXCOLOR(0.5f, 1.0f, 0.5f, 1.0f));
			break;

		case COLOR_GREEN:			//��
			CObject2D::SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
			break;

		case COLOR_LIGHTBLUE:		//��
			CObject2D::SetCol(D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
			break;

		case COLOR_BLUE:			//��
			CObject2D::SetCol(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
			break;

		case COLOR_PURPLE:			//��
			CObject2D::SetCol(D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f));
			break;

		case COLOR_PINK:			//��
			CObject2D::SetCol(D3DXCOLOR(1.0f, 0.5f, 1.0f, 1.0f));
			break;

		case COLOR_WHITE:			//��
			CObject2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			break;

		default:
			CObject2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetMyCol(COLOR_INVALID);
			break;
		}
	}

	VERTEX_2D*pVtx;        //���_���ւ̃|�C���^ 

	m_objpos += m_move;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̍X�V
	pVtx[0].pos = D3DXVECTOR3(m_objpos.x - m_Width, m_objpos.y - m_Height, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_objpos.x + m_Width, m_objpos.y - m_Height, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_objpos.x - m_Width, m_objpos.y + m_Height, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_objpos.x + m_Width, m_objpos.y + m_Height, 0.0f);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//����������������������������������������
//�I�u�W�F�N�g�Q�c�̕`�揈��
//����������������������������������������
void CObject2D::Draw()
{
	CTexture* pTexture = CApplication::GetTexture();

	//���_�o�b�t�@�̐���
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetTexture(m_texture));

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
		0,
		2);						//�v���~�e�B�u(�|���S��)��

	//�|���S���̕`��
	//m_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
	//	2,						//�v���~�e�B�u(�|���S��)��
	//	&pVtx[0],			//���_���̐퓬�A�h���X
	//	sizeof(VERTEX_2D));		//���_���\���̂̃T�C�Y
}

//����������������������������������������
//�e�N�X�`�����W
//����������������������������������������
void CObject2D::SetUV(float Xtop, float Xbottom, float Ytop, float Ybottom)
{
	VERTEX_2D*pVtx;        //���_���ւ̃|�C���^

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

//����������������������������������������
//�A�j���[�V����
//����������������������������������������
void CObject2D::SetAnim(int DivX, int DivY, int speed, int interval, bool loop)
{
	m_nCounterAnim++;

	//�A�j���[�V����
	if ((m_nCounterAnim % speed) == interval)//�����ő��x����
	{
		m_nPatternAnim++;

		CObject2D::SetUV((1.0f / DivX) * m_nPatternAnim,
			(1.0f / DivX) + (1.0f / DivX) * m_nPatternAnim,
			(1.0f / DivY) * m_nCntY,
			(1.0f / DivY) + (1.0f / DivY) * m_nCntY);

		if (DivX == m_nPatternAnim)
		{
			m_nCntY++;
		}

		if (m_nPatternAnim == (DivX + DivY) && !loop)
		{
			Uninit();
			return;
		}
	}
}

//����������������������������������������
//�l�p����
//����������������������������������������
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

//����������������������������������������
//�۔���
//����������������������������������������
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

//����������������������������������������
//���ϔ���
//����������������������������������������
bool CObject2D::AngleCollision(D3DXVECTOR3 pos, D3DXVECTOR3 Destpos, float minAngle, float maxAngle, float radius)
{
	//Min -1.0 Max 1.0�ŉ~�`����
	D3DXVECTOR3 vec = Destpos - pos;

	//���K��
	D3DXVec3Normalize(&vec, &vec);

	//����
	float fDot = sinf(D3DXVec3Dot(&D3DXVECTOR3(0, 1, 0), &vec));

	bool Radius = CircleCollision(pos, Destpos, radius, 2);

	if (fDot <= maxAngle && fDot > minAngle && Radius)
	{
		return true;
	}

	return false;
}

//����������������������������������������
//�w��͈͔̔���
//����������������������������������������
bool CObject2D::RangeCollision(D3DXVECTOR3* pos, float Xmin, float Xmax, float Ymin, float Ymax)
{
	D3DXVECTOR3 Pos = *pos;

	if (Pos.x <= Xmin)
	{
		return true;
	}

	if (Pos.x >= Xmax)
	{
		return true;
	}

	if (Pos.y <= Ymin)
	{
		return true;
	}

	if (Pos.y >= Ymax)
	{
		return true;
	}

	return false;
}
