//**************************************************
// 
// texture.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "application.h"
#include "texture.h"
#include "renderer.h"

#include <assert.h>

//==================================================
// 定義
//==================================================
const char* CTexture::s_FileName[] =
{// テクスチャのパス
	"data/TEXTURE/BULLET/flare.png",			// 弾１
	"data/TEXTURE/BULLET/BigBullet.png",		// 弾２
	"data/TEXTURE/BULLET/square.png",			// 弾３
	"data/TEXTURE/BULLET/bulletRed.png",		// 弾４
	"data/TEXTURE/Player.png",					// プレイヤー
	"data/TEXTURE/funnel.png",					// ファンネル
	"data/TEXTURE/funnel2.png",					// ファンネル２
	"data/TEXTURE/explosion000.png",			// 爆発
	"data/TEXTURE/ENEMY/choco.png",				// 敵１
	"data/TEXTURE/ENEMY/bird.png",				// 敵２
	"data/TEXTURE/ENEMY/Ghost.png",				// 敵３
	"data/TEXTURE/ENEMY/FireFairy.png",			// 敵４
	"data/TEXTURE/ENEMY/AquaFairy.png",			// 敵５
	"data/TEXTURE/ENEMY/Girl.png",				// 敵６
	"data/TEXTURE/ITEM/scoreItem.png",			// スコアアイテム１
	"data/TEXTURE/ITEM/scoreItemB.png",			// スコアアイテム２
	"data/TEXTURE/ITEM/recovery.png",			// 回復アイテム２
	"data/TEXTURE/ITEM/magnet.png",				// アビリティアイテム
	"data/TEXTURE/ITEM/orb.png",				// 自機強化アイテム
	"data/TEXTURE/UI/number000.png",			// スコア
	"data/TEXTURE/EFFECT/CircleA.png",			// アビリティ１
	"data/TEXTURE/EFFECT/bright.png",			// エフェクト１
	"data/TEXTURE/EFFECT/bright2.png",			// エフェクト２
	"data/TEXTURE/EFFECT/bright3.png",			// エフェクト３
	"data/TEXTURE/EFFECT/Aster.png",			// エフェクト４
	"data/TEXTURE/EFFECT/heart.png",			// ハートエフェクト
	"data/TEXTURE/EFFECT/biribiri.png",			// ビリビリエフェクト
	"data/TEXTURE/EFFECT/ring.png",				// 輪エフェクト
	"data/TEXTURE/EFFECT/MagicCircleB.png",		// 魔法陣エフェクト１
	"data/TEXTURE/EFFECT/MagicCircle.png",		// 魔法陣エフェクト２
	"data/TEXTURE/EFFECT/pipo-particle.png",	// パーティクル１
	"data/TEXTURE/EFFECT/pipo-particle2.png",	// パーティクル２
	"data/TEXTURE/EFFECT/pipo-particle3.png",	// パーティクル３
	"data/TEXTURE/FRAME/DamageFrame.png",		// フレームエフェクト１
	"data/TEXTURE/UI/Gauge.png",				// ゲージ
	"data/TEXTURE/UI/GaugeFrame.png",			// ゲージフレーム
	"data/TEXTURE/UI/fragment.png",				// 欠片
	"data/TEXTURE/BG/BG_ocean.jpg",				// 背景
	"data/TEXTURE/BG/BG_Glass.jpg",				// 背景
	"data/TEXTURE/BG/BG_cloud.png",				// 背景
	"data/TEXTURE/BG/BG_Sky2.jpg",				// 背景
	"data/TEXTURE/BG/BG_Bright.png",			// 背景
	"data/TEXTURE/BG/BG_laceframeA.png",		// 背景
	"data/TEXTURE/BG/BG_ScrollA.png",			// 背景
	"data/TEXTURE/BG/BG_Sky.png",				// タイトル背景
	"data/TEXTURE/TUTORIAL/tutorial1.png",		// チュートリアル
	"data/TEXTURE/TUTORIAL/tutorial2.png",		// チュートリアル
	"data/TEXTURE/TUTORIAL/tutorial3.png",		// チュートリアル
	"data/TEXTURE/TUTORIAL/tutorial4.png",		// チュートリアル
	"data/TEXTURE/TUTORIAL/tutorial5.png",		// チュートリアル
	"data/TEXTURE/TUTORIAL/tutorial6.png",		// チュートリアル
	"data/TEXTURE/UI/title.png",				// タイトルロゴ
	"data/TEXTURE/UI/PressEnter.png",			// エンター押下
	"data/TEXTURE/UI/Start.png",				// スタートボタン
	"data/TEXTURE/UI/Tutorial.png",				// チュートリアルボタン
	"data/TEXTURE/UI/Quit.png",					// 終了ボタン
	"data/TEXTURE/UI/rank.png",					// ランク
	"data/TEXTURE/UI/nowScore.png",				// 今回のスコア
	"data/TEXTURE/UI/new.png",					// NEW
	"data/TEXTURE/UI/HP.png",					// HP
	"data/TEXTURE/UI/MP.png"					// MP
};
static_assert(sizeof(CTexture::s_FileName) / sizeof(CTexture::s_FileName[0]) == CTexture::TEXTURE_MAX, "aho");

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CTexture::CTexture() :
	s_pTexture()
{
	memset(s_pTexture, 0, sizeof(s_pTexture));
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CTexture::~CTexture()
{
}

//--------------------------------------------------
// 全ての読み込み
//--------------------------------------------------
void CTexture::LoadAll()
{
	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	
	for (int i = 0; i < TEXTURE_MAX; ++i)
	{
		if (s_pTexture[i] != nullptr)
		{// テクスチャの読み込みがされている
			continue;
		}

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			s_FileName[i],
			&s_pTexture[i]);
	}
}

//--------------------------------------------------
// 読み込み
//--------------------------------------------------
void CTexture::Load(TEXTURE inTexture)
{
	assert(inTexture >= 0 && inTexture < TEXTURE_MAX);

	if (s_pTexture[inTexture] != nullptr)
	{// テクスチャの読み込みがされている
		return;
	}

	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		s_FileName[inTexture],
		&s_pTexture[inTexture]);
}

//--------------------------------------------------
// 全ての解放
//--------------------------------------------------
void CTexture::ReleaseAll(void)
{
	for (int i = 0; i < TEXTURE_MAX; ++i)
	{
		if (s_pTexture[i] != NULL)
		{// テクスチャの解放
			s_pTexture[i]->Release();
			s_pTexture[i] = NULL;
		}
	}
}

//--------------------------------------------------
// 解放
//--------------------------------------------------
void CTexture::Release(TEXTURE inTexture)
{
	assert(inTexture >= 0 && inTexture < TEXTURE_MAX);

	if (s_pTexture[inTexture] != NULL)
	{// テクスチャの解放
		s_pTexture[inTexture]->Release();
		s_pTexture[inTexture] = NULL;
	}
}

//--------------------------------------------------
// 取得
//--------------------------------------------------
LPDIRECT3DTEXTURE9 CTexture::GetTexture(TEXTURE inTexture)
{
	if (inTexture == TEXTURE_NONE)
	{// テクスチャを使用しない
		return nullptr;
	}

	assert(inTexture >= 0 && inTexture < TEXTURE_MAX);

	// 読み込み
	Load(inTexture);

	return s_pTexture[inTexture];
}
