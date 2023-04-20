#include "frameeffect.h"
#include "object2d.h"
#include "main.h"

//����������������������������������������
//�t���[���G�t�F�N�g�̃R���X�g���N�^
//����������������������������������������
CFrameEffect::CFrameEffect()
{
	m_col = D3DXCOLOR(1.0f,1.0f,1.0f,0.9f);
}

//����������������������������������������
//�t���[���G�t�F�N�g�̃f�X�g���N�^
//����������������������������������������
CFrameEffect::~CFrameEffect()
{
}

//����������������������������������������
//�t���[���G�t�F�N�g�̐���
//����������������������������������������
CFrameEffect * CFrameEffect::Create()
{
	CFrameEffect *pFrameEffect = nullptr;
	pFrameEffect = new CFrameEffect;

	//�k���`�F�b�N
	if (pFrameEffect != nullptr)
	{
		// �|���S���̏���������
		pFrameEffect->Init();
		pFrameEffect->SetType(CObject::OBJTYPE_FRAMEEFFECT);
	}

	return pFrameEffect;
}

//����������������������������������������
//�t���[���G�t�F�N�g�̏���������
//����������������������������������������
HRESULT CFrameEffect::Init()
{
	CObject2D::SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 ,0.0f));
	CObject2D::SetCol(m_col);
	CObject2D::SetScale(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	CObject2D::Init();
	CObject2D::SetTexture(CTexture::TEXTURE_DAMAGEFRAME);

	m_col = GetCol();

	return S_OK;
}

//����������������������������������������
//�t���[���G�t�F�N�g�̏I������
//����������������������������������������
void CFrameEffect::Uninit()
{
	CObject2D::Uninit();
	CObject2D::Release();
}

//����������������������������������������
//�t���[���G�t�F�N�g�̍X�V����
//����������������������������������������
void CFrameEffect::Update()
{
	CObject2D::Update();
	m_col.a -= 0.01f;

	CObject2D::SetCol(m_col);

	if (m_col.a <= 0.0f)
	{//�A���t�@�l���O�ɂȂ�����
		Uninit();
	}
}

//����������������������������������������
//�t���[���G�t�F�N�g�̕`�揈��
//����������������������������������������
void CFrameEffect::Draw()
{
	CObject2D::Draw();
}