//
//ParticleEmitter.h
//
#ifndef _PARTICLE_EMITTER_H_
#define _PARTICLE_EMITTER_H_

#include "particle.h"

class CParticle;

class CParticleEmitter : CObject
{
public:
	CParticleEmitter();
	~CParticleEmitter();

	static CParticleEmitter* Create(std::string str);

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw() { ; }
	void AfterRelease() { m_afterRelease = true; }
	void Destroy() { m_release = true; }

	void SetPos(D3DXVECTOR3 pos);

	D3DXVECTOR3 GetPos();
	bool GetDestroy() { return m_release; }

private:
	std::vector<CParticle*> m_particle;
	std::vector<CParticle::SInfo> m_particleInfo;
	std::vector<int> m_life;
	std::vector<bool> m_endList;
	D3DXVECTOR3 m_popPos;
	D3DXVECTOR3 m_move;
	int m_time;
	bool m_afterRelease;
	bool m_release;
};

#endif