#include "main.h"
#include "input.h"

//����������������������������������������
//�L�[�{�[�h�̃R���X�g���N�^
//����������������������������������������
CInput::CInput()
{
	m_pDevice = nullptr;
}

//����������������������������������������
//�L�[�{�[�h�̃f�X�g���N�^
//����������������������������������������
CInput::~CInput()
{

}

HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	//DirectX�I�u�W�F�N�g�̍쐬
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
	{
		return E_FAIL;
	}

	//���̓f�o�C�X�i�L�[�{�[�h�̐����j
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	return S_OK;
}

void CInput::Uninit()
{
	//���̓f�o�C�X�i�L�[�{�[�h�̔j���j
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	//DirectX�I�u�W�F�N�g�̔j��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

LPDIRECTINPUTDEVICE8 CInput::GetInputDevice()
{
	return m_pDevice;
}