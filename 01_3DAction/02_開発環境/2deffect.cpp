#include "application.h"
#include "renderer.h"
#include "2deffect.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 2Dエフェクトのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
C2DEffect::C2DEffect(int nPriority) :
	CObject2D(CObject::PRIORITY_FOURTH),
	m_info({}),
	m_nTime(0)			// 時間
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 2Dエフェクトのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
C2DEffect::~C2DEffect()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 2Dエフェクトの生成
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
C2DEffect * C2DEffect::Create(SInfo& info, const std::string url, int nPriority)
{
	C2DEffect *pParticle = new C2DEffect(nPriority);

	if (pParticle != nullptr)
	{
		pParticle->SetInfo(info);
		pParticle->SetPath(url);
		pParticle->Init();
	}
	else
	{
		assert(false);
	}

	return pParticle;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 2Dエフェクトの初期化
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
HRESULT C2DEffect::Init()
{
	//テクスチャの読み込み
	BindTexture(m_path);

	//オブジェクトの初期化
	CObject2D::SetPos(m_info.pos);
	CObject2D::SetMove(m_info.move);
	CObject2D::SetCol(m_info.col);
	CObject2D::SetScale(D3DXVECTOR2(15.0f, 15.0f));
	CObject2D::Init();

	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 2Dエフェクトの更新
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void C2DEffect::Update()
{
	CObject2D::Update();

	Behavior(m_info.infoProperty);

	m_nTime++;
	if (m_nTime >= m_info.destroyTime)
	{
		CObject2D::Uninit();
		return;
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 2Dエフェクトの描画
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void C2DEffect::Draw()
{
	// デバイスのポインタを取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	// アルファテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	CObject2D::Draw();

	// アルファテストを無効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 2Dエフェクトのプロパティに応じた処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void C2DEffect::Behavior(std::vector<std::string>& prop)
{
	for (auto p : prop)
	{
		// 色の変移
		if (p == "ColorTransition")
		{
			D3DXCOLOR col = CObject2D::GetCol();

			col.r += (m_info.destCol.r - col.r) / (m_info.destroyTime * m_info.colAttenuation);
			col.g += (m_info.destCol.g - col.g) / (m_info.destroyTime * m_info.colAttenuation);
			col.b += (m_info.destCol.b - col.b) / (m_info.destroyTime * m_info.colAttenuation);

			CObject2D::SetCol(col);
			continue;
		}

		// テクスチャの拡大
		if (p == "Scaling")
		{
			D3DXVECTOR2 scale = CObject2D::GetScale();
			scale.x += m_info.scalingSpeed;
			scale.y += m_info.scalingSpeed;

			CObject2D::SetScale(scale);
			continue;
		}

		// 指定した位置に向かって移動
		if (p == "Vector")
		{
			D3DXVECTOR3 objPos = CObject2D::GetPos();
			D3DXVECTOR3 vec = m_info.destPos - objPos;
			D3DXVec3Normalize(&vec, &vec);

			objPos += vec * m_info.moveAttenuation;

			CObject2D::SetPos(objPos);
			continue;
		}
	}
}