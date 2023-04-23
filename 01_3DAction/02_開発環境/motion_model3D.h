//=============================================================================
//
// 3Dモーションキャラクタークラス(motion_model3D.h)
// Author : 唐﨑結斗
// 概要 : 3Dプレイヤー生成を行う
//
//=============================================================================
#ifndef _MOTION_MODEL3D_H_			// このマクロ定義がされてなかったら
#define _MOTION_MODEL3D_H_			// 二重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "object.h"
#include "main.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CMotion;

//=============================================================================
// 3Dプレイヤークラス
// Author : 唐﨑結斗
// 概要 : 3Dプレイヤー生成を行うクラス
//=============================================================================
class CMotionModel3D
{
public:
	//--------------------------------------------------------------------
	// 静的メンバ関数
	//--------------------------------------------------------------------
	static CMotionModel3D *Create();			// 3Dプレイヤーの生成

	//--------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//--------------------------------------------------------------------
	CMotionModel3D();
	~CMotionModel3D();

	//--------------------------------------------------------------------
	// メンバ関数
	//--------------------------------------------------------------------
	HRESULT Init();											// 初期化
	void Uninit();												// 終了
	void Update();												// 更新
	void Destroy() { m_bRelease = true; }

	// Setter
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };				// 位置
	void SetModelPos(D3DXVECTOR3 pos) { m_pos = pos; };					// 位置
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };
	void SetSize(D3DXVECTOR3 size) { m_size = size; }			// 大きさ
	void SetMtxWorld(D3DXMATRIX mtxWorld) { m_mtxWorld = mtxWorld; }	// ワールドマトリックスのセッター
	void SetMotion(const char *pName);									// モーション情報の設定
	void SetMove(D3DXVECTOR3 inMove) { m_move = inMove; }
	void SetCol(D3DXCOLOR) {};
	void SetUpdateStop(bool isStop) { m_isUpdateStop = isStop; }
	void SetMaxMinVtx();

	// Getter
	D3DXVECTOR3 GetPos() { return m_pos; }						// 位置
	D3DXVECTOR3 GetSize()  { return m_size; }					// 大きさ
	D3DXMATRIX GetMtxWorld() { return m_mtxWorld; }						// ワールドマトリックスのゲッター
	CMotion *GetMotion() { return m_pMotion; }							// モーション情報の取得
	D3DXVECTOR3 GetMove() { return m_move; }
	D3DXCOLOR GetCol() { return D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetMaxVtx() { return m_MaxVtx; }
	D3DXVECTOR3 GetMinVtx() { return m_MinVtx; }

	float LenSegOnSeparateAxis(D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3 = 0);

private:
	//--------------------------------------------------------------------
	// メンバ変数
	//--------------------------------------------------------------------
	CMotion			*m_pMotion;				// モーションインスタンス
	D3DXVECTOR3		m_MinVtx;				// モデルの頂点最小値
	D3DXVECTOR3		m_MaxVtx;				// モデルの頂点最大値
	D3DXMATRIX		m_mtxWorld;				// ワールドマトリックス
	D3DXVECTOR3		m_pos;					// 位置
	D3DXVECTOR3		m_move;					// 
	D3DXVECTOR3		m_rot;					// 向き
	D3DXVECTOR3		m_size;					// 大きさ
	bool			m_isUpdateStop;			// 更新を停止させる。
	bool m_bRelease;
};

#endif