//=========================================
// 
// パーティクルエミッタ
// Author YudaKaito
// Author HamadaRyuuga
//=========================================
//=========================================
// include
//=========================================
#include "particle_manager.h"
#include "file.h"

#include <assert.h>

int CParticleManager::m_MaxIndex = 0;
//-----------------------------------------
// コンストラクタ
//-----------------------------------------
CParticleManager::CParticleManager() :
	m_numAll(0),
	m_particleEmitter({})
{
}

//-----------------------------------------
// デストラクタ
//-----------------------------------------
CParticleManager::~CParticleManager()
{
}

//-----------------------------------------
// 初期化
//-----------------------------------------
HRESULT CParticleManager::Init()
{
	CFile *pFile = nullptr;

	pFile->LoadJson("data/FILE/rot.json");

	return S_OK;
}

//-----------------------------------------
// 終了
//-----------------------------------------
void CParticleManager::Uninit()
{
	for (CParticleEmitter* emitter : m_particleEmitter)
	{
		if (emitter != nullptr)
		{
			emitter->Uninit();
			delete emitter;
			emitter = nullptr;
		}
	}
}

//-----------------------------------------
// 更新
//-----------------------------------------
void CParticleManager::Update()
{
	for (CParticleEmitter* i : m_particleEmitter)
	{
		if (i == nullptr)
		{
			continue;
		}

		i->Update();
	}
}

//-----------------------------------------
// 生成
//-----------------------------------------
int CParticleManager::Create(const D3DXVECTOR3& pos, const int& index,int Type)
{
	CParticleEmitter* emitter = new CParticleEmitter();

	emitter->Init();		// 初期化
	emitter->SetPos(pos);	// 位置の更新

	if (m_bundledData[Type].size() <= index)
	{
		assert(false);
		return 0;
	}

	emitter->SetParticle(m_bundledData[Type].at(index).particleData);	// 指定されてたパーティクルデータの挿入
	emitter->SetEmitter(m_bundledData[Type].at(index).emitterData);

	m_numAll++;
	m_particleEmitter.push_back(emitter);

	return m_particleEmitter.size();
}

//-----------------------------------------
// リリース
//-----------------------------------------
void CParticleManager::Release(const int idx)
{
	delete m_particleEmitter.at(idx);
	m_particleEmitter.erase(m_particleEmitter.begin() + (idx));
}

//-----------------------------------------
// 設定
//-----------------------------------------
void CParticleManager::SetBundledData(const BundledData& inData,int Data)
{
	m_bundledData[Data].push_back(inData);
}

//-----------------------------------------
// チェンジ機能
//-----------------------------------------
void CParticleManager::ChangeBundledData(const int idx, const BundledData& inData)
{
	m_bundledData[m_Index].at(idx) = inData;
}

//-----------------------------------------
// 指定された番号の位置を変更する
//-----------------------------------------
void CParticleManager::SetEmitterPos(const int idx, const D3DXVECTOR3 & inPos)
{
	m_particleEmitter.at(idx)->SetPos(inPos);
}
