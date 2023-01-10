#pragma once
#include "DirectXMath.h"
#include "CubeObject3D.h"
#include "Metaball.h"

class Collision
{
private:
	//当たり判定の計算に必要な構造体
	struct CubeVertex
	{
		DirectX::XMFLOAT3 c;	//中心
		//DirectX::XMFLOAT3 v[8];	//各頂点の座標
		DirectX::XMFLOAT3 min;	//-x,-y,-z
		DirectX::XMFLOAT3 max;	//x,y,z
	};
	//当たり判定の計算に必要な構造体
	struct SphereVertex
	{
		DirectX::XMFLOAT3 c;	//中心
		DirectX::XMFLOAT3 r;	//半径
	};
public:
	//衝突判定を行うオブジェクトをセット
	void SetObject(CubeObject3D* cube , Metaball* metaball);
	//更新
	bool Update();
private:
	//あたり判定を行うオブジェクト
	CubeObject3D* cube1 = nullptr;
	CubeObject3D* cube2 = nullptr;
	Metaball* metaball1 = nullptr;
	Metaball* metaball2 = nullptr;
	//当たり判定に必要な変数
	CubeVertex cubeVertex1;
	CubeVertex cubeVertex2;
	SphereVertex sphereVertex1;
	SphereVertex sphereVertex2;

	bool hit;
};

