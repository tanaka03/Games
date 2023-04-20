//**************************************************
// 
// Hackathon ( utility.cpp )
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "utility.h"

//--------------------------------------------------
// �p�x�̐��K��
//--------------------------------------------------
void NormalizeAngle(float *pAngle)
{
	if (*pAngle >= D3DX_PI)
	{// 3.14���傫��
		*pAngle -= D3DX_PI * 2.0f;
	}
	else if (*pAngle <= -D3DX_PI)
	{// -3.14��菬����
		*pAngle += D3DX_PI * 2.0f;
	}
}

//--------------------------------------------------
// �z�[�~���O
//--------------------------------------------------
bool Homing(D3DXVECTOR3 *pPosOut, const D3DXVECTOR3 &posNow, const D3DXVECTOR3 &posDest, float fSpeed)
{
	D3DXVECTOR3 vecDiff = posDest - posNow;

	float fLength = D3DXVec3Length(&vecDiff);

	if (fLength <= fSpeed)
	{// ������蒷������������
		*pPosOut = posDest;
		return true;
	}
	else
	{// ������蒷�����傫����
		*pPosOut = posNow + ((vecDiff / fLength) * fSpeed);
		return false;
	}
}

//--------------------------------------------------
// �����_�̃����_��
//--------------------------------------------------
float FloatRandam(float fMax, float fMin)
{
	return ((rand() / (float)RAND_MAX) * (fMax - fMin)) + fMin;
}

//--------------------------------------------------
// �����̃����_��
//--------------------------------------------------
int IntRandam(int nMax, int nMin)
{
	return (int)((rand() / (int)RAND_MAX) * (nMax - nMin)) + nMin;
}

//--------------------------------------------------
// sin�J�[�u�̒l��1.0f�`0.0f�ŋA���Ă���
//--------------------------------------------------
float SinCurve(int nTime, float fCycle)
{
	return  (sinf((nTime * fCycle) * (D3DX_PI * 2.0f)) + 1.0f) * 0.5f;
}

//--------------------------------------------------
// cos�J�[�u�̒l��1.0f�`0.0f�ŋA���Ă���
//--------------------------------------------------
float CosCurve(int nTime, float fCycle)
{
	return  (cosf((nTime * fCycle) * (D3DX_PI * 2.0f)) + 1.0f) * 0.5f;
}

//--------------------------------------------------
// �J�[�u�̒l���A���Ă���
//--------------------------------------------------
float Curve(float fCurve, float fMax, float fMin)
{
	return (fCurve * (fMax - fMin)) + fMin;
}
