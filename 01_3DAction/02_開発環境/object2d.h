//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//Object2D.h
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

#include "object.h"
#include "texture.h"

//*****************************************************************************
// 構造体定義
//*****************************************************************************
// 頂点フォーマット
const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

// 頂点データ
struct VERTEX_2D
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
};

class CObject2D : public CObject
{
public:
	explicit CObject2D(int priority = CObject::PRIORITY_THIRD);
	~CObject2D() override;

	static CObject2D* Create(D3DXVECTOR3 pos, D3DXVECTOR2 scale, std::string tex, int priority, D3DXCOLOR col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));			// 生成処理

	HRESULT Init() override;																				// 初期化処理
	void Uninit() override;																					// 終了処理
	void Update() override;																					// 更新処理
	void Draw() override;																					// 描画処理
	void BindTexture(std::string inPath);																	// テクスチャのバインド
	void SetUV(float Xtop, float Xbottom, float Ytop, float Ybottom);										// UV座標の設定
	void SetAnimation(const int U, const int V, const int Speed, const int Drawtimer, const bool loop);		// アニメーションの設定
	bool SquareCollision(D3DXVECTOR3 pos, D3DXVECTOR3 Destpos, float Length, float CollisionVal);			// 四角判定
	bool CircleCollision(D3DXVECTOR3 pos, D3DXVECTOR3 Destpos, float Radius, float CollisionVal);			// 丸判定

	//セッター
	void SetPos(D3DXVECTOR3 pos) override { m_objpos = pos; }												// 位置の設定
	void SetMove(D3DXVECTOR3 move) { m_move = move; }														// 移動量の設定
	void SetCol(D3DXCOLOR col) { m_col = col; }																// 色の設定
	void SetScale(D3DXVECTOR2 scale) { m_Width = scale.x, m_Height = scale.y; }								// テクスチャの大きさの設定
	void SetRot(float rot) { m_rot = rot; }																	// 向きの設定
	void SetTexture(LPDIRECT3DTEXTURE9 tex) { m_pTexture = tex; }
	void Destroy() override { m_bRelease = true; }															// 死亡フラグ

	//ゲッター
	D3DXVECTOR3 GetPos() override { return m_objpos; }														// 位置を取得
	D3DXVECTOR3 GetMove() { return m_move; }																// 移動量を取得
	D3DXVECTOR2 GetScale() { return D3DXVECTOR2(m_Width, m_Height); }										// 大きさを取得
	D3DXCOLOR GetCol() { return m_col; }																	// 色を取得
	LPDIRECT3DTEXTURE9 GetTexture() { return m_pTexture; }													// テクスチャの情報を取得
	float GetWidth() { return m_Width; }																	// 幅を取得
	float GetHeight() { return m_Height; }																	// 高さを取得
	bool GetDestroy() override { return m_bRelease; }														// 死亡しているかどうか

protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファ

private:
	LPDIRECT3DTEXTURE9 m_pTexture;			// テクスチャ
	D3DXVECTOR3 m_objpos;					// オブジェクトの位置
	D3DXVECTOR3 m_move;						// 移動量
	D3DXCOLOR m_col;						// 色
	int m_nCounterAnim;						// アニメーションカウンタ
	int m_nPatternAnim;						// アニメーションパターン
	int m_nCntY;							// Y座標を動かす際に使用するカウンタ
	int m_CounterAnim;						// アニメーションカウンター
	int m_PatternAnimX;						// Xのパターン
	int m_PatternAnimY;						// Yのパターン
	int m_DivisionX;						// X分割数
	int m_DivisionY;						// Y分割数
	int m_DivisionMAX;						// 最大分割数
	int m_AnimationSpeed;					// アニメーションする速度
	int m_AnimationSpdCnt;					// アニメーションのスピードカウンター
	int m_Timer;							// タイマー
	int m_CntTime;							// テクスチャアニメーションのタイマー
	float m_Width;							// 幅
	float m_Height;							// 高さ
	float m_rot;							// 向き
	bool m_bAnimation;						// アニメーションをするかどうか
	bool m_bLoop;							// アニメーションをループするかどうか
	bool m_bRelease;						// 死亡フラグ
};

#endif