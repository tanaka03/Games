//��������������������������
//meshfield.h
//��������������������������
#ifndef _MESHFIELD_H_		//��d�K�[�h�C���N���[�h
#define _MESHFIELD_H_

#include "mesh.h"
#include "texture.h"

class CMeshField : public CMesh
{
public:
	CMeshField();
	~CMeshField();

	static CMeshField* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, int X, int Z);

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

private:
	int m_MeshField_VertexNum;
	int m_MeshField_PrimitiveNum;
};

#endif
