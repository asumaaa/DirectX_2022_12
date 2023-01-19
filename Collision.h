#pragma once
#include "DirectXMath.h"

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
		DirectX::XMFLOAT3 min;
		DirectX::XMFLOAT3 max;
	};
public:
	//�Փ˔�����s���I�u�W�F�N�g���Z�b�g(�����̂Ƌ�)
	void SetObject(DirectX::XMFLOAT3 cubePos, DirectX::XMFLOAT3 cubeScale);
	//�X�V
	bool Update(DirectX::XMFLOAT3 spherePos, DirectX::XMFLOAT3 sphereScale);
private:
	//�����蔻��ɕK�v�ȕϐ�
	CubeVertex cubeVertex1;
	SphereVertex sphereVertex1;

	/*DirectX::XMFLOAT3 cubePos;
	DirectX::XMFLOAT3 cubeScale;*/

	bool hit;
};

