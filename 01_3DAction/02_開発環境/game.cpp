#include "game.h"
#include "file.h"
#include "player.h"
#include "meshfield.h"
#include "application.h"
#include "input.h"
#include "keyboard.h"
#include "light.h"
#include "application.h"
#include "camera.h"
#include "enemy.h"
#include "combo.h"
#include "2deffect.h"
#include "utility.h"
#include "stage.h"
#include "ability_select.h"
#include "enemy_emitter.h"
#include "sound.h"

#include "depthbuffershadow.h"
#include "lambert.h"
#include "shadow.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//ゲームのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CGame::CGame() : m_nTime(0),
m_stopTimer(false)
{
	m_killCnt = 0;
	m_bClear = false;
	m_bDeath = false;
	m_comboDisappear = false;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//ゲームのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CGame::~CGame()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//ゲームの初期化処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
HRESULT CGame::Init()
{
	//ライトクラスの生成
	m_pLight = new CLight;
	m_pLight->Init();

	m_pDepthBuffShadow = new CDepthBufferShadow();
	m_pDepthBuffShadow->Load();

	m_pLambert = new CLambert();
	m_pLambert->Load();

	m_pShadow = new CShadow();
	m_pShadow->CreateZTexture();

	// プレイヤーの生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(-100.0f, 100.0f, 0.0f));

	// メッシュの生成
	m_pMesh = CMeshField::Create(D3DXVECTOR3(-10.0f, 0.0f, 5.0f), D3DXVECTOR3(3500.0f, 0.0f, 3500.0f), 20, 20);

	// アビリティの生成
	m_pAbilitySelect = CAbilitySelect::Create();

	// エネミーエミッタの生成
	m_pEnemyEmitter = CEnemyEmitter::Create();

	// ステージの生成
	m_pStage = CStage::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	CObject2D::Create(D3DXVECTOR3(1080.0f, 70.0f, 0.0f), D3DXVECTOR2(200.0f, 60.0f), "BLUEFRAME", CObject::PRIORITY_THIRD, D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.6f));
	CObject2D::Create(D3DXVECTOR3(230.0f, 70.0f, 0.0f), D3DXVECTOR2(240.0f, 60.0f), "BLUEFRAME", CObject::PRIORITY_THIRD, D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.6f));

	// コンボの生成
	CObject2D::Create(D3DXVECTOR3(1145.0f, 50.0f, 0.0f), D3DXVECTOR2(80.0f, 40.0f), "NUMBERFRAME", CObject::PRIORITY_THIRD, D3DXCOLOR(1.0f, 0.8f, 0.0f, 0.8f));
	m_pNumber = CNumber::Create(D3DXVECTOR3(1100.0f, 50.0f, 0.0f), D3DXVECTOR2(15.0f, 20.0f), CNumber::NUMBER_COMBO, "NUMBER2", 4, CObject::PRIORITY_THIRD);
	m_pNumber->SetValue(0);
	m_pNumber->SetTime(600);
	CObject2D::Create(D3DXVECTOR3(990.0f, 50.0f, 0.0f), D3DXVECTOR2(80.0f, 40.0f), "TEXT_COMBO", CObject::PRIORITY_THIRD, D3DXCOLOR(1.0f, 0.8f, 0.0f, 1.0f));

	// スコアの生成
	CObject2D::Create(D3DXVECTOR3(275.0f, 50.0f, 0.0f), D3DXVECTOR2(145.0f, 40.0f), "NUMBERFRAME", CObject::PRIORITY_THIRD, D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.8f));
	m_pScore = CNumber::Create(D3DXVECTOR3(170.0f, 50.0f, 0.0f), D3DXVECTOR2(15.0f, 20.0f), CNumber::NUMBER_SCORE, "NUMBER2", 8, CObject::PRIORITY_FOURTH);
	m_pScore->SetValue(0);
	CObject2D::Create(D3DXVECTOR3(80.0f, 50.0f, 0.0f), D3DXVECTOR2(80.0f, 40.0f), "TEXT_SCORE", CObject::PRIORITY_THIRD, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));

	// タイムの生成
	CObject2D::Create(D3DXVECTOR3(1145.0f, 100.0f, 0.0f), D3DXVECTOR2(80.0f, 40.0f), "NUMBERFRAME", CObject::PRIORITY_THIRD, D3DXCOLOR(1.0f, 0.5f, 0.0f, 0.8f));
	m_pTime = CNumber::Create(D3DXVECTOR3(1120.0f, 100.0f, 0.0f), D3DXVECTOR2(15.0f, 20.0f), CNumber::NUMBER_SCORE, "NUMBER2", 3, CObject::PRIORITY_FOURTH);
	m_pTime->SetValue(150);
	CObject2D::Create(D3DXVECTOR3(990.0f, 100.0f, 0.0f), D3DXVECTOR2(80.0f, 40.0f), "TEXT_TIME", CObject::PRIORITY_THIRD, D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f));

	// SPテキスト生成
	CObject2D::Create(D3DXVECTOR3(80.0f, 100.0f, 0.0f), D3DXVECTOR2(80.0f, 40.0f), "TEXT_SP", CObject::PRIORITY_THIRD, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));

	CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_STAGE1);

	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//ゲームの終了処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CGame::Uninit()
{
	CObject::ReleaseAll();

	// 影クラスの破棄
	if (m_pShadow != nullptr)
	{
		delete m_pShadow;
		m_pShadow = nullptr;
	}

	// ランバート照明の破棄
	if (m_pLambert != nullptr)
	{
		delete m_pLambert;
		m_pLambert = nullptr;
	}

	// Ｚバッファシャドウの破棄
	if (m_pDepthBuffShadow != nullptr)
	{
		delete m_pDepthBuffShadow;
		m_pDepthBuffShadow = nullptr;
	}

	// アビリティセレクトクラスの破棄
	if (m_pAbilitySelect != nullptr)
	{
		m_pAbilitySelect->AfterRelease();
		m_pAbilitySelect->Uninit();
		delete m_pAbilitySelect;
		m_pAbilitySelect = nullptr;
	}

	//エネミーエミッタクラスの破棄
	if (m_pEnemyEmitter != nullptr)
	{
		m_pEnemyEmitter->AfterRelease();
		m_pEnemyEmitter->Uninit();
		delete m_pEnemyEmitter;
		m_pEnemyEmitter = nullptr;
	}

	//ライトクラスの破棄
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//ゲームの更新処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CGame::Update()
{
	CApplication::GetInstance()->GetCamera()->Update();
	CApplication::GetInstance()->GetCamera()->SetCamera();

	if (!m_stopTimer)
	{
		m_nTime++;
	}

	if ((m_nTime % 60) == 0)
	{
		int currentTime = m_pTime->GetValue();
		currentTime--;
		m_pTime->SetValue(currentTime);
	}

	// コンボ関係
	{
		int value = m_pNumber->GetValue();
		int oldValue = m_pNumber->GetOldValue();

		if (value != oldValue)
		{	// 現在のコンボ数が変化した場合
			if (value == 0)
			{	// コンボ数が０の時は何もしない
				return;
			}

			std::vector<std::string> list;
			C2DEffect::SInfo effectData = {};

			effectData.pos = D3DXVECTOR3(1185.0f, 50.0f, 0.0f);
			effectData.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			effectData.col = D3DXCOLOR(0.5f, 1.0f, 0.0f, 1.0f);
			effectData.destCol = D3DXCOLOR(0.8f, 0.3f, 0.0f, 1.0f);
			effectData.destroyTime = 50;
			effectData.colAttenuation = 0.7f;
			effectData.scalingSpeed = 2.0f;

			CUtility::stringMultiPush(list, "ColorTransition, Scaling");
			effectData.infoProperty = list;

			C2DEffect::Create(effectData, "CIRCLE", CObject::PRIORITY_THIRD);

			m_pNumber->SetOldValue(value);
			m_pNumber->SetTime(300);
		}
	}

	if (m_comboDisappear)
	{
		m_pNumber->SetValue(1);
		m_pNumber->SetOldValue(1);
		m_comboDisappear = false;
	}

	if (m_pAbilitySelect != nullptr)
	{
		m_pAbilitySelect->Update();
	}

	if (m_pEnemyEmitter != nullptr)
	{
		m_pEnemyEmitter->Update();
	}

	static int gameEndTime;

	// プレイヤー死亡時
	if (m_bDeath)
	{
		CApplication::GetInstance()->GetSound()->Stop(CSound::LABEL_BGM_STAGE1);
		CApplication::GetInstance()->GetMode()->SetMode(MODE_CONTINUE);
	}
	else if (m_bClear || m_pTime->GetValue() == 0)
	{
		gameEndTime = m_nTime;
		CObject::PauseAll();

		// クリア時のバナー生成
		m_pEndBanner = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(720.0f, 300.0f), "CLEAR_BANNER", CObject::PRIORITY_FOURTH);
	}
	else if (m_bClear || m_pTime->GetValue() < 0)
	{
		if (m_pEndBanner->GetPos().x >= SCREEN_WIDTH / 2)
		{
			D3DXVECTOR3 bannerPos = m_pEndBanner->GetPos();
			bannerPos.x -= 18.0f;
			m_pEndBanner->SetPos(bannerPos);
		}

		if (m_nTime >= gameEndTime + 200)
		{
			CApplication::GetInstance()->GetSound()->Stop(CSound::LABEL_BGM_STAGE1);
			CApplication::GetInstance()->GetMode()->SetMode(MODE_RESULT);
		}
	}
}