#ifndef _PARTICLE_MANAGER_H_
#define _PARTICLE_MANAGER_H_

#include "file.h"
#include "particle.h"

class CParticle;

class CParticleManager
{
public:
	CParticleManager();
	~CParticleManager();

	HRESULT Init();
	void ReleaseAll();
	void Load(nlohmann::json& list);
	void LoadAll();

	std::vector<CParticle::SInfo> GetParticleData(std::string str);
	std::map<std::string, std::vector<CParticle::SInfo>, std::less<>> GetData() { return m_data; }

private:
	void SafeLoad(nlohmann::json check, std::string str, int& value) { if (check[str].empty()) value = 0;	 else value = check[str]; }
	void SafeLoad(nlohmann::json check, std::string str, float& value) { if (check[str].empty()) value = 0.0f;  else value = check[str]; }
	void SafeLoad(nlohmann::json check, std::string str, bool& value) { if (check[str].empty()) value = false; else value = check[str]; }
	void SafeLoad(nlohmann::json check, std::string str, std::string& name) { if (check[str].empty()) name = "null"; else name = check[str]; }
	void SafeLoad(nlohmann::json check, std::string str, D3DXVECTOR3& value)
	{
		if (check[str].empty()) value = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		else value = D3DXVECTOR3(check[str]["X"], check[str]["Y"], check[str]["Z"]);
	}
	void SafeLoad(nlohmann::json check, std::string str, D3DXCOLOR& value)
	{
		if (check[str].empty()) value = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		else value = D3DXCOLOR(check[str]["R"], check[str]["G"], check[str]["B"], check[str]["A"]);
	}

	std::map<std::string, std::vector<CParticle::SInfo>, std::less<>> m_data;
};

#endif