//=============================================================================
// DepthBufferShadow.h
//=============================================================================
#ifndef _DepthBufferShadow_H_
#define _DepthBufferShadow_H_

#include "shader.h"

class CDepthBufferShadow : public CShader
{
public:
	CDepthBufferShadow();
	~CDepthBufferShadow();

	HRESULT Load() override;
	void Begin() override;

	void SetAmbient(float value);
	void SetAmbient(D3DXVECTOR4* value);
	void SetDiffuse(D3DXVECTOR4 value);
	void SetMatrix(D3DXMATRIX* pMatWorld, D3DXMATRIX* pMatLight, D3DXVECTOR4* pLightDir);
	void SetBias(float bias)				 { if (m_pEffect != nullptr) m_pEffect->SetFloat(m_pBias, bias); }
	void SetShadowColor(float shadowCol)	 { if (m_pEffect != nullptr) m_pEffect->SetFloat(m_pShadowColor, shadowCol); }
	void SetMtxView(D3DXMATRIX mtx) { m_mtxView = mtx; }
	void SetMtxProjection(D3DXMATRIX mtx) { m_mtxProj = mtx; }

	D3DXMATRIX GetMtxView() { return m_mtxView; }
	D3DXMATRIX GetMtxProjection() { return m_mtxProj; }

private:
	D3DXMATRIX m_mtxView;
	D3DXMATRIX m_mtxProj;

	D3DXHANDLE m_pTechnique;
	D3DXHANDLE m_pWVP;
	D3DXHANDLE m_pLWVP;
	D3DXHANDLE m_pLWVPT;
	D3DXHANDLE m_pMatDiffuse;
	D3DXHANDLE m_pLightDir;
	D3DXHANDLE m_pAmbient;
	D3DXHANDLE m_pBias;
	D3DXHANDLE m_pShadowColor;
};

#endif