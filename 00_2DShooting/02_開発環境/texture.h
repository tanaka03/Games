//**************************************************
// 
// texture.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TEXTURE_H_	//このマクロ定義がされてなかったら
#define _TEXTURE_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>

//==================================================
// 定義
//==================================================
class CTexture
{
public: /* 定義 */
	enum TEXTURE
	{
		TEXTURE_BULLET = 0,
		TEXTURE_BIGBULLET,
		TEXTURE_SQUAREBULLET,
		TEXTURE_REDBULLET,
		TEXTURE_PLAYER,
		TEXTURE_FUNNEL,
		TEXTURE_FUNNEL2,
		TEXTURE_EXPLOSION,
		TEXTURE_ENEMYDOG,
		TEXTURE_ENEMYBIRD,
		TEXTURE_ENEMYGHOST,
		TEXTURE_ENEMYFAIRYFIRE,
		TEXTURE_ENEMYFAIRYAQUA,
		TEXTURE_ENEMYGIRL,
		TEXTURE_SCOREITEM1,
		TEXTURE_SCOREITEM2,
		TEXTURE_RECOVERYITEM,
		TEXTURE_MAGNET,
		TEXTURE_ORB,
		TEXTURE_NUMBER,
		TEXTURE_ABILITY1,
		TEXTURE_EFFECT1,
		TEXTURE_EFFECT2,
		TEXTURE_EFFECT3,
		TEXTURE_EFFECT4,
		TEXTURE_EFFECTHEART,
		TEXTURE_EFFECTSPARK,
		TEXTURE_EFFECTRING,
		TEXTURE_EFFECTMAGIC1,
		TEXTURE_EFFECTMAGIC2,
		TEXTURE_PIPO_EFFECT,
		TEXTURE_PIPO_EFFECT2,
		TEXTURE_PIPO_EFFECT3,
		TEXTURE_DAMAGEFRAME,
		TEXTURE_GAUGE,
		TEXTURE_GAUGEFRAME,
		TEXTURE_FRAGMENT,
		TEXTURE_BG,
		TEXTURE_BGGLASS,
		TEXTURE_BGCLOUD,
		TEXTURE_BGSKY,
		TEXTURE_BGBRIGHT,
		TEXTURE_BGLACEA,
		TEXTURE_BGLACEB,
		TEXTURE_BGTITLE,
		TEXTURE_TUTORIAL1,
		TEXTURE_TUTORIAL2,
		TEXTURE_TUTORIAL3,
		TEXTURE_TUTORIAL4,
		TEXTURE_TUTORIAL5,
		TEXTURE_TUTORIAL6,
		TEXTURE_TITLE,
		TEXTURE_PRESSENTER,
		TEXTURE_START,
		TEXTURE_TUTORIAL,
		TEXTURE_QUIT,
		TEXTURE_RANK,
		TEXTURE_NOWSCORE,
		TEXTURE_NEW,
		TEXTURE_HP,
		TEXTURE_MP,
		TEXTURE_MAX,
		TEXTURE_NONE,	// 使用しない
	};

	static const char* s_FileName[];	// ファイルパス

public:
	CTexture();		// デフォルトコンストラクタ
	~CTexture();	// デストラクタ

public: /* メンバ関数 */
	void LoadAll();										// 全ての読み込み
	void Load(TEXTURE inTexture);						// 指定の読み込み
	void ReleaseAll();									// 全ての破棄
	void Release(TEXTURE inTexture);					// 指定の破棄
	LPDIRECT3DTEXTURE9 GetTexture(TEXTURE inTexture);	// 情報の取得

private: /* メンバ変数 */
	LPDIRECT3DTEXTURE9 s_pTexture[TEXTURE_MAX];	// テクスチャの情報
};

#endif // !_TEXTURE_H_
