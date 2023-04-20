#include "main.h"
#include "input.h"
#include "keyboard.h"
#include "application.h"
#include "bg.h"
#include "bullet.h"
#include "particle_manager.h"
#include "player.h"
#include "enemy.h"
#include "renderer.h"
#include "texture.h"
#include "score.h"
#include "sound.h"
#include "mode.h"
#include "file.h"
#include "debugproc.h"

CEnemy *CApplication::m_pEnemy = nullptr;
CInputKeyboard *CApplication::m_pInputKeyboard = nullptr;
CItem *CApplication::m_pItem = nullptr;
CRenderer *CApplication::m_pRenderer = nullptr;
CSound *CApplication::m_pSound = nullptr;
CTexture *CApplication::m_pTexture = nullptr;
CDebugProc *CApplication::m_pDebugProc = nullptr;

CMode *CApplication::m_mode = nullptr;

CApplication::CApplication()
{

}

CApplication::~CApplication()
{

}

HRESULT CApplication::Init(HWND hWnd, HINSTANCE hInstance)
{
	//�L�[�{�[�h�N���X�̐���
	m_pInputKeyboard = new CInputKeyboard;

	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{//���������������s�����ꍇ
		return -1;
	}

	//�����_�����O�N���X�̐���
	m_pRenderer = new CRenderer;

	// ����������
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{//���������������s�����ꍇ
		return -1;
	}

#ifdef _DEBUG
	m_pDebugProc = new CDebugProc;
	m_pDebugProc->Init();
#endif

	//�e�N�X�`���N���X�̐���
	m_pTexture = new CTexture;

	//�T�E���h�N���X�̐���
	m_pSound = new CSound;
	if (FAILED(m_pSound->Init(hWnd)))
	{//���������������s�����ꍇ
		return -1;
	}

	//���[�h�N���X�̐���
	m_mode = new CMode;

	if (FAILED(m_mode->Init()))
	{//���������������s�����ꍇ
		return -1;
	}

	return S_OK;
}

void CApplication::Uninit()
{
#ifdef _DEBUG
	//�f�o�b�O�v���V�[�W���̔j��
	if (m_pDebugProc != nullptr)
	{
		m_pDebugProc->Uninit();

		delete m_pDebugProc;
		m_pDebugProc = nullptr;
	}
#endif

	//�e�N�X�`���N���X�̔j��
	if (m_pTexture != nullptr)
	{
		m_pTexture->ReleaseAll();

		delete m_pTexture;
		m_pTexture = nullptr;
	}

	//�L�[�{�[�h�N���X�̔j��
	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard->Uninit();

		delete m_pInputKeyboard;
		m_pInputKeyboard = nullptr;
	}

	//���[�h�N���X�̔j��
	if (m_mode != nullptr)
	{
		// �I������
		m_mode->Uninit();

		delete m_mode;
		m_mode = nullptr;
	}

	//�����_�����O�N���X�̔j��
	if (m_pRenderer != nullptr)
	{
		// �I������
		m_pRenderer->Uninit();

		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	//�L�[�{�[�h�N���X�̔j��
	if (m_pInputKeyboard != nullptr)
	{
		// �I������
		m_pInputKeyboard->Uninit();

		delete m_pInputKeyboard;
		m_pInputKeyboard = nullptr;
	}

	//�T�E���h�N���X�̔j��
	if (m_pSound != nullptr)
	{
		// �I������
		m_pSound->Uninit();

		delete m_pSound;
		m_pSound = nullptr;
	}

}

void CApplication::Update()
{
	//�L�[�{�[�h�̍X�V�����͍ŏ��ɍs��
	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard->Update();
	}

	m_pRenderer->Update();
	m_mode->Update();
}

void CApplication::Draw()
{
	m_pRenderer->Draw();
}