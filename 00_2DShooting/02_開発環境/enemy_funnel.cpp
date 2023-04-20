#include "effect.h"
#include "enemy_funnel.h"
#include "application.h"
#include "input.h"
#include "keyboard.h"
#include "bullet.h"
#include "texture.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//爆発のコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CEnemyFunnel::CEnemyFunnel()
{
	m_fAngle = 0;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//爆発のデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CEnemyFunnel::~CEnemyFunnel()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//ファンネルの生成
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CEnemyFunnel * CEnemyFunnel::Create(D3DXVECTOR3 pos, EType type)
{
	CEnemyFunnel *pFunnel = nullptr;
	pFunnel = new CEnemyFunnel;

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
HRESULT CEnemyFunnel::Init()
{
	CObject2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CObject2D::SetScale(38.0f, 38.0f);
	CObject2D::Init();

	switch (GetFunnel())
	{
	case FUNNEL_BULLET:
		CObject2D::SetTexture(CTexture::TEXTURE_FUNNEL2);
		break;

	default:
		break;
	}

	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//ファンネルの終了処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CEnemyFunnel::Uninit()
{
	CObject2D::Uninit();
	CObject2D::Release();
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//ファンネルの更新処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CEnemyFunnel::Update()
{
	D3DXVECTOR3 addPos[4];
	D3DXMATRIX mtx;    // 計算用マトリックス
	m_pos = GetPos();
	m_fTimer++;
	m_nEffectTime++;
	m_nPressTime++;

	CObject2D::Update();

	switch (GetFunnel())
	{
	case FUNNEL_BULLET:
		//バレットクラスの生成
		if ((m_nPressTime % 80) == 0)
		{
			for (int i = 0; i < 5; i++)
			{
				m_pBullet = m_pBullet->Create(m_pos, D3DXVECTOR3(sinf((i * ((360 / 5) * (D3DX_PI / 180))) * m_fAngle), cosf((i * ((360 / 5) * (D3DX_PI / 180))) * m_fAngle), 0.0f) * 2.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 500, false, CBullet::BULLETTYPE_NORMAL, CBullet::BULLETTAG_ENEMY);
				m_pBullet->SetTexture(CTexture::TEXTURE_REDBULLET);
				m_pBullet->SetScale(15.0f, 15.0f);
				m_pBullet->SetCollisionScale(3.0f);
			}
			m_fAngle += 0.05f;
		}
		break;

	default:
		break;
	}

	if ((m_nEffectTime % 5) == 0)
	{
		m_pEffect = m_pEffect->Create(m_pos, D3DXVECTOR3(0.0f, -3.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), 120, CEffect::EFFECTTYPE_ASTER);
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
void CEnemyFunnel::Draw()
{
	CObject2D::Draw();
}
