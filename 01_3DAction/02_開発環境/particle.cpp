//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// パーティクル処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#include "application.h"
#include "renderer.h"
#include "particle.h"
#include "player.h"
#include "game.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// パーティクルのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CParticle::CParticle(int nPriority) :
	CBillboard(CObject::PRIORITY_THIRD),
	m_info({}),
	m_nTime(0)			// 時間
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// パーティクルのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CParticle::~CParticle()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// パーティクルの生成
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CParticle * CParticle::Create(SInfo& info, const std::string url, int nPriority)
{
	CParticle *pParticle = new CParticle(nPriority);

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
// パーティクルの初期化
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
HRESULT CParticle::Init()
{
	// テクスチャの読み込み
	BindTexture(m_path);

	// オブジェクトの初期化
	CBillboard::Init();

	CBillboard::SetPos(m_info.pos);
	CBillboard::SetMove(m_info.move * m_info.moveAttenuation);
	CBillboard::SetCol(m_info.col);
	CBillboard::SetScale(m_info.scale);
	CBillboard::SetBlend(BLEND_ADDITIVE);

	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// パーティクルの更新
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CParticle::Update()
{
	CBillboard::Update();

	Behavior(m_info.infoProperty);
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// パーティクルの描画
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CParticle::Draw()
{
	// デバイスのポインタを取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	// ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// Zテスト
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// アルファテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	CBillboard::Draw();

	// ライトを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// Zバッファの設定を元に戻す
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// アルファテストを無効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// パーティクルのプロパティに応じた処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CParticle::Behavior(std::vector<std::string>& prop)
{
	for (auto &p : prop)
	{
		// ビルボードの回転
		if (p == "Rotate")
		{
			CBillboard::Rotate(m_info.rotateValue);
		}

		// 色の変移
		else if (p == "ColorTransition")
		{
			D3DXCOLOR col = CBillboard::GetCol();

			col.r += (m_info.destCol.r - col.r) / (m_info.destroyTime * m_info.colAttenuation);
			col.g += (m_info.destCol.g - col.g) / (m_info.destroyTime * m_info.colAttenuation);
			col.b += (m_info.destCol.b - col.b) / (m_info.destroyTime * m_info.colAttenuation);

			CBillboard::SetCol(col);
		}

		// 拡縮
		else if (p == "Scaling")
		{
			D3DXVECTOR3 scale = CBillboard::GetScale();

			scale.x += m_info.scalingValue.x;
			scale.y += m_info.scalingValue.y;
			scale.z += m_info.scalingValue.z;

			CBillboard::SetScale(scale);
		}

		// 重力
		else if (p == "Gravity")
		{
			D3DXVECTOR3 move = CBillboard::GetMove();

			if (m_nTime >= m_info.fallDelayTime)
			{
				move.y -= m_info.weight;
			}

			CBillboard::SetMove(move);
		}

		// 指定した位置に向かって移動
		else if (p == "Vector")
		{
			D3DXVECTOR3 objPos = CBillboard::GetPos();
			D3DXVECTOR3 vec = m_info.destPos - objPos;
			D3DXVec3Normalize(&vec, &vec);

			objPos += vec * m_info.moveAttenuation;

			CBillboard::SetPos(objPos);
		}
	}
}