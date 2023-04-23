//����������������������������������������
// �p�[�e�B�N���̃t�@�C������ǂݍ��ޏ���
//����������������������������������������
#include "application.h"
#include "object3d.h"
#include "file.h"
#include "particle_manager.h"
#include "utility.h"

//��������������������������������������������������������������
//�p�[�e�B�N���}�l�[�W���̃R���X�g���N�^
//��������������������������������������������������������������
CParticleManager::CParticleManager()
{
}

//��������������������������������������������������������������
// �p�[�e�B�N���}�l�[�W���̃f�X�g���N�^
//��������������������������������������������������������������
CParticleManager::~CParticleManager()
{
}

//��������������������������������������������������������������
// �p�[�e�B�N���}�l�[�W���̏�����
//��������������������������������������������������������������
HRESULT CParticleManager::Init()
{
	return S_OK;
}

//��������������������������������������������������������������
// �p�[�e�B�N���}�l�[�W���̉��
//��������������������������������������������������������������
void CParticleManager::ReleaseAll()
{
	m_data.clear();
}

//��������������������������������������������������������������
// �t�@�C���ǂݍ���
//��������������������������������������������������������������
void CParticleManager::Load(nlohmann::json& list)
{
	if (list["PopNum"].empty())
	{
		assert(false);
	}

	int popNum = list["PopNum"];
	size_t size = list["Property"].size();

	std::vector<CParticle::SInfo> info = {};
	info.resize(size);
	for (size_t i = 0; i < size; i++)
	{
		info[i].popParticleNum = popNum;
		SafeLoad(list["Property"][i], "Pos", info[i].pos);								// �ʒu
		SafeLoad(list["Property"][i], "Move", info[i].move);							// �ړ���
		SafeLoad(list["Property"][i], "MoveAttenuation", info[i].moveAttenuation);		// �ړ��ʂ̌���
		SafeLoad(list["Property"][i], "Scale", info[i].scale);							// �傫��
		SafeLoad(list["Property"][i], "Color", info[i].col);							// �F
		SafeLoad(list["Property"][i], "DestColor", info[i].destCol);					// �ړI�̐F
		SafeLoad(list["Property"][i], "ColorAttenuation", info[i].colAttenuation);		// �F�̌�����
		SafeLoad(list["Property"][i], "ScalingValue", info[i].scalingValue);			// �g�k��
		SafeLoad(list["Property"][i], "Rotate", info[i].rotateValue);					// ��]��
		SafeLoad(list["Property"][i], "Weight", info[i].weight);						// �d��
		SafeLoad(list["Property"][i], "Radius", info[i].radius);						// �~��
		SafeLoad(list["Property"][i], "Life", info[i].destroyTime);						// ��������
		SafeLoad(list["Property"][i], "TexTag", info[i].texTag);						// �e�N�X�`��

		std::string prop;
		std::vector<std::string> behaviorList;

		SafeLoad(list["Property"][i], "Behavior", prop);		// �����̃v���p�e�B
		CUtility::stringMultiPush(behaviorList, prop);

		info[i].infoProperty = behaviorList;
	}

	m_data.insert(std::make_pair(list["Tag"], info));
}

//��������������������������������������������������������������
// �t�@�C���̑S�Ă̗v�f��ǂݍ���
//��������������������������������������������������������������
void CParticleManager::LoadAll()
{
	nlohmann::json list = CFile::LoadJsonStage(L"Data/FILE/particle.json");

	size_t size = list["PARTICLE"].size();

	for (size_t i = 0; i < size; i++)
	{
		if (list["PARTICLE"][i]["Tag"].empty())
		{
			continue;
		}

		Load(list["PARTICLE"].at(i));
	}
}

//��������������������������������������������������������������
// ���o�����f�[�^��Ԃ�����
//��������������������������������������������������������������
std::vector<CParticle::SInfo> CParticleManager::GetParticleData(std::string str)
{
	if (m_data.count(str) == 0)
	{	//���f���f�[�^�������ĂȂ������ꍇ
		assert(false);
	}

	return m_data[str];
}