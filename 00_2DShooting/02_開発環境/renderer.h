//����������������������������������������
//Renderer.h
//����������������������������������������
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <d3dx9.h>
#include <d3d9.h>

class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit();
	void Update();
	void Draw();
	void ReCreateDevice();
	bool DeviceLost();

	LPDIRECT3DDEVICE9 GetDevice() { return m_pD3DDevice; }	/*�l��return���邾���̏ꍇ���������A�Q�s�ȏ��cpp��*/

private:
	void DrawFPS();

	// Direct3D�I�u�W�F�N�g
	LPDIRECT3D9 m_pD3D;

	// Device�I�u�W�F�N�g
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	LPD3DXFONT m_pFont;
	D3DPRESENT_PARAMETERS m_pD3dpp;
};

#endif