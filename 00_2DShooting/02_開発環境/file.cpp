#include "application.h"
#include "file.h"
#include "object2d.h"
#include "particle.h"
#include "particle_manager.h"
#include "enemy.h"
#include "game.h"
#include "score.h"

#include "debugproc.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <windows.h>
#include <locale.h>
#include <algorithm>
#include <vector>
#include <assert.h>

using namespace std;
using namespace nlohmann;

int CFile::m_nTime = 0;

#define NUM_ENEMY	(10)

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//ファイルのリストの生成
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
json j;	//リストの生成
json enemy;	//敵リスト
json ranking;

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//ファイルのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CFile::CFile()
{
	m_nTime = 0;
	memset(m_pEnemy, 0, sizeof(m_pEnemy));
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//ファイルのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CFile::~CFile()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//ファイルの更新処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CFile::Update()
{
	m_nTime++;

	CDebugProc::Print("Time : %d", m_nTime);

	for (int i = 0; i < Max_EnemyData; i++)
	{
		if (m_enemy[i].frame == m_nTime)
		{
			m_pEnemy[i] = m_pEnemy[i]->Create(m_enemy[i].pos, m_enemy[i].type);
			m_pEnemy[i]->SetMove(m_enemy[i].move);
			m_pEnemy[i]->SetCol(m_enemy[i].col);
			m_pEnemy[i]->SetScale(m_enemy[i].scale.x, m_enemy[i].scale.y);
			m_pEnemy[i]->SetFiringTime(m_enemy[i].bullet_interval);
			m_pEnemy[i]->SetKillScore(m_enemy[i].score);
			m_pEnemy[i]->SetPlayerDamage(m_enemy[i].damage);
			m_pEnemy[i]->SetLife(m_enemy[i].life);
			m_pEnemy[i]->SetBulletLife(m_enemy[i].Bulletlife);
			m_pEnemy[i]->SetIdx(i);
		}

		for (int j = 0; j < m_pObject->GetObjAll(); j++)
		{
			CObject *pObject;
			pObject = m_pObject->GetMyObject(j);

			if (pObject == nullptr)
			{
				continue;
			}

			/*↓オブジェクトがnullptrではなかった場合通る↓*/

			CObject::EObjType objType;
			objType = pObject->GetObjType();

			if (objType != CObject::OBJTYPE_ENEMY)
			{
				continue;
			}

			CEnemy *pEnemy = (CEnemy*)pObject;
			int idx = pEnemy->GetIdx();

			for (int k = 0; k < m_enemy[idx].numKeyframe; k++)
			{
				if (m_enemy[idx].specified_frame[k] == m_nTime)
				{
					if (m_enemy[idx].keyPos[k] == D3DXVECTOR3(0.0f,0.0f,0.0f))
					{
						m_pEnemy[idx]->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					}

					else
					{
						D3DXVECTOR3 vec = m_enemy[idx].keyPos[k] - m_pEnemy[idx]->GetPos();
						D3DXVec3Normalize(&vec, &vec);
						m_pEnemy[idx]->SetMove(vec);
					}
				}
			}
		}
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//ファイルの入力処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CFile::Input(const char* FileName)
{
	string Path = "data/FILE/";
	const string pathToJSON = Path += FileName;
	ifstream ifs(pathToJSON);//開くやつ

	if (ifs)
	{//成功した場合

		ifs >> enemy;

		int idx = enemy["INDEX"];

		for (int i = 0; i < idx; i++)
		{
			string name = "ENEMY";
			string Number = std::to_string(i);
			name += Number;

			m_enemy[i].pos = D3DXVECTOR3(enemy[name]["POS"]["X"], enemy[name]["POS"]["Y"], enemy[name]["POS"]["Z"]);
			m_enemy[i].move = D3DXVECTOR3(enemy[name]["MOVE"]["X"], enemy[name]["MOVE"]["Y"], enemy[name]["MOVE"]["Z"]);
			m_enemy[i].col = D3DXCOLOR(enemy[name]["COL"]["R"], enemy[name]["COL"]["G"], enemy[name]["COL"]["B"], enemy[name]["COL"]["A"]);
			m_enemy[i].scale = D3DXVECTOR2(enemy[name]["SCALE"]["WIDTH"], enemy[name]["SCALE"]["HEIGHT"]);
			m_enemy[i].type = (CEnemy::ENEMYTYPE)enemy[name]["TYPE"];
			m_enemy[i].score = enemy[name]["SCORE"];
			m_enemy[i].bullet_interval = enemy[name]["INTERVAL"];
			m_enemy[i].damage = enemy[name]["DAMAGE"];
			m_enemy[i].Bulletlife = enemy[name]["BULLETLIFE"];
			m_enemy[i].life = enemy[name]["LIFE"];
			m_enemy[i].frame = enemy[name]["FRAME"];

			m_enemy[i].numKeyframe = enemy[name]["NUMMOVE"];

			for (int j = 0; j < m_enemy[i].numKeyframe; j++)
			{
				string keyName = "KEYFRAME";
				string keyNumber = to_string(j);
				keyName += keyNumber;

				m_enemy[i].specified_frame[j] = enemy[name][keyName]["MOVEFRAME"];
				m_enemy[i].keyPos[j] = D3DXVECTOR3(enemy[name][keyName]["KEYMOVE"]["X"], enemy[name][keyName]["KEYMOVE"]["Y"], enemy[name][keyName]["KEYMOVE"]["Z"]);
			}
		}
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//ファイルの出力処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CFile::Output(const char* FileName)
{
	//データの入れ方サンプル
	//j["DESTCOL"] = { { "R", DataEffect.color.destCol.r },{ "G" ,DataEffect.color.destCol.g } ,{ "B", DataEffect.color.destCol.b } ,{ "A", DataEffect.color.destCol.a } };
	//j["ENDTIME"] = DataEffect.color.nEndTime; 
	int nIndex = NUM_ENEMY;
	for (int i = 0; i < nIndex; i++)
	{
		string name = "ENEMY";
		string Number = to_string(i);
		name += Number;

		enemy[name] =
		{
			{ "POS",{ { "X", 200.0f + (100.0f * i) },{ "Y", 100.0 },{ "Z", 0.0 } } },
			{ "COL",{ { "R", 1.0 },{ "G", 0.0 },{ "B", 0.0 },{ "A", 1.0 } } },
			{ "SCALE",{ { "WIDTH", 38.0 },{ "HEIGHT", 38.0 } } },
			{ "LIFE", 15},
			{ "FRAME", 70},
			{ "TYPE", 4 },
		};

		enemy["INDEX"] = nIndex;
	}

	//出力するやつ
	auto jobj = enemy.dump();
	ofstream writing_file;
	string Path = "data/FILE/";
	const string pathToJSON = Path += FileName;
	writing_file.open(pathToJSON, ios::out);
	writing_file << jobj << endl;
	writing_file.close();
}

void CFile::LoadRanking(const char* FileName)
{
	string Path = "data/FILE/";
	const string pathToJSON = Path += FileName;
	ifstream ifs(pathToJSON);//開くやつ

	if (ifs)
	{//成功した場合

		ifs >> ranking;

		int RankingMax = 10;
		for (int i = 0; i < RankingMax; i++)
		{
			string name = "RANK";
			string Number = to_string(i);
			name += Number;

			m_nScore[i] = ranking[name]["SCORE"];
		}
	}
}

void CFile::SaveRanking(const char* FileName)
{
	CScore *pScore = nullptr;
	int RankingMax = 10;
	LoadRanking("ranking.json");
	m_nScore[10] = pScore->Get();
	vector<int> Score(begin(m_nScore), end(m_nScore));
	sort(Score.begin(), Score.end(), greater<int>{});

	for (int i = 0; i < RankingMax; i++)
	{
		string name = "RANK";
		string Number = to_string(i);
		name += Number;

		ranking[name] =
		{
			{ "SCORE", Score[i] },
		};
	}

	//出力するやつ
	auto jobj = ranking.dump();
	ofstream writing_file;
	string Path = "data/FILE/";
	const string pathToJSON = Path += FileName;
	writing_file.open(pathToJSON, ios::out);
	writing_file << jobj << endl;
	writing_file.close();
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//パーティクルファイルの読み込み
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//void CFile::LoadJson(const char* cUrl)
//{
//	ifstream ifs(cUrl);
//	int index = 0;
//
//	if (ifs)
//	{
//		CParticleManager::BundledData loadData = {};
//		CParticle::Info& particleInfo = loadData.particleData;
//
//		//StringToWString(UTF8toSjis(j["name"]));
//		//DataSet.unionsname = StringToWString(UTF8toSjis(j["unions"] ["name"]));
//		ifs >> j;
//
//		//こっちで構造体にデータを入れてます//文字は変換つけないとばぐるぞ＾＾これ-＞UTF8toSjis()
//		particleInfo.move = D3DXVECTOR3(j["MOVE"]["X"], j["MOVE"]["Y"], j["MOVE"]["Z"]);
//		particleInfo.rot = D3DXVECTOR3(j["ROT"]["X"], j["ROT"]["Y"], j["ROT"]["Z"]);
//		particleInfo.moveTransition = D3DXVECTOR3(j["MOVETRANSITION"]["X"], j["MOVETRANSITION"]["Y"], j["MOVETRANSITION"]["Z"]);;
//
//		particleInfo.color.colBigin = D3DXCOLOR(j["COL"]["R"], j["COL"]["G"], j["COL"]["B"], j["COL"]["A"]);
//		particleInfo.color.colRandamMax = D3DXCOLOR(j["COLRANDAMMAX"]["R"], j["COLRANDAMMAX"]["G"], j["COLRANDAMMAX"]["B"], j["COLRANDAMMAX"]["A"]);
//		particleInfo.color.colRandamMin = D3DXCOLOR(j["COLRANDAMMIN"]["R"], j["COLRANDAMMIN"]["G"], j["COLRANDAMMIN"]["B"], j["COLRANDAMMIN"]["A"]);
//		particleInfo.color.colTransition = D3DXCOLOR(j["COLTRANSITION"]["R"], j["COLTRANSITION"]["G"], j["COLTRANSITION"]["B"], j["COLTRANSITION"]["A"]);
//		particleInfo.color.destCol = D3DXCOLOR(j["DESTCOL"]["R"], j["DESTCOL"]["G"], j["DESTCOL"]["B"], j["DESTCOL"]["A"]);
//		particleInfo.color.nEndTime = j["ENDTIME"];
//		particleInfo.color.nCntTransitionTime = j["CNTTRANSITIONTIME"];
//		particleInfo.color.bColTransition = j["BCOLTRANSITION"];
//		particleInfo.color.bColRandom = j["COLRANDOM"];
//		particleInfo.color.bRandomTransitionTime = j["RANDOMTRANSITIONTIME"];
//
//		particleInfo.type = j["TYPE"];
//		particleInfo.fWidth = j["WIDTH"];
//		particleInfo.fHeight = j["HEIGHT"];
//		particleInfo.fRadius = j["RADIUS"];
//		particleInfo.fAngle = j["ANGLE"];
//		particleInfo.fWeight = j["WEIGHT"];
//		particleInfo.nLife = j["LIFE"];
//		particleInfo.fAttenuation = j["ATTENUATION"];
//		particleInfo.fWeightTransition = j["WEIGHTTRANSITION"];
//		particleInfo.nLife = j["LIFE"];
//		particleInfo.bBackrot = j["BACKROT"];
//		particleInfo.fScale = j["SCALE"];
//
//		static bool chack = true;
//
//		if (chack)
//		{
//			CApplication::GetParticleManager()->SetBundledData(loadData, index);
//			index++;
//		}
//		else
//		{
//			CApplication::GetParticleManager()->ChangeBundledData(0, loadData);
//		}
//	}
//}

/*
//============================
// 書込み
//============================
void SaveJson(nlohmann::json inJson, const std::string cUrl)
{
	auto jobj = inJson.dump();
	std::ofstream writing_file;
	const std::string pathToJSON = cUrl;
	writing_file.open(pathToJSON, std::ios::out);
	writing_file << jobj << std::endl;
	writing_file.close();
}

//============================
// 読込み
//============================
nlohmann::json LoadJson(const wchar_t* cUrl)
{
	std::ifstream ifs(cUrl);

	if (!ifs)
	{
		return nullptr;
	}
	nlohmann::json jsonData;
	ifs >> jsonData;

	return jsonData;
}

//--------------------------------------------------
// 値の読込み
//--------------------------------------------------
void LoadValueBundledData(nlohmann::json* inJson, DeepTable& inTable)
{
	std::vector<ConvTable> table = inTable.table;
	for (int i = 0; i < table.size(); i++)
	{
		if ((*inJson).count(table[i].name) == 0)
		{
			continue;
		}

		switch (table[i].type)
		{
		case UseChack:
			if (((DeepTable*)table[i].store)->use != nullptr)
			{
				*((DeepTable*)table[i].store)->use = true;
			}
			// 再起処理
			LoadValueBundledData(&((*inJson)[table[i].name]), *((DeepTable*)table[i].store));
			break;
		case Vector3:
		{
			auto VectorFloatToVector3 = [](std::vector<float> inVector)->D3DXVECTOR3
			{
				return D3DXVECTOR3(inVector[0], inVector[1], inVector[2]);
			};

			*((D3DXVECTOR3*)table[i].store) = VectorFloatToVector3((*inJson)[table[i].name]);
		}
		break;
		case Color:
		{
			auto VectorFloatToColor = [](std::vector<float> inVector)->D3DXCOLOR
			{
				return D3DXCOLOR(inVector[0], inVector[1], inVector[2], inVector[3]);
			};

			*((D3DXCOLOR*)table[i].store) = VectorFloatToColor((*inJson)[table[i].name]);
		}
		break;
		case Float:
			*((float*)table[i].store) = (*inJson)[table[i].name];
			break;
		case Int:
			*((int*)table[i].store) = (*inJson)[table[i].name];
			break;
		case Bool:
			*((bool*)table[i].store) = (*inJson)[table[i].name];
			break;

		default:
			break;
		}
	}
}
*/