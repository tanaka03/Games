//��������������������������
//light.h
//��������������������������
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "renderer.h"

class CLight
{
public:
	CLight();
	~CLight();

	void Init();
	void Uninit();
	void Update();

	D3DXVECTOR4 GetVecDir() { return m_lightDir; }
	D3DXVECTOR4 GetLightAim() { return m_lightAim; }
	D3DXVECTOR4 GetLightAt() { return m_lightAt; }
	D3DXVECTOR4 GetLightUp() { return m_lightUp; }
	D3DXMATRIX GetMatrix() { return m_lightMatrix; }
	D3DLIGHT9 GetLight(int idx) { return m_light[idx]; }

private:
	static const int MaxLight = 1;
	D3DLIGHT9 m_light[MaxLight];		//���C�g���
	D3DXVECTOR4 m_lightDir;													// ���C�g�̕����x�N�g��
	D3DXVECTOR4 m_lightAim = D3DXVECTOR4(0.0f, 0.0f, -1.0f, 1.0f);			// ���C�g�̎��_�x�N�g��
	D3DXVECTOR4 m_lightUp = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);			// ���C�g�̏�x�N�g��
	D3DXVECTOR4 m_lightAt = D3DXVECTOR4(0.5f, 0.0f, 0.0f, 1.0f);			// ���C�g�̎����x�N�g��
	D3DXMATRIX m_lightMatrix;												// ���C�g�̃r���[�s��
};

#endif
