#ifndef _3DEFFECT_H_
#define _3DEFFECT_H_

#include "object3d.h"
#include "texture.h"

class C3DEffect : public CObject
{
public:
	//--------------------------------------
	// ���f���f�[�^�̍\����
	//--------------------------------------
	struct SModelData
	{
		LPD3DXMESH mesh;						// ���b�V�����
		LPD3DXBUFFER buffMat;					// �}�e���A�����
		DWORD dwNum;							// �}�e���A���̌�
		D3DXVECTOR3 maxModel;					// ���f���̍ő�l
		D3DXVECTOR3 minModel;					// ���f���̍ŏ��l
		D3DXVECTOR3 posOffset;				// ���f���̈ʒu�̃I�t�Z�b�g
		D3DXVECTOR3 rotOffset;				// ���f���̌����̃I�t�Z�b�g
		int numVtx;							// ���_��
		int numPrim;							// �|���S����
	};

	//--------------------------------------
	// �G�t�F�N�g�C���t�H���[�V�����̍\����
	//--------------------------------------
	struct SInfo
	{
		D3DXVECTOR3 beginRot;
		D3DXVECTOR3 beginScale;
		D3DXVECTOR3 posOffset;
		D3DXVECTOR3 moveValue;
		D3DXVECTOR3 rotOffset;
		D3DXVECTOR3 rotateValue;
		D3DXVECTOR3 scalingValue;
		D3DXCOLOR col;
		D3DXCOLOR transitionCol;
		std::string texTag;
		std::string modelShape;
		int life;
		int transitionColEndTime;
		float moveAttenuation;
		float alphaAttenuation;
		bool tractPlayer;
		bool useFileTexture;
	};

	explicit C3DEffect(int priority = CObject::PRIORITY_THIRD);
	~C3DEffect() override;

	static C3DEffect *Create(C3DEffect::SInfo& info, int priority = CObject::PRIORITY_THIRD);	// ��������

	HRESULT Init() override;												// ����������
	void Uninit() override;
	void Update() override;													// �X�V����
	void Draw() override;													// �`�揈��
	void Destroy() { m_bRelease = true; }
	void UseEmitter() { m_useEmitter = true; }

	void SetPos(D3DXVECTOR3 pos) override { m_pos = pos; }
	void SetPosOffset(D3DXVECTOR3 offset, int idx = 0) { m_modelData[idx].posOffset = offset; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetRotOffset(D3DXVECTOR3 rot, int idx = 0) { m_modelData[idx].rotOffset = rot; }
	void SetScale(D3DXVECTOR3 scale) { m_scale = scale; }
	void SetInfo(SInfo& info) { m_info = info; }
	void SetPlayerTraction(bool set) { m_info.tractPlayer = set; }

	D3DXVECTOR3 GetPos() override { return m_pos; }
	D3DXVECTOR3 GetRot() { return m_rot; }
	D3DXVECTOR3 GetScale() { return m_scale; }
	D3DXMATRIX GetMtxWorld() { return m_ParentmtxWorld; }
	SInfo GetInfo() { return m_info; }
	SModelData GetModelData(int idx) { return m_modelData[idx]; }
	bool GetDestroy() override { return m_bRelease; }

private:
	void LoadModel(std::string path);
	void BindTexture(std::string inPath);

	LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`��
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_scale;
	D3DXCOLOR m_beginCol;
	D3DXMATRIX m_mtxWorld;
	D3DXMATRIX m_ParentmtxWorld;
	SInfo m_info;
	std::vector<SModelData> m_modelData;
	bool m_useEmitter;
	bool m_bRelease;
};
#endif