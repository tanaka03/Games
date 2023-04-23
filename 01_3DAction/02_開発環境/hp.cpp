#include "application.h"
#include "game.h"
#include "hp.h"
#include "object.h"
#include "player.h"
#include "object3d.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// HPのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CHp::CHp(int priority)
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// HPのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CHp::~CHp()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// HPの初期化
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
HRESULT CHp::Init()
{
	m_Width = GetScale().x;
	m_Height = GetScale().y;

	CBillboard::BindTexture("GAUGE");
	CBillboard::Init();

	m_pFrame = CBillboard::Create(GetPos(), D3DXVECTOR3(m_Width - 25.0f, m_Height, 0.0f), CObject::PRIORITY_FOURTH);
	m_pFrame->BindTexture("GAUGEFRAME");
	m_pFrame->AlphaTest();

	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// HPの終了
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CHp::Uninit()
{
	CBillboard::Uninit();

	m_pFrame->Destroy();
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// HPの更新
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CHp::Update()
{
	D3DXVECTOR3 pos = CBillboard::GetPos();
	int max = C3DGauge::GetMaxValue();
	int currentValue = C3DGauge::GetValue();

	m_pFrame->SetPos(D3DXVECTOR3(pos.x , pos.y , pos.z ));

	if (max < currentValue)
	{
		currentValue = max;
	}

	//頂点座標の設定
	VERTEX_3D *pVtx;        //頂点情報へのポインタ 

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-(m_Width / 2), m_Height, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(-(m_Width / 2) + (m_Width / 100) * ((currentValue * 100) / max), m_Height, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-(m_Width / 2), -m_Height, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(-(m_Width / 2) + (m_Width / 100) * ((currentValue * 100) / max), -m_Height, 0.0f);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// HPの描画
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CHp::Draw()
{
	// デバイスのポインタを取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	// ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	CBillboard::Draw();

	// ライトを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}