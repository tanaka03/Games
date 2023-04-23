//����������������������������������������
//model.h
//����������������������������������������
#ifndef _MODEL_H_	//���̃}�N����`������ĂȂ�������
#define _MODEL_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

#include "texture.h"

class CModel
{
public:
	struct SModelData
	{
		LPDIRECT3DVERTEXBUFFER9 vtxBuff;
		LPDIRECT3DINDEXBUFFER9 idxBuff;
		LPD3DXBUFFER buffMat;
		DWORD dwNum;
		LPD3DXMESH mesh;
		D3DXVECTOR3 maxModel;
		D3DXVECTOR3 minModel;
		int vtxCount;
		int primitiveCount;
	};

	CModel();
	~CModel();

	void Load(std::string str, std::string path);
	void Load(std::vector<std::string> data);
	void LoadAll();
	void Load_XFile(std::vector<std::string> data);
	void Erase(std::string str) { m_model.erase(str); }
	void Clear() { m_model.clear(); }
	void BindTexture(std::string inPath);

	//�Q�b�^�[
	CModel GetParent() { return *m_pParent; }
	D3DXMATRIX GetMtxWorld() { return m_mtxWorld; }
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(std::string model);
	LPDIRECT3DINDEXBUFFER9 GetIdxBuff(std::string model);
	D3DXVECTOR3 GetMinModel(std::string model);
	D3DXVECTOR3 GetMaxModel(std::string model);
	LPD3DXBUFFER GetBuffMat(std::string model);
	LPD3DXMESH GetMesh(std::string model);
	DWORD GetModelNum(std::string model);
	int GetVertexCount(std::string model);
	int GetPrimitiveCount(std::string model);

private:
	static const int PrimitiveNum = 3;

	// ���f���̏��
	std::map<std::string, SModelData, std::less<>> m_model;

	std::map<std::string, std::vector<int>> m_indices;				//�C���f�b�N�X�o�b�t�@�̏��
	std::map<std::string, std::vector<D3DXVECTOR3>> m_vertices;		//���_�o�b�t�@�̏��
	std::vector<std::string> m_nodeStr;								//�m�[�h�̖��O
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;
	LPDIRECT3DTEXTURE9 m_pTexture;
	CModel *m_pParent;

	D3DXVECTOR3 m_scale;
	D3DXVECTOR3 m_modelSize;
	D3DXMATRIX m_mtxWorld;
};

#endif
