#pragma once
#include "DirectXMath.h"
#include "CubeObject3D.h"
#include "Metaball.h"

class Collision
{
private:
	//�����蔻��̌v�Z�ɕK�v�ȍ\����
	struct CubeVertex
	{
		DirectX::XMFLOAT3 c;	//���S
		//DirectX::XMFLOAT3 v[8];	//�e���_�̍��W
		DirectX::XMFLOAT3 min;	//-x,-y,-z
		DirectX::XMFLOAT3 max;	//x,y,z
	};
	//�����蔻��̌v�Z�ɕK�v�ȍ\����
	struct SphereVertex
	{
		DirectX::XMFLOAT3 c;	//���S
		DirectX::XMFLOAT3 r;	//���a
	};
public:
	//�Փ˔�����s���I�u�W�F�N�g���Z�b�g
	void SetObject(CubeObject3D* cube , Metaball* metaball);
	//�X�V
	bool Update();
private:
	//�����蔻����s���I�u�W�F�N�g
	CubeObject3D* cube1 = nullptr;
	CubeObject3D* cube2 = nullptr;
	Metaball* metaball1 = nullptr;
	Metaball* metaball2 = nullptr;
	//�����蔻��ɕK�v�ȕϐ�
	CubeVertex cubeVertex1;
	CubeVertex cubeVertex2;
	SphereVertex sphereVertex1;
	SphereVertex sphereVertex2;

	bool hit;
};

