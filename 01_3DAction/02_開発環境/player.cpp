//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// プレイヤー操作処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#include <stdlib.h>
#include "object3d.h"
#include "application.h"
#include "input.h"
#include "keyboard.h"
#include "player.h"
#include "camera.h"
#include "debugproc.h"
#include "model.h"
#include "meshfield.h"
#include "utility.h"
#include "enemy.h"
#include "bullet.h"
#include "game.h"
#include "3dgauge.h"
#include "gauge.h"
#include "stage.h"
#include "3deffect_emitter.h"
#include "motion_model3D.h"
#include "motion.h"
#include "parts.h"
#include "number.h"
#include "sp.h"
#include "3deffect.h"
#include "ability_select.h"
#include "sound.h"
#include "particle_emitter.h"

#include "field_damage.h"
#include "beam.h"
#include "crystal.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// プレイヤーのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CPlayer::CPlayer() : 
	m_time(0),
	m_basicPower(1),
	m_attackSpeed(15),
	m_life(100),
	m_basicWalkSpeed(8.0f),
	m_bCollision(false),
	m_event(EVENT_NONE)
{
	SetObjType(OBJTYPE_PLAYER);
	SetObjState(CObject::OBJSTATE_3D);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bJump = false;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// プレイヤーのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CPlayer::~CPlayer()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// プレイヤーの生成
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CPlayer * CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer *pPlayer = nullptr;
	pPlayer = new CPlayer;

	//ヌルチェック
	if (pPlayer != nullptr)
	{
		// ポリゴンの初期化処理
		pPlayer->SetPos(pos);
		pPlayer->Init();
	}

	return pPlayer;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// プレイヤーの初期化
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
HRESULT CPlayer::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	//モデルのロード
	m_pMotionModel = CMotionModel3D::Create();
	m_pMotionModel->SetMotion("data/MODEL/Player2/motion.txt");

	for (int i = 0; i < m_pMotionModel->GetMotion()->GetMaxParts(); i++)
	{
		m_pMotionModel->GetMotion()->GetParts(i)->Init();
	}

	m_modelData.resize(1);
	m_modelData[0].m_minModel = m_pMotionModel->GetMinVtx();
	m_modelData[0].m_maxModel = m_pMotionModel->GetMaxVtx();

	m_beginPos = m_objpos;

	m_pExp.resize(4);
	m_pExp[0] = CGauge::Create(D3DXVECTOR3((float)SCREEN_WIDTH / 2 , 5.0f,0.0f), 0.0f, D3DXVECTOR2((float)SCREEN_WIDTH,5.0f), D3DXCOLOR(0.0f,1.0f,0.5f,1.0f), CGauge::GAUGETYPE_EXP, CObject::PRIORITY_FOURTH);
	m_pExp[1] = CGauge::Create(D3DXVECTOR3((float)SCREEN_HEIGHT / 2, (float)-SCREEN_WIDTH + 5.0f, 0.0f), 90.0f, D3DXVECTOR2((float)SCREEN_HEIGHT, 5.0f), D3DXCOLOR(0.0f, 1.0f, 0.5f, 1.0f), CGauge::GAUGETYPE_EXP, CObject::PRIORITY_FOURTH);
	m_pExp[2] = CGauge::Create(D3DXVECTOR3((float)-SCREEN_WIDTH / 2, (float)-SCREEN_HEIGHT + 5.0f, 0.0f), 180.0f, D3DXVECTOR2((float)SCREEN_WIDTH, 5.0f), D3DXCOLOR(0.0f, 1.0f, 0.5f, 1.0f), CGauge::GAUGETYPE_EXP, CObject::PRIORITY_FOURTH);
	m_pExp[3] = CGauge::Create(D3DXVECTOR3((float)-SCREEN_HEIGHT / 2, 5.0f, 0.0f), 270.0f, D3DXVECTOR2((float)SCREEN_HEIGHT, 5.0f), D3DXCOLOR(0.0f, 1.0f, 0.5f, 1.0f), CGauge::GAUGETYPE_EXP, CObject::PRIORITY_FOURTH);

	m_pHp = C3DGauge::Create(m_objpos, D3DXVECTOR3(50.0f,5.0f,0.0f), D3DXCOLOR(0.0f,1.0f,1.0f,1.0f), C3DGauge::GAUGETYPE_HP, CObject::PRIORITY_THIRD);
	m_pHp->ValueSetting(100);

	m_pSp = CGauge::Create(D3DXVECTOR3(270.0f, 100.0f, 0.0f), 0.0f, D3DXVECTOR2(250.0f, 10.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), CGauge::GAUGETYPE_SP, CObject::PRIORITY_THIRD);
	m_pSp->SetValue(0);
	m_pSp->SetMaxValue(100);

	m_numExpGauge = 0;

	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// プレイヤーの終了
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CPlayer::Uninit()
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

	Destroy();
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// プレイヤーの更新
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CPlayer::Update()
{
	// モデルの大きさの半分を計算する処理
	auto center = [](SModelData data) {
		return data.m_maxModel - data.m_minModel;
	};

	m_pMotionModel->Update();

	m_posOld = m_objpos;
	m_objpos += m_move;

	//----------------------------------------------------------
	// 衝突判定
	//----------------------------------------------------------
	CMeshField *pMesh = CApplication::GetInstance()->GetMode()->GetGame()->GetMeshField();
	bool collision = pMesh->Collision(m_objpos);

	CStage *pStage = CApplication::GetInstance()->GetMode()->GetGame()->GetStage();
	bool stagecollision = pStage->GetCollision();

	m_bJump = false;

	if (collision)
	{
		if (m_event != EVENT_JUMPING)
		{
			D3DXVECTOR3 collisionPos = pMesh->GetHitPos();
			m_move.y = 0.0f;
			m_objpos = D3DXVECTOR3(m_objpos.x, collisionPos.y, m_objpos.z);
			m_bJump = true;
		}
	}
	else if (stagecollision)
	{
		if (m_event != EVENT_JUMPING)
		{
			D3DXVECTOR3 collisionPos = pStage->GetCollisionPos();
			m_move.y = 0.0f;
			m_objpos = D3DXVECTOR3(m_objpos.x, collisionPos.y, m_objpos.z);
			m_bJump = true;
		}
	}
	else
	{
		m_move.y -= 0.5f;
	}

	//----------------------------------------------------------

	// プレイヤー行動処理
	Action();

	// 無敵状態の処理
	Invincible();

	// モーションの遷移関係
	if (m_transitionTime >= 0)
	{
		m_transitionTime--;
	}

	m_fSpeed = m_basicWalkSpeed;

	// スキル
	if (m_skill.m_damageField)
	{
		if ((m_time % 100) == 0)
		{
			CDamageField::Create(m_objpos, CObject::PRIORITY_THIRD);
		}
	}

	m_time++;

	if (m_objpos.y <= -300.0f)
	{
		m_objpos = m_beginPos;
	}

	//----------------------------------------------------------
	//正規化
	//----------------------------------------------------------

	// 目的の向きの正規化
	if (m_rotDest.x - m_rot.x > D3DX_PI)
	{
		m_rotDest.x -= D3DX_PI * 2;
	}

	else if (m_rotDest.x - m_rot.x < -D3DX_PI)
	{
		m_rotDest.x += D3DX_PI * 2;
	}

	if (m_rotDest.y - m_rot.y > D3DX_PI)
	{
		m_rotDest.y -= D3DX_PI * 2;
	}

	else if (m_rotDest.y - m_rot.y < -D3DX_PI)
	{
		m_rotDest.y += D3DX_PI * 2;
	}

	//モデルの回転の慣性
	m_rot.x += (m_rotDest.x - m_rot.x) * 0.1f;
	m_rot.y += (m_rotDest.y - m_rot.y) * 0.1f;

	// 向きの正規化
	CUtility::angleNormalize(m_rot.y);

	//----------------------------------------------------------
	// ゲージの処理
	//----------------------------------------------------------
	static int cntRankUp;
	{
		m_pExp[m_numExpGauge]->SetMaxValue(2 + cntRankUp);

		if (m_pExp[m_numExpGauge]->GetMaxValue() <= m_pExp[m_numExpGauge]->GetValue())
		{
			if (m_numExpGauge >= (int)m_pExp.size() - 1)
			{
				m_numExpGauge = 0;

				CApplication::GetInstance()->GetMode()->GetGame()->GetAbilitySelect()->Start();

				for (size_t i = 0; i < m_pExp.size(); i++)
				{
					m_pExp[i]->SetValue(0);
					cntRankUp++;
				}
			}
			else
			{
				m_numExpGauge++;
			}
		}
	}

	m_pHp->SetPos(D3DXVECTOR3(m_objpos.x, m_objpos.y + 90.0f, m_objpos.z));

	if (m_pSp->GetValue() >= m_pSp->GetMaxValue())
	{
		CCrystal::Create(m_objpos, PRIORITY_THIRD);
		m_pSp->SetValue(0);
	}

	// プレイヤー死亡処理
	if (m_life <= 0)
	{
		CPlayer::Destroy();
		CApplication::GetInstance()->GetMode()->GetGame()->SetDeath(true);
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// プレイヤーの描画
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CPlayer::Draw()
{
	// デバイスのポインタを取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス

	// ワールドマトリックスを初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_objpos.x, m_objpos.y, m_objpos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	if (m_pMotionModel->GetMotion() != nullptr)
	{	// パーツの描画設定
		m_pMotionModel->GetMotion()->SetParts(m_mtxWorld);
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// プレイヤーのモデルデータを取得
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CPlayer::LoadModel(std::string path)
{
	// モデルデータのポインタを取得
	CModel *pModel = CApplication::GetInstance()->GetModel();

	SModelData data = {};

	data.m_mesh = pModel->GetMesh(path);
	data.m_buffMat = pModel->GetBuffMat(path);
	data.m_dwNum = pModel->GetModelNum(path);
	data.m_maxModel = pModel->GetMaxModel(path);
	data.m_minModel = pModel->GetMinModel(path);
	data.m_pVtxBuff = pModel->GetVtxBuff(path);
	data.m_pIdxBuff = pModel->GetIdxBuff(path);
	data.m_numVtx = pModel->GetVertexCount(path);
	data.m_numPrim = pModel->GetPrimitiveCount(path);

	m_modelData.push_back(data);
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// プレイヤーの入力情報による行動
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CPlayer::Action()
{
	CCamera *pCamera = CApplication::GetInstance()->GetCamera();
	CCamera::CAMERA *camera = pCamera->GetCamera();

	D3DXVECTOR3 vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//----------------------------------------------------------
	// 攻撃関係
	//----------------------------------------------------------

	if (CApplication::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{
		Motion(MOTION_NEUTRAL);
		Attack();
	}

	// 攻撃のクールタイムカウント
	m_coolTime--;
	if (m_coolTime <= 0)
	{
		m_attackType = ATTACK_FIRST;
	}

	//----------------------------------------------------------
	// 移動関係
	//----------------------------------------------------------

	// 奥
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_W))
	{
		Motion(MOTION_MOVE);
		vec = D3DXVECTOR3(-(sinf(camera->rot.y + D3DX_PI * 0.0f) * m_fSpeed), 0.0f, -(cosf(camera->rot.y + D3DX_PI * 0.0f) * m_fSpeed));
		m_rotDest.y = camera->rot.y + D3DX_PI * 0.0f;				//目的の角度

		// 右奥
		if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_D))
			vec = D3DXVECTOR3(-(sinf(camera->rot.y + D3DX_PI * 0.25f) * m_fSpeed), 0.0f, -(cosf(camera->rot.y + D3DX_PI * 0.25f) * m_fSpeed)),
			m_rotDest.y = camera->rot.y + D3DX_PI * 0.25f;

		// 左奥
		else if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_A))
			vec = D3DXVECTOR3((sinf(camera->rot.y + D3DX_PI * 0.75f) * m_fSpeed), 0.0f, (cosf(camera->rot.y + D3DX_PI * 0.75f) * m_fSpeed)),
			m_rotDest.y = camera->rot.y - D3DX_PI * 0.25f;
	}

	// 後
	else if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_S))
	{
		Motion(MOTION_MOVE);
		vec = D3DXVECTOR3((sinf(camera->rot.y + D3DX_PI * 0.0f) * m_fSpeed), 0.0f, (cosf(camera->rot.y + D3DX_PI * 0.0f) * m_fSpeed));
		m_rotDest.y = camera->rot.y - D3DX_PI * 1.0f;

		// 右後
		if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_D))
			vec = D3DXVECTOR3(-(sinf(camera->rot.y + D3DX_PI * 0.75f) * m_fSpeed), 0.0f, -(cosf(camera->rot.y + D3DX_PI * 0.75f) * m_fSpeed)),
			m_rotDest.y = camera->rot.y + D3DX_PI * 0.75f;

		// 左後
		else if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_A))
			vec = D3DXVECTOR3((sinf(camera->rot.y + D3DX_PI * 0.25f) * m_fSpeed), 0.0f, (cosf(camera->rot.y + D3DX_PI * 0.25f) * m_fSpeed)),
			m_rotDest.y = camera->rot.y - D3DX_PI * 0.75f;
	}

	// 右
	else if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_D))
	{
		Motion(MOTION_MOVE);
		vec = D3DXVECTOR3(-(sinf(camera->rot.y + D3DX_PI * 0.5f) * m_fSpeed), 0.0f, -(cosf(camera->rot.y + D3DX_PI * 0.5f) * m_fSpeed));
		m_rotDest.y = camera->rot.y + D3DX_PI * 0.5f;
	}

	// 左
	else if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_A))
	{
		Motion(MOTION_MOVE);
		vec = D3DXVECTOR3((sinf(camera->rot.y + D3DX_PI * 0.5f) * m_fSpeed), 0.0f, (cosf(camera->rot.y + D3DX_PI * 0.5f) * m_fSpeed));
		m_rotDest.y = camera->rot.y - D3DX_PI * 0.5f;
	}

	m_objpos.x += vec.x;
	m_objpos.z += vec.z;
	m_vec = vec;

	// ジャンプ
	if (m_bJump)
	{
		if (CApplication::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_SPACE))
		{
			m_move.y = ((m_move.y + 25.0f) - m_move.y) * 0.4f;
			m_event = EVENT_JUMPING;
		}
	}

	if (m_objpos != m_posOld)
	{
		if (m_event == EVENT_JUMPING)
		{
			Motion(MOTION_JUMP);
		}
	}
	else
	{
		Motion(MOTION_NEUTRAL);
	}

	switch (m_event)
	{
	case EVENT_JUMPING:
		if (m_move.y < 0)
		{
			m_event = EVENT_FALLING;
		}
		break;

	default:
		break;
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// プレイヤーの攻撃
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CPlayer::Attack()
{
	// 攻撃の判定などのパラメータ設定処理
	auto paramSet = [this](int power, int transTime, int invTime, float hitRad, bool invincible, EAttack Next) {
		m_hitPower = power;
		m_transitionTime = transTime;
		m_invincibleTime = invTime;
		m_hitRadius = hitRad;
		m_invincible = invincible;
		m_attackType = Next;
	};

	// モーションが終わるまで攻撃不可
	if (m_transitionTime > 0)
	{
		return;
	}

	CGame *pGame = CApplication::GetInstance()->GetMode()->GetGame();
	int coolTimeDiv = 40;

	switch (m_attackType)
	{
	case ATTACK_FIRST:
		Motion(MOTION_ATTACK);
		CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_SE_PUNCH);
		paramSet(0, 40, 90, 35.0f, true, ATTACK_SECOND);
		m_coolTime = m_invincibleTime + coolTimeDiv;
		break;

	case ATTACK_SECOND:
		Motion(MOTION_ATTACK2);
		CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_SE_STRIKE);
		paramSet(3, 40, 110, 45.0f, true, ATTACK_THIRD);
		m_coolTime = m_invincibleTime + coolTimeDiv;
		break;

	case ATTACK_THIRD:
		Motion(MOTION_ATTACK3);
		CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_SE_KICK);

		if (m_skill.m_beam)	paramSet(10, 80, 120, 110.0f, true, ATTACK_BEAM);
		else				paramSet(12, 120, 100, 150.0f, true, ATTACK_FIRST);

		m_coolTime = m_invincibleTime + coolTimeDiv;
		break;

	case ATTACK_BEAM:
		Motion(MOTION_ATTACK4);
		m_pSkill = CBeam::Create(D3DXVECTOR3(m_objpos.x, m_objpos.y + 70.0f, m_objpos.z), 120, CObject::PRIORITY_THIRD);
		paramSet(12, 120, 140, 150.0f, true, ATTACK_FIRST);
		m_coolTime = m_invincibleTime + coolTimeDiv;
		break;

	default:
		break;
	}

	// 敵とプレイヤーの当たり判定
	CObject *pObject = CObject::GetTop(PRIORITY_THIRD);
	while (pObject != nullptr)
	{
		if (pObject == this)
		{
			pObject = pObject->GetNext();
			continue;
		}

		// オブジェクトのタイプを取得
		CObject::EObjType objType = pObject->GetObjType();

		if (objType != OBJTYPE_ENEMY)
		{
			pObject = pObject->GetNext();
			continue;
		}

		// オブジェクトタイプがプレイヤーの場合通る

		CEnemy *pObj = (CEnemy*)pObject;
		CEnemy::SModelData enemyModelData = *pObj->GetModelData(0);

		// モデルの半径
		D3DXVECTOR3 enemyModelRadius = (enemyModelData.maxModel - enemyModelData.minModel) / 2;

		if (CUtility::isCircleCollision(m_objpos, m_hitRadius, pObj->GetPos(), enemyModelRadius.x))
		{	// プレイヤーと敵が当たった場合
			CApplication::GetInstance()->GetMode()->GetGame()->GetCombo()->AddValue(1);
			pObj->SetState(CEnemy::STATE_DAMAGE);
			pObj->AddLife(-(m_basicPower + m_hitPower));

			m_pDamage = CNumber::Create(D3DXVECTOR3(pObj->GetPos().x, pObj->GetPos().y + 50.0f, pObj->GetPos().z), D3DXVECTOR2(15.0f, 15.0f), CNumber::NUMBER_DAMAGE, "NUMBER2", 3, CObject::PRIORITY_THIRD);
			m_pDamage->SetValue((m_basicPower + m_hitPower));

			m_pSp->AddValue(round((float)pGame->GetCombo()->GetValue() * 0.5f));
		}

		// ポインタを次に進める
		pObject = pObject->GetNext();
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// プレイヤーのモーション遷移
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CPlayer::Motion(EMotionType type)
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
	m_pMotionModel->GetMotion()->SetNumMotion(m_motionType);
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// プレイヤーの無敵状態の処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CPlayer::Invincible()
{
	if (m_invincibleTime >= 0)
	{
		m_invincibleTime--;
		return;
	}

	m_invincible = false;
}