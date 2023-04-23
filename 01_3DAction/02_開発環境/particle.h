#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "billboard.h"

class CParticle : public CBillboard
{
public:
	//--------------------------------------
	// �p�[�e�B�N�����̍\����
	//--------------------------------------
	struct SInfo
	{
		D3DXVECTOR3 pos;						// �ʒu
		D3DXVECTOR3 destPos;					// �ړI�̈ʒu
		D3DXVECTOR3 move;						// �ړ���
		D3DXVECTOR3 scale;						// �傫��
		D3DXVECTOR3 scalingValue;				// �g�k��
		D3DXCOLOR col;							// �F
		D3DXCOLOR destCol;						// �ړI�̐F
		std::vector<std::string> infoProperty;	// �v���p�e�B
		std::string texTag;						// �e�N�X�`���̃^�O
		int destroyTime;						// �G�t�F�N�g����������
		int fallDelayTime;						// ������܂ł̒x��
		int popParticleNum;						// �������鐔
		float moveAttenuation;					// �ړ��̌�����
		float colAttenuation;					// �F�̌�����
		float rotateValue;						// ��]��
		float radius;							// �~��
		float weight;							// �d��
	};

	explicit CParticle(int nPriority = CObject::PRIORITY_THIRD);
	~CParticle() override;

	static CParticle *Create(SInfo& info, std::string url, int nPriority = CObject::PRIORITY_THIRD);	// ��������

	HRESULT Init() override;												// ����������
	void Update() override;													// �X�V����
	void Draw() override;													// �`�揈��
	void Behavior(std::vector<std::string>& prop);							// �p�[�e�B�N���̋���

	//�Z�b�^�[
	void SetInfo(SInfo& info) { m_info = info; }
	void SetPath(std::string path) { m_path = path; }

	int GetLife() { return m_info.destroyTime; }

private:
	SInfo m_info;						// �p�[�e�B�N���̏��
	std::string m_path;					// �e�N�X�`���̃p�X
	int m_nTime;						// ����
};
#endif