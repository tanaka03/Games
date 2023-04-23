//��������������������������
//light.cpp
//��������������������������
#include "light.h"
#include "application.h"
#include "renderer.h"

//��������������������������������������������������������������
// ���C�g�̃R���X�g���N�^
//��������������������������������������������������������������
CLight::CLight()
{
}

//��������������������������������������������������������������
// ���C�g�̃f�X�g���N�^
//��������������������������������������������������������������
CLight::~CLight()
{
}

//��������������������������������������������������������������
// ���C�g�̏�����
//��������������������������������������������������������������
void CLight::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	D3DMATERIAL9 material;
	memset(&material, 0, sizeof(D3DMATERIAL9));

	//���C�g���N���A����
	memset(&m_light, 0, sizeof(D3DLIGHT9));

	D3DXMATRIX mtxRot;

	//���s�����̉�]�}�g���b�N�X
	D3DXMatrixIdentity(&m_lightMatrix);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, D3DXToRadian(180.0f), D3DXToRadian(90.0f), 0.0f);
	D3DXMatrixMultiply(&m_lightMatrix, &m_lightMatrix, &mtxRot);

	D3DXVec3TransformCoord((D3DXVECTOR3*)&m_lightAim, (D3DXVECTOR3*)&m_lightAim, &m_lightMatrix);
	D3DXVec3TransformCoord((D3DXVECTOR3*)&m_lightUp, (D3DXVECTOR3*)&m_lightUp, &m_lightMatrix);
	D3DXVec3TransformCoord((D3DXVECTOR3*)&m_lightAt, (D3DXVECTOR3*)&m_lightAt, &m_lightMatrix);

	//���C�g�̕����x�N�g�����v�Z
	m_lightDir = m_lightAt - m_lightAim;

	//m_lightAim.y += 6.5f;
	m_lightAim.z += 0.6f;

	//----------------------------------------------------------
	// �P�ڂ̃��C�g��ݒ�
	//----------------------------------------------------------
	//���C�g�̎�ނ�ݒ�
	m_light[0].Type = D3DLIGHT_DIRECTIONAL;

	//���C�g�̊g�U����ݒ�
	m_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���K������
	D3DXVec3Normalize((D3DXVECTOR3*)&m_lightDir, (D3DXVECTOR3*)&m_lightDir);
	m_light[0].Direction = (D3DXVECTOR3)m_lightDir;

	//���C�g��ݒ肷��
	pDevice->SetLight(0, &m_light[0]);

	//���C�g��L���ɂ���
	pDevice->LightEnable(0, TRUE);
}

//��������������������������������������������������������������
// ���C�g�̏I��
//��������������������������������������������������������������
void CLight::Uninit()
{
}

//��������������������������������������������������������������
// ���C�g�̍X�V
//��������������������������������������������������������������
void CLight::Update()
{
}