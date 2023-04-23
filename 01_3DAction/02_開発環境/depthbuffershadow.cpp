#include "depthbuffershadow.h"
#include "application.h"
#include "renderer.h"

//
// fvXobt@VhEĚRXgN^
//
CDepthBufferShadow::CDepthBufferShadow()
{
}

//
// fvXobt@VhEĚfXgN^
//
CDepthBufferShadow::~CDepthBufferShadow()
{
}

//
// fvXobt@VhEĚfxt@CĚÇÝÝ
//
HRESULT CDepthBufferShadow::Load()
{
	// foCXĚ|C^đćž
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	if (SUCCEEDED(D3DXCreateEffectFromFile(pDevice, _T("DepthBufferShadow.fx"), NULL, NULL, 0, NULL, &m_pEffect, NULL)))
	{
		m_pTechnique = m_pEffect->GetTechniqueByName("TShader");
		m_pWVP = m_pEffect->GetParameterByName(NULL, "m_WVP");
		m_pLWVP = m_pEffect->GetParameterByName(NULL, "m_LWVP");
		m_pLWVPT = m_pEffect->GetParameterByName(NULL, "m_LWVPT");
		m_pMatDiffuse = m_pEffect->GetParameterByName(NULL, "m_matDiffuse");
		m_pLightDir = m_pEffect->GetParameterByName(NULL, "m_LightDir");
		m_pAmbient = m_pEffect->GetParameterByName(NULL, "m_Ambient");
		m_pBias = m_pEffect->GetParameterByName(NULL, "m_Bias");
		m_pShadowColor = m_pEffect->GetParameterByName(NULL, "m_ShadowColor");

		m_pEffect->SetTechnique(m_pTechnique);
	}
	else
	{
		return E_FAIL;
	}

	return S_OK;
}

//
// fvXobt@VhEĚJn
//
void CDepthBufferShadow::Begin()
{
	if (m_pEffect == nullptr)
	{
		return;
	}

	// foCXĚ|C^đćž
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	pDevice->GetTransform(D3DTS_VIEW, &m_mtxView);
	pDevice->GetTransform(D3DTS_PROJECTION, &m_mtxProj);
	m_pEffect->Begin(NULL, 0);
}

//
// fvXobt@VhEĚArGgÝč
//
void CDepthBufferShadow::SetAmbient(float value)
{
	// foCXĚ|C^đćž
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	if (m_pEffect != nullptr)
	{
		D3DXVECTOR4 A;
		A = D3DXVECTOR4(value, value, value, 1.0f);
		m_pEffect->SetVector(m_pAmbient, &A);
	}

	else
	{
		D3DMATERIAL9 old_material;
		pDevice->GetMaterial(&old_material);
		old_material.Ambient.r = value;
		old_material.Ambient.g = value;
		old_material.Ambient.b = value;
		old_material.Ambient.a = 1.0f;
		pDevice->SetMaterial(&old_material);
	}
}

void CDepthBufferShadow::SetAmbient(D3DXVECTOR4* value)
{
	// foCXĚ|C^đćž
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	if (m_pEffect != nullptr)
	{
		m_pEffect->SetVector(m_pAmbient, value);
	}

	else
	{
		D3DMATERIAL9 old_material;
		pDevice->GetMaterial(&old_material);
		old_material.Ambient.r = value->x;
		old_material.Ambient.g = value->y;
		old_material.Ambient.b = value->z;
		old_material.Ambient.a = value->w;
		pDevice->SetMaterial(&old_material);
	}
}

//
// fĚ}eAĚfBt[YJ[ĚÝč
//
void CDepthBufferShadow::SetDiffuse(D3DXVECTOR4 value)
{
	if (m_pEffect == nullptr)
	{
		return;
	}
	m_pEffect->SetVector(m_pMatDiffuse, &value);
}

//
// fvXobt@VhEĚ}gbNXÝč
//
void CDepthBufferShadow::SetMatrix(D3DXMATRIX* pMatWorld, D3DXMATRIX* pMatLight, D3DXVECTOR4* pLightDir)
{
	// foCXĚ|C^đćž
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	if (m_pEffect != nullptr)
	{
		D3DXMATRIX m, m1, m2;
		D3DXVECTOR4 LightDir;
		D3DXVECTOR4 v;

		//JîĚsńĎˇ}gbNXđÝč
		m = (*pMatWorld) * m_mtxView * m_mtxProj;
		m_pEffect->SetMatrix(m_pWVP, &m);

		//CgĚűüxNgvZ
		LightDir = *pLightDir;
		D3DXMatrixInverse(&m1, NULL, pMatWorld);
		D3DXVec4Transform(&v, &LightDir, &m1);

		//XYZŹŞĚłKť
		D3DXVec3Normalize((D3DXVECTOR3*)&v, (D3DXVECTOR3*)&v);
		m_pEffect->SetVector(m_pLightDir, &v);

		//CgîĚsńĎˇ}gbNXđÝč
		m = (*pMatWorld) * (*pMatLight);
		m_pEffect->SetMatrix(m_pLWVP, &m);

		//CgîĚsńĎˇ}gbNXđeNX`[ŔWnÖĎˇ
		D3DXMatrixScaling(&m1, 0.5f, -0.5f, 1.0f);
		D3DXMatrixTranslation(&m2, 0.5f, 0.5f, 0.0f);
		m = m * m1 * m2;
		m_pEffect->SetMatrix(m_pLWVPT, &m);
	}
	else
	{
		pDevice->SetTransform(D3DTS_WORLD, pMatWorld);
	}
}
