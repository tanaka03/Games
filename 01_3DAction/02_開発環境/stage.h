//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//Stage.h
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#ifndef _STAGE_H_
#define _STAGE_H_

#include "object.h"

class CModel;
class CDepthBufferShadow;
class CLambert;
class CShadow;

class CObject2D;

class CStage : public CObject
{
public:
	//--------------------------------------
	// モデルデータの構造体
	//--------------------------------------
	struct SModelData
	{
		LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点情報
		LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;		// インデックス情報
		LPD3DXMESH m_mesh;						// メッシュ情報
		LPD3DXBUFFER m_buffMat;					// マテリアル情報
		DWORD m_dwNum;							// マテリアルの個数
		D3DXVECTOR3 m_maxModel;					// モデルの最大値
		D3DXVECTOR3 m_minModel;					// モデルの最小値
		int m_numVtx;							// 頂点数
		int m_numPrim;							// ポリゴン数
	};

	CStage();
	~CStage() override;

	static CStage *Create(D3DXVECTOR3 pos);
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void LoadModel(std::string path);
	bool isIntersect(const LPD3DXMESH& mesh, D3DXVECTOR3 pos, D3DXVECTOR3 vecDir, float distanceRange, float& hitDistance, bool* overRange = false);
	void Destroy() override { m_bRelease = true; }

	void SetPos(D3DXVECTOR3 pos) override { m_objpos = pos; }

	D3DXVECTOR3 GetPos() override { return m_objpos; }
	D3DXVECTOR3 GetCollisionPos() { return m_collisionPos; }
	bool GetDestroy() override { return m_bRelease; }
	bool GetCollision() { return m_bCollision; }
	SModelData *GetModelData(int idx) { return &m_modelData[idx]; }

private:
	D3DXVECTOR3 m_objpos;
	D3DXVECTOR3 m_hitPos;
	D3DXVECTOR3 m_enemyHitPos;
	D3DXVECTOR3 m_collisionPos;
	D3DXVECTOR3 m_enemyCollisionPos;
	std::vector<SModelData> m_modelData;
	std::vector<D3DXVECTOR3> m_vertices;
	DWORD m_dwVtxCount;
	bool m_bPlayer;
	bool m_bCollision;
	bool m_bOverRange;
	bool m_bRelease;
};

#endif