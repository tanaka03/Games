//
//Application.h
//
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "main.h"

class CInputKeyboard;
class CObject;
class CRenderer;
class CTexture;
class CCamera;
class CDebugProc;
class CFile;
class CModel;
class CUtility;
class CMode;
class CMeshField;
class CObjectXGroup;
class C3DEffectManager;
class CEnemyManager;
class CSound;
class CParticleManager;

class CDepthBufferShadow;
class CLambert;
class CShadow;

class CApplication
{
public:
	static CApplication *GetInstance();

	CApplication();
	~CApplication();

	HRESULT Init(HWND hWnd, HINSTANCE hInstance);
	void Uninit();
	void Update();
	void Draw();

	CInputKeyboard *GetInputKeyboard() { return m_pInputKeyboard; }
	CRenderer *GetRenderer() { return m_pRenderer; }
	CCamera *GetCamera() { return m_pCamera; }
	CDebugProc *GetDebugProc() { return m_pDebugProc; }
	CFile *GetFile() { return m_pFile; }
	CMeshField *GetMeshField() { return m_pMesh; }
	CTexture *GetTexture() { return m_pTexture; }
	CModel *GetModel() { return m_pModel; }
	CUtility *GetUtility() { return m_pUtility; }
	CMode *GetMode() { return m_pMode; }
	CObjectXGroup *GetObjectXGroup() { return m_pObjectXGroup; }
	C3DEffectManager *GetEffectManager() { return m_pEffectManager; }
	CEnemyManager *GetEnemyManager() { return m_pEnemyManager; }
	CParticleManager *GetParticleManager() { return m_pParticleManager; }
	CSound *GetSound() { return m_pSound; }

	CShadow *GetShadow() { return m_pShadow; }
	CLambert *GetLambert() { return m_pLambert; }
	CDepthBufferShadow *GetDepthBuffShadow() { return m_pDepthBuffShadow; }

private:
	static CApplication *m_pApplication;

	CObject *m_pObject;
	CMeshField *m_pMesh;
	CCamera *m_pCamera;
	CInputKeyboard *m_pInputKeyboard;
	CRenderer *m_pRenderer;
	CTexture *m_pTexture;
	CDebugProc *m_pDebugProc;
	CFile *m_pFile;
	CModel *m_pModel;
	CUtility *m_pUtility;
	CMode *m_pMode;
	CObjectXGroup *m_pObjectXGroup;
	C3DEffectManager *m_pEffectManager;
	CEnemyManager *m_pEnemyManager;
	CParticleManager *m_pParticleManager;
	CSound *m_pSound;

	CShadow *m_pShadow;
	CLambert *m_pLambert;
	CDepthBufferShadow *m_pDepthBuffShadow;

	bool m_bWire;
};

#endif