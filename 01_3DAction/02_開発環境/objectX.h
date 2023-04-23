#ifndef _OBJECTX_H_
#define _OBJECTX_H_

#include "main.h"
#include "object.h"

class CObjectX : public CObject
{
public:
	explicit CObjectX(int nPriority = CObject::PRIORITY_THIRD);
	~CObjectX() override;

	HRESULT Init() override;											// 初期化処理
	void Uninit() override;												// 終了処理
	void Update() override;												// 更新処理
	void Draw() override;												// 描画処理
	void Draw(D3DXMATRIX mtxParent);									// 描画処理
	void VtxUpdate() {};												// 頂点座標更新処理
	void Destroy() override { m_bRelease = true; }
	void CalculationVtx();												// 頂点最大小値の計算処理

	// Setter
	void SetPos(D3DXVECTOR3 pos) override;								// 座標設定処理
	void SetSize(D3DXVECTOR3 size);										// サイズ設定処理
	void SetMove(D3DXVECTOR3 move);										// 移動量設定処理
	void SetCol(D3DXCOLOR col);											// 色設定処理
	void SetRot(D3DXVECTOR3 rot);										// 向き設定処理
	void SetMaxVtx(D3DXVECTOR3 Maxvtx);									// 頂点最大値設定処理
	void SetMinVtx(D3DXVECTOR3 Minvtx);									// 頂点最小値設定処理
	void SetParent(CObjectX* inParent) { m_pParent = inParent; }		// 親モデルの情報
	void SetCollisionFlag(bool inFlag) { m_isCollision = inFlag; }

	// Getter
	D3DXVECTOR3 GetPos(void) override { return m_pos; }					// 座標取得処理
	D3DXVECTOR3 GetSize(void) { return m_size; }						// サイズ取得処理
	D3DXVECTOR3 GetMove(void) { return m_move; }						// 移動量取得処理
	D3DXVECTOR3 GetRot(void) { return m_rot; }							// 向き取得処理
	D3DXCOLOR GetCol(void) { return m_col; }							// 色取得処理
	D3DXVECTOR3 GetMaxVtx(void) { return m_MaxVtx; }					// 頂点最大値取得処理
	D3DXVECTOR3 GetMinVtx(void) { return m_MinVtx; }					// 頂点最小値取得処理
	CObjectX* GetParent(void) { return m_pParent; }						// 親モデルの情報
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }
	LPD3DXMESH GetMesh() { return m_pMesh; }
	LPD3DXBUFFER GetBuffMat() { return m_pBuffMat; }
	DWORD GetNumMat() { return m_NumMat; }
	bool IsCollision() { return m_isCollision; }
	bool GetDestroy() override { return m_bRelease; }

	static CObjectX *Create(D3DXVECTOR3 pos, int nPriority);			// 生成処理
	void LoadModel(const char *aFileName);								// モデルの読み込み処理

	// Collision
	bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pSize);													// 当たり判定 (左右, 奥, 手前)
	bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *inMaxVtx, D3DXVECTOR3 *inMinVtx);							// 当たり判定 (左右, 奥, 手前)
	bool UpCollision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pSize, D3DXVECTOR3 *pMove);								// 当たり判定 (上側)
	bool UpCollision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *inMaxVtx, D3DXVECTOR3 *inMinVtx, D3DXVECTOR3 *pMove);	// 当たり判定 (上側)

private:
	D3DXVECTOR3 m_pos;					// 座標
	D3DXVECTOR3 m_rot;					// 角度
	D3DXVECTOR3 m_size;					// 座標
	D3DXVECTOR3 m_move;					// 角度
	D3DXVECTOR3 m_MinVtx;				// モデルの頂点最小値
	D3DXVECTOR3 m_MaxVtx;				// モデルの頂点最大値
	D3DXCOLOR m_col;					// 色
	D3DXMATRIX m_mtxWorld;				// ワールドマトリックス
	LPD3DXMESH m_pMesh;					// メッシュ情報へのポインタ
	LPD3DXBUFFER m_pBuffMat;			// マテリアル情報へのポインタ
	DWORD m_NumMat;						// マテリアル情報の数

	CObjectX *m_pParent;				// 親モデルの情報
	bool m_isCollision;					// 当たり判定が必要か

	bool m_bRelease;
};
#endif