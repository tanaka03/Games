#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "billboard.h"

class CParticle : public CBillboard
{
public:
	//--------------------------------------
	// パーティクル情報の構造体
	//--------------------------------------
	struct SInfo
	{
		D3DXVECTOR3 pos;						// 位置
		D3DXVECTOR3 destPos;					// 目的の位置
		D3DXVECTOR3 move;						// 移動量
		D3DXVECTOR3 scale;						// 大きさ
		D3DXVECTOR3 scalingValue;				// 拡縮量
		D3DXCOLOR col;							// 色
		D3DXCOLOR destCol;						// 目的の色
		std::vector<std::string> infoProperty;	// プロパティ
		std::string texTag;						// テクスチャのタグ
		int destroyTime;						// エフェクトを消す時間
		int fallDelayTime;						// 落ちるまでの遅延
		int popParticleNum;						// 生成する数
		float moveAttenuation;					// 移動の減衰量
		float colAttenuation;					// 色の減衰量
		float rotateValue;						// 回転量
		float radius;							// 円周
		float weight;							// 重さ
	};

	explicit CParticle(int nPriority = CObject::PRIORITY_THIRD);
	~CParticle() override;

	static CParticle *Create(SInfo& info, std::string url, int nPriority = CObject::PRIORITY_THIRD);	// 生成処理

	HRESULT Init() override;												// 初期化処理
	void Update() override;													// 更新処理
	void Draw() override;													// 描画処理
	void Behavior(std::vector<std::string>& prop);							// パーティクルの挙動

	//セッター
	void SetInfo(SInfo& info) { m_info = info; }
	void SetPath(std::string path) { m_path = path; }

	int GetLife() { return m_info.destroyTime; }

private:
	SInfo m_info;						// パーティクルの情報
	std::string m_path;					// テクスチャのパス
	int m_nTime;						// 時間
};
#endif