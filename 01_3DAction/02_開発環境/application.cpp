#include "application.h"
#include "renderer.h"
#include "texture.h"
#include "keyboard.h"
#include "camera.h"
#include "light.h"
#include "object.h"
#include "object3d.h"
#include "player.h"
#include "file.h"
#include "model.h"
#include "meshfield.h"
#include "enemy.h"
#include "utility.h"
#include "mode.h"
#include "objectX_group.h"
#include "3deffect_manager.h"
#include "enemy_manager.h"
#include "particle_manager.h"
#include "sound.h"

#include "debugproc.h"

//��������������������������������������������������������������
// �ÓI�����o�ϐ��錾
//��������������������������������������������������������������
CApplication* CApplication::m_pApplication = nullptr;

//��������������������������������������������������������������
// �O���[�o���ϐ��錾
//��������������������������������������������������������������
CObject *g_apObject = nullptr;
CObject3D *g_apObject3d = nullptr;

//��������������������������������������������������������������
// �V���O���g���ŃC���X�^���X�̐����A�擾
//��������������������������������������������������������������
CApplication* CApplication::GetInstance()
{
	if (m_pApplication == nullptr)
	{
		m_pApplication = new CApplication;
	}

	return m_pApplication;
}

//��������������������������������������������������������������
// �A�v���P�[�V�����̃R���X�g���N�^
//��������������������������������������������������������������
CApplication::CApplication() :
	m_pRenderer(nullptr)
{
	m_bWire = false;
}

//��������������������������������������������������������������
// �A�v���P�[�V�����̃f�X�g���N�^
//��������������������������������������������������������������
CApplication::~CApplication()
{
}

//��������������������������������������������������������������
// �A�v���P�[�V�����̏�����
//��������������������������������������������������������������
HRESULT CApplication::Init(HWND hWnd, HINSTANCE hInstance)
{
	srand(time(0));

	//�����_�����O�N���X�̐���
	m_pRenderer = new CRenderer;
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{//���������������s�����ꍇ
		return -1;
	}

#ifdef _DEBUG
	m_pDebugProc = new CDebugProc;
	m_pDebugProc->Init();
#endif

	//�L�[�{�[�h�N���X�̐���
	m_pInputKeyboard = new CInputKeyboard;
	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{//���������������s�����ꍇ
		return -1;
	}

	//�t�@�C���N���X�̐���
	m_pFile = new CFile;

	//���[�e�B���e�B�N���X�̐���
	m_pUtility = new CUtility;

	//�e�N�X�`���N���X�̐���
	m_pTexture = new CTexture;
	m_pTexture->LoadAll();

	//���f���N���X�̐���
	m_pModel = new CModel;
	m_pModel->LoadAll();

	// �T�E���h�N���X�̐���
	m_pSound = new CSound;
	m_pSound->Init(hWnd);

	// ���f���̐���
	m_pObjectXGroup = new CObjectXGroup;
	m_pObjectXGroup->LoadAll();

	// �G�t�F�N�g�}�l�[�W���̐���
	m_pEffectManager = new C3DEffectManager;
	m_pEffectManager->LoadAll();

	// �p�[�e�B�N���}�l�[�W���̐���
	m_pParticleManager = new CParticleManager;
	m_pParticleManager->LoadAll();

	// �G�l�~�[�}�l�[�W���̐���
	m_pEnemyManager = new CEnemyManager;
	m_pEnemyManager->LoadAll();

	//���[�h�N���X�̐���
	m_pMode = new CMode;
	if (FAILED(m_pMode->Init()))
	{//���������������s�����ꍇ
		return -1;
	}

	//�J�����N���X�̐���
	m_pCamera = new CCamera;
	m_pCamera->Init();

	return S_OK;
}

//��������������������������������������������������������������
// �A�v���P�[�V�����̏I��
//��������������������������������������������������������������
void CApplication::Uninit()
{
#ifdef _DEBUG
	// �f�o�b�O�v���V�[�W���̔j��
	if (m_pDebugProc != nullptr)
	{
		m_pDebugProc->Uninit();
		delete m_pDebugProc;
		m_pDebugProc = nullptr;
	}
#endif

	CObject::ReleaseAll();

	// ���[�h�N���X�̔j��
	if (m_pMode != nullptr)
	{
		m_pMode->Uninit();
		delete m_pMode;
		m_pMode = nullptr;
	}

	// ���[�e�B���e�B�N���X�̔j��
	if (m_pUtility != nullptr)
	{
		delete m_pUtility;
		m_pUtility = nullptr;
	}

	// �G�t�F�N�g�}�l�[�W���̔j��
	if (m_pEffectManager != nullptr)
	{
		m_pEffectManager->ReleaseAll();
		delete m_pEffectManager;
		m_pEffectManager = nullptr;
	}

	// �p�[�e�B�N���}�l�[�W���̔j��
	if (m_pParticleManager != nullptr)
	{
		m_pParticleManager->ReleaseAll();
		delete m_pParticleManager;
		m_pParticleManager = nullptr;
	}

	// �G�l�~�[�}�l�[�W���̔j��
	if (m_pEnemyManager != nullptr)
	{
		m_pEnemyManager->ReleaseAll();
		delete m_pEnemyManager;
		m_pEnemyManager = nullptr;
	}

	// �e�N�X�`���N���X�̔j��
	if (m_pTexture != nullptr)
	{
		m_pTexture->UnloadAll();

		delete m_pTexture;
		m_pTexture = nullptr;
	}

	// ���f���N���X�̔j��
	if (m_pModel != nullptr)
	{
		m_pModel->Clear();
		delete m_pModel;
		m_pModel = nullptr;
	}

	// �T�E���h�N���X�̔j��
	if (m_pSound != nullptr)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}

	// X���f���̍폜
	if (m_pObjectXGroup != nullptr)
	{
		m_pObjectXGroup->UnloadAll();
		delete m_pObjectXGroup;
		m_pObjectXGroup = nullptr;
	}

	// �J�����N���X�̔j��
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	// �L�[�{�[�h�N���X�̔j��
	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = nullptr;
	}

	// �����_�����O�N���X�̔j��
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	// �t�@�C���N���X�̔j��
	if (m_pFile != nullptr)
	{
		delete m_pFile;
		m_pFile = nullptr;
	}

	// �A�v���P�[�V�����̉��
	if (m_pApplication != nullptr)
	{
		delete m_pApplication;
		m_pApplication = nullptr;
	}
}

//��������������������������������������������������������������
// �A�v���P�[�V�����̍X�V
//��������������������������������������������������������������
void CApplication::Update()
{
	// �L�[�{�[�h�̍X�V�����͍ŏ��ɍs��
	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard->Update();
	}

	// �����_���[�N���X�̍X�V
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Update();
	}

	// ���[�h�N���X�̍X�V
	if (m_pMode != nullptr)
	{
		m_pMode->Update();
	}

	// ���C���[�t���[���ɂ��鏈��
	if (m_pInputKeyboard->GetTrigger(DIK_F2))
	{
		m_bWire = ((!m_bWire) ? true : false);
		if (m_bWire)		m_pRenderer->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		else if (!m_bWire)	m_pRenderer->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
}

//��������������������������������������������������������������
// �A�v���P�[�V�����̕`��
//��������������������������������������������������������������
void CApplication::Draw()
{
	// �����_���[�N���X�̕`��
	m_pRenderer->Draw();
}