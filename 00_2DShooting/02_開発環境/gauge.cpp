#include "object2d.h"
#include "gauge.h"
#include "hp.h"
#include "mp.h"
#include "texture.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//静的メンバ変数宣言
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CGauge *CGauge::m_apGauge;

CGauge::CGauge()
{
}

CGauge::~CGauge()
{
}

//ゲージの生成
CGauge * CGauge::Create(D3DXVECTOR3 pos, ETYPE type)
{
	switch (type)
	{
	case GAUGETYPE_HP:
		m_apGauge = new CHp;
		break;

	case GAUGETYPE_MP:
		m_apGauge = new CMp;
		break;

	default:
		break;
	}

	//ヌルチェック
	if (m_apGauge != nullptr)
	{
		m_apGauge->SetPos(pos);
		m_apGauge->SetType(type);
		m_apGauge->Init();
	}

	return m_apGauge;
}