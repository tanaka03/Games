//
//Utility.h
//
#ifndef _UTILITY_H_
#define _UTILITY_H_

class CUtility
{
public:
	CUtility();
	~CUtility();

	static float floatRandam(float fMax, float fMin);
	static float easeInOutSine(float anim);
	static void angleNormalize(float& angle);
	static bool isCircleCollision(const D3DXVECTOR3& pos, float radius, const D3DXVECTOR3& destPos, float destRadius);	//Õ“Ë”»’è
	static bool isRectCollision(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& size, 
								const D3DXVECTOR3& destPos, const D3DXVECTOR3& destSize, const D3DXVECTOR3& destMin, const D3DXVECTOR3& destMax);
	static bool isCrossCollision(const D3DXVECTOR3& pos, const D3DXVECTOR3& minSize, const D3DXVECTOR3& maxSize, const D3DXMATRIX& mtxWorld);
	static void stringMultiPush(std::vector<std::string>& list, std::string prop);

	static float Vec2Cross(D3DXVECTOR3* vec1, D3DXVECTOR3* vec2);

private:
};

#endif
