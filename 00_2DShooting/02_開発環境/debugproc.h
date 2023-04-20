//
//DebugProc.h
//
#ifndef _DEBUGPROC_H_
#define _DEBUGPROC_H_

#include <string>
#include <d3dx9.h>
#include <d3d9.h>

class CDebugProc
{
public:
	CDebugProc();
	~CDebugProc();

	void Init();
	void Uninit();

	static void Print(const char *pFormat, ...);
	static void Draw();

private:
	static std::string m_Str;
	static LPD3DXFONT m_pFont;
};

#endif
