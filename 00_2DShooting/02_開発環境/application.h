//
//Application.h
//
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "main.h"

class CMode;

class CEnemy;
class CInputKeyboard;
class CItem;
class CObject;
class CRenderer;
class CSound;
class CTexture;
class CDebugProc;

class CApplication
{
public:
	CApplication();
	~CApplication();

	HRESULT Init(HWND hWnd, HINSTANCE hInstance);
	void Uninit();
	void Update();
	void Draw();

	static CEnemy *GetEnemy() { return m_pEnemy; }
	static CInputKeyboard *GetInputKeyboard() { return m_pInputKeyboard; }
	static CItem * GetItem() { return m_pItem; }
	static CRenderer *GetRenderer() { return m_pRenderer; }
	static CSound *GetSound() { return m_pSound; }
	static CTexture *GetTexture() { return m_pTexture; }

private:
	static CMode *m_mode;

	static CEnemy *m_pEnemy;
	static CInputKeyboard *m_pInputKeyboard;
	static CItem *m_pItem;
	static CRenderer *m_pRenderer;
	static CSound *m_pSound;
	static CTexture *m_pTexture;
	static CDebugProc *m_pDebugProc;
};

#endif