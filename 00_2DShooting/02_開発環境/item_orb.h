//����������������������������������������
//OrbItem.h
//����������������������������������������
#ifndef _ORBITEM_H_
#define _ORBITEM_H_

#include "item.h"

class CEffect;

class COrbItem : public CItem
{
public:
	COrbItem();
	~COrbItem();

	HRESULT Init();
	void Uninit();
	void Update();

	//�Z�b�^�[
	void SetObtainScale(float scale) { m_fScale = scale; }

	//�Q�b�^�[
	float GetObtainScale() { return m_fScale; }

private:
	void Draw();
	D3DXVECTOR3 m_pos;
	CEffect *m_pEffect;
	float m_fScale;
};

#endif