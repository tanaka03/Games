#include "application.h"
#include "object2d.h"
#include "input.h"
#include "keyboard.h"
#include "texture.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// オブジェクト２Dのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CObject2D::CObject2D(int priority) :
	m_nCounterAnim(0),
	m_nPatternAnim(0),
	m_bAnimation(false),
	m_pTexture(nullptr)
{
	SetObjState(CObject::OBJSTATE_2D);
	m_col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	m_objpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntY = 0;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// オブジェクト２Dのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CObject2D::~CObject2D()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// オブジェクト２Dの生成
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CObject2D * CObject2D::Create(D3DXVECTOR3 pos, D3DXVECTOR2 scale, std::string tex, int priority, D3DXCOLOR col)
{
	CObject2D *pObj = nullptr;
	pObj = new CObject2D(priority);

	//ヌルチェック
	if (pObj != nullptr)
	{
		// ポリゴンの初期化処理
		pObj->SetPos(pos);
		pObj->SetScale(scale);
		pObj->SetCol(col);
		pObj->BindTexture(tex);
		pObj->Init();
	}

	return pObj;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// オブジェクト２Dの初期化
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
HRESULT CObject2D::Init()
{
	// デバイスのポインタを取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,		// 確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,									// リソースの使用方法
		FVF_VERTEX_2D,										// 頂点フォーマット
		D3DPOOL_MANAGED,									// リソース配置のプールタイプ
		&m_pVtxBuff,										// 頂点バッファリソース
		NULL);

	VERTEX_2D*pVtx;        //頂点情報へのポインタ

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// オブジェクト２Dの終了
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CObject2D::Uninit()
{
	//頂点バッファの破壊
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	Destroy();
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// オブジェクト２Dの更新
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CObject2D::Update()
{
	VERTEX_2D*pVtx;        //頂点情報へのポインタ 

	m_objpos += m_move;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//// 頂点座標の更新
	//pVtx[0].pos = D3DXVECTOR3(m_objpos.x - m_Width, m_objpos.y - m_Height, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(m_objpos.x + m_Width, m_objpos.y - m_Height, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(m_objpos.x - m_Width, m_objpos.y + m_Height, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(m_objpos.x + m_Width, m_objpos.y + m_Height, 0.0f);

	D3DXMATRIX mtx;    // 計算用マトリックス
	D3DXVECTOR3 afterPos[4];

	//ゲージの頂点座標
	const D3DXVECTOR3 Vtx[4] =
	{
		D3DXVECTOR3(m_objpos.x - m_Width, m_objpos.y - m_Height, 0.0f),
		D3DXVECTOR3(m_objpos.x + m_Width, m_objpos.y - m_Height, 0.0f),
		D3DXVECTOR3(m_objpos.x - m_Width, m_objpos.y + m_Height, 0.0f),
		D3DXVECTOR3(m_objpos.x + m_Width, m_objpos.y + m_Height, 0.0f),
	};

	 //頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// マトリックスの生成
	D3DXMatrixIdentity(&mtx);

	// ヨー、ピッチ、ロールを指定してマトリックスを作成
	D3DXMatrixRotationYawPitchRoll(&mtx, 0.0f, 0.0f, D3DXToRadian(m_rot));

	// 頂点座標の更新
	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&afterPos[i], &Vtx[i], &mtx);
		pVtx[i].pos = afterPos[i];
	}

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	// 頂点カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// 頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	if (m_bAnimation)
	{	// テクスチャアニメーションをする場合
		m_CntTime++;

		if (m_CntTime >= m_Timer)
		{
			m_AnimationSpdCnt++;
			if (m_AnimationSpdCnt >= m_AnimationSpeed)
			{
				m_AnimationSpdCnt = 0;
				m_PatternAnimX++;

				if (m_PatternAnimX > m_DivisionX)
				{	//アニメーション
					m_PatternAnimX = 0;
					m_PatternAnimY++;

					if (m_PatternAnimY >= m_DivisionY)
					{
						m_PatternAnimY = 0;

						if (!m_bLoop)
						{	//ループしない場合
							Uninit();
							return;
						}
					}
				}

				float U = 1.0f / (m_DivisionX);
				float V = 1.0f / (m_DivisionY);

				SetUV(U * (m_PatternAnimX)
					, U *(m_PatternAnimX)+U
					, V * (m_PatternAnimY)
					, V * (m_PatternAnimY)+V);
			}
		}
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// オブジェクト２Dの描画
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CObject2D::Draw()
{
	// テクスチャのポインタを取得
	CTexture* pTexture = CApplication::GetInstance()->GetTexture();

	// デバイスのポインタを取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		// プリミティブの種類
		0,											// 最初の頂点インデックス
		2);											// プリミティブ(ポリゴン)数

	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// オブジェクト２Dのテクスチャをバインド
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CObject2D::BindTexture(std::string inPath)
{
	m_pTexture = CApplication::GetInstance()->GetTexture()->GetTexture(inPath);		// テクスチャのポインタ
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// オブジェクト２DのテクスチャのUV座標を設定
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CObject2D::SetUV(float Xtop, float Xbottom, float Ytop, float Ybottom)
{
	VERTEX_2D*pVtx;				// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(Xtop, Ytop);
	pVtx[1].tex = D3DXVECTOR2(Xbottom, Ytop);
	pVtx[2].tex = D3DXVECTOR2(Xtop, Ybottom);
	pVtx[3].tex = D3DXVECTOR2(Xbottom, Ybottom);

	// 頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// オブジェクト２Dのアニメーションの設定
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CObject2D::SetAnimation(const int U, const int V, const int Speed, const int Drawtimer, const bool loop)
{
	m_DivisionX = U;
	m_DivisionY = V;
	m_DivisionMAX = m_DivisionY*m_DivisionX;

	m_PatternAnimX = 1;
	m_PatternAnimY = 1;
	m_AnimationSpeed = Speed;
	m_Timer = Drawtimer;
	m_bAnimation = true;
	m_bLoop = loop;

	//表示座標を更新
	SetUV(1.0f / m_DivisionX * (m_PatternAnimX / (m_DivisionX))
		, 1.0f / m_DivisionX *(m_PatternAnimX / (m_DivisionX)) + 1.0f / m_DivisionX
		, 1.0f / m_DivisionY * (m_PatternAnimY % (m_DivisionY))
		, 1.0f / m_DivisionY * (m_PatternAnimY % (m_DivisionY)+1.0f / m_DivisionY* m_DivisionY));
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// オブジェクト２Dの四角判定
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
bool CObject2D::SquareCollision(D3DXVECTOR3 pos, D3DXVECTOR3 Destpos, float Length, float CollisionVal)
{
	float fDistance = ((Destpos.x - pos.x) * (Destpos.x - pos.x)) +
		((Destpos.y - pos.y) * (Destpos.y - pos.y));

	float fRad = powf((Length + Length), CollisionVal);

	if (fDistance <= fRad)
	{
		return true;
	}
	return false;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// オブジェクト２Dの丸判定
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
bool CObject2D::CircleCollision(D3DXVECTOR3 pos, D3DXVECTOR3 Destpos, float Radius, float CollisionVal)
{
	float fDistance = ((Destpos.x - pos.x) * (Destpos.x - pos.x)) +
		((Destpos.y - pos.y) * (Destpos.y - pos.y));

	float fRad = powf((Radius + Radius) * D3DX_PI, CollisionVal);

	if (fDistance <= fRad)
	{
		return true;
	}
	return false;
}