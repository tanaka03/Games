#include "main.h"
#include "object2d.h"
#include "effect.h"
#include "explosion.h"

//����������������������������������������
//�����̃R���X�g���N�^
//����������������������������������������
CExplosion::CExplosion()
{
}

//����������������������������������������
//�����̃f�X�g���N�^
//����������������������������������������
CExplosion::~CExplosion()
{

}

//����������������������������������������
//�����̐���
//����������������������������������������
CExplosion * CExplosion::Create(D3DXVECTOR3 pos)
{
	CExplosion *pExplosion = nullptr;
	pExplosion = new CExplosion;

	//�k���`�F�b�N
	if (pExplosion != nullptr)
	{
		// �|���S���̏���������
		pExplosion->Init();
		pExplosion->SetPos(pos);
	}

	return pExplosion;
}

//����������������������������������������
//�����̏���������
//����������������������������������������
HRESULT CExplosion::Init()
{
	CObject2D::SetCol(D3DXCOLOR(1.0f, 0.4f, 0.0f, 1.0f));
	CObject2D::SetScale(38.0f, 38.0f);
	CObject2D::Init();

	CObject2D::SetTexture(CTexture::TEXTURE_EXPLOSION);

	return S_OK;
}

//����������������������������������������
//�����̏I������
//����������������������������������������
void CExplosion::Uninit()
{
	CObject2D::Uninit();
	CObject::Release();
}

//����������������������������������������
//�����̍X�V����
//����������������������������������������
void CExplosion::Update()
{
	CEffect *pEffect = nullptr;

	CObject2D::Update();

	//�A�j���[�V����
	CObject2D::SetAnim(8,1,3,1, false);
}

//����������������������������������������
//�����̕`�揈��
//����������������������������������������
void CExplosion::Draw()
{
	CObject2D::Draw();
}
