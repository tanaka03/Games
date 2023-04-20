#include "fade.h"
#include "main.h"

CFade::CFade()
{
}

CFade::~CFade()
{
}

CFade * CFade::Create(int fadetime, EFadeType type)
{
	CFade *pFade = nullptr;
	pFade = new CFade;

	//ヌルチェック
	if (pFade != nullptr)
	{
		// ポリゴンの初期化処理
		pFade->SetFadeType(type);
		pFade->SetFadeSecond(fadetime);
		pFade->Init();
	}

	return pFade;
}

HRESULT CFade::Init()
{
	CObject2D::SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	CObject2D::SetScale(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	CObject2D::Init();

	switch (GetFadeType())
	{
	case FADE_IN:
		m_col.a = 0.0f;
		break;

	case FADE_OUT:
		m_col.a = 1.0f;
		break;

	default:
		break;
	}

	return S_OK;
}

void CFade::Uninit()
{
	CObject2D::Uninit();
	CObject2D::Release();
}

void CFade::Update()
{
	CObject2D::Update();

	switch (GetFadeType())
	{
	case FADE_IN:
		m_col.a += 0.03f;

		if (m_col.a >= 1.0f)
		{
			//Sleep(GetFadeSecond());
			Uninit();
			return;
		}
		break;

	case FADE_OUT:
		m_col.a -= 0.03f;

		if (m_col.a <= 0.0f)
		{
			Uninit();
			return;
		}
		break;

	default:
		break;
	}

	SetCol(m_col);
}

void CFade::Draw()
{
	CObject2D::Draw();
}