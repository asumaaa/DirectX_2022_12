#pragma once
#include "CubeModel.h"
#include "CubeObject3D.h"
#include "DirectXCommon.h"
#include "DXInput.h"
#include "input.h"
#include "Collision.h"

class Player
{
public:
	//�V���O���g���C���X�^���X
	Player* GetInstance();
	Player();
	~Player();
	void Initialize(ID3D12Device* device, CubeModel* model, Input* input,DXInput* dxInput);
	void Update();
	void Move();
	void Draw(ID3D12GraphicsCommandList* cmdList);
	//�����蔻��
	void UpdateCollision(Collision* collision);

	//�Q�b�^�[�@�Z�b�^�[�@
	XMFLOAT3 GetPosition() { return position; };
	XMFLOAT3 GetRotation() { return rotation; };
	XMFLOAT3 GetScale() { return scale; };
	void SetPosition(XMFLOAT3 pos);
	void SetRotation(XMFLOAT3 rot);
	void SetScale(XMFLOAT3 sca);
private:
	ID3D12Device* device;
	CubeModel* model = nullptr;
	std::unique_ptr<CubeObject3D> object3d;
	DXInput* dxInput;
	Input* input;
	//�A�t�B���ϊ����
	XMFLOAT3 scale = { 1,1,1 };
	XMFLOAT3 rotation = { 0,0,0 };	//�v���C���[�{���̊p�x
	XMFLOAT3 position = { 0,0,0 };

	//�ړ��p�ϐ�
	XMFLOAT3 fallVelocity = { 0,0,0 };
	float fallTimer = 0.0f;

	bool groundFlag = false;
};

