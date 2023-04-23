//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// パーティクルのファイル情報を読み込む処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#include "application.h"
#include "object3d.h"
#include "file.h"
#include "particle_manager.h"
#include "utility.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//パーティクルマネージャのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CParticleManager::CParticleManager()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// パーティクルマネージャのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CParticleManager::~CParticleManager()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// パーティクルマネージャの初期化
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
HRESULT CParticleManager::Init()
{
	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// パーティクルマネージャの解放
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CParticleManager::ReleaseAll()
{
	m_data.clear();
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ファイル読み込み
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CParticleManager::Load(nlohmann::json& list)
{
	if (list["PopNum"].empty())
	{
		assert(false);
	}

	int popNum = list["PopNum"];
	size_t size = list["Property"].size();

	std::vector<CParticle::SInfo> info = {};
	info.resize(size);
	for (size_t i = 0; i < size; i++)
	{
		info[i].popParticleNum = popNum;
		SafeLoad(list["Property"][i], "Pos", info[i].pos);								// 位置
		SafeLoad(list["Property"][i], "Move", info[i].move);							// 移動量
		SafeLoad(list["Property"][i], "MoveAttenuation", info[i].moveAttenuation);		// 移動量の減衰
		SafeLoad(list["Property"][i], "Scale", info[i].scale);							// 大きさ
		SafeLoad(list["Property"][i], "Color", info[i].col);							// 色
		SafeLoad(list["Property"][i], "DestColor", info[i].destCol);					// 目的の色
		SafeLoad(list["Property"][i], "ColorAttenuation", info[i].colAttenuation);		// 色の減衰量
		SafeLoad(list["Property"][i], "ScalingValue", info[i].scalingValue);			// 拡縮量
		SafeLoad(list["Property"][i], "Rotate", info[i].rotateValue);					// 回転量
		SafeLoad(list["Property"][i], "Weight", info[i].weight);						// 重さ
		SafeLoad(list["Property"][i], "Radius", info[i].radius);						// 円周
		SafeLoad(list["Property"][i], "Life", info[i].destroyTime);						// 生存時間
		SafeLoad(list["Property"][i], "TexTag", info[i].texTag);						// テクスチャ

		std::string prop;
		std::vector<std::string> behaviorList;

		SafeLoad(list["Property"][i], "Behavior", prop);		// 動きのプロパティ
		CUtility::stringMultiPush(behaviorList, prop);

		info[i].infoProperty = behaviorList;
	}

	m_data.insert(std::make_pair(list["Tag"], info));
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ファイルの全ての要素を読み込み
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CParticleManager::LoadAll()
{
	nlohmann::json list = CFile::LoadJsonStage(L"Data/FILE/particle.json");

	size_t size = list["PARTICLE"].size();

	for (size_t i = 0; i < size; i++)
	{
		if (list["PARTICLE"][i]["Tag"].empty())
		{
			continue;
		}

		Load(list["PARTICLE"].at(i));
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 抽出したデータを返す処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
std::vector<CParticle::SInfo> CParticleManager::GetParticleData(std::string str)
{
	if (m_data.count(str) == 0)
	{	//モデルデータが入ってなかった場合
		assert(false);
	}

	return m_data[str];
}