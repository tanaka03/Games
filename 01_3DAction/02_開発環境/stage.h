//����������������������������������������
//Stage.h
//����������������������������������������
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
	// ���f���f�[�^�̍\����
	//--------------------------------------
	struct SModelData
	{
		LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_���
		LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;		// �C���f�b�N�X���
		LPD3DXMESH m_mesh;						// ���b�V�����
		LPD3DXBUFFER m_buffMat;					// �}�e���A�����
		DWORD m_dwNum;							// �}�e���A���̌�
		D3DXVECTOR3 m_maxModel;					// ���f���̍ő�l
		D3DXVECTOR3 m_minModel;					// ���f���̍ŏ��l
		int m_numVtx;							// ���_��
		int m_numPrim;							// �|���S����
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