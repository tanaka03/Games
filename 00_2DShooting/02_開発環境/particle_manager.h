//=========================================
// 
// パーティクルエミッタ
// Author YudaKaito
// Author HamadaRyuuga
//=========================================
#ifndef _PARTICLE_MANAGER_H_
#define _PARTICLE_MANAGER_H_

//=========================================
// include
//=========================================
#include <d3dx9.h>
#include <vector>
#include "particle.h"
#include "particle_emitter.h"

//=========================================
// 前方宣言
//=========================================
class CParticleEmitter;

//=========================================
// パーティクルファクトリー
//=========================================
class CParticleManager
{
public:	// 構造体
	struct BundledData
	{
		CParticle::Info particleData;
		CParticleEmitter::Info emitterData;
	};

	enum NOWMAGIC
	{
		NOW_STORM = 0,		// 風
		NOW_SUN,			// 雷
		NOW_FIRE,		    // 火
		NOW_ICE,			// 氷
		NOW_NON,
		NOW_MAX
	};
public:
	CParticleManager();
	~CParticleManager();

	HRESULT Init();
	void Uninit();
	void Update();
	int Create(const D3DXVECTOR3& pos, const int& idx, int Type);
	void Release(const int idx);
	void SetBundledData(const BundledData&inData, int Data);
	void ChangeBundledData(const int idx, const BundledData&inData);
	void SetEmitterPos(const int idx,const D3DXVECTOR3& inPos);

	// ゲッタ―
	std::vector<BundledData>& GetBundledData(int ind) { return m_bundledData[ind]; }
	std::vector<CParticleEmitter*> GetEmitter() { return m_particleEmitter; }
private:
	int m_numAll;	// 生成数
	std::vector<BundledData> m_bundledData[10];	// 情報体
	std::vector<CParticleEmitter*> m_particleEmitter;	// エミッタ―情報
	int m_Index;
	static int m_MaxIndex;
};

#endif // !_PARTICLE_FACTORY_H_
