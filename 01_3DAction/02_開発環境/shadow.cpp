#include "shadow.h"
#include "application.h"
#include "renderer.h"
#include "light.h"
#include "object.h"
#include "mode.h"
#include "game.h"
#include "object2d.h"
#include "keyboard.h"

//��������������������������������������������������������������
// �e�̃R���X�g���N�^
//��������������������������������������������������������������
CShadow::CShadow() : lightEnlargement(15200.0f)
{
}

//��������������������������������������������������������������
// �e�̃f�X�g���N�^
//��������������������������������������������������������������
CShadow::~CShadow()
{
}

//��������������������������������������������������������������
// ���C�g���_�Ő��E�����鏈��
//��������������������������������������������������������������
void CShadow::StartViewfromLight()
{
	// �f�o�C�X�̃|�C���^���擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	// ���C�g�̃|�C���^���擾
	CLight* pLight = CApplication::GetInstance()->GetMode()->GetGame()->GetLight();

	// ���C�g����̎��_�̐ݒ�
	D3DXVECTOR3 LEye = D3DXVECTOR3(pLight->GetLightAim().x, pLight->GetLightAim().y , pLight->GetLightAim().z) * lightEnlargement;
	D3DXVECTOR4 LightDir = pLight->GetVecDir();

	// �f�v�X�o�b�t�@�T�[�t�F�C�X�Ƀ��C�g�ʒu����̃V�[����Z�l���o��
	D3DXMatrixLookAtLH(&m_mtxView, &LEye, (D3DXVECTOR3*)&pLight->GetLightAt(), (D3DXVECTOR3*)&pLight->GetLightUp());

	// ���C�g�ʒu����̐��ˉe�s��̍쐬
	D3DXMatrixOrthoLH(&m_mtxProj,
		(float)SCREEN_WIDTH * 15,
		(float)SCREEN_HEIGHT * 15,
		100.0f,
		20000.0f);

	D3DXMatrixIdentity(&m_mtxWorld);
	m_calcWVP = m_mtxWorld * m_mtxView * m_mtxProj;

	// �T���v���[�X�e�[�g�̐ݒ�
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);

	pDevice->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	pDevice->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	pDevice->SetSamplerState(1, D3DSAMP_MIPFILTER, D3DTEXF_NONE);

	//�A���t�@�u�����h�ɂ�鍇�����@����`�����ɂ���
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//���̒l�ƃe�N�X�`���[�̃A���t�@�l�Ƃ��r����
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000080);

	// �e�N�X�`���̃A���t�@�l���傫�������ꍇ��������
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

	//�����_�[�^�[�Q�b�g�T�[�t�F�C�X��ݒ肷��
	pDevice->GetRenderTarget(0, &m_oldSurface);
	pDevice->SetRenderTarget(0, m_pZBufferSurface);

	pDevice->GetDepthStencilSurface(&m_oldZMap);
	pDevice->SetDepthStencilSurface(m_pZBuffer);

	// �����_�[�^�[�Q�b�g��ς����ꍇ�A�N���A����
	pDevice->Clear(0L,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		0xFFFFFFFF,
		1.0f,
		0L
	);
}

void CShadow::StartViewfromLight(D3DXMATRIX& mtxWorld)
{
	// �f�o�C�X�̃|�C���^���擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	// ���C�g�̃|�C���^���擾
	CLight* pLight = CApplication::GetInstance()->GetMode()->GetGame()->GetLight();

	// ���C�g����̎��_�̐ݒ�
	D3DXVECTOR3 LEye = D3DXVECTOR3(pLight->GetLightAim().x, pLight->GetLightAim().y, pLight->GetLightAim().z) * lightEnlargement;
	D3DXVECTOR4 LightDir = pLight->GetVecDir();

	// �f�v�X�o�b�t�@�T�[�t�F�C�X�Ƀ��C�g�ʒu����̃V�[����Z�l���o��
	D3DXMatrixLookAtLH(&m_mtxView, &LEye, (D3DXVECTOR3*)&pLight->GetLightAt(), (D3DXVECTOR3*)&pLight->GetLightUp());

	// ���C�g�ʒu����̐��ˉe�s��̍쐬
	D3DXMatrixOrthoLH(&m_mtxProj,
		(float)SCREEN_WIDTH * 10,
		(float)SCREEN_HEIGHT * 10,
		100.0f,
		9000.0f);

	D3DXMatrixIdentity(&m_mtxWorld);
	m_calcWVP = mtxWorld * m_mtxView * m_mtxProj;

	// �T���v���[�X�e�[�g�̐ݒ�
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);

	pDevice->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	pDevice->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	pDevice->SetSamplerState(1, D3DSAMP_MIPFILTER, D3DTEXF_NONE);

	//�A���t�@�u�����h�ɂ�鍇�����@����`�����ɂ���
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//���̒l�ƃe�N�X�`���[�̃A���t�@�l�Ƃ��r����
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000080);

	// �e�N�X�`���̃A���t�@�l���傫�������ꍇ��������
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

	//�����_�[�^�[�Q�b�g�T�[�t�F�C�X��ݒ肷��
	pDevice->GetRenderTarget(0, &m_oldSurface);
	pDevice->SetRenderTarget(0, m_pZBufferSurface);

	pDevice->GetDepthStencilSurface(&m_oldZMap);
	pDevice->SetDepthStencilSurface(m_pZBuffer);

	// �����_�[�^�[�Q�b�g��ς����ꍇ�A�N���A����
	pDevice->Clear(0L,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		0xFFFFFFFF,
		1.0f,
		0L
	);
}

//��������������������������������������������������������������
// ���C�g���_�̏������I��
//��������������������������������������������������������������
void CShadow::EndViewfromLight()
{
	// �f�o�C�X�̃|�C���^���擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	//m_pTex->SetTexture(m_pZBufferTexture);

	pDevice->SetRenderTarget(0, m_oldSurface);
	if (m_oldSurface != nullptr)
	{
		m_oldSurface->Release();
	}

	pDevice->SetDepthStencilSurface(m_oldZMap);
	if (m_oldZMap != nullptr)
	{
		m_oldZMap->Release();
	}
}

//��������������������������������������������������������������
// �[�x�e�N�X�`���̐���
//��������������������������������������������������������������
void CShadow::CreateZTexture()
{
	// �f�o�C�X�̃|�C���^���擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	DWORD SurfaceWidth = (DWORD)SCREEN_WIDTH * 2.5f;
	DWORD SurfaceHeight = (DWORD)SCREEN_HEIGHT * 2.5f;

	HRESULT hr;

	// �e�N�X�`���̐���
	hr = D3DXCreateTexture(pDevice,
		SurfaceWidth,
		SurfaceHeight,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_R32F,
		D3DPOOL_DEFAULT,
		&m_pZBufferTexture);

	if (hr == E_FAIL)
	{	// �e�N�X�`���𐶐��ł��Ȃ������ꍇ
		assert(false);
	}

	m_pZBufferTexture->GetSurfaceLevel(0, &m_pZBufferSurface);

	// �[�x�X�e���V���̐���
	hr = pDevice->CreateDepthStencilSurface(SurfaceWidth,
		SurfaceHeight,
		D3DFMT_D16,
		D3DMULTISAMPLE_NONE,
		0,
		TRUE,
		&m_pZBuffer,
		NULL);

	if (hr == E_FAIL)
	{	// �X�e���V���̃T�[�t�F�C�X�𐶐��ł��Ȃ������ꍇ
		assert(false);
	}
}