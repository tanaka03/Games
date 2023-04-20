#include "object2d.h"
#include "application.h"
#include "bg.h"
#include "texture.h"

//����������������������������������������
//�w�i�̃R���X�g���N�^
//����������������������������������������
CBg::CBg()
{
	m_fV = 0.0f;
	m_range = D3DXVECTOR2(1.0f,1.0f);
}

//����������������������������������������
//�w�i�̃f�X�g���N�^
//����������������������������������������
CBg::~CBg()
{
}

//����������������������������������������
//�w�i�̐���
//����������������������������������������
CBg * CBg::Create(EBGType type, bool alpha)
{
	CBg *pBg = nullptr;
	pBg = new CBg;

	//�k���`�F�b�N
	if (pBg != nullptr)
	{
		pBg->m_apObject2D = new CObject2D;

		pBg->SetBg(type);
		pBg->SetAlphaBlend(alpha);
		pBg->Init();
		pBg->SetType(CObject::OBJTYPE_BG);
	}

	return pBg;
}

//����������������������������������������
//�w�i�̏���������
//����������������������������������������
HRESULT CBg::Init()
{
	if (m_apObject2D != nullptr)
	{
		m_apObject2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
		m_apObject2D->SetScale(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		m_apObject2D->Init();
		m_col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		m_apObject2D->SetCol(m_col);

		switch (GetBg())
		{
		case BG_TITLE:
			m_apObject2D->SetTexture(CTexture::TEXTURE_BGTITLE);
			break;

		case BG_TITLELACE1:
			m_apObject2D->SetTexture(CTexture::TEXTURE_BGLACEB);
			break;

		case BG_GAME1:
			m_apObject2D->SetTexture(CTexture::TEXTURE_BG);
			break;

		case BG_GAMECLOUD:
			m_apObject2D->SetTexture(CTexture::TEXTURE_BGCLOUD);
			break;

		case BG_GAMEBRIGHT:
			m_apObject2D->SetTexture(CTexture::TEXTURE_BGBRIGHT);
			break;

		case BG_GAMELACE1:
			m_apObject2D->SetTexture(CTexture::TEXTURE_BGLACEA);
			break;

		case BG_RESULT:
			m_apObject2D->SetTexture(CTexture::TEXTURE_BGSKY);
			break;

		case BG_TUTORIAL:
			m_apObject2D->SetTexture(CTexture::TEXTURE_BGGLASS);
			break;

		default:
			break;
		}
	}

	return S_OK;
}

//����������������������������������������
//�w�i�̏I������
//����������������������������������������
void CBg::Uninit()
{
	if (m_apObject2D != nullptr)
	{
		m_apObject2D->Uninit();
		CObject::Release();
	}
}

//����������������������������������������
//�w�i�̍X�V����
//����������������������������������������
void CBg::Update()
{
	if (m_apObject2D != nullptr)
	{
		m_apObject2D->Update();
		m_range = GetRange();
		m_col.a = GetAlpha();

		if (GetScroll())
		{
			m_fV -= m_fSpeed;

			if (GetHorizon())
			{
				m_apObject2D->SetUV((m_range.x / 1) * m_fV, (m_range.x / 1) + (m_range.x / 1) * m_fV, 0.0f, m_range.y);
			}

			else
			{
				m_apObject2D->SetUV(0.0f, m_range.x, (m_range.y / 1) * m_fV, (m_range.y / 1) + (m_range.y / 1) * m_fV);
			}
		}

		m_apObject2D->SetCol(m_col);
	}
}

//����������������������������������������
//�w�i�̕`�揈��
//����������������������������������������
void CBg::Draw()
{
	if (m_apObject2D != nullptr)
	{
		//���Z����
		if (GetAlphaBlend())
		{
			CApplication::GetRenderer()->GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			CApplication::GetRenderer()->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			CApplication::GetRenderer()->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		}

		m_apObject2D->Draw();

		//�ݒ�����ɖ߂�
		if (GetAlphaBlend())
		{
			CApplication::GetRenderer()->GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			CApplication::GetRenderer()->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			CApplication::GetRenderer()->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}
	}
}