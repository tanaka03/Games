#ifndef _3DEFFECTEMITTER_H_
#define _3DEFFECTEMITTER_H_

#include "3deffect.h"
#include "texture.h"

class C3DEffect;

class C3DEffectEmitter
{
public:
	C3DEffectEmitter();
	~C3DEffectEmitter();

	static C3DEffectEmitter* Create(std::string tag);

	HRESULT Init();								// ‰Šú‰»ˆ—
	void Uninit();
	void Update();								// XVˆ—

	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	void SetScale(D3DXVECTOR3 scale);

	C3DEffect *GetEffect(int idx) { return m_pEffect[idx]; }
	std::vector<C3DEffect*> GetEffectData() { return m_pEffect; }

private:
	std::vector<C3DEffect::SInfo> m_effectInfo;
	std::vector<C3DEffect*> m_pEffect;
	std::vector<int> m_life;
	D3DXVECTOR3 m_pos;
};

#endif