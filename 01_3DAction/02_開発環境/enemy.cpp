#include <stdlib.h>
#include "object3d.h"
#include "application.h"
#include "input.h"
#include "keyboard.h"
#include "enemy.h"
#include "camera.h"
#include "debugproc.h"
#include "file.h"
#include "light.h"
#include "model.h"
#include "meshfield.h"
#include "player.h"
#include "utility.h"
#include "game.h"
#include "3dgauge.h"
#include "particle.h"
#include "stage.h"
#include "motion.h"
#include "motion_model3D.h"
#include "parts.h"
#include "player.h"
#include "gauge.h"
#include "score.h"
#include "item.h"
#include "particle_emitter.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 敵のコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CEnemy::CEnemy() :
	m_col(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f)),
	m_fAttenuation(0.6f),
	m_bCollision(false),
	m_OnceCollision(true)
{
	SetObjType(OBJTYPE_ENEMY);
	SetObjState(CObject::OBJSTATE_3D);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bJump = false;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 敵のデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CEnemy::~CEnemy()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 敵の生成
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CEnemy * CEnemy::Create(SInfo& info)
{
	CEnemy *pPlayer = nullptr;
	pPlayer = new CEnemy;

	//ヌルチェック
	if (pPlayer != nullptr)
	{
		// ポリゴンの初期化処理
		pPlayer->SetInfo(info);
		pPlayer->Init();
	}

	return pPlayer;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 敵の初期化
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
HRESULT CEnemy::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	//モデルのロード
	m_pMotionModel = CMotionModel3D::Create();
	m_pMotionModel->SetMotion(m_info.animationPath.c_str());

	m_info.power = 1;
	m_info.scale = D3DXVECTOR3(1.0f,1.0f,1.0f);
	m_fAttenuation = m_info.speed;

	for (int i = 0; i < m_pMotionModel->GetMotion()->GetMaxParts(); i++)
	{
		m_pMotionModel->GetMotion()->GetParts(i)->Init();
	}

	m_modelData.resize(1);
	m_modelData[0].minModel = m_pMotionModel->GetMinVtx();
	m_modelData[0].maxModel = m_pMotionModel->GetMaxVtx();

	m_pHp = C3DGauge::Create(m_objpos, D3DXVECTOR3(50.0f, 5.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), C3DGauge::GAUGETYPE_HP, CObject::PRIORITY_THIRD);
	m_pHp->ValueSetting(m_info.life);
	m_pHp->SetMaxValue(m_info.life);

	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 敵の終了
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CEnemy::Uninit()
{
	//モデルデータが空じゃない場合
	if (!m_modelData.empty())
	{
		m_modelData.clear();
	}

	if (m_pMotionModel != nullptr)
	{
		m_pMotionModel->Uninit();
		delete m_pMotionModel;
		m_pMotionModel = nullptr;
	}

	if (m_pHp != nullptr)
	{
		m_pHp->Destroy();
	}

	Destroy();
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 敵の更新
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CEnemy::Update()
{
	CPlayer *pPlayer = CApplication::GetInstance()->GetMode()->GetGame()->GetPlayer();

	m_posOld = m_objpos;

	m_pMotionModel->Update();

	// 衝突判定
	CMeshField *pMesh = CApplication::GetInstance()->GetMode()->GetGame()->GetMeshField();
	bool collision = pMesh->Collision(m_objpos);

	if (m_bCollision)
	{
		m_move.y = 0.0f;
		m_objpos = D3DXVECTOR3(m_objpos.x, m_collisionPos.y, m_objpos.z);
		m_bJump = true;
	}
	if (collision)
	{
		D3DXVECTOR3 collisionPos = pMesh->GetHitPos();
		m_move.y = 0.0f;
		m_objpos = D3DXVECTOR3(m_objpos.x, collisionPos.y, m_objpos.z);
		m_bJump = true;
	}
	else
	{
		m_move.y -= 3.5f;
		m_bJump = false;
	}

	m_objpos += m_move;
	m_fAttenuation = m_info.speed;

	// モーションの遷移関係
	if (m_transitionTime >= 0)
	{
		m_transitionTime--;
	}

	//敵とプレイヤーの当たり判定
	CObject *pObject = CObject::GetTop(PRIORITY_THIRD);
	while (pObject != nullptr)
	{
		if (pObject == this)
		{
			pObject = pObject->GetNext();
			continue;
		}

		//オブジェクトのタイプを取得
		CObject::EObjType objType = pObject->GetObjType();

		if (objType == OBJTYPE_ENEMY)
		{	// オブジェクトタイプが敵の場合
			CEnemy *pObj = (CEnemy*)pObject;
			CEnemy::SModelData enemyModelData = *pObj->GetModelData(0);

			//モデルの半径
			D3DXVECTOR3 selfModelRadius = (m_modelData[0].maxModel - m_modelData[0].minModel) / 2;
			D3DXVECTOR3 enemyModelRadius = (enemyModelData.maxModel - enemyModelData.minModel) / 2;

			if (CUtility::isCircleCollision(m_objpos, selfModelRadius.x, pObj->GetPos(), enemyModelRadius.x))
			{	// 敵と敵が当たった場合
				m_fAttenuation = 0.0f;
			}
		}

		if (objType == OBJTYPE_PLAYER)
		{	//オブジェクトタイプがプレイヤーの場合
			CPlayer *pObj = (CPlayer*)pObject;
			CPlayer::SModelData playerModelData = *pObj->GetModelData(0);

			//モデルの半径
			D3DXVECTOR3 selfModelRadius = (m_modelData[0].maxModel - m_modelData[0].minModel) / 2;
			D3DXVECTOR3 playerModelRadius = (playerModelData.m_maxModel - playerModelData.m_minModel) / 2;

			if (CUtility::isCircleCollision(m_objpos, selfModelRadius.x, pObj->GetPos(), playerModelRadius.x))
			{	//プレイヤーと敵が当たった場合
				m_fAttenuation = 0.0f;
			}

			if (m_info.visionValue.empty())
			{	// 設定された挙動の範囲の数値が存在しない場合
				pObject = pObject->GetNext();
				continue;
			}

			for (size_t i = 0; i < m_info.visionValue.size(); i++)
			{
				if (CUtility::isCircleCollision(m_objpos, m_info.visionValue[i], pObj->GetPos(), playerModelRadius.x))
				{	//プレイヤーが敵の判定の範囲内だった場合
					Behavior(i);
				}
			}
		}

		pObject = pObject->GetNext();
	}

	if (m_posOld != m_objpos)
	{
		Motion(MOTION_MOVE);
	}
	else
	{
		Motion(MOTION_NEUTRAL);
	}

	EnemyState();

	m_pHp->SetPos(D3DXVECTOR3(m_objpos.x, m_objpos.y + 50.0f, m_objpos.z));
	m_pHp->SetValue(m_info.life);

	//目的の方向の正規化
	if (m_rotDest.y - m_rot.y > D3DX_PI)
	{
		m_rotDest.y -= D3DX_PI * 2;
	}

	else if (m_rotDest.y - m_rot.y < -D3DX_PI)
	{
		m_rotDest.y += D3DX_PI * 2;
	}

	//======================
	//正規化
	//======================
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2;
	}

	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}

	if (m_objpos.y <= -100.0f)
	{
		Destroy();
	}

	if (m_info.life <= 0)
	{
		CApplication::GetInstance()->GetMode()->GetGame()->AddKillCount();
		std::vector<std::string> list;

		int expNum = pPlayer->GetNumExpGauge();
		CGauge *pGauge = pPlayer->GetExpGauge(expNum);
		pGauge->AddValue(m_info.exp);

		CApplication::GetInstance()->GetMode()->GetGame()->GetScore()->AddValue(m_info.score);

		////パーティクル（適当
		//CParticle::SInfo particle = {};
		//particle.pos = m_objpos;
		//particle.scale = D3DXVECTOR3(35.0f,35.0f,0.0f);
		//particle.col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		//particle.destCol = D3DXCOLOR(1.0f, 0.5f, 0.0f, 0.0f);
		//particle.colAttenuation = 0.8f;
		//particle.destroyTime = 70;
		//particle.rotateValue = 0.1f;
		//particle.fallDelayTime = 35;
		//particle.weight = 0.5f;

		//CUtility::stringMultiPush(list, "Rotate, ColorTransition, Gravity");
		//particle.infoProperty = list;

		//int popParticle = 10;

		//for (int i = 0; i < popParticle; i++)
		//{
		//	particle.move = D3DXVECTOR3(-sinf((i * ((360 / popParticle) * (D3DX_PI / 180)))), 1.5f, -cosf((i * ((360 / popParticle) * (D3DX_PI / 180))))) * 2.5f;
		//	CParticle::Create(particle, "STAR2", CObject::PRIORITY_THIRD);
		//}

		CParticleEmitter *pEmitter = CParticleEmitter::Create("Attack");
		pEmitter->SetPos(m_objpos);

		CItem::Create(m_objpos);

		Destroy();
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 敵の描画
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CEnemy::Draw()
{
	D3DXVECTOR3 playerPos = CApplication::GetInstance()->GetMode()->GetGame()->GetPlayer()->GetPos();
	D3DXVECTOR3 distance = playerPos - m_objpos;

	if (distance.x > 500.0f && distance.y > 350.0f && distance.z > 500.0f)
	{
		return;
	}

	// デバイスのポインタを取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス

	//ワールドマトリックスを初期化
	D3DXMatrixIdentity(&m_enemymtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_enemymtxWorld, &m_enemymtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_objpos.x, m_objpos.y, m_objpos.z);
	D3DXMatrixMultiply(&m_enemymtxWorld, &m_enemymtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_enemymtxWorld);

	if (m_pMotionModel->GetMotion() != nullptr)
	{// パーツの描画設定
		m_pMotionModel->GetMotion()->SetParts(m_enemymtxWorld);
	}

	//プレイヤーの位置反映の設定
	//EnemyMtx();

	////モデルの描画
	//ModelDraw();
}

void CEnemy::Behavior(int idx)
{
	if (m_info.behavior.empty())
	{
		return;
	}

	CPlayer *pPlayer = CApplication::GetInstance()->GetMode()->GetGame()->GetPlayer();

	// 追従
	if (m_info.behavior[idx] == "Adulation")
	{
		D3DXVECTOR3 playerPos = pPlayer->GetPos();

		D3DXVECTOR3 vec = D3DXVECTOR3(playerPos.x, playerPos.y + m_move.y, playerPos.z) - m_objpos;
		D3DXVec3Normalize(&vec, &vec);

		//敵の移動
		m_objpos += vec * m_fAttenuation;

		float rotX = playerPos.x - m_objpos.x;
		float rotZ = playerPos.z - m_objpos.z;

		//向きの計算
		float angle = atan2f(rotX, rotZ) + D3DX_PI;
		m_rot = D3DXVECTOR3(0.0f, angle, 0.0f);
	}

	// 攻撃
	if (m_info.behavior[idx] == "Attack")
	{
		m_attackCnt++;
		if (m_info.coolTime >= m_attackCnt)
		{
			return;
		}

		Motion(MOTION_ATTACK);
		m_transitionTime = 20;
		int damage = -(m_info.power);

		if (!pPlayer->GetInvincible())
		{	// 無敵状態ではない場合
			pPlayer->SetSpeed(0.5f);
			pPlayer->GetHPGauge()->AddValue(damage);
			pPlayer->SetLife(pPlayer->GetHPGauge()->GetValue());
		}

		m_attackCnt = 0;
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 敵の位置のマトリックス設定
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CEnemy::EnemyMtx()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス

	//ワールドマトリックスを初期化
	D3DXMatrixIdentity(&m_enemymtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_enemymtxWorld, &m_enemymtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_objpos.x, m_objpos.y, m_objpos.z);
	D3DXMatrixMultiply(&m_enemymtxWorld, &m_enemymtxWorld, &mtxTrans);

	//Zテスト
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_enemymtxWorld);
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 敵のモデルのマトリックスを設定
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CEnemy::ModelDraw()
{
	for (unsigned int i = 0; i < m_modelData.size(); i++)
	{
		LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得
		D3DXMATRIX parent = m_enemymtxWorld;

		D3DXMATRIX mtxRot, mtxTrans, mtxScale;			//計算用マトリックス
		D3DMATERIAL9 matDef;							//現在のマテリアルを保存
		D3DXMATERIAL *pMat;								//マテリアルデータへのポインタ

		//テクスチャの設定を戻す
		pDevice->SetTexture(0, NULL);

		//ワールドマトリックスを初期化
		D3DXMatrixIdentity(&m_mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_modelData[i].rotOffset.y, m_modelData[i].rotOffset.x, m_modelData[i].rotOffset.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, m_modelData[i].posOffset.x, m_modelData[i].posOffset.y, m_modelData[i].posOffset.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		// 行列拡縮関数
		D3DXMatrixScaling(&mtxScale, m_info.scale.x, m_info.scale.y, m_info.scale.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

		//親のマトリックスをプレイヤーにする
		pDevice->GetTransform(D3DTS_WORLD, &parent);

		//親のマトリックスとかけ合わせる
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &parent);

		//Zテスト
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

		//モデルの影
		//Shadow();

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//現在のマテリアルを保存
		pDevice->GetMaterial(&matDef);

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)m_modelData[i].buffMat->GetBufferPointer();

		for (unsigned int j = 0; j < m_modelData[i].dwNum; j++)
		{
			//マテリアルの設定
			pDevice->SetMaterial(&pMat[j].MatD3D);

			D3DMATERIAL9 material = pMat[j].MatD3D;
			material.Diffuse = m_col;

			//マテリアルの設定
			pDevice->SetMaterial(&material);

			//モデルパーツの描画
			m_modelData[i].mesh->DrawSubset(j);
		}

		//保持していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 敵のモデルデータを取得
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CEnemy::LoadModel(std::string path)
{
	CModel *pModel = CApplication::GetInstance()->GetModel();
	SModelData data = {};

	data.mesh = pModel->GetMesh(path);
	data.buffMat = pModel->GetBuffMat(path);
	data.dwNum = pModel->GetModelNum(path);
	data.maxModel = pModel->GetMaxModel(path);
	data.minModel = pModel->GetMinModel(path);
	data.pVtxBuff = pModel->GetVtxBuff(path);
	data.pIdxBuff = pModel->GetIdxBuff(path);
	data.numVtx = pModel->GetVertexCount(path);
	data.numPrim = pModel->GetPrimitiveCount(path);

	m_modelData.push_back(data);
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 敵の状態変化
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CEnemy::EnemyState()
{
	switch (m_state)
	{
	case CEnemy::STATE_DAMAGE:
		m_stateTime++;

		if ((m_stateTime % 10) == 0)
		{
			m_col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			m_state = CEnemy::STATE_DEFAULT;
		}
		break;

	default:
		m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_stateTime = 0;
		break;
	}
}

void CEnemy::Motion(EMotionType type)
{
	if (m_transitionTime >= 0)
	{
		return;
	}

	if (m_motionType == type)
	{	// 前回と同じモーションタイプだった場合
		return;
	}

	m_motionType = type;
	m_pMotionModel->GetMotion()->SetNumMotion(type);
}