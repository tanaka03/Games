//
//Item.h
//
#ifndef _ITEM_H_
#define _ITEM_H_

#include "billboard.h"

class CItem : public CObject
{
public:
	struct SModelData
	{
		LPDIRECT3DVERTEXBUFFER9 pVtxBuff;
		LPDIRECT3DINDEXBUFFER9 pIdxBuff;
		LPD3DXMESH mesh;
		LPD3DXBUFFER buffMat;
		DWORD dwNum;
		D3DXVECTOR3 maxModel;
		D3DXVECTOR3 minModel;
		D3DXVECTOR3 posOffset;
		D3DXVECTOR3 rotOffset;
		int numVtx;
		int numPrim;
	};

	CItem();
	~CItem() override;

	static CItem* Create(D3DXVECTOR3 pos, int priority = CObject::PRIORITY_THIRD);

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void LoadModel(std::string path);
	void Destroy() override { m_release = true; }

	void SetPos(D3DXVECTOR3 pos) { m_objpos = pos; }

	D3DXVECTOR3 GetPos() override { return m_objpos; }
	bool GetDestroy() { return m_release; }

private:
	D3DXVECTOR3 m_objpos;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX m_mtxWorld;
	std::vector<SModelData> m_modelData;
	int  m_time;
	bool m_release;
};

#endif