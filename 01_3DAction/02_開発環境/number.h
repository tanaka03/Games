#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "object.h"

class CObject2D;
class CBillboard;

class CNumber : public CObject
{
public:
	enum ENumberType
	{
		NUMBER_SCORE = 0,
		NUMBER_COMBO,
		NUMBER_DAMAGE,
		NUMBER_MAX
	};

	CNumber();
	~CNumber();

	static CNumber *Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, ENumberType type, std::string path, int digits, int priority);

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override {};
	void AddValue(int value);
	void Destroy() override { m_release = true; }

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetScale(D3DXVECTOR2 scale) { m_scale = scale; }
	void SetNumberType(ENumberType type) { m_type = type; }
	void SetValueList(std::vector<int> list) { m_list = list; }
	void SetValue(int value);
	void SetOldValue(int value) { m_oldValue = value; }
	void SetTime(int time);

	D3DXVECTOR3 GetPos() { return m_pos; }
	D3DXVECTOR2 GetScale() { return m_scale; }
	ENumberType GetNumberType() { return m_type; }
	std::vector<CObject2D*> GetNumberTex() { return m_number; }
	CObject2D *GetNumberTex(int idx) { return m_number[idx]; }
	std::vector<CBillboard*> Get3DNumberTex() { return m_3Dnumber; }
	CBillboard *Get3DNumberTex(int idx) { return m_3Dnumber[idx]; }
	std::vector<int> GetValueList() { return m_list; }
	int GetDigits() { return m_digit; }
	int GetValue() { return m_value; }
	int GetOldValue() { return m_oldValue; }
	bool GetDestroy() { return m_release; }

private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR2 m_scale;
	ENumberType m_type;
	std::vector<CObject2D*> m_number;
	std::vector<CBillboard*> m_3Dnumber;
	std::vector<int> m_list;
	std::vector<bool> m_endList;
	std::string m_path;
	int m_digit;
	int m_value;
	int m_oldValue;
	int m_life;
	int m_priority;
	const float texDivision = 25.0f;
	bool m_release;
};

#endif