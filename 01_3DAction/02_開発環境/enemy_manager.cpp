#include "application.h"
#include "object3d.h"
#include "file.h"
#include "enemy_manager.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// エネミーマネージャのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CEnemyManager::CEnemyManager()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// エネミーマネージャのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CEnemyManager::~CEnemyManager()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// エネミーマネージャの初期化
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
HRESULT CEnemyManager::Init()
{
	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// エネミーマネージャの解放
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CEnemyManager::ReleaseAll()
{
	m_data.clear();
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ファイル読み込み
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CEnemyManager::Load(nlohmann::json& list)
{
	size_t size = list["Property"].size();
	std::vector<CEnemy::SInfo> info = {};

	info.resize(size);
	for (size_t i = 0; i < size; i++)
	{
		SafeLoad(list["Property"][i], "Scale", info[i].scale);
		SafeLoad(list["Property"][i], "Speed", info[i].speed);
		SafeLoad(list["Property"][i], "Power", info[i].power);
		SafeLoad(list["Property"][i], "Life", info[i].life);
		SafeLoad(list["Property"][i], "CoolTime", info[i].coolTime);
		SafeLoad(list["Property"][i], "Score", info[i].score);
		SafeLoad(list["Property"][i], "Exp", info[i].exp);
		SafeLoad(list["Property"][i], "AnimationPath", info[i].animationPath);

		if (list["Property"][i]["Vision"].empty())
		{
			continue;
		}

		size_t visionSize = list["Property"][i]["Vision"].size();
		info[i].visionValue.resize(visionSize);
		info[i].behavior.resize(visionSize);

		for (size_t j = 0; j < visionSize; j++)
		{
			SafeLoad(list["Property"][i]["Vision"][j], "VisionValue", info[i].visionValue[j]);
			SafeLoad(list["Property"][i]["Vision"][j], "Behavior", info[i].behavior[j]);
		}
	}

	m_data.insert(std::make_pair(list["Tag"], info));
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ファイルの全ての要素を読み込み
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CEnemyManager::LoadAll()
{
	nlohmann::json list = CFile::LoadJsonStage(L"Data/FILE/enemy.json");

	size_t size = list["ENEMY"].size();

	for (size_t i = 0; i < size; i++)
	{
		if (list["ENEMY"][i]["Tag"].empty())
		{
			continue;
		}

		Load(list["ENEMY"].at(i));
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 抽出したデータを返す処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
std::vector<CEnemy::SInfo> CEnemyManager::GetEnemyData(std::string str)
{
	if (m_data.count(str) == 0)
	{	//モデルデータが入ってなかった場合
		assert(false);
	}

	return m_data[str];
}