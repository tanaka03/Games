#include "bullet.h"
#include "object3d.h"
#include "enemy.h"
#include "utility.h"
#include "application.h"
#include "game.h"
#include "combo.h"
#include "mode.h"
#include "player.h"
#include "gauge.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 弾のコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CBullet::CBullet(int priority) : CBillboard(CObject::PRIORITY_THIRD)
{
	SetObjType(OBJTYPE_BULLET);
	m_life = 0;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 弾のデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CBullet::~CBullet()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 弾の生成
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int life, int priority)
{
	CBullet *pObj = nullptr;
	pObj = new CBullet(priority);

	if (pObj != nullptr)
	{
		pObj->SetPos(pos);
		pObj->SetMove(move);
		pObj->SetLife(life);
		pObj->Init();
	}

	return pObj;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 弾の初期化
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
HRESULT CBullet::Init()
{
	SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetScale(D3DXVECTOR3(10.0f, 10.0f, 0.0f));
	CBillboard::BindTexture("BULLET");
	CBillboard::Init();
	SetBlend(BLEND_NONE);

	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 弾の終了
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CBullet::Uninit()
{
	CBillboard::Uninit();
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 弾の更新
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CBullet::Update()
{
	CGame *pGame = CApplication::GetInstance()->GetMode()->GetGame();
	CPlayer *pPlayer = pGame->GetPlayer();

	CBillboard::Update();

	D3DXVECTOR3 pos = CBillboard::GetPos();

	// 敵と弾の当たり判定
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

		if (CUtility::isCircleCollision(pos, 20.0f, pObj->GetPos(), enemyModelRadius.x))
		{	// プレイヤーと敵が当たった場合
			CApplication::GetInstance()->GetMode()->GetGame()->GetCombo()->AddValue(1);
			pObj->SetState(CEnemy::STATE_DAMAGE);
			pObj->AddLife(-(pPlayer->GetPower()));
			this->Destroy();
		}

		// ポインタを次に進める
		pObject = pObject->GetNext();
	}

	m_life--;
	if (m_life <= 0)
	{
		Uninit();
		return;
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 弾の描画
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CBullet::Draw()
{
	// デバイスのポインタを取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	// ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// アルファテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	CBillboard::Draw();

	// ライトを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// アルファテストを無効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}