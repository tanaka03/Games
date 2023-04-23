//����������������������������������������
//Renderer.h
//����������������������������������������
#ifndef _RENDERER_H_
#define _RENDERER_H_

class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit();
	void Update();
	void Draw();

	LPDIRECT3DDEVICE9 GetDevice() { return m_pD3DDevice; }
	D3DPRESENT_PARAMETERS GetParameters() { return m_pD3dpp; }

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