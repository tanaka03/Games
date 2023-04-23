#include "debugproc.h"
#include "main.h"
#include "application.h"
#include "renderer.h"

//��������������������������������������������������������������
// �f�o�b�O�v���V�[�W���̃R���X�g���N�^
//��������������������������������������������������������������
CDebugProc::CDebugProc()
{
}

//��������������������������������������������������������������
// �f�o�b�O�v���V�[�W���̃f�X�g���N�^
//��������������������������������������������������������������
CDebugProc::~CDebugProc()
{
}

//��������������������������������������������������������������
// �f�o�b�O�v���V�[�W���̏�����
//��������������������������������������������������������������
void CDebugProc::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();
	D3DXCreateFont(pDevice, 25, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Debug"), &m_pFont);
}

//��������������������������������������������������������������
// �f�o�b�O�v���V�[�W���̏I��
//��������������������������������������������������������������
void CDebugProc::Uninit()
{
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}
}

//��������������������������������������������������������������
// �f�o�b�O�v���V�[�W���̕����̎w��q��ϊ�����
//��������������������������������������������������������������
void CDebugProc::Print(const char *pFormat, ...)
{
	va_list args;
	va_start(args, pFormat);

	std::vector<int> Find;
	m_Str = pFormat;
	unsigned int nCntStr = 0;
	int nCntDeleted = 0;
	int nCntAdd = 0;

	// ����̕����̈ʒu�̐��l��ۑ�
	while (nCntStr < m_Str.length())
	{
		if (m_Str.substr(nCntStr, 1) == "%")
		{
			Find.push_back(nCntStr);
		}
		nCntStr++;
	}

	// ����̐��l�̏ꏊ������
	for (const auto &pos : Find)
	{
		std::string destStr = m_Str.substr(pos - nCntDeleted, 2);
		std::string argStr;

		if (destStr == "%d")
		{	// int�^
			int Arg = va_arg(args, int);
			argStr = std::to_string(Arg);
			nCntAdd = argStr.length();
			m_Str.replace(pos - nCntDeleted, destStr.length(), argStr);
			nCntDeleted += destStr.length();
		}

		if (destStr == "%f")
		{	// double�^�ifloat����va_arg�ňÖٓI��double�ɕϊ�����Ă��܂������Ȃ��j
			double Arg = va_arg(args, double);
			argStr = std::to_string(Arg);
			argStr += 'f';
			nCntAdd = argStr.length();
			m_Str.replace(pos - nCntDeleted, destStr.length(), argStr);
			nCntDeleted += destStr.length();
		}

		if (destStr == "%c")
		{	// char�^
			char Arg = va_arg(args, char);
			argStr = Arg;
			nCntAdd = argStr.length();
			m_Str.replace(pos - nCntDeleted, destStr.length(), argStr);
			nCntDeleted += destStr.length();
		}

		if (destStr == "%s")
		{	// const char�^
			const char* Arg = va_arg(args, const char*);
			argStr = Arg;
			nCntAdd = argStr.length();
			m_Str.replace(pos - nCntDeleted, destStr.length(), argStr);
			nCntDeleted += destStr.length();
		}

		nCntDeleted -= nCntAdd;
	}

	va_end(args);
}

//��������������������������������������������������������������
// �f�o�b�O�v���V�[�W���̃e�L�X�g�`��
//��������������������������������������������������������������
void CDebugProc::Draw()
{
	if (m_pFont == nullptr)
	{
		return;
	}

	RECT rect = { 0, 10, SCREEN_WIDTH, SCREEN_HEIGHT };

	wsprintf((TCHAR*)m_Str.c_str(), _T(m_Str.c_str()));

	// �e�L�X�g�`��
	m_pFont->DrawText(NULL, m_Str.c_str(), -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}