//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//Shadow.h
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#ifndef _SHADOW_H_
#define _SHADOW_H_

class CObject2D;

class CShadow
{
public:
	CShadow();
	~CShadow();

	void StartViewfromLight();
	void StartViewfromLight(D3DXMATRIX& mtxWorld);
	void EndViewfromLight();
	void CreateZTexture();

	void SetEnlargement(float value) { lightEnlargement = value; }

	D3DXMATRIX GetMtxProjection() { return m_mtxProj; }
	D3DXMATRIX GetMtxView() { return m_mtxView; }
	D3DXMATRIX GetMtxWorld() { return m_mtxWorld; }
	D3DXMATRIX GetWVP() { return m_calcWVP; };
	LPDIRECT3DTEXTURE9 GetZBufferTexture() { return m_pZBufferTexture; }

private:
	D3DXMATRIX m_mtxProj;
	D3DXMATRIX m_mtxView;
	D3DXMATRIX m_mtxWorld;
	D3DXMATRIX m_calcWVP;

	LPDIRECT3DSURFACE9 m_oldSurface;
	LPDIRECT3DSURFACE9 m_oldZMap;

	//ライト位置から見たシーンのZ値を格納するサーフェイス
	LPDIRECT3DTEXTURE9 m_pZBufferTexture = NULL;
	LPDIRECT3DSURFACE9 m_pZBufferSurface = NULL;
	LPDIRECT3DSURFACE9 m_pZBuffer = NULL;

	float lightEnlargement;
};

#endif