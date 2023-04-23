//＝＝＝＝＝＝＝＝＝＝＝＝＝
//camera.h
//＝＝＝＝＝＝＝＝＝＝＝＝＝
#ifndef _CAMERA_H_		//二重ガードインクルード
#define _CAMERA_H_

#include "renderer.h"

class CObject;

class CCamera
{
public:
	struct CAMERA
	{
		D3DXVECTOR3 posV;			//視点
		D3DXVECTOR3 posVDest;		//目的の視点
		D3DXVECTOR3 posR;			//注視点
		D3DXVECTOR3 posRDest;		//目的の注視点
		D3DXVECTOR3 vecU;			//上方向ベクトル
		D3DXVECTOR3 rot;			//向き
		D3DXVECTOR3 rotDest;		//目的の向き
		D3DXMATRIX mtxProjection;	//プロジェクションマトリックス
		D3DXMATRIX mtxView;			//ビューマトリックス
		float fDistance;			//視点から注視点の距離
	};

	CCamera();
	~CCamera();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void ShakeCamera(int frame, float power) { m_quakeFrameCount = frame; m_quakeMagnitude = power; }

	//セッター
	void SetCamera(void);
	void SetTraction(bool set) { m_bTraction = set; }

	//ゲッター
	CAMERA *GetCamera(void) { return &m_camera; }
	D3DXVECTOR3 GetWorldPosR() { return m_worldposR; }
	D3DXMATRIX GetMtxWorld() { return m_mtxWorld; }

private:
	CAMERA m_camera;			// カメラの構造体
	D3DXMATRIX m_mtxWorld;		// カメラのマトリックス
	D3DXVECTOR3 m_worldposV;	// 視点
	D3DXVECTOR3 m_worldposR;	// 注視点
	D3DXVECTOR3 m_posOld;		// 前回の位置
	int m_quakeFrameCount;		// 揺れのフレーム数
	float m_quakeMagnitude;		// 揺れの大きさ
	bool m_bTraction;			// プレイヤーに追従するかどうか
};

#endif