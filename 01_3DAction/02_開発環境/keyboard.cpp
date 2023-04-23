#include "application.h"
#include "input.h"
#include "keyboard.h"

CInputKeyboard::CInputKeyboard()
{
}

CInputKeyboard::~CInputKeyboard()
{

}

//����������������������������������������
//�L�[�{�[�h�̏���������
//����������������������������������������
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(CInput::GetInputDevice()->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h��ݒ�
	if (FAILED(CInput::GetInputDevice()->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�̃A�N�Z�X�����l��
	CInput::GetInputDevice()->Acquire();

	return S_OK;
}

//����������������������������������������
//�I������
//����������������������������������������
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//����������������������������������������
//�X�V����
//����������������������������������������
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(CInput::GetInputDevice()->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];	//�L�[�{�[�h�̃g���K�[����ۑ�
			m_aKeyState[nCntKey] = aKeyState[nCntKey];		//�L�[�{�[�h�̃A�N�Z�X����ۑ�
		}
	}

	else
	{
		CInput::GetInputDevice()->Acquire();		//�L�[�{�[�h�̃A�N�Z�X�����l��
	}
}

//����������������������������������������
//�L�[�{�[�h�̃g���K�[�����擾
//����������������������������������������
bool CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//����������������������������������������
//�L�[�{�[�h�̃v���X�����l��
//����������������������������������������
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}