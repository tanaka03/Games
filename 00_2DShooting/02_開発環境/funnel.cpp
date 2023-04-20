#include "effect.h"
#include "funnel.h"
#include "application.h"
#include "input.h"
#include "keyboard.h"
#include "bullet.h"
#include "texture.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//爆発のコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CFunnel::CFunnel()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//爆発のデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CFunnel::~CFunnel()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//ファンネルの生成
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CFunnel * CFunnel::Create(D3DXVECTOR3 pos, EType type)
{
	CFunnel *pFunnel = nullptr;
	pFunnel = new CFunnel;

	//ヌルチェック
	if (pFunnel != nullptr)
	{
		// ポリゴンの初期化処理
		pFunnel->SetFunnel(type);
		pFunnel->Init();
		pFunnel->SetPos(pos);
	}

	return pFunnel;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//ファンネルの初期化処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
HRESULT CFunnel::Init()
{
	CObject2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CObject2D::SetScale(38.0f, 38.0f);
	CObject2D::Init();

	switch (GetFunnel())
	{
	case FUNNEL_BULLET:
		CObject2D::SetTexture(CTexture::TEXTURE_FUNNEL);
		break;

	default:
		break;
	}

	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//ファンネルの終了処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CFunnel::Uninit()
{
	CObject2D::Uninit();
	CObject2D::Release();
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//ファンネルの更新処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CFunnel::Update()
{
	D3DXVECTOR3 addPos[4];
	D3DXMATRIX mtx;    // 計算用マトリックス
	m_pos = GetPos();
	m_fTimer++;
	m_nEffectTime++;

	CObject2D::Update();

	switch (GetFunnel())
	{
	case FUNNEL_BULLET:
		if (CApplication::GetInputKeyboard()->GetPress(DIK_SPACE))
		{
			m_nPressTime++;

			//バレットクラスの生成
			if ((m_nPressTime % 5) == 0)
			{
				m_pBullet = m_pBullet->Create(m_pos, D3DXVECTOR3(0.0f, -15.0f, 0.0f), D3DXCOLOR(0.0f, 0.4f, 0.8f, 1.0f), 35, false, CBullet::BULLETTYPE_NORMAL, CBullet::BULLETTAG_PLAYER);
				m_pBullet->SetTexture(CTexture::TEXTURE_SQUAREBULLET);
				m_pBullet->SetCollisionScale(5.0f);
				m_nPressTime = 0;
			}
		}
		break;

	default:
		break;
	}

	if ((m_nEffectTime % 5) == 0)
	{
		m_pEffect = m_pEffect->Create(m_pos, D3DXVECTOR3(0.0f, 3.0f, 0.0f),D3DXCOLOR(1.0f,0.5f,0.0f,1.0f),120, CEffect::EFFECTTYPE_ASTER);
		m_pEffect->SetBehavior(CEffect::BEHAVIOR_ROTATION);
	}

	SetPos(m_pos);

	VERTEX_2D*pVtx;        //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// マトリックスの生成
	D3DXMatrixIdentity(&mtx);

	// ヨー、ピッチ、ロールを指定してマトリックスを作成
	D3DXMatrixRotationYawPitchRoll(&mtx, 0.0f, 0.0f, ((D3DX_PI * 1.5f) / 100.0f) * m_fTimer);

	// 頂点座標            ↓頂点数
	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&addPos[i], &sVtx[i], &mtx);
		pVtx[i].pos = m_pos + addPos[i] * (35.0f);    //<-サイズ変更
	}

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//ファンネルの描画処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CFunnel::Draw()
{
	CObject2D::Draw();
}
