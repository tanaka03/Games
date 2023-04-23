#include "application.h"
#include "object3d.h"
#include "file.h"
#include "3deffect_manager.h"

//��������������������������������������������������������������
// 3D�G�t�F�N�g�}�l�[�W���̃R���X�g���N�^
//��������������������������������������������������������������
C3DEffectManager::C3DEffectManager()
{
}

//��������������������������������������������������������������
// 3D�G�t�F�N�g�}�l�[�W���̃f�X�g���N�^
//��������������������������������������������������������������
C3DEffectManager::~C3DEffectManager()
{
}

//��������������������������������������������������������������
// 3D�G�t�F�N�g�}�l�[�W���̏�����
//��������������������������������������������������������������
HRESULT C3DEffectManager::Init()
{
	return S_OK;
}

//��������������������������������������������������������������
// 3D�G�t�F�N�g�}�l�[�W���̉��
//��������������������������������������������������������������
void C3DEffectManager::ReleaseAll()
{
	m_data.clear();
}

//��������������������������������������������������������������
// �t�@�C���ǂݍ���
//��������������������������������������������������������������
void C3DEffectManager::Load(nlohmann::json& list)
{
	size_t size = list["Property"].size();
	std::vector<C3DEffect::SInfo> info = {};

	info.resize(size);
	for (size_t i = 0; i < size; i++)
	{
		SafeLoad(list["Property"][i], "BeginRot", info[i].beginRot);							// �ŏ��̌���
		SafeLoad(list["Property"][i], "BeginScale", info[i].beginScale);						// �ŏ��̊g�k
		SafeLoad(list["Property"][i], "MoveValue", info[i].moveValue);							// �ړ���
		SafeLoad(list["Property"][i], "RotateValue", info[i].rotateValue);						// ��]��
		SafeLoad(list["Property"][i], "ScalingValue", info[i].scalingValue);					// �g�k��
		SafeLoad(list["Property"][i], "PosOffset", info[i].posOffset);							// �ʒu�̃I�t�Z�b�g
		SafeLoad(list["Property"][i], "RotOffset", info[i].rotOffset);							// �����̃I�t�Z�b�g
		SafeLoad(list["Property"][i], "Color", info[i].col);									// �F
		SafeLoad(list["Property"][i], "ColorTransition", info[i].transitionCol);				// �F�̑J��
		SafeLoad(list["Property"][i], "ColorTransitionEndTime", info[i].transitionColEndTime);	// �F�̑J�ڂ̏I������
		SafeLoad(list["Property"][i], "AlphaAttenuation", info[i].alphaAttenuation);			// �F�A���t�@�l�̌�����
		SafeLoad(list["Property"][i], "MoveAttenuation", info[i].moveAttenuation);				// �����̌�����
		SafeLoad(list["Property"][i], "Life", info[i].life);									// �G�t�F�N�g�̐�������
		SafeLoad(list["Property"][i], "TractionPlayer", info[i].tractPlayer);					// �v���C���[�ɒǏ]���邩�ǂ���
		SafeLoad(list["Property"][i], "UseFileTexture", info[i].useFileTexture);				// x�t�@�C���̃t�@�C���̃e�N�X�`�����g�p���邩�ǂ���
		SafeLoad(list["Property"][i], "TexTag", info[i].texTag);								// �e�N�X�`���̃^�O
		SafeLoad(list["Property"][i], "Shape", info[i].modelShape);								// ���f���̃^�O

		if (list["Property"][i]["Animation"].empty())
		{	// �A�j���[�V�����̗v�f���Ȃ������ꍇ
			continue;
		}

	}

	m_data.insert(std::make_pair(list["Tag"], info));
}

//��������������������������������������������������������������
// �t�@�C���̑S�Ă̗v�f��ǂݍ���
//��������������������������������������������������������������
void C3DEffectManager::LoadAll()
{
	nlohmann::json list = CFile::LoadJsonStage(L"Data/FILE/3DEffect.json");

	size_t size =list["EFFECT"].size();

	for (size_t i = 0; i < size; i++)
	{
		if (list["EFFECT"][i]["Tag"].empty())
		{
			continue;
		}

		Load(list["EFFECT"].at(i));
	}
}

//��������������������������������������������������������������
// ���o�����f�[�^��Ԃ�����
//��������������������������������������������������������������
std::vector<C3DEffect::SInfo> C3DEffectManager::GetEffectData(std::string str)
{
	if (m_data.count(str) == 0)
	{	//���f���f�[�^�������ĂȂ������ꍇ
		assert(false);
	}

	return m_data[str];
}