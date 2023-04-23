#include "application.h"
#include "game.h"
#include "sp.h"
#include "object.h"
#include "player.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 経験値ゲージのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CSp::CSp(int priority)
{
	//m_Width = 100.0f;
	//m_Height = 10.0f;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 経験値ゲージのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CSp::~CSp()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 経験値ゲージの初期化
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
HRESULT CSp::Init()
{
	m_Width = GetScale().x;
	m_Height = GetScale().y;

	CObject2D::BindTexture("GAUGE");
	CObject2D::Init();
	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 経験値ゲージの終了
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CSp::Uninit()
{
	CObject2D::Uninit();
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 経験値ゲージの更新
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CSp::Update()
{
	CObject2D::Update();

	D3DXVECTOR3 pos = CObject2D::GetPos();
	int max = CGauge::GetMaxValue();
	int currentValue = CGauge::GetValue();
	float rot = CGauge::GetRot();

	if (max < currentValue)
	{
		currentValue = max;
	}

	D3DXMATRIX mtx;    // 計算用マトリックス
	D3DXVECTOR3 afterPos[4];

	//ゲージの頂点座標
	const D3DXVECTOR3 Vtx[4] =
	{
		D3DXVECTOR3(pos.x - (m_Width / 2), pos.y - m_Height, 0.0f),
		D3DXVECTOR3(pos.x - (m_Width / 2) + (m_Width / 100) * ((currentValue * 100) / max), pos.y - m_Height, 0.0f),
		D3DXVECTOR3(pos.x - (m_Width / 2), pos.y + m_Height, 0.0f),
		D3DXVECTOR3(pos.x - (m_Width / 2) + (m_Width / 100) * ((currentValue * 100) / max), pos.y + m_Height, 0.0f),
	};

	//頂点座標の設定
	VERTEX_2D*pVtx;        //頂点情報へのポインタ 

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// マトリックスの生成
	D3DXMatrixIdentity(&mtx);

	// ヨー、ピッチ、ロールを指定してマトリックスを作成
	D3DXMatrixRotationYawPitchRoll(&mtx, 0.0f, 0.0f, D3DXToRadian(rot));

	// 頂点座標の更新
	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&afterPos[i], &Vtx[i], &mtx);
		pVtx[i].pos = afterPos[i];
	}

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 経験値ゲージの描画
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CSp::Draw()
{
	CObject2D::Draw();
}