#include <algorithm>
#include "object2d.h"
#include "number.h"
#include "renderer.h"
#include "application.h"
#include "camera.h"

#include "damage.h"
#include "score.h"
#include "combo.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ナンバーのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CNumber::CNumber() : 
	m_priority(CObject::PRIORITY_FOURTH),
	m_value(0)
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ナンバーのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CNumber::~CNumber()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ナンバーの生成
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CNumber *CNumber::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, ENumberType type, std::string path, int digits, int priority)
{
	CNumber *pNumber = nullptr;

	pNumber = new CNumber;

	if (pNumber != nullptr)
	{
		pNumber->m_pos = pos;
		pNumber->m_scale = size;
		pNumber->m_digit = digits;
		pNumber->m_type = type;
		pNumber->m_path = path;
		pNumber->m_priority = priority;
		pNumber->Init();
	}
	else
	{
		assert(false);
	}
	return pNumber;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ナンバーの初期化
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
HRESULT CNumber::Init()
{
	CObject::Invisible();

	m_list.resize(m_digit);
	m_endList.resize(m_digit);

	CScore *pScore = nullptr;
	CCombo *pCombo = nullptr;
	CDamage *pDamage = nullptr;

	switch (m_type)
	{
	case NUMBER_SCORE:
		for (int i = 0; i < m_digit; i++)
		{
			pScore = new CScore(m_priority);

			if (pScore != nullptr)
			{
				pScore->SetPos(D3DXVECTOR3(m_pos.x + (texDivision * i), m_pos.y, 0.0f));
				pScore->SetScale(m_scale);
				pScore->SetDigit(m_digit);
				pScore->SetMaxScore(m_digit);
				pScore->SetPosTexU(m_list[i]);
				pScore->BindTexture(m_path);
				pScore->Init();
			}

			m_number.push_back(pScore);
		}
		break;

	case NUMBER_COMBO:
		for (int i = 0; i < m_digit; i++)
		{
			pCombo = new CCombo(m_priority);

			if (pCombo != nullptr)
			{
				pCombo->SetPos(D3DXVECTOR3(m_pos.x + (texDivision * i), m_pos.y, 0.0f));
				pCombo->SetScale(m_scale);
				pCombo->SetDigit(m_digit);
				pCombo->SetMaxCombo(m_digit);
				pCombo->SetPosTexU(m_list[i]);
				pCombo->BindTexture(m_path);
				pCombo->Init();
			}

			m_number.push_back(pCombo);
		}
		break;

	case NUMBER_DAMAGE:		
		for (int i = 0; i < m_digit; i++)
		{
			pDamage = new CDamage(m_priority);

			if (pDamage != nullptr)
			{
				pDamage->SetPos(D3DXVECTOR3(m_pos.x + -texDivision * i, m_pos.y, m_pos.z + texDivision * i));
				pDamage->SetScale(D3DXVECTOR3(m_scale.x, m_scale.y, 0.0f));
				pDamage->SetDigit(m_digit);
				pDamage->SetMaxDamage(m_digit);
				pDamage->SetPosTexU(m_list[i]);
				pDamage->BindTexture(m_path);
				pDamage->Init();
			}

			m_3Dnumber.push_back(pDamage);
		}
		break;
	}

	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ナンバーの終了
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CNumber::Uninit()
{
	if (!m_number.empty())
	{
		m_number.clear();
	}

	if (!m_3Dnumber.empty())
	{
		m_3Dnumber.clear();
	}

	if (!m_list.empty())
	{
		m_list.clear();
	}

	if (!m_endList.empty())
	{
		m_endList.clear();
	}

	Destroy();
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ナンバーの更新
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CNumber::Update()
{
	CDamage *damageObj = nullptr;

	// スコアなどとは違い、大量に数値が生成されるオブジェクト用
	for (size_t i = 0; i < m_3Dnumber.size(); i++)
	{
		switch (m_type)
		{
		case NUMBER_DAMAGE:
			damageObj = dynamic_cast<CDamage*>(m_3Dnumber.at(i));

			if (damageObj->GetEnd())
			{
				m_endList[i] = true;
			}
			break;
		}
	}

	// 全てがtrueかどうか判定
	bool allEnd = std::all_of(m_endList.begin(), m_endList.end(), [](bool b) { return b; });
	if (allEnd)
	{
		for (auto &p : m_3Dnumber)
		{
			p->Destroy();
		}
		this->Destroy();
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ナンバーの数値を設定
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CNumber::SetValue(int value)
{
	m_value = value;

	// 2Dナンバーの処理
	for (size_t i = 0; i < m_number.size(); i++)
	{
		CScore *scoreObj = nullptr;
		CCombo *comboObj = nullptr;

		// それぞれの桁の数字を取得
		int ValueA = (int)powf(10, m_digit - (float)i);
		int ValueB = (int)powf(10, m_digit - ((float)i + 1));
		m_list[i] = m_value % ValueA / ValueB;

		switch (m_type)
		{
		case NUMBER_SCORE:
			scoreObj = dynamic_cast<CScore*>(m_number.at(i));

			if (scoreObj != nullptr)
			{
				scoreObj->SetPosTexU(m_list[i]);
				scoreObj->SetScore(value);
			}
			break;

		case NUMBER_COMBO:
			comboObj = dynamic_cast<CCombo*>(m_number.at(i));

			if (comboObj != nullptr)
			{
				comboObj->SetPosTexU(m_list[i]);
				comboObj->SetCombo(value);
			}
			break;
		}
	}

	// 3Dナンバーの処理
	for (size_t i = 0; i < m_3Dnumber.size(); i++)
	{
		CDamage *damageObj = nullptr;

		// それぞれの桁の数字を取得
		int ValueA = (int)powf(10, m_digit - (float)i);
		int ValueB = (int)powf(10, m_digit - ((float)i + 1));
		m_list[i] = m_value % ValueA / ValueB;

		switch (m_type)
		{
		case NUMBER_DAMAGE:
			damageObj = dynamic_cast<CDamage*>(m_3Dnumber.at(i));

			if (damageObj != nullptr)
			{
				damageObj->SetPosTexU(m_list[i]);
				damageObj->SetDamage(value);
			}
			break;
		}
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ナンバーの数値を加算
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CNumber::AddValue(int value)
{
	m_oldValue = m_value;
	m_value += value;
	SetValue(m_value);
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ナンバーのタイム設定
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CNumber::SetTime(int time)
{
	for (size_t i = 0; i < m_number.size(); i++)
	{
		CCombo *comboObj = nullptr;

		switch (m_type)
		{
		case NUMBER_COMBO:
			comboObj = dynamic_cast<CCombo*>(m_number.at(i));

			if (comboObj != nullptr)
			{
				comboObj->SetBeginTime(time);
			}
			break;
		}
	}
}