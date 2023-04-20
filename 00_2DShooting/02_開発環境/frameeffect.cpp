#include "frameeffect.h"
#include "object2d.h"
#include "main.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//フレームエフェクトのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CFrameEffect::CFrameEffect()
{
	m_col = D3DXCOLOR(1.0f,1.0f,1.0f,0.9f);
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//フレームエフェクトのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CFrameEffect::~CFrameEffect()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//フレームエフェクトの生成
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CFrameEffect * CFrameEffect::Create()
{
	CFrameEffect *pFrameEffect = nullptr;
	pFrameEffect = new CFrameEffect;

	//ヌルチェック
	if (pFrameEffect != nullptr)
	{
		// ポリゴンの初期化処理
		pFrameEffect->Init();
		pFrameEffect->SetType(CObject::OBJTYPE_FRAMEEFFECT);
	}

	return pFrameEffect;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//フレームエフェクトの初期化処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
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

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//フレームエフェクトの終了処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CFrameEffect::Uninit()
{
	CObject2D::Uninit();
	CObject2D::Release();
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//フレームエフェクトの更新処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CFrameEffect::Update()
{
	CObject2D::Update();
	m_col.a -= 0.01f;

	CObject2D::SetCol(m_col);

	if (m_col.a <= 0.0f)
	{//アルファ値が０になったら
		Uninit();
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//フレームエフェクトの描画処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CFrameEffect::Draw()
{
	CObject2D::Draw();
}