#include "debugproc.h"
#include "main.h"
#include "application.h"
#include "renderer.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// デバッグプロシージャのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CDebugProc::CDebugProc()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// デバッグプロシージャのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CDebugProc::~CDebugProc()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// デバッグプロシージャの初期化
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CDebugProc::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();
	D3DXCreateFont(pDevice, 25, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Debug"), &m_pFont);
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// デバッグプロシージャの終了
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CDebugProc::Uninit()
{
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// デバッグプロシージャの文字の指定子を変換する
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CDebugProc::Print(const char *pFormat, ...)
{
	va_list args;
	va_start(args, pFormat);

	std::vector<int> Find;
	m_Str = pFormat;
	unsigned int nCntStr = 0;
	int nCntDeleted = 0;
	int nCntAdd = 0;

	// 特定の文字の位置の数値を保存
	while (nCntStr < m_Str.length())
	{
		if (m_Str.substr(nCntStr, 1) == "%")
		{
			Find.push_back(nCntStr);
		}
		nCntStr++;
	}

	// 特定の数値の場所を検索
	for (const auto &pos : Find)
	{
		std::string destStr = m_Str.substr(pos - nCntDeleted, 2);
		std::string argStr;

		if (destStr == "%d")
		{	// int型
			int Arg = va_arg(args, int);
			argStr = std::to_string(Arg);
			nCntAdd = argStr.length();
			m_Str.replace(pos - nCntDeleted, destStr.length(), argStr);
			nCntDeleted += destStr.length();
		}

		if (destStr == "%f")
		{	// double型（floatだとva_argで暗黙的にdoubleに変換されてうまくいかない）
			double Arg = va_arg(args, double);
			argStr = std::to_string(Arg);
			argStr += 'f';
			nCntAdd = argStr.length();
			m_Str.replace(pos - nCntDeleted, destStr.length(), argStr);
			nCntDeleted += destStr.length();
		}

		if (destStr == "%c")
		{	// char型
			char Arg = va_arg(args, char);
			argStr = Arg;
			nCntAdd = argStr.length();
			m_Str.replace(pos - nCntDeleted, destStr.length(), argStr);
			nCntDeleted += destStr.length();
		}

		if (destStr == "%s")
		{	// const char型
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

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// デバッグプロシージャのテキスト描画
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CDebugProc::Draw()
{
	if (m_pFont == nullptr)
	{
		return;
	}

	RECT rect = { 0, 10, SCREEN_WIDTH, SCREEN_HEIGHT };

	wsprintf((TCHAR*)m_Str.c_str(), _T(m_Str.c_str()));

	// テキスト描画
	m_pFont->DrawText(NULL, m_Str.c_str(), -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}