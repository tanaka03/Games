#include "beam.h"
#include "utility.h"
#include "application.h"
#include "debugproc.h"
#include "game.h"
#include "enemy.h"
#include "3deffect_emitter.h"
#include "player.h"
#include "enemy.h"
#include "number.h"
#include "sound.h"
#include "3deffect.h"
#include "sp.h"
#include "number.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ビームのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CBeam::CBeam() :
	m_scale(1.0f)
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ビームのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CBeam::~CBeam()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ビームの生成
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CBeam * CBeam::Create(const D3DXVECTOR3 pos, int time, int priority)
{
	CBeam *pSkill = nullptr;
	pSkill = new CBeam;

	//ヌルチェック
	if (pSkill != nullptr)
	{
		pSkill->m_pos = pos;
		pSkill->m_enableTime = time;
		pSkill->Init();
	}

	return pSkill;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ビームの初期化
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
HRESULT CBeam::Init()
{
	m_p3DEffect = C3DEffectEmitter::Create("Beam");

	CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_SE_BEAM);
	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ビームの終了
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CBeam::Uninit()
{
	if (m_p3DEffect != nullptr)
	{
		m_p3DEffect->Uninit();
		delete m_p3DEffect;
		m_p3DEffect = nullptr;
	}

	// 死亡フラグ
	Destroy();
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ビームの更新
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CBeam::Update()
{
	CPlayer *pPlayer = CApplication::GetInstance()->GetMode()->GetGame()->GetPlayer();
	CGame *pGame = CApplication::GetInstance()->GetMode()->GetGame();

	m_p3DEffect->Update();
	m_p3DEffect->SetPos(D3DXVECTOR3(0.0f,150.0f,0.0f));

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
		D3DXVECTOR3 enemySize = (enemyModelData.maxModel + enemyModelData.minModel);

		if (CUtility::isCrossCollision(pObj->GetPos(), D3DXVECTOR3(-100.0f,0.0f,-900.0f), D3DXVECTOR3(100.0f,0.0f, 50.0f), m_p3DEffect->GetEffect(0)->GetMtxWorld()))
		{	// プレイヤーと敵が当たった場合
			CApplication::GetInstance()->GetMode()->GetGame()->GetCombo()->AddValue(1);
			pObj->SetState(CEnemy::STATE_DAMAGE);
			pObj->AddLife(-(pPlayer->GetPower() + 10));

			m_pDamage = CNumber::Create(D3DXVECTOR3(pObj->GetPos().x, pObj->GetPos().y + 70.0f, pObj->GetPos().z), D3DXVECTOR2(15.0f, 15.0f), CNumber::NUMBER_DAMAGE, "NUMBER2", 3, CObject::PRIORITY_THIRD);
			m_pDamage->SetValue((pPlayer->GetPower() + 10));

			pPlayer->GetSPGauge()->AddValue(roundf(pGame->GetCombo()->GetValue() * 0.5f));
		}

		// ポインタを次に進める
		pObject = pObject->GetNext();
	}

	// スキルの生存時間
	m_time++;
	if (m_time > m_enableTime)
	{
		// エフェクト
		{
			C3DEffect::SInfo info = {};
			info.beginScale = D3DXVECTOR3(10.0f, 1.0f, 10.0f);
			info.beginRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			info.col = D3DXCOLOR(0.0f, 0.5f, 0.5f, 1.0f);
			info.transitionCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			info.alphaAttenuation = 0.005f;
			info.scalingValue = D3DXVECTOR3(0.3f, 0.0f, 0.3f);
			info.rotateValue = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			info.life = 60;
			info.tractPlayer = true;
			info.modelShape = "CIRCLE";
			info.texTag = "CIRCLE";

			C3DEffect::Create(info);
		}

		Destroy();
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ビームの判定
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
bool CBeam::Collision(D3DXVECTOR3 destPos, D3DXVECTOR3 size)
{
	CPlayer *pPlayer = CApplication::GetInstance()->GetMode()->GetGame()->GetPlayer();

	D3DXMATRIX mtx = m_p3DEffect->GetEffect(0)->GetMtxWorld();
	D3DXVECTOR3 pos = pPlayer->GetPos();

	D3DXVECTOR3 minModel = D3DXVECTOR3(-1.0f, -15.0f,-1.0f);
	D3DXVECTOR3 maxModel = D3DXVECTOR3(1.0f, 10.0f, 1.0f);

	D3DXMATRIX invMtx;
	D3DXVECTOR3 localPos;
	D3DXVECTOR3 worldPos;

	// ワールド座標を計算
	D3DXVec3TransformCoord(&worldPos, &pos, &mtx);

	// 逆行列にする
	D3DXMatrixInverse(&invMtx, NULL, &mtx);

	// 逆行列計算をした行列をローカル座標変換
	D3DXVec3TransformCoord(&localPos, &worldPos, &invMtx);

	float fLeft = localPos.x + minModel.x;		//左
	float fRight = localPos.x + maxModel.x;	//右
	float fTop = localPos.y + maxModel.y;		//上
	float fBottom = localPos.y + minModel.y;	//下
	float fFront = localPos.z + minModel.z;	//前
	float fBehind = localPos.z + maxModel.z;	//後

		//前後
	if (fFront <= destPos.z - (size.z / 2)
		&& fBehind >= destPos.z + (size.z / 2))
	{
		//左から右
		if (fLeft < destPos.x + (size.x / 2))
		{
			return true;
		}

		//右から左
		else if (fRight > destPos.x - (size.x / 2))
		{
			return true;
		}
	}

	//左右
	if (fLeft < destPos.x - (size.x / 2)
		&& fRight > destPos.x + (size.x / 2))
	{
		//前から後
		if (fFront < destPos.z + (size.z / 2))
		{
			return true;
		}

		//後から前
		else if (fBehind > destPos.z - (size.z / 2))
		{
			return true;
		}
	}

	return false;
}