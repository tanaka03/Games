//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// パーティクルのエミッタ処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#include "particle_emitter.h"
#include "particle_manager.h"
#include "particle.h"
#include "application.h"
#include "player.h"
#include "game.h"
#include "utility.h"
#include "debugproc.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// パーティクルエミッタのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CParticleEmitter::CParticleEmitter()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// パーティクルエミッタのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CParticleEmitter::~CParticleEmitter()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// パーティクルエミッタの生成
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CParticleEmitter* CParticleEmitter::Create(std::string str)
{
	CParticleEmitter *pEmitter = nullptr;
	pEmitter = new CParticleEmitter;

	CParticleManager *pManager = CApplication::GetInstance()->GetParticleManager();

	if (pEmitter != nullptr)
	{
		pEmitter->m_particleInfo = pManager->GetParticleData(str);
		pEmitter->Init();
	}

	return pEmitter;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// パーティクルエミッタの初期化
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
HRESULT CParticleEmitter::Init()
{
	for (size_t i = 0; i < m_particleInfo.size(); i++)
	{
		m_endList.resize(m_particleInfo[i].popParticleNum);
		m_life.resize(m_particleInfo[i].popParticleNum);
		for (int j = 0; j < m_particleInfo[i].popParticleNum; j++)
		{
			for (auto &p : m_particleInfo[i].infoProperty)
			{
				if (p == "Move_Circle")
				{
					m_particleInfo[i].move = D3DXVECTOR3(-sinf((j * ((m_particleInfo[i].radius / m_particleInfo[i].popParticleNum) * (D3DX_PI / 180)))),
						m_particleInfo[i].move.y,
						-cosf((j * ((m_particleInfo[i].radius / m_particleInfo[i].popParticleNum) * (D3DX_PI / 180)))));
				}
			}
			m_particle.push_back(CParticle::Create(m_particleInfo[i], m_particleInfo[i].texTag));
			m_endList[j] = false;
			m_life[j] = m_particleInfo[i].destroyTime;
		}
	}

	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// パーティクルエミッタの終了
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CParticleEmitter::Uninit()
{
	if (!m_particle.empty())
	{
		for (size_t i = 0; i < m_particle.size(); i++)
		{
			m_particle[i]->Destroy();
		}
		m_particle.clear();
	}

	if (!m_particleInfo.empty())
	{
		m_particleInfo.clear();
	}

	// ライフの要素を削除
	if (!m_life.empty())
	{
		m_life.clear();
	}

	if (!m_endList.empty())
	{
		m_endList.clear();
	}

	this->Destroy();
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// パーティクルエミッタの更新
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CParticleEmitter::Update()
{
	for (size_t i = 0; i < m_particle.size(); i++)
	{
		m_life[i]--;
		if (m_life[i] == 0)
		{
			m_particle[i]->Destroy();
			m_endList[i] = true;
		}
	}

	// 全てがtrueかどうか判定
	bool allEnd = std::all_of(m_endList.begin(), m_endList.end(), [](bool b) { return b; });
	if (allEnd)
	{
		m_life.clear();
		m_particle.clear();
		this->Destroy();
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// パーティクルエミッタの位置設定
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CParticleEmitter::SetPos(D3DXVECTOR3 pos)
{
	for (auto &p : m_particle)
	{
		p->SetPos(pos);
	}
}

D3DXVECTOR3 CParticleEmitter::GetPos()
{
	return m_particle[0]->GetPos();
}