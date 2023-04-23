//=============================================================================
// Lambert.h
//=============================================================================
#ifndef _Lambert_H_
#define _Lambert_H_

#include "shader.h"

class CLambert : public CShader
{
public:
	CLambert();
	~CLambert();

	HRESULT Load() override;
	void Begin() override;

	void SetMatrix(D3DXMATRIX* pMatWVP);

private:
	D3DXHANDLE m_pTechnique;
	D3DXHANDLE m_pWVP;
};

#endif