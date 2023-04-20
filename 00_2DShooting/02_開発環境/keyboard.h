//����������������������������������������
//Keyboard.h
//����������������������������������������
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

//===============================
//���C�u�����̃����N
//===============================

#define NUM_KEY_MAX	(256)	//�L�[�̍ő吔

class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard() override;

	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;
	void Uninit() override;
	void Update() override;
	bool GetTrigger(int nKey);
	bool GetPress(int nKey);

private:
	BYTE m_aKeyState[NUM_KEY_MAX];		//�L�[�{�[�h�̃v���X���
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];
};

#endif