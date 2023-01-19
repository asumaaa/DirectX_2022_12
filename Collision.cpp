#include "Collision.h"
#include "Math2.h"

void Collision::SetObject(DirectX::XMFLOAT3 cubePos, DirectX::XMFLOAT3 cubeScale)
{
	//��������󂯎�����l�������o�ϐ��ɑ��
	/*this->cubePos = cubePos;
	this->cubeScale = cubeScale;*/

	//cubeVertex1�̒l��ݒ�
	cubeVertex1.c = cubePos;
	//�e���_�̍��W��ݒ� 0<-x-y-z> 1<-xy-z> 2<x-y-z> 3<xy-z> 4<-x-yz> 5<-xyz> 6<x-yz> 7<xyz>
	/*cubeVertex1.v[0] = { cube1->GetPosition().x - cube1->GetScale().x,cube1->GetPosition().y - cube1->GetScale().y, cube1->GetPosition().z - -cube1->GetScale().z };
	cubeVertex1.v[1] = { cube1->GetPosition().x - cube1->GetScale().x,cube1->GetPosition().y + cube1->GetScale().y, cube1->GetPosition().z - -cube1->GetScale().z };
	cubeVertex1.v[2] = { cube1->GetPosition().x + cube1->GetScale().x,cube1->GetPosition().y - cube1->GetScale().y, cube1->GetPosition().z - -cube1->GetScale().z };
	cubeVertex1.v[3] = { cube1->GetPosition().x + cube1->GetScale().x,cube1->GetPosition().y + cube1->GetScale().y, cube1->GetPosition().z - -cube1->GetScale().z };
	cubeVertex1.v[4] = { cube1->GetPosition().x - cube1->GetScale().x,cube1->GetPosition().y - cube1->GetScale().y, cube1->GetPosition().z + -cube1->GetScale().z };
	cubeVertex1.v[5] = { cube1->GetPosition().x - cube1->GetScale().x,cube1->GetPosition().y + cube1->GetScale().y, cube1->GetPosition().z + -cube1->GetScale().z };
	cubeVertex1.v[6] = { cube1->GetPosition().x + cube1->GetScale().x,cube1->GetPosition().y - cube1->GetScale().y, cube1->GetPosition().z + -cube1->GetScale().z };
	cubeVertex1.v[7] = { cube1->GetPosition().x + cube1->GetScale().x,cube1->GetPosition().y + cube1->GetScale().y, cube1->GetPosition().z + -cube1->GetScale().z };*/

	//min,max�̐ݒ�
	cubeVertex1.min = { cubePos.x - (cubeScale.x / 2) ,cubePos.y - (cubeScale.y),cubePos.z - (cubeScale.z / 2) };
	cubeVertex1.max = { cubePos.x + (cubeScale.x / 2) ,cubePos.y + (cubeScale.y),cubePos.z + (cubeScale.z / 2) };
}

bool Collision::Update(DirectX::XMFLOAT3 spherePos, DirectX::XMFLOAT3 sphereScale)
{
	//cubeVertex1�̒l��ݒ�
	/*cubeVertex1.c = cubePos;*/

	//min,max�̐ݒ�
	/*cubeVertex1.min = { cubePos.x - (cubeScale.x * 2) ,cubePos.y - (cubeScale.y * 2),cubePos.z - (cubeScale.z * 2) };
	cubeVertex1.max = { cubePos.x + (cubeScale.x * 2) ,cubePos.y + (cubeScale.y * 2),cubePos.z + (cubeScale.z * 2) };*/
	/*cubeVertex1.min = { cubePos.x - (cubeScale.x *1.5f) ,cubePos.y - (cubeScale.y * 1.5f),cubePos.z - (cubeScale.z * 1.5f) };
	cubeVertex1.max = { cubePos.x + (cubeScale.x *1.5f) ,cubePos.y + (cubeScale.y * 1.5f),cubePos.z + (cubeScale.z * 1.5f) }; */

	//SphereVertex1�̒l��ݒ�
	sphereVertex1.c = spherePos;
	sphereVertex1.r = sphereScale;
	sphereVertex1.min = { spherePos.x - (sphereScale.x / 2) ,spherePos.y - (sphereScale.y),spherePos.z - (sphereScale.z / 2) };
	sphereVertex1.max = { spherePos.x + (sphereScale.x / 2) ,spherePos.y + (sphereScale.y),spherePos.z + (sphereScale.z / 2) };

	//�~�̒��S���W�������͈͓̂̔��ɂ���ꍇ�̃x�N�g��
	DirectX::XMFLOAT3 v{};
	//�t���O��p��
	bool xFlag = false;
	bool yFlag = false;
	bool zFlag = false;
	//�e���̍��W����`�͈͓̔��ɂ���ꍇ�t���O�𗧂Ă�
	if (sphereVertex1.max.x >= cubeVertex1.min.x && sphereVertex1.min.x <= cubeVertex1.max.x)xFlag = true;
	if (sphereVertex1.max.y >= cubeVertex1.min.y && sphereVertex1.min.y <= cubeVertex1.max.y)yFlag = true;
	if (sphereVertex1.max.z >= cubeVertex1.min.z && sphereVertex1.min.z <= cubeVertex1.max.z)zFlag = true;

	//�S�Ă̍��W���͈͓��ɂ������瓖����
	if (xFlag == true && yFlag == true && zFlag == true)return 1;

	////x���Ay���͈͓̔��ɍ��W������ꍇ
	//else if (xFlag == true && yFlag == true)
	//{
	//	//���W����O�ɂ���ꍇ
	//	if (sphereVertex1.c.z < cubeVertex1.min.z)
	//	{
	//		v = { 0,0,sphereVertex1.c.z - cubeVertex1.min.z };
	//	}
	//	//���W���ɂ���ꍇ
	//	if (sphereVertex1.c.z < cubeVertex1.min.z)
	//	{
	//		v = { 0,0,sphereVertex1.c.z - cubeVertex1.max.z };
	//	}
	//}

	////y���Az���͈͓̔��ɍ��W������ꍇ
	//else if (yFlag == true && zFlag == true)
	//{
	//	//���W�����ɂ���ꍇ
	//	if (sphereVertex1.c.x < cubeVertex1.min.x)
	//	{
	//		v = { sphereVertex1.c.x - cubeVertex1.min.x,0,0};
	//	}
	//	//���W���E�ɂ���ꍇ
	//	if (sphereVertex1.c.x < cubeVertex1.min.x)
	//	{
	//		v = { sphereVertex1.c.x - cubeVertex1.max.x,0,0};
	//	}
	//}

	////x���Az���͈͓̔��ɍ��W������ꍇ
	//else if (xFlag == true && zFlag == true)
	//{
	//	//���W�����ɂ���ꍇ
	//	if (sphereVertex1.c.y < cubeVertex1.min.y)
	//	{
	//		v = { 0,sphereVertex1.c.y - cubeVertex1.min.y,0 };
	//	}
	//	//���W���E�ɂ���ꍇ
	//	if (sphereVertex1.c.y < cubeVertex1.min.y)
	//	{
	//		v = { 0,sphereVertex1.c.y - cubeVertex1.max.y,0 };
	//	}
	//}

	////����ȊO�̏ꍇ
	//else
	//{
	//	if (sphereVertex1.c.x < cubeVertex1.c.x)v.x = sphereVertex1.c.x - cubeVertex1.min.x;
	//	if (sphereVertex1.c.x > cubeVertex1.c.x)v.x = sphereVertex1.c.x - cubeVertex1.max.x;
	//	if (sphereVertex1.c.y < cubeVertex1.c.y)v.y = sphereVertex1.c.y - cubeVertex1.min.y;
	//	if (sphereVertex1.c.y > cubeVertex1.c.y)v.y = sphereVertex1.c.y - cubeVertex1.max.y;
	//	if (sphereVertex1.c.z < cubeVertex1.c.z)v.z = sphereVertex1.c.z - cubeVertex1.min.z;
	//	if (sphereVertex1.c.z > cubeVertex1.c.z)v.z = sphereVertex1.c.z - cubeVertex1.max.z;
	//}

	////�x�N�g�������a��菬������Γ�����
	//if(vector3Length(v) <= sphereVertex1.r.x)
	//{
	//	return 1;
	//}

	//�������Ă��Ȃ�
	return 0;
}