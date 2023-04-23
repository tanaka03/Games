#include "application.h"
#include "object3d.h"
#include "file.h"
#include "3deffect_manager.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 3Dエフェクトマネージャのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
C3DEffectManager::C3DEffectManager()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 3Dエフェクトマネージャのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
C3DEffectManager::~C3DEffectManager()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 3Dエフェクトマネージャの初期化
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
HRESULT C3DEffectManager::Init()
{
	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 3Dエフェクトマネージャの解放
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void C3DEffectManager::ReleaseAll()
{
	m_data.clear();
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ファイル読み込み
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void C3DEffectManager::Load(nlohmann::json& list)
{
	size_t size = list["Property"].size();
	std::vector<C3DEffect::SInfo> info = {};

	info.resize(size);
	for (size_t i = 0; i < size; i++)
	{
		SafeLoad(list["Property"][i], "BeginRot", info[i].beginRot);							// 最初の向き
		SafeLoad(list["Property"][i], "BeginScale", info[i].beginScale);						// 最初の拡縮
		SafeLoad(list["Property"][i], "MoveValue", info[i].moveValue);							// 移動量
		SafeLoad(list["Property"][i], "RotateValue", info[i].rotateValue);						// 回転量
		SafeLoad(list["Property"][i], "ScalingValue", info[i].scalingValue);					// 拡縮量
		SafeLoad(list["Property"][i], "PosOffset", info[i].posOffset);							// 位置のオフセット
		SafeLoad(list["Property"][i], "RotOffset", info[i].rotOffset);							// 向きのオフセット
		SafeLoad(list["Property"][i], "Color", info[i].col);									// 色
		SafeLoad(list["Property"][i], "ColorTransition", info[i].transitionCol);				// 色の遷移
		SafeLoad(list["Property"][i], "ColorTransitionEndTime", info[i].transitionColEndTime);	// 色の遷移の終了時間
		SafeLoad(list["Property"][i], "AlphaAttenuation", info[i].alphaAttenuation);			// 色アルファ値の減衰量
		SafeLoad(list["Property"][i], "MoveAttenuation", info[i].moveAttenuation);				// 動きの減衰量
		SafeLoad(list["Property"][i], "Life", info[i].life);									// エフェクトの生存時間
		SafeLoad(list["Property"][i], "TractionPlayer", info[i].tractPlayer);					// プレイヤーに追従するかどうか
		SafeLoad(list["Property"][i], "UseFileTexture", info[i].useFileTexture);				// xファイルのファイルのテクスチャを使用するかどうか
		SafeLoad(list["Property"][i], "TexTag", info[i].texTag);								// テクスチャのタグ
		SafeLoad(list["Property"][i], "Shape", info[i].modelShape);								// モデルのタグ

		if (list["Property"][i]["Animation"].empty())
		{	// アニメーションの要素がなかった場合
			continue;
		}

	}

	m_data.insert(std::make_pair(list["Tag"], info));
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ファイルの全ての要素を読み込み
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void C3DEffectManager::LoadAll()
{
	nlohmann::json list = CFile::LoadJsonStage(L"Data/FILE/3DEffect.json");

	size_t size =list["EFFECT"].size();

	for (size_t i = 0; i < size; i++)
	{
		if (list["EFFECT"][i]["Tag"].empty())
		{
			continue;
		}

		Load(list["EFFECT"].at(i));
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 抽出したデータを返す処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
std::vector<C3DEffect::SInfo> C3DEffectManager::GetEffectData(std::string str)
{
	if (m_data.count(str) == 0)
	{	//モデルデータが入ってなかった場合
		assert(false);
	}

	return m_data[str];
}