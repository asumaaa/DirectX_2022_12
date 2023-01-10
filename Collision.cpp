#include "Collision.h"
#include "Math2.h"

void Collision::SetObject(CubeObject3D* cube, Metaball* metaball)
{
	//引数から受け取った値をメンバ変数に代入
	this->cube1 = cube;
	this->metaball1 = metaball;
}

bool Collision::Update()
{
	//cubeVertex1の値を設定
	cubeVertex1.c = cube1->GetPosition();
	//各頂点の座標を設定 0<-x-y-z> 1<-xy-z> 2<x-y-z> 3<xy-z> 4<-x-yz> 5<-xyz> 6<x-yz> 7<xyz>
	/*cubeVertex1.v[0] = { cube1->GetPosition().x - cube1->GetScale().x,cube1->GetPosition().y - cube1->GetScale().y, cube1->GetPosition().z - -cube1->GetScale().z };
	cubeVertex1.v[1] = { cube1->GetPosition().x - cube1->GetScale().x,cube1->GetPosition().y + cube1->GetScale().y, cube1->GetPosition().z - -cube1->GetScale().z };
	cubeVertex1.v[2] = { cube1->GetPosition().x + cube1->GetScale().x,cube1->GetPosition().y - cube1->GetScale().y, cube1->GetPosition().z - -cube1->GetScale().z };
	cubeVertex1.v[3] = { cube1->GetPosition().x + cube1->GetScale().x,cube1->GetPosition().y + cube1->GetScale().y, cube1->GetPosition().z - -cube1->GetScale().z };
	cubeVertex1.v[4] = { cube1->GetPosition().x - cube1->GetScale().x,cube1->GetPosition().y - cube1->GetScale().y, cube1->GetPosition().z + -cube1->GetScale().z };
	cubeVertex1.v[5] = { cube1->GetPosition().x - cube1->GetScale().x,cube1->GetPosition().y + cube1->GetScale().y, cube1->GetPosition().z + -cube1->GetScale().z };
	cubeVertex1.v[6] = { cube1->GetPosition().x + cube1->GetScale().x,cube1->GetPosition().y - cube1->GetScale().y, cube1->GetPosition().z + -cube1->GetScale().z };
	cubeVertex1.v[7] = { cube1->GetPosition().x + cube1->GetScale().x,cube1->GetPosition().y + cube1->GetScale().y, cube1->GetPosition().z + -cube1->GetScale().z };*/

	//min,maxの設定
	cubeVertex1.min = { cube1->GetPosition().x - cube1->GetScale().x ,cube1->GetPosition().y - cube1->GetScale().y,cube1->GetPosition().z - cube1->GetScale().z };
	cubeVertex1.max = { cube1->GetPosition().x + cube1->GetScale().x ,cube1->GetPosition().y + cube1->GetScale().y,cube1->GetPosition().z + cube1->GetScale().z };

	//SphereVertex1の値を設定
	sphereVertex1.c = metaball1->GetPosition();
	sphereVertex1.r = metaball1->GetScale();

	//円の中心座標が直方体の範囲内にある場合のベクトル
	DirectX::XMFLOAT3 v{};
	//フラグを用意
	bool xFlag = false;
	bool yFlag = false;
	bool zFlag = false;
	//各軸の座標が矩形の範囲内にある場合フラグを立てる
	if (sphereVertex1.c.x > cubeVertex1.min.x && sphereVertex1.c.x < cubeVertex1.max.x)xFlag = true;
	if (sphereVertex1.c.y > cubeVertex1.min.y && sphereVertex1.c.y < cubeVertex1.max.y)yFlag = true;
	if (sphereVertex1.c.z > cubeVertex1.min.z && sphereVertex1.c.z < cubeVertex1.max.z)zFlag = true;

	//全ての座標が範囲内にあったら当たり
	if (xFlag == true && yFlag == true && zFlag == true)return 1;

	////x軸、y軸の範囲内に座標がある場合
	//else if (xFlag == true && yFlag == true)
	//{
	//	//座標が手前にある場合
	//	if (sphereVertex1.c.z < cubeVertex1.min.z)
	//	{
	//		v = { 0,0,sphereVertex1.c.z - cubeVertex1.min.z };
	//	}
	//	//座標奥にある場合
	//	if (sphereVertex1.c.z < cubeVertex1.min.z)
	//	{
	//		v = { 0,0,sphereVertex1.c.z - cubeVertex1.max.z };
	//	}
	//}

	////y軸、z軸の範囲内に座標がある場合
	//else if (yFlag == true && zFlag == true)
	//{
	//	//座標が左にある場合
	//	if (sphereVertex1.c.x < cubeVertex1.min.x)
	//	{
	//		v = { sphereVertex1.c.x - cubeVertex1.min.x,0,0};
	//	}
	//	//座標が右にある場合
	//	if (sphereVertex1.c.x < cubeVertex1.min.x)
	//	{
	//		v = { sphereVertex1.c.x - cubeVertex1.max.x,0,0};
	//	}
	//}

	////x軸、z軸の範囲内に座標がある場合
	//else if (xFlag == true && zFlag == true)
	//{
	//	//座標が下にある場合
	//	if (sphereVertex1.c.y < cubeVertex1.min.y)
	//	{
	//		v = { 0,sphereVertex1.c.y - cubeVertex1.min.y,0 };
	//	}
	//	//座標が右にある場合
	//	if (sphereVertex1.c.y < cubeVertex1.min.y)
	//	{
	//		v = { 0,sphereVertex1.c.y - cubeVertex1.max.y,0 };
	//	}
	//}

	////それ以外の場合
	//else
	//{
	//	if (sphereVertex1.c.x < cubeVertex1.c.x)v.x = sphereVertex1.c.x - cubeVertex1.min.x;
	//	if (sphereVertex1.c.x > cubeVertex1.c.x)v.x = sphereVertex1.c.x - cubeVertex1.max.x;
	//	if (sphereVertex1.c.y < cubeVertex1.c.y)v.y = sphereVertex1.c.y - cubeVertex1.min.y;
	//	if (sphereVertex1.c.y > cubeVertex1.c.y)v.y = sphereVertex1.c.y - cubeVertex1.max.y;
	//	if (sphereVertex1.c.z < cubeVertex1.c.z)v.z = sphereVertex1.c.z - cubeVertex1.min.z;
	//	if (sphereVertex1.c.z > cubeVertex1.c.z)v.z = sphereVertex1.c.z - cubeVertex1.max.z;
	//}

	////ベクトルが半径より小さければ当たり
	//if(vector3Length(v) <= sphereVertex1.r.x)
	//{
	//	return 1;
	//}

	//当たっていない
	return 0;
}
